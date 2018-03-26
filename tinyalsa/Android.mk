LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= mixer.c pcm.c
LOCAL_MODULE := libtinyalsa_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils
LOCAL_CFLAGS += -Werror
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= tinyplay.c
LOCAL_MODULE := tinyplay_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= tinycap.c
LOCAL_MODULE := tinycap_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= tinymix.c
LOCAL_MODULE := tinymix_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= tinypcminfo.c
LOCAL_MODULE := tinypcminfo_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)
