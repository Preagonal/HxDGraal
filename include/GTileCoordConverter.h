#pragma once

#include <chrono>
#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include "DataInspectorShared.h"
#include "DataInspectorPluginServer.h"

class GTileCoordConverter : public TExternalDataTypeConverter
{
public:
    static TExternalDataTypeConverter* Create()
    {
        return new GTileCoordConverter();
    }

public:
    GTileCoordConverter()
    {
        FTypeName = L"Graal - Tile Coord";
        FFriendlyTypeName = FTypeName;
        FWidth = dtwFixed;
        FMaxTypeSize = 1;
        FSupportedByteOrders = 1 << boLittleEndian | 1 << boBigEndian;
        FSupportsStrToBytes = 0;
    }

public:
    virtual void ChangeByteOrder(uint8_t* Bytes, int ByteCount, TByteOrder TargetByteOrder) override {}
    virtual TBytesToStrError BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr) override;
    virtual TStrToBytesError StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes) override;
};

//----------------------------

TBytesToStrError GTileCoordConverter::BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr)
{
    if (ByteCount >= 1)
    {
        ConvertedByteCount = 1;
        float tileUnsigned = static_cast<uint8_t>(Bytes[1] - 32) / 2.0f;
		float tileSigned = static_cast<int8_t>(Bytes[1] - 32) / 2.0f;

        if (Bytes[1] < 236)
            ConvertedStr = std::format(L"{}", tileUnsigned);
        else
            ConvertedStr = std::format(L"{} ({})", tileUnsigned, tileSigned);

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

TStrToBytesError GTileCoordConverter::StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes)
{
    return stbeNone;
}
