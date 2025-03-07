/*
 * Copyright 2025 R Franks
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <gtest/gtest.h>
#include <OpusCommentHeader.h>
#include <OpusFileCommon.h>
#include "data.h"

// Demonstrate some basic assertions.
TEST(OpusCommentHeader, BasicParsing) {
  OpusCommentHeader_t header;
  ASSERT_EQ(opus_comment_header_load(&header, test_data + 0x4B),
            OPUSFILE_OK);
}
TEST(OpusCommentHeader, BasicParsingError) {
  OpusCommentHeader_t header;
  char invalid_test_data[762];
  memcpy(invalid_test_data, test_data, 762);
  invalid_test_data[0x4D] = '\x76';
  ASSERT_EQ(opus_comment_header_load(&header, invalid_test_data + 0x4B),
            OPUSFILE_BAD_MAGIC);
}

TEST(OpusCommentHeader, ParsingHeader) {
  OpusCommentHeader_t header;
  opus_comment_header_load(&header, test_data + 0x4B);
  EXPECT_EQ(header.signature, 0x736761547375704F);
  EXPECT_EQ(header.vendor_string_length, 11);
}
