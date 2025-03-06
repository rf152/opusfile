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
#pragma once
#include "OpusFileCommon.h"
#include <stdint.h>

#define OPUSHEAD_MAGIC 0x646165487375704F


#ifdef __cplusplus
extern "C" {
#endif
typedef struct __attribute((packed)) {
  uint64_t signature;
  uint8_t version;
  uint8_t channel_count;
  uint16_t pre_skip;
  uint32_t input_sample_rate;
  uint16_t output_gain;
  uint8_t mapping_family;
} OpusIdHeader_t;

enum OPUSFILE_RETURN opus_id_header_load(OpusIdHeader_t* header,
                                         const char* data);


#ifdef __cplusplus
}
#endif
