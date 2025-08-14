add_library(ncnn_mpy INTERFACE)

# Add the binding file to the library.
target_sources(ncnn_mpy INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/ncnn_mp.c
)

#[[
Add link flags here due to linking error:
/home/willaaaaaaa/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20241119/xtensa-esp-elf/bin/../lib/gcc/xtensa-esp-elf/14.2.0/../../../../xtensa-esp-elf/bin/ld: /home/willaaaaaaa/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20241119/xtensa-esp-elf/bin/../lib/gcc/xtensa-esp-elf/14.2.0/../../../../xtensa-esp-elf/lib/esp32/no-rtti/libm_nano.a(libm_a-fegetround.o): in function `fesetround':
/builds/idf/crosstool-NG/.build/xtensa-esp-elf/src/newlib/newlib/libm/machine/xtensa/fegetround.c:43: multiple definition of `fesetround'; /home/willaaaaaaa/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20241119/xtensa-esp-elf/bin/../lib/gcc/xtensa-esp-elf/14.2.0/../../../../xtensa-esp-elf/lib/esp32/no-rtti/libm_nano.a(libm_a-fesetround.o):/builds/idf/crosstool-NG/.build/xtensa-esp-elf/src/newlib/newlib/libm/fenv/fesetround.c:65: first defined here
]]
target_link_options(ncnn_mpy INTERFACE 
    "$<$<COMPILE_LANGUAGE:C>:-Wl,--allow-multiple-definition>"
    "$<$<COMPILE_LANGUAGE:CXX>:-Wl,--allow-multiple-definition>"
)

find_package(ncnn CONFIG)

if(ncnn_FOUND)
    message(STATUS "Found ncnn via find_package. Using its include directories and link libraries.")
    target_include_directories(ncnn_mpy INTERFACE
        ${ncnn_INCLUDE_DIRS}
    )
    target_link_libraries(ncnn_mpy INTERFACE
        ${ncnn_LIBRARIES}
    )
else()
    message(STATUS "ncnn not found via find_package. Using manual path setup.")
    if(NOT DEFINED NCNN_INSTALL_PREFIX)
        set(NCNN_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../../ncnn/build/install" CACHE PATH "Path to the ncnn installation directory.")
    endif()

    target_include_directories(ncnn_mpy INTERFACE
        "${NCNN_INSTALL_PREFIX}/include"
    )
    # Link the pre-built ncnn static library.
    target_link_libraries(ncnn_mpy INTERFACE
        "${NCNN_INSTALL_PREFIX}/lib/libncnn.a"
    )
endif()

# Link our user module to the main 'usermod' target.
target_link_libraries(usermod INTERFACE ncnn_mpy)
