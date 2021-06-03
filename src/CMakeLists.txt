add_library(
        sources
        STATIC
        filter.cpp
        histogram.cpp
        imageIO.cpp
        transformation.cpp
)

target_include_directories(
        sources
        PUBLIC
        ${PROJECT_SOURCE_DIR}/lib
)