//---------------------------------------------------------------------------


#pragma hdrstop

#include "SysConfig.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

SystemConfig::SystemConfig()
{
    config.Open("idra.db3");
    load();
}
bool SystemConfig::load()
{

    port = config.ReadInteger("config","port",6);
    devName  = config.ReadString("config","curDevice","").c_str();

    return true;
}
bool SystemConfig::save()
{
    config.WriteInteger("config","port",port);
    config.ReadString("config","curDevice",devName.c_str());
    return true;
}
