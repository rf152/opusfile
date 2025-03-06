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
#include "OpusCommentHeader.h"
#include <stdio.h>
#include <string.h>

enum OPUSFILE_RETURN opus_comment_header_load(OpusCommentHeader_t* header,
                                              const char* data) {
  memcpy((void*) header, data, 19);
  if (header->signature != OPUSTAGS_MAGIC) {
    return OPUSFILE_BAD_MAGIC;
  }
  return OPUSFILE_OK;
}
