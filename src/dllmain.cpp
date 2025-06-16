#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "DataInspectorPluginServer.h"
#include "GByteConverter.h"
#include "GByte5aConverter.h"
#include "GModTimeConverter.h"
#include "GDESConverter.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            RegisterDataTypeConverter(GByteConverter<1>::Create);
            RegisterDataTypeConverter(GByteConverter<2>::Create);
            RegisterDataTypeConverter(GByteConverter<3>::Create);
            RegisterDataTypeConverter(GByteConverter<4>::Create);
            RegisterDataTypeConverter(GByteConverter<5>::Create);
            RegisterDataTypeConverter(GByte5aConverter::Create);
            RegisterDataTypeConverter(GModTimeConverter::Create);
            RegisterDataTypeConverter(GDESConverter::Create);
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
