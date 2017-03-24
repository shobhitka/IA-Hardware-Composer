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

#include <hwclayer.h>

namespace hwcomposer {

void HwcLayer::SetNativeHandle(HWCNativeHandle handle) {
  sf_handle_ = handle;
}

void HwcLayer::SetTransform(int32_t transform) {
  transform_ = transform;
}

void HwcLayer::SetAlpha(uint8_t alpha) {
  alpha_ = alpha;
}

void HwcLayer::SetBlending(HWCBlending blending) {
  blending_ = blending;
}

void HwcLayer::SetSourceCrop(const HwcRect<float>& source_crop) {
  source_crop_ = source_crop;
}

void HwcLayer::SetDisplayFrame(const HwcRect<int>& display_frame) {
  display_frame_ = display_frame;
}

}  // namespace hwcomposer

extern "C" {
void hwclayer_init(void **layer) {
  hwcomposer::HwcLayer *hwc_layer = new hwcomposer::HwcLayer();

  *layer = (void *)hwc_layer;
}

void hwclayer_set_transform(void *layer, int transform) {
  hwcomposer::HwcLayer *hwc_layer = (hwcomposer::HwcLayer *)layer;
  hwc_layer->SetTransform(transform);
}

void hwclayer_set_alpha(void *layer, int alpha) {
  hwcomposer::HwcLayer *hwc_layer = (hwcomposer::HwcLayer *)layer;
  hwc_layer->SetAlpha(alpha);
}

void hwclayer_set_crop(void *layer, int x, int y, int width, int height) {
  hwcomposer::HwcLayer *hwc_layer = (hwcomposer::HwcLayer *)layer;

  hwc_layer->SetSourceCrop(
      hwcomposer::HwcRect<float>(x, y, width, height));
}

void hwclayer_set_frame(void *layer, int x, int y, int width, int height) {
  hwcomposer::HwcLayer *hwc_layer = (hwcomposer::HwcLayer *)layer;

  hwc_layer->SetSourceCrop(
      hwcomposer::HwcRect<int>(x, y, width, height));
}

void hwclayer_set_native_handle(void *layer, struct gbm_import_fd_data *data) {
  hwcomposer::HwcLayer *hwc_layer = (hwcomposer::HwcLayer *)layer;

	struct gbm_handle handle;
	memcpy(&handle.import_data, data, sizeof(*data));

  hwc_layer->SetNativeHandle(&handle);
}

void hwclayer_destroy(void *layer) {
}
}
