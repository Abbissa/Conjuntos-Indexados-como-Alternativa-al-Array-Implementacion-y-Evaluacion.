cmake_minimum_required(VERSION 3.0.0)
project(OrderedLists VERSION 0.1.0)

include(CTest)
enable_testing()

# Añadir -O3


add_compile_definitions(BSType=0 RecStruct)
add_compile_definitions(BSType=0 RecPtr)

add_compile_definitions(BSType=1 IterStruct)
add_compile_definitions(BSType=1 IterPtr)


# set_source_files_properties(./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp PROPERTIES LANGUAGE CXX)

add_executable(RecStruct ./InsercionEnListasC/insercion.c)
add_executable(IterStruct ./InsercionEnListasC/insercion.c)
add_executable(RecPtr ./InsercionEnListasC/insercionV2.c)
add_executable(IterPtr ./InsercionEnListasC/insercionV2.c)


# add_compile_definitions(GNType=0 GappedRandomTest)

# add_compile_definitions(GNType=1 GappedOrderedTest)
# add_compile_definitions(GNType=2 GappedInverseOrderTest)

# add_compile_definitions(GLType=0 GappedInverseOrderTest)
# add_compile_definitions(GLType=0 GappedOrderedTest)
# add_compile_definitions(GLType=0 GappedInverseOrderTest)

# add_compile_definitions(GNType=0 GappedV2RandomTest)
# add_compile_definitions(GNType=1 GappedV2OrderedTest)
# add_compile_definitions(GNType=2 GappedV2InverseOrderTest)

# add_compile_definitions(GLType=1 GappedV2InverseOrderTest)
# add_compile_definitions(GLType=1 GappedV2OrderedTest)
# add_compile_definitions(GLType=1 GappedV2InverseOrderTest)

# add_library(GL ./Prototipo/GappedList.hpp)
# add_library(GLV2 ./Prototipo/GappedListV2.hpp)

# target_include_directories(GL PUBLIC ${CMAKE_CURRENT_LIST_DIR})
# target_include_directories(GLV2 PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# add_executable(GappedRandomTest ./Prototipo/Test.cpp)
# add_executable(GappedOrderedTest ./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp)
# add_executable(GappedInverseOrderTest ./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp)

# add_executable(GappedV2RandomTest ./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp)
# add_executable(GappedV2OrderedTest ./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp)
# add_executable(GappedV2InverseOrderTest ./Prototipo/Test.cpp ./Prototipo/GappedList.hpp ./Prototipo/GappedListV2.hpp)



# target_link_libraries(GappedRandomTest GL)
# target_link_libraries(GappedOrderedTest GL)
# target_link_libraries(GappedInverseOrderTest GL)

# target_link_libraries(GappedV2RandomTest GLV2)
# target_link_libraries(GappedV2OrderedTest GLV2)
# target_link_libraries(GappedV2InverseOrderTest GLV2)


set(i 10000)
MATH(EXPR cntr 200000)
while(i LESS_EQUAL cntr)

    # add_test(NAME GappedRandomTest${i} COMMAND GappedRandomTest 0 ${i})
    # add_test(NAME GappedRandomTestWithNegativeNumers${i} COMMAND GappedRandomTest -${i} ${i})
    # add_test(NAME GappedOrderedTest${i} COMMAND GappedOrderedTest 0 ${i})
    # add_test(NAME GappedInverseOrderTest${i} COMMAND GappedInverseOrderTest 0 ${i})
    
    # add_test(NAME GappedV2RandomTest${i} COMMAND GappedV2RandomTest 0 ${i})
    # add_test(NAME GappedV2RandomTestWithNegativeNumers${i} COMMAND GappedV2RandomTest -${i} ${i})
    # add_test(NAME GappedV2OrderedTest${i} COMMAND GappedV2OrderedTest 0 ${i})
    # add_test(NAME GappedV2InverseOrderTest${i} COMMAND GappedV2InverseOrderTest 0 ${i})



    add_test(NAME RecStruct${i} COMMAND RecStruct ${i})
    add_test(NAME IterStruct${i} COMMAND IterStruct ${i})
    add_test(NAME RecPtr${i} COMMAND RecPtr ${i})
    add_test(NAME IterPtr${i} COMMAND IterPtr ${i})

    MATH(EXPR i ${i}*2)
endwhile()




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
