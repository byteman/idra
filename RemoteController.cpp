//---------------------------------------------------------------------------


#pragma hdrstop

#include "RemoteController.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RemoteController::RemoteController()
{
     m_idra = NULL;
     m_name = "";
}
int RemoteController::load(AnsiString name,IDraDevice* pIdra)
{
    m_name = name ;
    m_idra = pIdra;
    m_db.open("idra.db3");

    CppSQLite3Buffer sql;
    sql.format("select * from tbl_ctrl_%Q",m_name);
    CppSQLite3Query qry = m_db.execQuery(sql);

    m_keyMap.clear();
    
    while(!qry.eof())
    {

         AnsiString key = qry.fieldValue("key");
         m_keyMap[key] =  qry.fieldValue("codec");
         
         qry.nextRow();
    }
    qry.finalize();
      
}
int RemoteController::unLoad()
{
    m_db.close();
}
int RemoteController::addKey(AnsiString keyName, AnsiString keyCodec)
{
    CppSQLite3Buffer sql;
    sql.format("insert or rollback into tbl_ctrl_%Q (key,codec) values(%Q,%Q)",m_name, keyName, keyCodec);

    try
    {
         int ret = m_db.execDML(sql);
         if(ret > 0) return 0;
    }
    catch(CppSQLite3Exception& e)
    {

    }

    return -1;
   
}
int RemoteController::sendKey(AnsiString keyName)
{
    if(m_keyMap.find(keyName) == m_keyMap.end())
    {
        return -1;
    }

    AnsiString codec = m_keyMap[keyName];

    if(m_idra)
    {
        unsigned char cmd[128] = {0,};
        memcpy(cmd,codec.data(),128);
        m_idra->sendKey(cmd);
    }

}
