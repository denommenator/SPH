set(EXPORT_DATA_PATH "${PROJECT_SOURCE_DIR}/exportdata")

configure_file (
    "${PROJECT_SOURCE_DIR}/include/SPH/serializers_io_defs.hpp.in"
    "${PROJECT_BINARY_DIR}/include/SPH/serializers_io_defs.hpp"
    )