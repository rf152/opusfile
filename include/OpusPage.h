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
#include <stdint.h>
#include "OpusFileCommon.h"

#define OGGS_MAGIC 0x5367674F  // "OggS"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute((packed)) {
  uint32_t signature;
  uint8_t version;
  uint8_t flags;
  uint64_t granule_position;
  uint32_t serial_number;
  uint32_t sequence_number;
  uint32_t checksum;
  uint8_t segment_table_length;
  uint8_t segment_table[255];
  uint8_t data_location;
  uint16_t length;
  uint16_t offset;
  uint8_t next_segment;
  const char* data;
} OpusPage_t;

enum OPUSFILE_RETURN opus_page_load(OpusPage_t *page,
                                    const char* source,
                                    uint64_t offset);
enum OPUSFILE_RETURN opus_page_load_segment_table(OpusPage_t* page,
                                                  const char* source);
int16_t opus_page_get_segment(OpusPage_t *page,
                              uint8_t segment,
                              char* buffer);

int16_t opus_page_get_next_segment(OpusPage_t *page,
                                   char* buffer);

#ifdef __cplusplus
}
#endif
