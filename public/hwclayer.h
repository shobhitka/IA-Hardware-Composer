/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef PUBLIC_HWCLAYER_H_
#define PUBLIC_HWCLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <gbm.h>

/* C Wrappers */

void hwclayer_init(void **layer);
void hwclayer_set_transform(void *layer, int transform);
void hwclayer_set_alpha(void *layer, int alpha);
void hwclayer_set_crop(void *layer, int x, int y, int width, int height);
void hwclayer_set_frame(void *layer, int x, int y, int width, int height);
void hwclayer_set_native_handle(void *layer, struct gbm_import_fd_data *data);
void hwclayer_destroy(void *layer);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <hwcdefs.h>
#include <platformdefines.h>

#include <nativefence.h>

namespace hwcomposer {

struct HwcLayer {
  ScopedFd acquire_fence;
  NativeFence release_fence;

  void SetNativeHandle(HWCNativeHandle handle);

  HWCNativeHandle GetNativeHandle() const {
    return sf_handle_;
  }

  void SetTransform(int32_t sf_transform);

  uint32_t GetTransform() const {
    return transform_;
  }

  void SetAlpha(uint8_t alpha);

  uint8_t GetAlpha() const {
    return alpha_;
  }

  void SetBlending(HWCBlending blending);

  HWCBlending GetBlending() const {
    return blending_;
  }

  void SetSourceCrop(const HwcRect<float>& source_crop);
  const HwcRect<float>& GetSourceCrop() const {
    return source_crop_;
  }

  void SetDisplayFrame(const HwcRect<int>& display_frame);
  const HwcRect<int>& GetDisplayFrame() const {
    return display_frame_;
  }

 private:
  uint32_t transform_ = 0;
  uint8_t alpha_ = 0xff;
  HwcRect<float> source_crop_;
  HwcRect<int> display_frame_;
  HWCBlending blending_ = HWCBlending::kBlendingNone;
  HWCNativeHandle sf_handle_ = 0;
};

}  // namespace hwcomposer
#endif  // __cplusplus
#endif  // PUBLIC_HWCLAYER_H_
