#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <string>
#include <vector>

#include "DataInspectorShared.h"
#include "DataInspectorPluginInterface.h"

class TExternalDataTypeConverter
{
public:
    TExternalDataTypeConverter() = default;

    virtual void Assign(TExternalDataTypeConverter* Source);

    virtual void ChangeByteOrder(uint8_t* Bytes, int ByteCount, TByteOrder TargetByteOrder) = 0;
    virtual TBytesToStrError BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr) = 0;
    virtual TStrToBytesError StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes) = 0;

protected:
    std::wstring FTypeName;
    std::wstring FFriendlyTypeName;
    TDataTypeWidth FWidth = dtwFixed;
    int FMaxTypeSize = 0;
    TByteOrders FSupportedByteOrders = 0;
    BOOL FSupportsStrToBytes = 0;

private:
    std::wstring FLastReturnedString;
    std::vector<uint8_t> FLastReturnedByteArray;
    friend HXDGRAAL_EXPORT TBytesToStrError __stdcall BytesToStr(void*, uint8_t*, int, TIntegerDisplayOption, int*, const wchar_t**);
    friend HXDGRAAL_EXPORT TStrToBytesError __stdcall StrToBytes(void*, const wchar_t*, TIntegerDisplayOption, uint8_t**, int*);

    // Getters
public:
    const std::wstring& GetTypeName() { return FTypeName; }
    const std::wstring& GetFriendlyTypeName() { return FFriendlyTypeName; }
    const TDataTypeWidth& GetWidth() { return FWidth; }
    const int& GetMaxTypeSize() { return FMaxTypeSize; }
    const TByteOrders& GetSupportedByteOrders() { return FSupportedByteOrders; }
    const BOOL GetSupportsStrToBytes() { return FSupportsStrToBytes; }
};

// Class factory function / virtual constructor
typedef TExternalDataTypeConverter* (*TExternalDataTypeConverterFactoryFunction)();

void RegisterDataTypeConverter(TExternalDataTypeConverterFactoryFunction ConverterFactoryFunc);
