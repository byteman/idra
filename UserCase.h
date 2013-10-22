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
    void reset();  //����һ������ǰ�����ȸ�λ��
    size_t getKeyCount();
    //��ָ����Ű��������ƶ�һ��.
    int moveUp(int index);
    //��ָ����Ű��������ƶ�һ��.
    int moveDown(int index);
    size_t getNextKey(AnsiString& key);
    /*
       function:�ڶ�ʱ��������������
       index:���ص�ǰ���е��ǵڼ�������
       bool:true���سɹ���false���ؽ�����
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
