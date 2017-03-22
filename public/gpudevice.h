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

#ifndef PUBLIC_GPUDEVICE_H_
#define PUBLIC_GPUDEVICE_H_

#include <scopedfd.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* C Wrappers */
#define true 1
#define false 0

typedef struct hwc_handle {
	void *device;
	void *display;
	int width;
	int height;
	int refresh_rate;

} hwc_handle;

int device_initialize(hwc_handle **handle);
void device_destroy(hwc_handle *handle);
int get_display(hwc_handle *handle);

#ifdef __cplusplus
}
#endif	// __cplusplus

#ifdef __cplusplus

#include <memory>
#include <vector>

namespace hwcomposer {

class NativeDisplay;

class DisplayHotPlugEventCallback {
 public:
  virtual ~DisplayHotPlugEventCallback() {
  }
  virtual void Callback(std::vector<NativeDisplay*> connected_displays) = 0;
};

class GpuDevice {
 public:
  GpuDevice();

  virtual ~GpuDevice();

  // Open device.
  bool Initialize();

  NativeDisplay* GetDisplay(uint32_t display);

  NativeDisplay* GetVirtualDisplay();

  std::vector<NativeDisplay*> GetConnectedPhysicalDisplays();

  void RegisterHotPlugEventCallback(
      std::shared_ptr<DisplayHotPlugEventCallback> callback);

 private:
  class DisplayManager;
  // Order is important here as we need fd_ to be valid
  // till all cleanup is done.
  ScopedFd fd_;
  std::unique_ptr<DisplayManager> display_manager_;
  bool initialized_;
};

}  // namespace hwcomposer

#endif // __cplusplus

#endif  // PUBLIC_GPUDEVICE_H_
