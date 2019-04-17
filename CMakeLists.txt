cmake_minimum_required(VERSION 3.14)
project(keep_talking_and_nobody_explodes_hacker)

set(CMAKE_CXX_STANDARD          17  CACHE STRING "CXX standard version")
set(CMAKE_CXX_STANDARD_REQUIRED ON  CACHE BOOL   "version required")
set(CMAKE_CXX_EXTENSIONS        OFF CACHE BOOL   "compiler extension")

set(Clang_WARN_OPTIONS
  -Weverything
  -Wno-c++98-compat
)
set(GNU_WARN_OPTIONS
  -Wall
  -Walloc-zero
  -Walloca
  -Wcast-qual
  -Wchkp
  -Wconditionally-supported
  -Wconversion
  -Wdate-time
  -Wdisabled-optimization
  -Wdouble-promotion
  -Wduplicated-branches
  -Wduplicated-cond
  -Wextra
  -Whsa
  -Wimplicit-fallthrough
  -Winvalid-pch
  -Wlogical-op
  -Wmissing-declarations
  -Wmissing-include-dirs
  -Wnormalized
  -Wnull-dereference
  -Wopenmp-simd
  -Wpacked
  -Wpedantic
  -Wredundant-decls
  -Wrestrict
  -Wsized-deallocation
  -Wstack-protector
  -Wstrict-overflow
  -Wsuggest-attribute=noreturn
  -Wsuggest-final-methods
  -Wsuggest-final-types
  -Wswitch-enum
  -Wsync-nand
  -Wtrampolines -Wfloat-equal -Wshadow
  -Wuninitialized
  -Wunsafe-loop-optimizations
  -Wunused-parameter
  -Wuseless-cast
  -Wvla
  -Wzero-as-null-pointer-constant
)

add_compile_options(
  "$<$<CXX_COMPILER_ID:Clang>:${Clang_WARN_OPTIONS}>"
  "$<$<CXX_COMPILER_ID:GNU>:${GNU_WARN_OPTIONS}>"
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

include_directories(include)

add_library(modules src/module/wire src/module/button src/module/keypads src/module/simon src/module/whos_on_first src/module/memory src/module/morse_code)
add_executable(executable src/main.cpp src/ktanehack.cpp src/bomb_information.cpp)
target_link_libraries(executable modules)

add_custom_target(run
  COMMAND executable < ${CMAKE_SOURCE_DIR}/input
  DEPENDS executable
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
