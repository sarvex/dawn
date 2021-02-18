// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/utils/tmpfile.h"

#include <stdio.h>
#include <cstdio>

namespace tint {
namespace utils {

namespace {

std::string TmpFilePath() {
  char name[L_tmpnam];
  if (tmpnam_s(name, L_tmpnam - 1) == 0) {
    return name;
  }
  return "";
}

}  // namespace

TmpFile::TmpFile() : path_(TmpFilePath()) {}

TmpFile::~TmpFile() {
  if (!path_.empty()) {
    remove(path_.c_str());
  }
}

bool TmpFile::Append(const void* data, size_t size) const {
  FILE* file = nullptr;
  if (fopen_s(&file, path_.c_str(), "ab") != 0) {
    return false;
  }
  fwrite(data, size, 1, file);
  fclose(file);
  return true;
}

}  // namespace utils
}  // namespace tint
