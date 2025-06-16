#pragma once

#ifndef HxDGraal_EXPORT
#define HxDGraal_EXPORT __declspec(dllexport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "DataInspectorShared.h"

#ifdef __cplusplus  
extern "C" {
#endif

    HxDGraal_EXPORT BOOL __stdcall GetDataTypeConverterClassIDs(
        PConverterClassID* ClassIDsOrFactoryFuncs,
        int* Count);

    HxDGraal_EXPORT void* __stdcall CreateConverter(
        TConverterClassID ClassIDOrFactoryFunc,
        const wchar_t** TypeName,
        const wchar_t** FriendlyTypeName,
        TDataTypeWidth* Width,
        int* MaxTypeSize,
        TByteOrders* SupportedByteOrders,
        BOOL* SupportsStrToBytes);

    HxDGraal_EXPORT void __stdcall DestroyConverter(
        void* ThisPtr);

    HxDGraal_EXPORT void __stdcall AssignConverter(
        void* ThisPtr,
        void* Source);

    HxDGraal_EXPORT void __stdcall ChangeByteOrder(
        void* ThisPtr,
        uint8_t* Bytes,
        int ByteCount,
        TByteOrder TargetByteOrder);

    HxDGraal_EXPORT TBytesToStrError __stdcall BytesToStr(
        void* ThisPtr,
        uint8_t* Bytes,
        int ByteCount,
        TIntegerDisplayOption IntegerDisplayOption,
        int* ConvertedByteCount,
        const wchar_t** ConvertedStr);

    HxDGraal_EXPORT TStrToBytesError __stdcall StrToBytes(
        void* ThisPtr,
        const wchar_t* Str,
        TIntegerDisplayOption IntegerDisplayOption,
        uint8_t** ConvertedBytes,
        int* ConvertedByteCount);

#ifdef __cplusplus  
}
#endif
