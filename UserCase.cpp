//---------------------------------------------------------------------------


#pragma hdrstop

#include "UserCase.h"
#include "RemoteControllerMgr.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
UserCase::UserCase(AnsiString name)
{
    m_name    = name;
    tableName = "tbl_uc_"+name;

    m_index = 0;
    m_keyList = new TList();
    loadKey();
}
UserCase::~UserCase()
{
    clearKeyList();
    if(m_keyList) delete m_keyList;
}
//获取按键个数。
size_t UserCase::getKeyCount()
{
    return m_keyList->Count;
}
//获取按键列表。
bool UserCase::getKeyList(TUserCaseKeyList& keyList)
{
     for(size_t i = 0; i < m_keyList->Count; i++)
     {
          keyList.push_back((UserCaseKey*)m_keyList->Items[i]);
     }
     return true;

}
int  UserCase::getKeyTime(int index)
{
    if( index >= m_keyList->Count) return -1;

    UserCaseKey* pUCKey = (UserCaseKey*)m_keyList->Items[index];

    return pUCKey->time;
}
UserCaseKey* UserCase::getKey(int index)
{
    if( index >= m_keyList->Count) return NULL;

    UserCaseKey* pUCKey = (UserCaseKey*)m_keyList->Items[index];

    return pUCKey;
}
void UserCase::reset()
{
     m_index = 0;
}
//获取用例名字。
AnsiString UserCase::getName()
{
    return m_name;
}
//获取下一个运行的按键.
size_t UserCase::getNextKey(AnsiString& key)
{
     return 0;

}
bool UserCase::clearKeyList()
{
    
    for(int i = 0; i < m_keyList->Count; i++)
        delete m_keyList->Items[i];
    m_keyList->Clear();

    return true;
}
//保存按键数据到数据库中。
bool UserCase::saveKeys(void)
{
     try
     {
          CppSQLite3Buffer sql;
          sql.format("delete from %s ",tableName);

          m_db.execDML(sql);

          sql.format("begin transaction");
          m_db.execDML(sql);
          for(size_t i = 0; i < m_keyList->Count; i++)
          {
                UserCaseKey *pKey =  (UserCaseKey *)m_keyList->Items[i];
                insertKeyToDB(pKey->keyName, pKey->time );
          }
          sql.format("commit transaction");
          m_db.execDML(sql);
     }
     catch(CppSQLite3Exception& e)
     {

     }
}
/*
从数据库中加载用例的按键信息
*/
bool UserCase::loadKey(void)
{
      try
      {
          m_db.open("idra.db3");
          
          if(!m_db.tableExists(tableName.c_str())) return false;

          CppSQLite3Buffer sql;
          sql.format("select * from %s",tableName);
          CppSQLite3Query qry = m_db.execQuery(sql);

          if(m_keyList) m_keyList->Clear();
          
          while(!qry.eof())
          {
              AnsiString name = qry.fieldValue("name");
              int keyS = qry.getIntField("keytime",1000);

              addKey(keyS,name);

              qry.nextRow();
          }
          qry.finalize();

          return true;
      }
      catch(CppSQLite3Exception& e)
      {


      }
      return false;
}
//run
bool UserCase::run(int &index)
{
     if( (m_index+1) >= m_keyList->Count)
     {
         index = m_index;
         return false;
     }
     UserCaseKey* pKey = (UserCaseKey*)m_keyList->Items[m_index];

     pKey->count+=1000;
     if(pKey->count >= pKey->time)
     {
         RemoteControllerMgr::get()->sendKey(pKey->keyName);
     }
}

////////////////////////////////////////////////////////////////////////////
//删除指定设备。
bool UserCase::deleteKey(int index)
{
     if( m_keyList == NULL) return false;

     if(m_keyList->Count < (index+1)) return false;

     UserCaseKey* pKey = (UserCaseKey*) m_keyList->Items[index];

     delete pKey;
     m_keyList->Delete(index);

     return true;
}
//修改指定按键的名称和按键间隔
bool UserCase::modifyKey(int index, int keytime, AnsiString keyname)
{
     if( m_keyList == NULL) return false;

     if(m_keyList->Count < (index+1)) return false;

     UserCaseKey* pKey = (UserCaseKey*) m_keyList->Items[index];

     pKey->time    = keytime;
     pKey->keyName = keyname;

     return true;
}
//在某个位置插入按键
bool UserCase::insertKey(int index, int keytime, AnsiString keyname)
{
     if( m_keyList == NULL) return false;

     UserCaseKey* pKey = new UserCaseKey(keyname,keytime);

     m_keyList->Insert(index, pKey);

     return true;

}
//在用例表的最后面添加一个按键
bool UserCase::addKey(int keytime, AnsiString keyname)
{
     if( m_keyList == NULL) return false;

     UserCaseKey* pKey = new UserCaseKey(keyname,keytime);
     m_keyList->Add(pKey);

     return true;
}
//插入一条数据到数据库表中。
bool UserCase::insertKeyToDB(AnsiString keyname, int keytime)
{
     try
     {
          CppSQLite3Buffer sql;
          sql.format("insert or rollback into %s (name,keytime) values(%Q,%d)",tableName,keyname,keytime);

          m_db.execDML(sql);

          return true;
     }
     catch(CppSQLite3Exception& e)
     {

     }
     return false;
}

int UserCase::moveUp(int index)
{
     int to = (index - 1);
     if(to <= -1) to = 0;
     m_keyList->Move(index, to);

     return to;
}
//将指定序号按键往下移动一个.
int UserCase::moveDown(int index)
{
    int to = (index + 1);
     if(to >= m_keyList->Count) to = to -1;
     m_keyList->Move(index, to);
     return to;
}
