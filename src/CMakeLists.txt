# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/SPH/*.hpp")
set(HEADER_LIST "${SPH_SOURCE_DIR}/include/SPH/coordinates.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(SPH_library coordinates.cpp ${HEADER_LIST})

target_link_libraries (SPH_library Eigen3::Eigen)

# We need this directory, and users of our library will need it too
target_include_directories(SPH_library PUBLIC ../include)


# All users of this library will need at least C++11
target_compile_features(SPH_library PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

  