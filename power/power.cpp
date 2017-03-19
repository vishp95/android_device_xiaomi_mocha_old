/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (c) 2012-2014, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (C) 2015 The CyanogenMod Project
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

#include <hardware/hardware.h>
#include <hardware/power.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <utils/Log.h>
#include <cutils/properties.h>

#define BUF_SIZE 80
#define TAP_TO_WAKE_NODE "/proc/touchpanel/double_tap_enable"

static void power_init(__attribute__ ((unused)) struct power_module *) { }

void sysfs_write(const char *path, const char *s)
{
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }
    close(fd);
}

static void set_feature(__attribute__ ((unused)) struct power_module *module, feature_t feature, __attribute__ ((unused)) int state)
{
    switch (feature) {
    case POWER_FEATURE_DOUBLE_TAP_TO_WAKE:
        ALOGW("Double tap to wake\n");
        char tmp_str[BUF_SIZE];
        snprintf(tmp_str, BUF_SIZE, "%d", state);
        sysfs_write(TAP_TO_WAKE_NODE, tmp_str);
        break;
    default:
        ALOGW("Error setting the feature, it doesn't exist %d\n", feature);
        break;
    }
}

static void power_hint(struct power_module *module, power_hint_t hint, void *data) { }

static struct hw_module_methods_t power_module_methods = {
    open: NULL,
};

static void power_set_interactive(struct power_module *module, int on) {
}

struct power_module HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        module_api_version: POWER_MODULE_API_VERSION_0_3,
        hal_api_version: HARDWARE_HAL_API_VERSION,
        id: POWER_HARDWARE_MODULE_ID,
        name: "mocha smoke PowerHAL",
        author: "artt",
        methods: &power_module_methods,
        dso: NULL,
        reserved: {0},
    },

    init: power_init,
    setInteractive: power_set_interactive,
    powerHint: power_hint,
    setFeature: set_feature,
    getFeature: 0,
};
