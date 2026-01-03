
add_library(
    ${PROJECT_NAME}
    FourierTransform.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ../Headers)
