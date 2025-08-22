#pragma once

#include <chrono>
#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include "DataInspectorShared.h"
#include "DataInspectorPluginServer.h"

class GPixelCoordConverter : public TExternalDataTypeConverter
{
public:
    static TExternalDataTypeConverter* Create()
    {
        return new GPixelCoordConverter();
    }

public:
    GPixelCoordConverter()
    {
        FTypeName = L"Graal - Pixel Coord";
        FFriendlyTypeName = FTypeName;
        FWidth = dtwFixed;
        FMaxTypeSize = 2;
        FSupportedByteOrders = 1 << boLittleEndian | 1 << boBigEndian;
        FSupportsStrToBytes = 0;
    }

public:
    virtual void ChangeByteOrder(uint8_t* Bytes, int ByteCount, TByteOrder TargetByteOrder) override {}
    virtual TBytesToStrError BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr) override;
    virtual TStrToBytesError StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes) override;
};

//----------------------------

TBytesToStrError GPixelCoordConverter::BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr)
{
    if (ByteCount >= 2)
    {
        ConvertedByteCount = 2;
        int32_t pixelPosition =
              (static_cast<int32_t>(Bytes[0] - 32) << (7 * 1))
            + (static_cast<int32_t>(Bytes[1] - 32));

        bool isNegative = (pixelPosition & 0x1) != 0;
        pixelPosition >>= 1;

		ConvertedStr = std::format(L"{}", isNegative ? -pixelPosition : pixelPosition);
        return btseNone;
    }
    else
    {
        ConvertedByteCount = 0;
        ConvertedStr = L""; // Warning: do not set to NULL, this will throw exceptions

        return btseBytesTooShort;
    }
    return btseNone;
}

TStrToBytesError GPixelCoordConverter::StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes)
{
    return stbeNone;
}
