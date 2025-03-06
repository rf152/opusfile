include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

link_directories(../src/)

add_executable(
  opus_page_test
  opus_page_test.cc
)
target_link_libraries(
  opus_page_test
  GTest::gtest_main
)

target_link_libraries(opus_page_test opus_file)

include(GoogleTest)
gtest_discover_tests(opus_page_test)
