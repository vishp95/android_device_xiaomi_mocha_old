/*
   Copyright (C) 2018 Artyom Bambalov <artem-bambalov@yandex.ru>
 */

#define LOG_TAG "mocha_init"

#include <cutils/log.h>
#include <sys/sysinfo.h>

#include "property_service.h"

char const* heapstartsize;
char const* heapgrowthlimit;
char const* heapsize;
char const* heapminfree;

void get_dalvik_heap_props()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram > 2048ull * 1024 * 1024) {
        ALOGV("3Gb RAM device");
        heapstartsize = "8m";
        heapgrowthlimit = "288m";
        heapsize = "768m";
        heapminfree = "512k";
    } else {
        ALOGV("2Gb RAM device");
        heapstartsize = "16m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heapminfree = "2m";
    }
}

void vendor_load_properties()
{
    get_dalvik_heap_props();

    property_set("dalvik.vm.heapstartsize", heapstartsize);
    property_set("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_set("dalvik.vm.heapsize", heapsize);
    property_set("dalvik.vm.heaptargetutilization", "0.75");
    property_set("dalvik.vm.heapminfree", heapminfree);
    property_set("dalvik.vm.heapmaxfree", "8m");
}
