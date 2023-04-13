cmake_minimum_required(VERSION 3.0.0)
project(OrderedLists VERSION 0.1.0)

include(CTest)
enable_testing()

# Añadir -O3

add_compile_options(-O3)

# Definiciones de compilacion
add_executable(GenRandom ./genNumbers/genNumbers.cpp)
add_executable(GenOrdered ./genNumbers/genNumbers.cpp)
add_executable(GenInverse ./genNumbers/genNumbers.cpp)

target_compile_definitions(GenRandom PUBLIC GNType=0)
target_compile_definitions(GenOrdered PUBLIC GNType=1)
target_compile_definitions(GenInverse PUBLIC GNType=2)


add_executable(StructArrayRec ./InsercionEnListasC/StructArray.c)
target_compile_definitions(StructArrayRec PUBLIC BSType=0 )

add_executable(StructArrayIter ./InsercionEnListasC/StructArray.c)
target_compile_definitions(StructArrayIter PUBLIC BSType=1 )

add_executable(PtrArrayRec ./InsercionEnListasC/PtrArray.c)
target_compile_definitions(PtrArrayRec PUBLIC BSType=0 )

add_executable(PtrArrayIter ./InsercionEnListasC/PtrArray.c)
target_compile_definitions(PtrArrayIter PUBLIC BSType=1 )

add_executable(HollowList ./Prototipo/Test.cpp ./Prototipo/HollowList.hpp ./Prototipo/ptrHollowList.hpp)
target_compile_definitions(HollowList PUBLIC GLType=0)

add_executable(ptrHollowList ./Prototipo/Test.cpp ./Prototipo/HollowList.hpp ./Prototipo/ptrHollowList.hpp)
target_compile_definitions(ptrHollowList PUBLIC GLType=1)

add_executable(TestVector ./Prototipo/TestVector.cpp)
add_executable(TestSet ./Prototipo/TestSet.cpp)

# Distintos tipos de listas ordenadas a probar
set(programs
    StructArrayRec
    StructArrayIter
    PtrArrayRec
    PtrArrayIter
    HollowList
    ptrHollowList
    TestVector
    TestSet
    
)
# Generadores de numeros
set(gens
    GenRandom
    GenOrdered
    GenInverse
)
# Listas más rapidas para probar con casos más grandes
set(fPrograms
    ptrHollowList
    TestSet
)

file(WRITE ${CMAKE_SOURCE_DIR}/genGraphs/CSV/base/base.csv PROGRAM,NUMBERS,SIZE,TIME\n)

function(defineCase program gen i)
MATH(EXPR j ${i}+1000000)
message("Defining case ${program} ${gen} ${i} ${j}")
    add_custom_command( 
        TARGET ${program} POST_BUILD
        COMMAND ${gen} ${j} >tmp
        COMMAND ${program} ${i}  < tmp >> ${output}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction(defineCase program gen i)
    
    
set(i 100000)
MATH(EXPR cntr 500000)
while(i LESS_EQUAL cntr)
    foreach(program ${programs})
        foreach(gen ${gens})
            set(output ${CMAKE_SOURCE_DIR}/genGraphs/CSV/${gen}.csv)
            add_custom_command( 
                TARGET ${gen} POST_BUILD
                COMMAND echo "PROGRAM,TYPE,TEST,SIZE,TIME" > ${output})
            defineCase(${program} ${gen} ${i})
        endforeach()
    endforeach()
    MATH(EXPR i ${i}+100000)
endwhile()


# Añadir mas casos para las listas más rapidas
set(i 600000)
MATH(EXPR cntr 3000000)
while(i LESS_EQUAL cntr)
    foreach(program ${fPrograms})
        foreach(gen ${gens})
            set(output ${CMAKE_SOURCE_DIR}/genGraphs/CSV/${gen}.csv)

            defineCase(${program} ${gen} ${i})
        endforeach()
    endforeach()
    MATH(EXPR i ${i}+200000)
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
