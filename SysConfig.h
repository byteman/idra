//---------------------------------------------------------------------------

#ifndef SysConfigH
#define SysConfigH
#include "CppSQLite3.h"
#include <Classes.hpp>
//---------------------------------------------------------------------------
class SystemConfig
{
public:
        SystemConfig();
        bool load();
        int port;
        AnsiString devName;
        CppSQLite3DB m_db;
};
#endif
