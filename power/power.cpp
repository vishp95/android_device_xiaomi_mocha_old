/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (c) 2012-2014, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (C) 2015 The CyanogenMod Project
 * Copyright (C) 2017 arttttt
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

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <utils/Log.h>

#include <cutils/properties.h>
#include <hardware/power.h>

#define BUF_SIZE 80
#define TAP_TO_WAKE_NODE "/proc/touchpanel/double_tap_enable"
#define TAG "PowerHAL"
#define POWER_PROFILE_PROPERTY  "sys.perf.profile"

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_BIAS_POWER_SAVE,
    PROFILE_MAX
};

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void sysfs_write(char *path, const char *s)
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

static void sysfs_write_int(char *path, int value)
{
	char buf[BUF_SIZE];
	snprintf(buf, BUF_SIZE, "%d", value);
	sysfs_write(path, buf);
}

static void property_set_int(char *property, int value)
{
	char buf[BUF_SIZE];
	snprintf(buf, BUF_SIZE, "%d", value);
	property_set(property, buf);
}

static void power_init(__attribute__ ((unused)) struct power_module *) {
	ALOGW("%s: power_init\n", TAG);
}

static void power_set_interactive(__attribute__ ((unused)) struct power_module *module, __attribute__ ((unused)) int on) { 
	ALOGW("%s: power_set_interactive\n", TAG);
}

static void set_power_profile(int profile)
{
	property_set_int(POWER_PROFILE_PROPERTY, profile);
	ALOGW("%s: set power profile = %d", TAG, profile);
}

static void power_hint(__attribute__ ((unused)) struct power_module *module, power_hint_t hint, void *data) { 
	switch (hint) {
		case POWER_HINT_SET_PROFILE:
			pthread_mutex_lock(&lock);
			set_power_profile(*(int32_t *)data);
			pthread_mutex_unlock(&lock);
		break;
	}
}

static void set_feature(__attribute__ ((unused)) struct power_module *module, feature_t feature, int state)
{
	switch (feature) {
		case POWER_FEATURE_DOUBLE_TAP_TO_WAKE:
			ALOGW("%s: Double tap to wake\n", TAG);
			char tmp_str[BUF_SIZE];
			snprintf(tmp_str, BUF_SIZE, "%d", state);
			sysfs_write(TAP_TO_WAKE_NODE, tmp_str);
		break;
		default:
			ALOGE("Error setting the feature, it doesn't exist %d\n", feature);
	}
	ALOGW("%s: feature = %d\n", TAG, feature);
}

static int get_feature(__attribute__((unused)) struct power_module *module, feature_t feature)
{
	switch (feature) {
		case POWER_FEATURE_SUPPORTED_PROFILES:
			ALOGW("%s: power profiles POWER_FEATURE_SUPPORTED_PROFILES\n", TAG);
			return PROFILE_MAX;
		default:
			ALOGE("Error getting the feature, it doesn't exist %d\n", feature);
	}
	return -1;
}

static struct hw_module_methods_t power_module_methods = {
	.open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = POWER_MODULE_API_VERSION_0_3,
		.hal_api_version = HARDWARE_HAL_API_VERSION,
		.id = POWER_HARDWARE_MODULE_ID,
		.name = "mocha smoke PowerHAL",
		.author = "arttttt",
		.methods = &power_module_methods,
		.dso = NULL,
        .reserved = {0},
	},

	.init = power_init,
	.setInteractive = power_set_interactive,
	.powerHint = power_hint,
	.setFeature = set_feature,
	.getFeature = get_feature
};
