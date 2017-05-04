include $(call all-makefiles-under,$(LOCAL_PATH))

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        camera/Camera.cpp \
        camera/CameraMetadata.cpp \
        camera/CaptureResult.cpp \
        camera/CameraParameters2.cpp \
        camera/ICamera.cpp \
        camera/ICameraClient.cpp \
        camera/ICameraService.cpp \
        camera/ICameraServiceListener.cpp \
        camera/ICameraServiceProxy.cpp \
        camera/ICameraRecordingProxy.cpp \
        camera/ICameraRecordingProxyListener.cpp \
        camera/camera2/ICameraDeviceUser.cpp \
        camera/camera2/ICameraDeviceCallbacks.cpp \
        camera/camera2/CaptureRequest.cpp \
        camera/camera2/OutputConfiguration.cpp \
        camera/CameraBase.cpp \
        camera/CameraUtils.cpp \
        camera/VendorTagDescriptor.cpp \
        camera/CameraParameters.cpp \
        sensor.c \
        camera.c


LOCAL_SHARED_LIBRARIES := \
        libcutils \
        libutils \
        liblog \
        libbinder \
        libhardware \
        libui \
        libgui \
        libcamera_metadata

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/camera/include \
        system/media/camera/include \
        system/media/private/camera/include

LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE := libmocha_camera
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := mocha_omx.cpp
LOCAL_SHARED_LIBRARIES := libbinder
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE := libmocha_omx
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := powerservice_client.c 
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE := libpowerservice_client
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
    bionic/bionic_time_conversions.cpp \
    bionic/pthread_cond.cpp
LOCAL_SHARED_LIBRARIES := libc
LOCAL_MODULE := libmocha_libc
LOCAL_CLANG := false
LOCAL_CXX_STL := none
LOCAL_SANITIZE := never
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_CLANG := true
LOCAL_CPPFLAGS := -std=c++1y -Weverything -Werror

# The static constructors and destructors in this library have not been noted to
# introduce significant overheads
LOCAL_CPPFLAGS += -Wno-exit-time-destructors
LOCAL_CPPFLAGS += -Wno-global-constructors

# We only care about compiling as C++14
LOCAL_CPPFLAGS += -Wno-c++98-compat-pedantic

# We don't need to enumerate every case in a switch as long as a default case
# is present
LOCAL_CPPFLAGS += -Wno-switch-enum

# Allow calling variadic macros without a __VA_ARGS__ list
LOCAL_CPPFLAGS += -Wno-gnu-zero-variadic-macro-arguments

# Don't warn about struct padding
LOCAL_CPPFLAGS += -Wno-padded

LOCAL_CPPFLAGS += -DDEBUG_ONLY_CODE=$(if $(filter userdebug eng,$(TARGET_BUILD_VARIANT)),1,0)

LOCAL_SRC_FILES := \
	libgui/IGraphicBufferConsumer.cpp \
	libgui/IConsumerListener.cpp \
	libgui/BitTube.cpp \
	libgui/BufferItem.cpp \
	libgui/BufferItemConsumer.cpp \
	libgui/BufferQueue.cpp \
	libgui/BufferQueueConsumer.cpp \
	libgui/BufferQueueCore.cpp \
	libgui/BufferQueueProducer.cpp \
	libgui/BufferSlot.cpp \
	libgui/ConsumerBase.cpp \
	libgui/CpuConsumer.cpp \
	libgui/DisplayEventReceiver.cpp \
	libgui/GLConsumer.cpp \
	libgui/GraphicBufferAlloc.cpp \
	libgui/GraphicsEnv.cpp \
	libgui/GuiConfig.cpp \
	libgui/IDisplayEventConnection.cpp \
	libgui/IGraphicBufferAlloc.cpp \
	libgui/IGraphicBufferProducer.cpp \
	libgui/IProducerListener.cpp \
	libgui/ISensorEventConnection.cpp \
	libgui/ISensorServer.cpp \
	libgui/ISurfaceComposer.cpp \
	libgui/ISurfaceComposerClient.cpp \
	libgui/LayerState.cpp \
	libgui/OccupancyTracker.cpp \
	libgui/Sensor.cpp \
	libgui/SensorEventQueue.cpp \
	libgui/SensorManager.cpp \
	libgui/StreamSplitter.cpp \
	libgui/Surface.cpp \
	libgui/SurfaceControl.cpp \
	libgui/SurfaceComposerClient.cpp \
	libgui/SyncFeatures.cpp \

LOCAL_SHARED_LIBRARIES := \
 	libnativeloader \
	libbinder \
	libcutils \
	libEGL \
	libGLESv2 \
	libsync \
	libui \
	libutils \
	liblog


LOCAL_MODULE := libmocha_libgui

ifeq ($(TARGET_BOARD_PLATFORM), tegra)
	LOCAL_CFLAGS += -DDONT_USE_FENCE_SYNC
endif
ifeq ($(TARGET_BOARD_PLATFORM), tegra3)
	LOCAL_CFLAGS += -DDONT_USE_FENCE_SYNC
endif

ifeq ($(TARGET_NO_SENSOR_PERMISSION_CHECK),true)
LOCAL_CPPFLAGS += -DNO_SENSOR_PERMISSION_CHECK
endif

ifeq ($(TARGET_FORCE_SCREENSHOT_CPU_PATH),true)
LOCAL_CPPFLAGS += -DFORCE_SCREENSHOT_CPU_PATH
endif

include $(BUILD_SHARED_LIBRARY)

ifeq (,$(ONE_SHOT_MAKEFILE))
include $(call first-makefiles-under,$(LOCAL_PATH))
endif
