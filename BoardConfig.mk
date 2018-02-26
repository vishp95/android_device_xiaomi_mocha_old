USE_CAMERA_STUB := true

# inherit from the proprietary version
-include vendor/xiaomi/mocha/BoardConfigVendor.mk

TARGET_ARCH := arm
TARGET_NO_BOOTLOADER := true
TARGET_BOARD_PLATFORM := tegra
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_VARIANT := cortex-a15
TARGET_ARCH_VARIANT := armv7-a-neon
ARCH_ARM_HAVE_TLS_REGISTER := true

TARGET_BOOTLOADER_BOARD_NAME := mocha

BOARD_KERNEL_CMDLINE := androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x10000000
BOARD_KERNEL_PAGESIZE := 2048
BOARD_MKBOOTIMG_ARGS := --dt device/xiaomi/mocha/dt.img

BOARD_USE_CUSTOM_RECOVERY_FONT :=  \"roboto_23x41.h\"
BRIGHTNESS_SYS_FILE := /sys/class/leds/button-backlight/brightness	  
TARGET_USE_CUSTOM_LUN_FILE_PATH := /sys/class/android_usb/android0/f_mass_storage/lun/file
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_HAS_NO_SELECT_BUTTON := true

TW_THEME := portrait_hdpi
TW_EXTERNAL_STORAGE_PATH := "/external_sd"
TW_EXTERNAL_STORAGE_MOUNT_POINT := "external_sd"
RECOVERY_SDCARD_ON_DATA := true
TW_FLASH_FROM_STORAGE := true
TW_NO_USB_STORAGE := true

BOARD_BOOTIMAGE_PARTITION_SIZE := 20971520
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 20971520
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 671088640
BOARD_USERDATAIMAGE_PARTITION_SIZE := 13742637056
BOARD_FLASH_BLOCK_SIZE := 131072

PRODUCT_COPY_FILES += device/xiaomi/mocha/twrp.fstab:recovery/root/etc/twrp.fstab

TARGET_PREBUILT_KERNEL := device/xiaomi/mocha/kernel

# MultiROM
MR_PIXEL_FORMAT := RGB_565
MR_INPUT_TYPE := type_b
MR_INIT_DEVICES := device/xiaomi/mocha/multirom/mr_init_devices.c
MR_DPI := xhdpi
MR_DPI_FONT := 320
MR_FSTAB := device/xiaomi/mocha/multirom/twrp.fstab
MR_KEXEC_MEM_MIN := 0x85000000
MR_KEXEC_DTB := true
MR_DEVICE_HOOKS := device/xiaomi/mocha/multirom/mr_hooks.c
MR_DEVICE_HOOKS_VER := 3
MR_DEVICE_VARIANTS := mocha
MR_USE_MROM_FSTAB := true
TARGET_RECOVERY_IS_MULTIROM := false
