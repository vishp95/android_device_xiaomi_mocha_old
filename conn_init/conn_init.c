
/*
 * Copyright (C) 2017 arttttt
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

#include <stdlib.h>
#include <string.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include <errno.h>

#define MAC_PARTION "/dev/block/platform/700b0600.sdhci/by-name/BKB"
#define MAC_PARTION_OLD "/dev/block/platform/sdhci-tegra.3/by-name/BKB"
#define BT_MAC_PROP "persist.service.bdroid.bdaddr"
#define WIFI_MAC_PROP "/sys/module/bcmdhd/parameters/mac"

void set_macs(FILE *fp)
{
	char buf[30];
	fread(buf, sizeof(char), 22, fp);
	
	snprintf(buf, 30, "%x:%x:%x:%x:%x:%x\n",
		(unsigned char)buf[14],
		(unsigned char)buf[13],
		(unsigned char)buf[12],
		(unsigned char)buf[11],
		(unsigned char)buf[10],
		(unsigned char)buf[9]);
	property_set(BT_MAC_PROP, buf);

	fseek(fp, sizeof(char) * 22, SEEK_SET);
	fread(buf, sizeof(char), 22, fp);

	snprintf(buf, 30, "0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
		(unsigned char)buf[14],
		(unsigned char)buf[13],
		(unsigned char)buf[12],
		(unsigned char)buf[11],
		(unsigned char)buf[10],
		(unsigned char)buf[9]);

	FILE *wfp = fopen(WIFI_MAC_PROP, "w");
	if (wfp == NULL) {
		ALOGE("Can't open /sys/module/bcmdhd/parameters/mac error: %d", errno);
		return;
	}
	fwrite(buf, sizeof(unsigned char), 30, wfp);
	fclose(wfp);
}

int main(void)
{
	FILE *fp;
	fp = fopen(MAC_PARTION, "r");
	if (fp == NULL) {
		ALOGE("Can't open /dev/block/platform/700b0600.sdhci/by-name/BKB error: %d", errno);
		fp = fopen(MAC_PARTION_OLD, "r");
		if (fp == NULL) {
			ALOGE("Can't open /dev/block/platform/sdhci-tegra.3/by-name/BKB error: %d", errno);
			return 0;
		}
	}
	set_macs(fp);
	fclose(fp);

	return 0;
}
