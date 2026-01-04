
add_library(
    ${PROJECT_NAME}
    FourierTransform.cpp
    Graphics.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ../Headers)
