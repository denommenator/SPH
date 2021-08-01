# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.


file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${SPH_SOURCE_DIR}/include/SPH/*.hpp")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${SPH_SOURCE_DIR}/src/*.cpp")



# Make an automatic library - will be static or dynamic based on user setting
add_library(SPH_library ${SOURCE_LIST} ${HEADER_LIST})

target_link_libraries (SPH_library PUBLIC Eigen3::Eigen)

target_link_libraries (SPH_library PRIVATE indicators::indicators)

# We need this directory, and users of our library will need it too
target_include_directories(SPH_library PUBLIC ${SPH_SOURCE_DIR}/include)


# All users of this library will need at least C++11
target_compile_features(SPH_library PUBLIC cxx_std_14)



# IDEs should put the headers in a nice place
source_group(
  TREE "${SPH_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

  