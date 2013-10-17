//---------------------------------------------------------------------------

#ifndef SysConfigH
#define SysConfigH
#include "CppSQLite3.h"
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
