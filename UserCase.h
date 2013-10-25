//---------------------------------------------------------------------------

#ifndef UserCaseH
#define UserCaseH
#include <classes.hpp>
#include <vector>
#include "cppSqlite3.h"

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
typedef std::vector<UserCaseKey*> TUserCaseKeyList;

//---------------------------------------------------------------------------
class UserCase
{
public:
    UserCase(AnsiString name);
    ~UserCase();


    bool loadKey(void);
    bool saveKeys(void);
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
    
    int  getKeyTime(int index);
    UserCaseKey* getKey(int index);
    bool insertKeyToDB(AnsiString keyname, int keytime);
    bool deleteKey(int index);
    bool modifyKey(int index, int keytime, AnsiString keyname);
    bool insertKey(int index, int keytime, AnsiString keyname);
    bool addKey(int keytime, AnsiString keyname);
    /*
       function:�ڶ�ʱ��������������
       index:���ص�ǰ���е��ǵڼ�������
       bool:true���سɹ���false���ؽ�����
    */

    bool run(int &index);

    AnsiString getName();
private:
    bool clearKeyList();     
    AnsiString   m_name;
    AnsiString   tableName;

    int          m_index;

    TList  *m_keyList;
    
    CppSQLite3DB       m_db;
};
#endif
