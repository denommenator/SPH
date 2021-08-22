cmake_minimum_required(VERSION 3.20)

#project name
project(SPH)

#for using the LSP linter. 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(src)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)


FetchContent_Declare(
  indicators
  GIT_REPOSITORY https://github.com/p-ranav/indicators.git
  )
FetchContent_MakeAvailable(indicators)


include(CTest)
add_subdirectory(test)
add_subdirectory(include/SPH)
add_subdirectory(apps)