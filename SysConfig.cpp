//---------------------------------------------------------------------------


#pragma hdrstop

#include "SysConfig.h"
#include "ByDBConfig.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

SystemConfig::SystemConfig()
{

}
bool SystemConfig::load()
{
    ByDBConfig config;
    config.Open("idra.db3");


    //config.ReadString("tbl_system","")

}
