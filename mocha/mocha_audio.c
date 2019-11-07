#include <cutils/log.h>
#include <dlfcn.h>
#include <stdbool.h>
#include "unicode/ucnv.h"

int (*nvrm_open_new)(void *pHandle);

int NvRmOpen(void *pHandle, int DeviceId) {
    void *rm = dlopen("libnvrm.so", RTLD_NOW);

    if (!rm) {
        ALOGE("failed to find nvrm");
    } else {
        ALOGE("nvrm found");
    }

    *(void **)(&nvrm_open_new) = dlsym(rm, "NvRmOpenNew");

    if (!nvrm_open_new) {
        ALOGE("failed to find NvRmOpenNew symbol");
    } else {
        ALOGE("NvRmOpenNew found");
    }

    int result = nvrm_open_new(pHandle);

    ALOGE("nvrm_open_new result = %d", result);

    return result;
}

U_STABLE UConverter* U_EXPORT2
ucnv_open_51(const char *converterName, UErrorCode *err)
{
    return ucnv_open(converterName, err);
}

U_STABLE void  U_EXPORT2
ucnv_close_51(UConverter * converter)
{
    return ucnv_close(converter);
}

U_STABLE void U_EXPORT2 UCNV_TO_U_CALLBACK_STOP_51(
                  const void *context,
                  UConverterToUnicodeArgs *toUArgs,
                  const char* codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode * err)
{
    UCNV_TO_U_CALLBACK_STOP(context, toUArgs, codeUnits, length, reason, err);
}

U_STABLE void U_EXPORT2 UCNV_FROM_U_CALLBACK_STOP_51(
                  const void *context,
                  UConverterFromUnicodeArgs *fromUArgs,
                  const UChar* codeUnits,
                  int32_t length,
                  UChar32 codePoint,
                  UConverterCallbackReason reason,
                  UErrorCode * err)
{
    UCNV_FROM_U_CALLBACK_STOP (context, fromUArgs, codeUnits, length, codePoint, reason, err);
}

U_STABLE void U_EXPORT2
ucnv_setToUCallBack_51(UConverter * converter,
                     UConverterToUCallback newAction,
                     const void* newContext,
                     UConverterToUCallback *oldAction,
                     const void** oldContext,
                     UErrorCode * err)
{
    ucnv_setToUCallBack(converter, newAction, newContext, oldAction, oldContext, err);
}

U_STABLE void U_EXPORT2
ucnv_setFromUCallBack_51(UConverter * converter,
                       UConverterFromUCallback newAction,
                       const void *newContext,
                       UConverterFromUCallback *oldAction,
                       const void **oldContext,
                       UErrorCode * err)
{
    ucnv_setFromUCallBack(converter, newAction, newContext, oldAction, oldContext, err);
}

U_STABLE void U_EXPORT2
ucnv_convertEx_51(UConverter *targetCnv, UConverter *sourceCnv,
               char **target, const char *targetLimit,
               const char **source, const char *sourceLimit,
               UChar *pivotStart, UChar **pivotSource,
               UChar **pivotTarget, const UChar *pivotLimit,
               UBool reset, UBool flush,
               UErrorCode *pErrorCode)
{
    ucnv_convertEx(targetCnv, sourceCnv, target, targetLimit, source, sourceLimit,
                   pivotStart, pivotSource, pivotTarget, pivotLimit, reset, flush,
                   pErrorCode);
}

void _ZN7android8MonoPipeC1Ejjb(size_t reqFrames, unsigned format_old, bool writeCanBlock)
{

}

unsigned _ZN7android16Format_from_SR_CEjj(unsigned sampleRate, unsigned channelCount)
{
    ALOGE("_ZN7android16Format_from_SR_CEjj. sampleRate = %d, channelCount = %d", sampleRate, channelCount);
    return 0;
}
