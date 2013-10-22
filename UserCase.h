//---------------------------------------------------------------------------

#ifndef UserCaseH
#define UserCaseH
#include <classes.hpp>
#include <vector>
#include "cppSqlite3.h"
#include "RemoteControllerMgr.h"
struct UserCaseKey
{
    UserCaseKey()
    {
        keyName = "";
        time = 1000;
        count = 0;
    }
    UserCaseKey(AnsiString name, int tm):
        keyName(name),
        time(tm)
    {
        count = 0;
    }
    AnsiString keyName;
    int time;
    int count;

};
typedef std::vector<UserCaseKey> TUserCaseKeyList;

//---------------------------------------------------------------------------
class UserCase
{
public:
    UserCase(AnsiString name,AnsiString context="",int intervalMS=1000);
    ~UserCase();


    bool loadKey(void);
    bool getKeyList(TUserCaseKeyList& keyList);
 /////////////////////////discard interface/////////////////////
    TStringList* getKeyList();
    int  getInterval();
    bool getKeyList(TStringList* keyList);
    //////////////////////////////////////////////////
    void reset();  //启动一个用例前必须先复位。
    size_t getKeyCount();
    //将指定序号按键往上移动一个.
    int moveUp(int index);
    //将指定序号按键往下移动一个.
    int moveDown(int index);
    size_t getNextKey(AnsiString& key);
    /*
       function:在定时器中运行用例。
       index:返回当前运行的是第几个按键
       bool:true返回成功，false返回结束。
    */

    bool run(int &index);
    
    AnsiString getName();
private:
    AnsiString   m_name;
    AnsiString tableName;
    TStringList* m_context;
    int m_interval_ms;
    int m_index;
    //TUserCaseKeyList m_keyList;
    TList  *m_keyList;
    
    CppSQLite3DB       m_db;
};
#endif
