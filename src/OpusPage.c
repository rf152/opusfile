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
#include "OpusPage.h"
#include <string.h>
#include <stdio.h>

enum OPUSFILE_RETURN opus_page_load(OpusPage_t *page,
                                    const char* source, uint64_t offset) {
  enum OPUSFILE_RETURN return_value;
  memcpy((char *)page, source + offset, 27);
  if (page->signature != OGGS_MAGIC) {
    return OPUSFILE_BAD_MAGIC;
  }
  page->data = source + offset;
  return_value = opus_page_load_segment_table(page, source + offset);
  if (return_value) return return_value;
  return OPUSFILE_OK;
}

enum OPUSFILE_RETURN opus_page_load_segment_table(OpusPage_t* page,
                                                  const char* source) {
  uint16_t datalength = 0;
  for (int i=0; i < page->segment_table_length; i++) {
    uint8_t segment_length = 0;
    memcpy((uint8_t *)&segment_length, source + 27 + i, 1);
    page->segment_table[i] = segment_length;
    datalength += segment_length;
  }
  page->data_location = 27 + page->segment_table_length;
  page->length = 27 + page->segment_table_length + datalength;
  page->next_segment = 0;
  return OPUSFILE_OK;
}

int16_t opus_page_get_segment(OpusPage_t *page,
                              uint8_t segment,
                              char* buffer) {
  // Check that the segment exists in this page
  if (segment >= page->segment_table_length) {
    return OPUSFILE_INVALID_SEGMENT;
  }
  uint16_t segment_offset = 0;  // Start at the beginning
  segment_offset += page->data_location;  // Add the offset for the header

  for (int i = 0; i < segment; i++) {
    segment_offset += page->segment_table[i];
  }
  memcpy(buffer, page->data + segment_offset, page->segment_table[segment]);
  return page->segment_table[segment];
}

int16_t opus_page_get_next_segment(OpusPage_t *page,
                                   char* buffer) {
  // Check we are not at the end
  if (page->next_segment == page->segment_table_length) {
    return OPUSFILE_END_OF_PAGE;
  }
  return opus_page_get_segment(page, page->next_segment++, buffer);
}
