
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

#define TAG "conn_init"
#define MAC_PARTION "/dev/block/platform/700b0600.sdhci/by-name/BKB"
#define MAC_PARTION_OLD "/dev/block/platform/sdhci-tegra.3/by-name/BKB"
#define BT_MAC_PROP "ro.bt.bdaddr_path"
#define WIFI_MAC_PROP "/sys/module/bcmdhd/parameters/mac"
#define BT_MAC_FILE "/data/misc/bluetooth/bt_mac.conf"

void set_bt_mac(FILE *fp) {
	char buf[30];
	FILE *bmfp;

	fseek(fp, 0, SEEK_SET);
	fread(buf, sizeof(char), 22, fp);

	bmfp = fopen(BT_MAC_FILE, "w");
	if (bmfp == NULL) {
		ALOGE("%s: Can't open %s error: %d", TAG, BT_MAC_FILE, errno);
		return;
	} else {
		fprintf(bmfp, "%02x:%02x:%02x:%02x:%02x:%02x\n", 
			(unsigned char)buf[14],
			(unsigned char)buf[13],
			(unsigned char)buf[12],
			(unsigned char)buf[11],
			(unsigned char)buf[10],
			(unsigned char)buf[9]);
		fclose(bmfp);
	}
	property_set(BT_MAC_PROP, BT_MAC_FILE);
}

void set_wifi_mac(FILE *fp)
{
	char buf[30];
	
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
		ALOGE("%s: Can't open %s error: %d", TAG, WIFI_MAC_PROP, errno);
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
		ALOGE("%s: Can't open %s error: %d", TAG, MAC_PARTION, errno);
		fp = fopen(MAC_PARTION_OLD, "r");
		if (fp == NULL) {
			ALOGE("%s: Can't open %s error: %d", TAG, MAC_PARTION_OLD, errno);
			return 0;
		}
	}
	set_wifi_mac(fp);
	set_bt_mac(fp);
	fclose(fp);

	return 0;
}
