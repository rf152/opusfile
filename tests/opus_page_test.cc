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
#include <OpusPage.h>
#include <OpusFileCommon.h>
#include "data.h"

// Demonstrate some basic assertions.
TEST(OpusPage, BasicParsing) {
  OpusPage_t page;
  enum OPUSFILE_RETURN retval;
  retval = opus_page_load(&page, validtestdata, 0);
  ASSERT_EQ(retval, OPUSFILE_OK);
}
TEST(OpusPage, BasicParsingErrorMagic) {
  OpusPage_t page;
  EXPECT_EQ(opus_page_load(&page, invalidtestdata, 0), OPUSFILE_BAD_MAGIC);
}

TEST(OpusPage, ParsingMagicHeader) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  EXPECT_EQ(page.signature, 0x5367674F);
}

TEST(OpusPage, ParsingSegmentCountFirst) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  EXPECT_EQ(page.segment_table_length, 1);
}

TEST(OpusPage, ParsingSegmentCountThird) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0x7F);
  EXPECT_EQ(page.segment_table_length, 4);
}

TEST(OpusPage, GetSegment) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  char buffer[19];
  char data[19] = {
    '\x4F', '\x70', '\x75', '\x73', '\x48', '\x65', '\x61', '\x64',
    '\x01', '\x01', '\x38', '\x01', '\x80', '\xBB', '\x00', '\x00',
    '\x00', '\x00', '\x00',
  };
  opus_page_get_segment(&page, 0, buffer);
  EXPECT_STREQ(buffer, data);
}

TEST(OpusPage, GetInvalidSegment) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  char buffer[19];
  EXPECT_EQ(opus_page_get_segment(&page, 1, buffer), OPUSFILE_INVALID_SEGMENT);
}

TEST(OpusPage, GetNextSegment) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  char buffer[19];
  char data[19] = {
    '\x4F', '\x70', '\x75', '\x73', '\x48', '\x65', '\x61', '\x64',
    '\x01', '\x01', '\x38', '\x01', '\x80', '\xBB', '\x00', '\x00',
    '\x00', '\x00', '\x00',
  };
  opus_page_get_next_segment(&page, buffer);
  EXPECT_STREQ(buffer, data);
}

TEST(OpusPage, GetNextSegmentEndOfPage) {
  OpusPage_t page;
  opus_page_load(&page, validtestdata, 0);
  char buffer[19];
  opus_page_get_next_segment(&page, buffer);
  EXPECT_EQ(opus_page_get_next_segment(&page, buffer), OPUSFILE_END_OF_PAGE);
}
