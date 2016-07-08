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
    installer.cpp)

add_executable(openjcvm ${VM_SOURCES})
add_executable(test_readux ${TEST_READUX_SOURCES})
