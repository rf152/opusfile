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
#include <OpusIdHeader.h>
#include <OpusFileCommon.h>
#include "data.h"

// Demonstrate some basic assertions.
TEST(OpusIdHeader, BasicParsing) {
  OpusIdHeader_t header;
  ASSERT_EQ(opus_id_header_load(&header, test_data + 0x1C), OPUSFILE_OK);
}
TEST(OpusIdHeader, BasicParsingError) {
  OpusIdHeader_t header;
  char invalid_test_data[762];
  memcpy(invalid_test_data, test_data, 762);
  invalid_test_data[0x22] = '\x76';
  ASSERT_EQ(opus_id_header_load(&header, invalid_test_data + 0x1C),
            OPUSFILE_BAD_MAGIC);
}

TEST(OpusIdHeader, ParsingHeader) {
  OpusIdHeader_t header;
  opus_id_header_load(&header, test_data + 0x1C);
  EXPECT_EQ(header.signature, 0x646165487375704F);
  EXPECT_EQ(header.version, 1);
  EXPECT_EQ(header.channel_count, 1);
  EXPECT_EQ(header.pre_skip, 312);
  EXPECT_EQ(header.input_sample_rate, 48000);
  EXPECT_EQ(header.output_gain, 0);
  EXPECT_EQ(header.mapping_family, 0);
}
