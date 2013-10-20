//---------------------------------------------------------------------------

#ifndef SysConfigH
#define SysConfigH
#include "ByDBConfig.h"
#include <Classes.hpp>
//---------------------------------------------------------------------------
struct SystemConfig
{
    SystemConfig();
    bool load();
    bool save();
    int port;
    AnsiString devName;
    ByDBConfig config;
};
#endif
