set(VM_SOURCES
    installer.cpp
    javaclass.cpp
    javalang.cpp
    jni.cpp
    library.cpp
    openjcvm.cpp
    readijc.cpp
    vm.cpp
)

set(TEST_READUX_SOURCES
    testreadux.cpp
    installer.cpp
)

set(TEST_READIJC_SOURCES
    testreadijc.cpp
    installer.cpp
    readijc.cpp
)

add_executable(openjcvm ${VM_SOURCES})
add_executable(test_readux ${TEST_READUX_SOURCES})
add_executable(test_readijc ${TEST_READIJC_SOURCES})

add_test(ReadUx ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_readux)
