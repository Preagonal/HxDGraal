#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include "DataInspectorShared.h"
#include "DataInspectorPluginServer.h"

class GDESConverter : public TExternalDataTypeConverter
{
public:
    static TExternalDataTypeConverter* Create()
    {
        return new GDESConverter();
    }

public:
    GDESConverter()
    {
        FTypeName = L"Graal - DES";
        FFriendlyTypeName = FTypeName;
        FWidth = dtwFixed;
        FMaxTypeSize = 10;
        FSupportedByteOrders = 1 << boLittleEndian | 1 << boBigEndian;
        FSupportsStrToBytes = 0;
    }

public:
    virtual void ChangeByteOrder(uint8_t* Bytes, int ByteCount, TByteOrder TargetByteOrder) override {}
    virtual TBytesToStrError BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr) override;
    virtual TStrToBytesError StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes) override;
};

//----------------------------

TBytesToStrError GDESConverter::BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr)
{
    if (ByteCount >= 10)
    {
        ConvertedByteCount = 10;

        uint64_t firstHalf =
              (static_cast<uint64_t>(Bytes[0]) << (7 * 4)) // alternative version with no -32 offset
            + (static_cast<uint64_t>(Bytes[1] - 32) << (7 * 3))
            + (static_cast<uint64_t>(Bytes[2] - 32) << (7 * 2))
            + (static_cast<uint64_t>(Bytes[3] - 32) << (7 * 1))
            + (static_cast<uint64_t>(Bytes[4] - 32));

        uint64_t secondHalf =
              (static_cast<uint64_t>(Bytes[5]) << (7 * 4)) // alternative version with no -32 offset
            + (static_cast<uint64_t>(Bytes[6] - 32) << (7 * 3))
            + (static_cast<uint64_t>(Bytes[7] - 32) << (7 * 2))
            + (static_cast<uint64_t>(Bytes[8] - 32) << (7 * 1))
            + (static_cast<uint64_t>(Bytes[9] - 32));

        uint8_t desKey[8] =
        {
            uint8_t(firstHalf),
			uint8_t(firstHalf >> 8),
            uint8_t(firstHalf >> 16),
            uint8_t(firstHalf >> 24),
            uint8_t(secondHalf),
            uint8_t(secondHalf >> 8),
            uint8_t(secondHalf >> 16),
			uint8_t(secondHalf >> 24)
        };

		uint64_t* ConvertedInt = reinterpret_cast<uint64_t*>(desKey);

        switch (IntegerDisplayOption)
        {
            case idoDecimal:
                ConvertedStr = std::format(L"{}", *ConvertedInt);
                break;
            case idoHexadecimalUpperCase:
                ConvertedStr = std::format(L"{:X}", *ConvertedInt);
                break;
            case idoHexadecimalLowerCase:
                ConvertedStr = std::format(L"{:x}", *ConvertedInt);
                break;
        }

        return btseNone;
    }
    else
    {
        ConvertedByteCount = 0;
        ConvertedStr = L""; // Warning: do not set to NULL, this will throw exceptions

        return btseBytesTooShort;
    }
}

TStrToBytesError GDESConverter::StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes)
{
    /*
    static_assert(sizeof(long) >= sizeof(int32_t),
        "str2int must return an integer of at least sizeof(int32_t)");

    int base;
    switch (FormattingOptions.IntegerBase)
    {
        case ibDecimal:
            base = 10;
            break;
        case ibHexadecimal:
            base = 16;
            break;
    }

    long I;
    trim(Str);
    TStrToBytesError result = str2int(Str.c_str(), &I, base);

    // hexadecimal numbers are always handled as unsigned integers
    if (result == stbeOverflow)
    {
        unsigned long UI;
        result = str2uint(Str.c_str(), &UI, base);
        I = (long)UI;
    }

    ConvertedBytes.resize(sizeof(int32_t));
    *((int32_t*)&ConvertedBytes[0]) = (int32_t)I;

    if (sizeof(long) > sizeof(int32_t))
    {
        if (result == stbeNone)
            if (I < INT32_MIN)
                return stbeUnderflow;
            else if (I > INT32_MAX)
                return stbeOverflow;
    }
    return result;
    */
    return stbeNone;
}
