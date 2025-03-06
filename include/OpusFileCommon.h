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

#ifdef __cplusplus
extern "C" {
#endif

enum OPUSFILE_RETURN {
  OPUSFILE_OK = 0,
  OPUSFILE_ERR_UNKNOWN = -1,
  OPUSFILE_BAD_MAGIC = -3,
  OPUSFILE_NO_SEGMENTS = -4,
  OPUSFILE_DECODER_ERROR = -5,
  OPUSFILE_END_OF_PAGE = -6,
  OPUSFILE_END_OF_FILE = -7,
  OPUSFILE_INVALID_SEGMENT = -8,
};

#ifdef __cplusplus
}
#endif
