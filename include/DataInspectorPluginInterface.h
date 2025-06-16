#pragma once

#ifndef HXDGRAAL_EXPORT
#define HXDGRAAL_EXPORT __declspec(dllexport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>

#include "DataInspectorShared.h"

#ifdef __cplusplus  
extern "C" {
#endif

    HXDGRAAL_EXPORT BOOL __stdcall GetDataTypeConverterClassIDs(
        PConverterClassID* ClassIDsOrFactoryFuncs,
        int* Count);

    HXDGRAAL_EXPORT void* __stdcall CreateConverter(
        TConverterClassID ClassIDOrFactoryFunc,
        const wchar_t** TypeName,
        const wchar_t** FriendlyTypeName,
        TDataTypeWidth* Width,
        int* MaxTypeSize,
        TByteOrders* SupportedByteOrders,
        BOOL* SupportsStrToBytes);

    HXDGRAAL_EXPORT void __stdcall DestroyConverter(
        void* ThisPtr);

    HXDGRAAL_EXPORT void __stdcall AssignConverter(
        void* ThisPtr,
        void* Source);

    HXDGRAAL_EXPORT void __stdcall ChangeByteOrder(
        void* ThisPtr,
        uint8_t* Bytes,
        int ByteCount,
        TByteOrder TargetByteOrder);

    HXDGRAAL_EXPORT TBytesToStrError __stdcall BytesToStr(
        void* ThisPtr,
        uint8_t* Bytes,
        int ByteCount,
        TIntegerDisplayOption IntegerDisplayOption,
        int* ConvertedByteCount,
        const wchar_t** ConvertedStr);

    HXDGRAAL_EXPORT TStrToBytesError __stdcall StrToBytes(
        void* ThisPtr,
        const wchar_t* Str,
        TIntegerDisplayOption IntegerDisplayOption,
        uint8_t** ConvertedBytes,
        int* ConvertedByteCount);

#ifdef __cplusplus  
}
#endif
