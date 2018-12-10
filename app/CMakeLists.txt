cmake_minimum_required(VERSION 3.4.1)

add_library( # Specifies the name of the library.
             addHello

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/addHello.cpp )


add_library( # Specifies the name of the library.
             hookSo

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/inlineHook/relocate.c
             src/main/jni/inlineHook/inlineHook.c
             src/main/jni/inlineHook/main.cpp)


include_directories(src/main/jni/include/)


find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # CMake needs to locate.
              log )

target_link_libraries( # Specifies the target library.
                       addHello

                       # Links the log library to the target library.
                       ${log-lib} )

target_link_libraries( # Specifies the target library.
                       hookSo

                       # Links the log library to the target library.
                       ${log-lib} )