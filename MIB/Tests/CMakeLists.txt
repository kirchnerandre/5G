
enable_testing()

add_executable(
    Test_001
    Test_001_FourierTransform.cpp)
add_test(
    NAME    Test_001
    COMMAND ./Test_001.exe)
target_include_directories(
    Test_001
    PUBLIC ../Headers)
target_link_libraries(
    Test_001
    PRIVATE ${PROJECT_NAME})
