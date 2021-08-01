add_executable(test_wave_01 test_wave_01.cpp)

target_compile_features(test_wave_01 PRIVATE cxx_std_11)

target_link_libraries(test_wave_01 PRIVATE SPH_library indicators::indicators)


