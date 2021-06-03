add_library(filter STATIC filter.cpp)
add_library(histogram STATIC histogram.cpp)
add_library(imageio STATIC imageIO.cpp)
add_library(transformation STATIC transformation.cpp)
add_library(binarization STATIC binarization.cpp)

set(TARGET_NAME filter histogram imageio transformation binarization)

MACRO(ALL_TARGET_INCLUDE_DIRECTORIES target_name)
    FOREACH(target ${target_name})
        target_include_directories(
                ${target}
                PUBLIC
                ${PROJECT_SOURCE_DIR}/lib
        )
    ENDFOREACH()
ENDMACRO()

ALL_TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME})
