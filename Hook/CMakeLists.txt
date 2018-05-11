cmake_minimum_required(VERSION 3.9)
project(Hook)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_FLAGS "-msse -msse2 -msse3 -mmmx -masm=intel")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${CMAKE_FLAGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CMAKE_FLAGS})
set(HOOK_HOST_LIBRARY "libz.a ")
set(CMAKE_LINKER_FLAGS "-fvisibility=default -Wl,--enable-stdcall-fixup -Wl,--export-all-symbols -Wl,--whole-archive ${HOOK_HOST_LIBRARY} -Wl,--no-whole-archive")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_LINKER_FLAGS}")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${CMAKE_LINKER_FLAGS}")
link_libraries(opengl32 jsoncpp)
add_library(Hook SHARED 
    dllmain.cpp 
    Hook.h
    Hook.cpp
    )
#target_link_libraries(Hook libz.a)
#add_executable