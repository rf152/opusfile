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
#include "OpusFile.h"
#include "OpusPage.h"
#include <stdio.h>

enum OPUSFILE_RETURN opus_file_load(OpusFile_t* opus_file,
                                    const char* data,
                                    size_t data_length) {
  opus_file->current_page = 2;
  opus_file->data_length = data_length;
  opus_file->data = data;

  enum OPUSFILE_RETURN return_value;

  // Load in the ID header
  OpusPage_t firstpage;
  OpusIdHeader_t id_header;
  return_value = opus_page_load(&firstpage, data, 0);
  if (return_value) return return_value;

  return_value = opus_id_header_load(&id_header,
                                     data + firstpage.data_location);
  if (return_value) return return_value;

  // Load in the comment header
  OpusPage_t secondpage;
  return_value = opus_page_load(&secondpage, data, firstpage.length);
  if (return_value) return return_value;

  OpusCommentHeader_t comment_header;
  return_value = opus_comment_header_load(&comment_header,
                                          data + secondpage.offset
                                            + secondpage.data_location);
  if (return_value) return return_value;

  // Create the decoder
  int decoderError = 0;
  opus_file->decoder = opus_decoder_create(id_header.input_sample_rate,
                                           id_header.channel_count,
                                           &decoderError);
  if (decoderError != OPUS_OK) {
    return OPUSFILE_DECODER_ERROR;
  }

  // Get the pointer in the right place - we don't want to re-read the first and
  // second pages as they don't contain any audio data.
  size_t runthrough_pointer = secondpage.offset + secondpage.length;
  int8_t index = -1;

  // Load the data pages into the pages array.
  while (runthrough_pointer < data_length) {
    index++;
    opus_file->pages[index] = malloc(sizeof(OpusPage_t));
    return_value = opus_page_load(opus_file->pages[index],
                                  data,
                                  runthrough_pointer);
    if (return_value) return return_value;
    runthrough_pointer += opus_file->pages[index]->length;
  }

  // Store the complete number of pages (including the first two pages)
  opus_file->page_count = index + 3;

  // All ok!
  return OPUSFILE_OK;
}

uint32_t opus_file_get_pcm(OpusFile_t* opus_file,
                           int16_t length,
                           int16_t* pcm,
                           int16_t frame_size,
                           enum OPUSFILE_RETURN *error) {
  // First, we need to get the next segment
  uint8_t opus_buffer[255];
  int16_t getsegret = 0;

  getsegret = opus_page_get_next_segment(
                            opus_file->pages[opus_file->current_page],
                            opus_buffer);
  if (getsegret == OPUSFILE_END_OF_PAGE) {
    // Rewind the page
    opus_file->pages[opus_file->current_page]->next_segment = 0;
    opus_file->current_page++;
    // Check we are not at the end of the file
    if (opus_file->current_page == opus_file->page_count) {
      // We are at the end of the file.
      // Should we repeat?
      if (opus_file->repeat) {
        // Ok, so rewind back to the beginning, so we can get the first segment
        // of the first page.
        opus_file->current_page = 2;
      } else {
        // We're at the end of this page. We should set the error return,
        // and then drop out. We're not going to make any nice PCM data
        // this time!
        *error = OPUSFILE_END_OF_FILE;
        return 0;
      }
    }
    // Ok, so we should now get the next segment of whatever the next page is.
    getsegret = opus_page_get_next_segment(
                        opus_file->pages[opus_file->current_page],
                        opus_buffer);
  }

  // We now have some opus data in our opus_buffer.
  // Lets decode it
  return opus_decode(opus_file->decoder,
                     opus_buffer,
                     getsegret,
                     pcm,
                     frame_size,
                     0);
}
