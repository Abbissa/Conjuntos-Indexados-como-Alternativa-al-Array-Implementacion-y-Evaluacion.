cmake_minimum_required(VERSION 3.0.0)
project(OrderedLists VERSION 0.1.0)

include(CTest)
enable_testing()

# Anadir -O3

add_compile_options(-O3)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
message(STATUS "CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION is ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "FLAGS is ${CMAKE_CXX_FLAGS}")




add_executable(StructArrayRec ./InsercionEnListasC/StructArray.c)
target_compile_definitions(StructArrayRec PUBLIC BSType=0 )

add_executable(StructArrayIter ./InsercionEnListasC/StructArray.c)
target_compile_definitions(StructArrayIter PUBLIC BSType=1 )

add_executable(PtrArrayRec ./InsercionEnListasC/PtrArray.c)
target_compile_definitions(PtrArrayRec PUBLIC BSType=0 )

add_executable(PtrArrayIter ./InsercionEnListasC/PtrArray.c)
target_compile_definitions(PtrArrayIter PUBLIC BSType=1 )


# Definiciones de compilacion
add_executable(GenRandom ./genNumbers/genNumbers.cpp)
add_executable(GenOrdered ./genNumbers/genNumbers.cpp)
add_executable(GenInverse ./genNumbers/genNumbers.cpp)

target_compile_definitions(GenRandom PUBLIC GNType=0)
target_compile_definitions(GenOrdered PUBLIC GNType=1)
target_compile_definitions(GenInverse PUBLIC GNType=2)


function(addHollowListExecutable type)
    add_executable(HollowList${type} ./Prototipo/Test.cpp ./Prototipo/HollowList.hpp ./Prototipo/ptrHollowList.hpp  ./InsercionEnListas/puntuacionLarge.hpp InsercionEnListas/puntuacionMedium.hpp InsercionEnListas/puntuacionSmall.hpp)
    target_compile_definitions(HollowList${type} PUBLIC HLType=0)
    target_compile_definitions(HollowList${type} PUBLIC testType=${type})
endfunction(addHollowListExecutable type)

function(addptrHollowListExecutable type)
    add_executable(ptrHollowList${type} ./Prototipo/Test.cpp ./Prototipo/HollowList.hpp ./Prototipo/ptrHollowList.hpp ./InsercionEnListas/puntuacionLarge.hpp ./InsercionEnListas/puntuacionMedium.hpp InsercionEnListas/puntuacionSmall.hpp)
    target_compile_definitions(ptrHollowList${type} PUBLIC HLType=1)
    target_compile_definitions(ptrHollowList${type} PUBLIC testType=${type})
    
endfunction(addptrHollowListExecutable type)

function(addTestVectorExecutable type)
    add_executable(TestVector${type} ./Prototipo/TestVector.cpp ./InsercionEnListas/puntuacionLarge.hpp ./InsercionEnListas/puntuacionMedium.hpp InsercionEnListas/puntuacionSmall.hpp)
    target_compile_definitions(TestVector${type} PUBLIC testType=${type})
    
endfunction()

function(addTestSetExecutable type)
    add_executable(TestSet${type} ./Prototipo/TestSet.cpp ./InsercionEnListas/puntuacionLarge.hpp ./InsercionEnListas/puntuacionMedium.hpp InsercionEnListas/puntuacionSmall.hpp)
    target_compile_definitions(TestSet${type} PUBLIC testType=${type})
endfunction(addTestSetExecutable type)

function(addBinaryHeapExecutable type)
    add_executable(TestBinaryHeap${type} ./Prototipo/TestBinaryHeap.cpp
     ./InsercionEnListas/puntuacionLarge.hpp
      ./InsercionEnListas/puntuacionMedium.hpp 
      InsercionEnListas/puntuacionSmall.hpp)
    target_compile_definitions(TestBinaryHeap${type} PUBLIC testType=${type})
endfunction(addBinaryHeapExecutable type)

# Distintos tipos de listas ordenadas a probar
set(types
    0
    1
    2)

foreach(type ${types})
    addHollowListExecutable(${type})
    addptrHollowListExecutable(${type})
    addTestVectorExecutable(${type})
    addTestSetExecutable(${type})
    addBinaryHeapExecutable(${type})
endforeach()

# Generadores de numeros
set(gens
    GenRandom
    GenOrdered
    GenInverse
)


file(WRITE ${CMAKE_SOURCE_DIR}/genGraphs/CSV/base/base.csv PROGRAM,NUMBERS,SIZE,TIME\n)

foreach(gen ${gens})
    set(output ${CMAKE_SOURCE_DIR}/genGraphs/CSV/${gen}.csv)
            add_custom_command( 
                TARGET ${gen} POST_BUILD
            COMMAND echo "PROGRAM,TEST,TYPE,SIZE,TIME" > ${output})
endforeach()

add_custom_command(TARGET GenRandom POST_BUILD
    COMMAND echo "PROGRAM,TEST,TYPE,SIZE,MEM,SYS_TIME,ELAPSED_TIME,PAGE_FAULTS" > ${CMAKE_SOURCE_DIR}/genGraphs/CSV/sys.csv)

function(defineCaseHollowList program gen i type)
    MATH(EXPR j 2*${i}+2000000)
    set(size 128)
    MATH(EXPR cntr 512)
    while(size LESS_EQUAL cntr)
        add_custom_command( 
            TARGET ${program}${type} POST_BUILD
            COMMAND ${gen} ${j} >tmp
            COMMAND /usr/bin/time -o ${CMAKE_SOURCE_DIR}/genGraphs/CSV/sys.csv
                -a
                -f "${program}-${size},${gen},${type},${i},%M,%S,%e,%R" 
                ${CMAKE_BINARY_DIR}/${program}${type} ${i} ${size}  < tmp >> ${output}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        MATH(EXPR size 2*${size})
    endwhile()
endfunction(defineCaseHollowList program gen i)

function(defineCase program gen i type)
    MATH(EXPR j 2*${i}+2000000)
    add_custom_command( 
        TARGET ${program}${type} POST_BUILD
        COMMAND ${gen} ${j} >tmp
        COMMAND /usr/bin/time -o ${CMAKE_SOURCE_DIR}/genGraphs/CSV/sys.csv
        -a 
        -f "${program},${gen},${type},${i},%M,%S,%e,%R"
        ${CMAKE_BINARY_DIR}/${program}${type} ${i}  < tmp >> ${output}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction(defineCase program gen i)

set(i 500000)
MATH(EXPR cntr 4000000)
set(repeat 2)
while(i LESS_EQUAL cntr)
    foreach(gen ${gens})
        foreach(type ${types})
            set(output ${CMAKE_SOURCE_DIR}/genGraphs/CSV/${gen}.csv)
            defineCase(TestSet ${gen} ${i} ${type})
            foreach(rep RANGE ${repeat})
                defineCaseHollowList(ptrHollowList ${gen} ${i} ${type})
                defineCaseHollowList(HollowList ${gen} ${i} ${type})
                defineCase(TestBinaryHeap ${gen} ${i} ${type})
            endforeach()
        endforeach()
    endforeach()
    MATH(EXPR i ${i}+500000)
endwhile()


file(GLOB FILES_TO_CAT ${CMAKE_SOURCE_DIR}/genGraphs/CSV/*.csv )

list(SORT FILES_TO_CAT)

add_custom_command(
    OUTPUT res.csv
    COMMAND cat ${CMAKE_SOURCE_DIR}/genGraphs/CSV/base/base.csv > ${CMAKE_SOURCE_DIR}/genGraphs/res.csv
    COMMAND cat ${FILES_TO_CAT} >> ${CMAKE_SOURCE_DIR}/genGraphs/res.csv
    DEPENDS ${FILES_TO_CAT}
)

add_custom_target(concatenate_files DEPENDS res.csv)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
