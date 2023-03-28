cmake_minimum_required(VERSION 3.0.0)
project(OrderedLists VERSION 0.1.0)

include(CTest)
enable_testing()


add_compile_definitions(BSType=0 RecStruct)
add_compile_definitions(BSType=0 RecPtr)

add_compile_definitions(BSType=1 IterStruct)
add_compile_definitions(BSType=1 IterPtr)

add_executable(RecStruct insercion.c)
add_executable(IterStruct insercion.c)
add_executable(RecPtr insercionV2.c)
add_executable(IterPtr insercionV2.c)

  

set(i 10000)
MATH(EXPR cntr 200000)
while(i LESS_EQUAL cntr)

    add_test(NAME RecStruct${i} COMMAND RecStruct ${i})
    add_test(NAME IterStruct${i} COMMAND IterStruct ${i})
    add_test(NAME RecPtr${i} COMMAND RecPtr ${i})
    add_test(NAME IterPtr${i} COMMAND IterPtr ${i})

    MATH(EXPR i ${i}*2)
endwhile()




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
