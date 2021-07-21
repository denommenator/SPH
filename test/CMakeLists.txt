# Testing library
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2

file(GLOB TEST_SOURCE_LIST CONFIGURE_DEPENDS "${SPH_SOURCE_DIR}/test/*.test.cpp")


# Tests need to be added as executables first
add_executable(test_main 
					test_main.cpp 
					${TEST_SOURCE_LIST}
					)

# I'm using C++17 in the test
target_compile_features(test_main PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(test_main PRIVATE SPH_library Catch2::Catch2 Eigen3::Eigen)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME test_main 
		COMMAND test_main --success) 

