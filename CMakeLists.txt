cmake_minimum_required (VERSION 3.1)
set (NOR_EXE_NAME ch347-nor-prog)
set (TLE920X_EXE_NAME ch347-tle920x-cmd)
project (ch347-tools C CXX)
find_package(PkgConfig)
pkg_check_modules(libusb-1.0 REQUIRED libusb-1.0)

add_executable(${NOR_EXE_NAME} ch347.c spi-op.cpp nor-main.cpp misc.cpp spi_flash.cpp spi_ids.cpp stdafx.cpp)
set_property(TARGET ${NOR_EXE_NAME} PROPERTY C_STANDARD 99)
target_link_libraries(${NOR_EXE_NAME} ${libusb-1.0_LIBRARIES})

add_executable(${TLE920X_EXE_NAME} ch347.c spi-op.cpp main.cpp spi_tle920x.cpp)
set_property(TARGET ${TLE920X_EXE_NAME} PROPERTY C_STANDARD 99)
target_link_libraries(${TLE920X_EXE_NAME} ${libusb-1.0_LIBRARIES})
