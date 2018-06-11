LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= src/mixer.c src/pcm.c
LOCAL_MODULE := libtinyalsa_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils
LOCAL_CFLAGS += -Werror
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= utils/tinyplay.c
LOCAL_MODULE := tinyplay_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= utils/tinycap.c
LOCAL_MODULE := tinycap_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= utils/tinymix.c
LOCAL_MODULE := tinymix_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES:= device/xiaomi/mocha/tinyalsa/include
LOCAL_SRC_FILES:= utils/tinypcminfo.c
LOCAL_MODULE := tinypcminfo_mocha
LOCAL_SHARED_LIBRARIES:= libcutils libutils libtinyalsa_mocha
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Werror
include $(BUILD_EXECUTABLE)
