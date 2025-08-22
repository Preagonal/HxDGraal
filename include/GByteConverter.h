#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include "DataInspectorShared.h"
#include "DataInspectorPluginServer.h"

template<size_t N>
class GByteConverter : public TExternalDataTypeConverter
{
public:
    static TExternalDataTypeConverter* Create()
    {
        return new GByteConverter<N>();
    }

public:
    GByteConverter()
    {
        FTypeName = std::format(L"Graal - GBYTE{}", N);
        FFriendlyTypeName = FTypeName;
        FWidth = dtwFixed;
        FMaxTypeSize = N;
        FSupportedByteOrders = 1 << boLittleEndian | 1 << boBigEndian;
        FSupportsStrToBytes = 0;
    }

public:
    template<size_t Count>
    uint64_t CalculateGByte(uint8_t* bytes) const
    {
        return (static_cast<uint64_t>(static_cast<uint8_t>(bytes[0] - 32)) << (7 * (Count - 1))) + CalculateGByte<Count - 1>(bytes + 1);
    }

    template<>
    uint64_t CalculateGByte<1>(uint8_t* bytes) const
    {
        return static_cast<uint8_t>(bytes[0] - 32);
    }

    template<>
    uint64_t CalculateGByte<0>(uint8_t* bytes) const
    {
        return 0;
    }

public:
    virtual void ChangeByteOrder(uint8_t* Bytes, int ByteCount, TByteOrder TargetByteOrder) override {}
    virtual TBytesToStrError BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr) override;
    virtual TStrToBytesError StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes) override;
};

//----------------------------

template<size_t N>
TBytesToStrError GByteConverter<N>::BytesToStr(uint8_t* Bytes, int ByteCount, TIntegerDisplayOption IntegerDisplayOption, int& ConvertedByteCount, std::wstring& ConvertedStr)
{
    if (ByteCount >= N)
    {
        ConvertedByteCount = N;
        uint64_t ConvertedInt = CalculateGByte<N>(Bytes) & 0xFFFFFFFF;

        switch (IntegerDisplayOption)
        {
            case idoDecimal:
                ConvertedStr = std::format(L"{}", ConvertedInt);
                break;
            case idoHexadecimalUpperCase:
                ConvertedStr = std::format(L"{:X}", ConvertedInt);
                break;
            case idoHexadecimalLowerCase:
                ConvertedStr = std::format(L"{:x}", ConvertedInt);
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

template<size_t N>
TStrToBytesError GByteConverter<N>::StrToBytes(std::wstring Str, TIntegerDisplayOption IntegerDisplayOption, std::vector<uint8_t>& ConvertedBytes)
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
