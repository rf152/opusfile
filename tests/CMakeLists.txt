include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

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
gtest_discover_tests(opus_page_test)

add_executable(
  opus_id_header_test
  opus_id_header_test.cc
)
target_link_libraries(
  opus_id_header_test
  GTest::gtest_main
)

target_link_libraries(opus_id_header_test opus_file)
gtest_discover_tests(opus_id_header_test)

add_executable(
  opus_comment_header
  opus_comment_header_test.cc
)
target_link_libraries(
  opus_comment_header
  GTest::gtest_main
)

target_link_libraries(opus_comment_header opus_file)
gtest_discover_tests(opus_comment_header)
