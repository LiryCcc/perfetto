/*
 * Copyright (C) 2024 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_TRACE_PROCESSOR_IMPORTERS_COMMON_TRACKS_COMMON_H_
#define SRC_TRACE_PROCESSOR_IMPORTERS_COMMON_TRACKS_COMMON_H_

#include <cstdint>

#include "perfetto/ext/base/string_utils.h"
#include "perfetto/ext/base/string_view.h"
#include "src/trace_processor/importers/common/tracks.h"

namespace perfetto::trace_processor::tracks {

// This file acts as a shared source track, dimension and unit blueprints which
// are used from many places throughout the codebase. It's strongly recomended
// to use the shared blueprints from this file where possible.

// Begin dimension blueprints.

inline constexpr auto kGpuDimensionBlueprint =
    tracks::UintDimensionBlueprint("gpu");

inline constexpr auto kUidDimensionBlueprint =
    tracks::UintDimensionBlueprint("uid");

inline constexpr auto kCpuDimensionBlueprint =
    tracks::UintDimensionBlueprint("cpu");

inline constexpr auto kNameFromTraceDimensionBlueprint =
    tracks::StringDimensionBlueprint("name");

inline constexpr auto kLinuxDeviceDimensionBlueprint =
    tracks::StringDimensionBlueprint("linux_device");

inline constexpr auto kIrqDimensionBlueprint =
    tracks::UintDimensionBlueprint("irq");

inline constexpr auto kProcessDimensionBlueprint =
    tracks::UintDimensionBlueprint("upid");

inline constexpr auto kThreadDimensionBlueprint =
    tracks::UintDimensionBlueprint("utid");

inline constexpr auto kNetworkInterfaceDimensionBlueprint =
    tracks::StringDimensionBlueprint("network_interface");

inline constexpr auto kThermalZoneDimensionBlueprint =
    tracks::StringDimensionBlueprint("thermal_zone");

// End dimension blueprints.

// Begin of unit blueprints.

inline constexpr auto kBytesUnitBlueprint =
    tracks::StaticUnitBlueprint("bytes");

// Begin of shared unit blueprints.

// Begin slice blueprints

inline constexpr auto kLegacyGlobalInstantsBlueprint =
    tracks::SliceBlueprint("legacy_chrome_global_instants");

// End slice blueprints.

// Begin counter blueprints.

static constexpr auto kClockFrequencyBlueprint = tracks::CounterBlueprint(
    "clock_frequency",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kLinuxDeviceDimensionBlueprint),
    tracks::FnNameBlueprint([](base::StringView key) {
      return base::StackString<255>("%.*s Frequency", int(key.size()),
                                    key.data());
    }));

static constexpr auto kClockStateBlueprint = tracks::CounterBlueprint(
    "clock_state",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kLinuxDeviceDimensionBlueprint),
    tracks::FnNameBlueprint([](base::StringView key) {
      return base::StackString<255>("%.*s State", int(key.size()), key.data());
    }));

static constexpr auto kCpuFrequencyBlueprint = tracks::CounterBlueprint(
    "cpu_frequency",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kCpuDimensionBlueprint),
    tracks::StaticNameBlueprint("cpufreq"));

static constexpr auto kGpuFrequencyBlueprint = tracks::CounterBlueprint(
    "gpu_frequency",
    tracks::StaticUnitBlueprint("MHz"),
    tracks::DimensionBlueprints(kGpuDimensionBlueprint),
    tracks::StaticNameBlueprint("gpufreq"));

static constexpr auto kCpuIdleBlueprint = tracks::CounterBlueprint(
    "cpu_idle",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kCpuDimensionBlueprint),
    tracks::StaticNameBlueprint("cpuidle"));

static constexpr auto kThermalTemperatureBlueprint = tracks::CounterBlueprint(
    "thermal_temperature",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kThermalZoneDimensionBlueprint),
    tracks::FnNameBlueprint([](base::StringView tz) {
      return base::StackString<255>("%.*s Temperature",
                                    static_cast<int>(tz.size()), tz.data());
    }));

static constexpr auto kCoolingDeviceCounterBlueprint = tracks::CounterBlueprint(
    "cooling_device_counter",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(kLinuxDeviceDimensionBlueprint),
    tracks::FnNameBlueprint([](base::StringView cdev) {
      return base::StackString<255>("%.*s Cooling Device",
                                    static_cast<int>(cdev.size()), cdev.data());
    }));

constexpr auto kChromeProcessStatsBlueprint = tracks::CounterBlueprint(
    "chrome_process_stats",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kProcessDimensionBlueprint,
                                tracks::StringDimensionBlueprint("key")),
    tracks::FnNameBlueprint([](uint32_t, base::StringView name) {
      return base::StackString<128>("chrome.%.*s", int(name.size()),
                                    name.data());
    }));

constexpr auto kAndroidScreenStateBlueprint =
    tracks::CounterBlueprint("screen_state",
                             tracks::UnknownUnitBlueprint(),
                             tracks::DimensionBlueprints(),
                             tracks::StaticNameBlueprint("ScreenState"));

constexpr auto kAndroidBatteryStatsBlueprint = tracks::CounterBlueprint(
    "battery_stats",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(
        tracks::StringDimensionBlueprint("counter_key")),
    tracks::FnNameBlueprint([](base::StringView name) {
      return base::StackString<1024>("%.*s", int(name.size()), name.data());
    }));

constexpr auto kAndroidAtraceCounterBlueprint = tracks::CounterBlueprint(
    "atrace_counter",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kProcessDimensionBlueprint,
                                tracks::kNameFromTraceDimensionBlueprint),
    tracks::FnNameBlueprint([](uint32_t, base::StringView name) {
      return base::StackString<1024>("%.*s", int(name.size()), name.data());
    }));

constexpr auto kOomScoreAdjBlueprint = tracks::CounterBlueprint(
    "oom_score_adj",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kProcessDimensionBlueprint),
    tracks::StaticNameBlueprint("oom_score_adj"));

constexpr auto kOomScoreAdjThreadFallbackBlueprint = tracks::CounterBlueprint(
    "oom_score_adj_thread_fallback",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kThreadDimensionBlueprint),
    tracks::StaticNameBlueprint("oom_score_adj"));

constexpr auto kMmEventFnNameBlueprint = tracks::FnNameBlueprint(
    [](uint32_t, base::StringView type, base::StringView metric) {
      return base::StackString<1024>("mem.mm.%.*s.%.*s", int(type.size()),
                                     type.data(), int(metric.size()),
                                     metric.data());
    });

constexpr auto kMmEventBlueprint = tracks::CounterBlueprint(
    "mm_event",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(
        tracks::kProcessDimensionBlueprint,
        tracks::StringDimensionBlueprint("mm_event_type"),
        tracks::StringDimensionBlueprint("mm_event_metric")),
    kMmEventFnNameBlueprint);

constexpr auto kMmEventThreadFallbackBlueprint = tracks::CounterBlueprint(
    "mm_event_thread_fallback",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(
        tracks::kThreadDimensionBlueprint,
        tracks::StringDimensionBlueprint("mm_event_type"),
        tracks::StringDimensionBlueprint("mm_event_metric")),
    kMmEventFnNameBlueprint);

constexpr auto kPerfCounterBlueprint = tracks::CounterBlueprint(
    "perf_counter",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(
        tracks::kCpuDimensionBlueprint,
        tracks::UintDimensionBlueprint("perf_session_id"),
        tracks::kNameFromTraceDimensionBlueprint),
    tracks::DynamicNameBlueprint());

constexpr auto kGlobalGpuMemoryBlueprint =
    tracks::CounterBlueprint("gpu_memory",
                             tracks::kBytesUnitBlueprint,
                             tracks::DimensionBlueprints(),
                             tracks::StaticNameBlueprint("GPU Memory"));

constexpr auto kProcessGpuMemoryBlueprint = tracks::CounterBlueprint(
    "process_gpu_memory",
    tracks::kBytesUnitBlueprint,
    tracks::DimensionBlueprints(tracks::kProcessDimensionBlueprint),
    tracks::StaticNameBlueprint("GPU Memory"));

static constexpr auto kProcessMemoryBlueprint = tracks::CounterBlueprint(
    "process_memory",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(
        tracks::kProcessDimensionBlueprint,
        tracks::StringDimensionBlueprint("process_memory_key")),
    tracks::FnNameBlueprint([](uint32_t, base::StringView key) {
      return base::StackString<1024>("mem.%.*s", int(key.size()), key.data());
    }));

static constexpr auto kProcessMemoryThreadFallbackBlueprint =
    tracks::CounterBlueprint(
        "process_memory_thread_fallback",
        tracks::UnknownUnitBlueprint(),
        tracks::DimensionBlueprints(
            tracks::kThreadDimensionBlueprint,
            tracks::StringDimensionBlueprint("process_memory_key")),
        tracks::FnNameBlueprint([](uint32_t, base::StringView key) {
          return base::StackString<1024>("mem.%.*s", int(key.size()),
                                         key.data());
        }));

static constexpr auto kJsonCounterBlueprint = tracks::CounterBlueprint(
    "json_counter",
    tracks::UnknownUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kProcessDimensionBlueprint,
                                tracks::kNameFromTraceDimensionBlueprint),
    tracks::DynamicNameBlueprint());

static constexpr auto kJsonCounterThreadFallbackBlueprint =
    tracks::CounterBlueprint(
        "json_counter_thread_fallback",
        tracks::UnknownUnitBlueprint(),
        tracks::DimensionBlueprints(tracks::kThreadDimensionBlueprint,
                                    tracks::kNameFromTraceDimensionBlueprint),
        tracks::DynamicNameBlueprint());

static constexpr auto kGpuCounterBlueprint = tracks::CounterBlueprint(
    "gpu_counter",
    tracks::DynamicUnitBlueprint(),
    tracks::DimensionBlueprints(tracks::kGpuDimensionBlueprint,
                                tracks::kNameFromTraceDimensionBlueprint),
    tracks::DynamicNameBlueprint());

// End counter blueprints.

}  // namespace perfetto::trace_processor::tracks

#endif  // SRC_TRACE_PROCESSOR_IMPORTERS_COMMON_TRACKS_COMMON_H_
