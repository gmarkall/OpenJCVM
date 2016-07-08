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

add_executable(openjcvm ${VM_SOURCES})
