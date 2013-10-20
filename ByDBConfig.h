//---------------------------------------------------------------------------

#ifndef ByDBConfigH
#define ByDBConfigH
#include "ByConfig.h"
#include "CppSQLite3.h"
//---------------------------------------------------------------------------
class ByDBConfig:public TByConfigImpl
{
public:
      bool Open(std::string path);
      bool Close();
      
      double ReadFloat(const string Section, const string Ident, double Default);
      int    ReadInteger(const string Section, const string Ident, int Default);
      string ReadString(const string Section, const string Ident, const string Default);
      bool   WriteFloat(const string Section, const string Ident, double Value,int dot_cont=2);
      bool   WriteInteger(const string Section, const string Ident, int Value);
      bool   WriteString(const string Section, const string Ident, const string Value);
      bool   WriteBool(const string Section, const string Ident, bool Value);
      bool   ReadBool(const string Section, const string Ident, bool Default);
      bool   ValueExists(const string Section, const string Ident);
      bool   SectionExists(const string Section);
      bool   setProperty(const std::string& name, const std::string& value);

      ~ByDBConfig();
private:
      bool CreateTable(const std::string& table);
      void formatError(CppSQLite3Exception& e);
      bool tryParse(const std::string& s, int& value);
      bool tryParseFloat(const std::string& s, double& value);
      bool ExistKey(const string Section,const string Ident);
      bool UpdateValue(const string Section,const string Ident, const string Value);
      bool AddValue(const string Section,const string Ident, const string Value);
      CppSQLite3DB m_DB;
      std::string  m_lastErr;
      CppSQLite3Buffer m_lastSql;

};
#endif
