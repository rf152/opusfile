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

#include "OpusIdHeader.h"
#include "OpusCommentHeader.h"
#include "OpusPage.h"
#include "OpusFileCommon.h"
#include <stdint.h>
#include <stdlib.h>
#include <opus.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute((packed)) {
  const char* data;
  size_t current_page;
  size_t data_length;
  size_t page_count;
  OpusCommentHeader_t comment_header;
  OpusIdHeader_t id_header;
  uint8_t repeat;
  OpusDecoder *decoder;
  OpusPage_t *pages[255];
} OpusFile_t;

enum OPUSFILE_RETURN opus_file_load(OpusFile_t* opus_file,
                                    const char* data,
                                    size_t data_length);

uint32_t opus_file_get_pcm(OpusFile_t* opus_file,
                           int16_t length,
                           int16_t* pcm,
                           int16_t frame_size,
                           enum OPUSFILE_RETURN *error);


#ifdef __cplusplus
}
#endif
