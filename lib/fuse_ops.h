// Copyright 2021 The Fuse-Archive Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIB_FUSE_OPS_H
#define LIB_FUSE_OPS_H

#include <fuse.h>

// fuse_operations.statx was only added in libfuse 3.18; older 3.x releases
// (e.g. the 3.14 shipped by Ubuntu 24.04) don't declare that struct member at
// all. FUSE_USE_VERSION only requests an API compatibility level, not the
// actual installed library version; FUSE_MAJOR_VERSION/FUSE_MINOR_VERSION
// (from libfuse's own libfuse_config.h, pulled in via <fuse.h> above) report
// the real one.
#if defined(__linux__) &&      \
    (FUSE_MAJOR_VERSION > 3 || \
     (FUSE_MAJOR_VERSION == 3 && FUSE_MINOR_VERSION >= 18))
#define FUSE_HAS_STATX 1
#endif

#include "reader.h"

namespace fuse_archive {

struct Node;

struct FileHandle {
  Node* node = nullptr;
  Reader::Ptr reader;
};

// Returns a populated fuse_operations struct containing all the callback
// functions required for the FUSE filesystem behavior.
fuse_operations GetFuseOperations();

}  // namespace fuse_archive

#endif  // LIB_FUSE_OPS_H
