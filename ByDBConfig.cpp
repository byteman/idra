//---------------------------------------------------------------------------


#pragma hdrstop

#include "ByDBConfig.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#ifndef DB_DEBUG
#define DB_DBG 
#else

void __inline DB_DBG(const char *format, ...)
{
    fprintf(stderr,"%s",format);
}
#endif

ByDBConfig::~ByDBConfig()
{
      Close();
}
bool ByDBConfig::Open(std::string path)
{
    try{
        m_DB.open(path.c_str());

    }catch(CppSQLite3Exception& e){
        DB_DBG("open %s failed\n",path.c_str());
        return false;
    }
    return true;
}
bool ByDBConfig::Close()
{
    m_DB.close();
}
double ByDBConfig::ReadFloat(const string Section, const string Ident, double Default)
{
      std::string tmp_value = ReadString(Section,Ident,"none");
      double ret_value         = Default;
      if(tmp_value == "none")
      {

      }else{
          if(tryParseFloat(tmp_value,ret_value))
          {

          }
      }
      return ret_value;

}
bool ByDBConfig::tryParseFloat(const std::string& s, double& value)
{
	char temp;
	return std::sscanf(s.c_str(), "%lf%c", &value, &temp) == 1;
}
bool ByDBConfig::tryParse(const std::string& s, int& value)
{
	char temp;
	return std::sscanf(s.c_str(), "%d%c", &value, &temp) == 1;
}
int    ByDBConfig::ReadInteger(const string Section, const string Ident, int Default)
{
      std::string tmp_value = ReadString(Section,Ident,"none");
      int ret_value         = Default;
      if(tmp_value == "none")
      {

      }else{
          if(tryParse(tmp_value,ret_value))
          {

          }
      }
      return ret_value;

}

string ByDBConfig::ReadString(const string Section, const string Ident, const string Default)
{
  std::string ret_string = Default;
  try{
    m_lastSql.format("select * from %s where key =%Q",Section.c_str(),Ident.c_str());
    
    CppSQLite3Query qry = m_DB.execQuery(m_lastSql);
    if (!qry.eof()) {
       ret_string = qry.fieldValue("value");
    }
    qry.finalize();
  }catch (CppSQLite3Exception& e) {
     DB_DBG("error:  %s\n",e.errorCodeAsString(e.errorCode()));
  }
  return ret_string;

}
bool   ByDBConfig::WriteFloat(const string Section, const string Ident, double Value,int dot_cont)
{
       char tmp[32] = {0,};
       snprintf(tmp,32,"%d",Value);
       switch(dot_cont)
       {
          case 0:
                snprintf(tmp,32,"%d",(int)Value);
                break;
          case 1:
                snprintf(tmp,32,"%0.1f",Value);
                break;
          case 2:
                snprintf(tmp,32,"%0.2f",Value);
                break;
          case 3:
                snprintf(tmp,32,"%0.3f",Value);
                break;
          case 4:
                snprintf(tmp,32,"%0.4f",Value);
                break;
          case 5:
                snprintf(tmp,32,"%0.5f",Value);
                break;
          default:
                snprintf(tmp,32,"%0.2f",Value);
                break;

       }
       return WriteString(Section,Ident,tmp);

}
bool   ByDBConfig::WriteInteger(const string Section, const string Ident, int Value)
{
       char tmp[32] = {0,};
       snprintf(tmp,32,"%d",Value);
       return WriteString(Section,Ident,tmp);
}
bool   ByDBConfig::WriteString(const string Section, const string Ident, const string Value)
{
      bool ok = false;
      if(!SectionExists(Section))
      {
            if(!CreateTable(Section)) return false;
      }

      if(ExistKey(Section,Ident))
      {
        return UpdateValue(Section,Ident,Value);
      }else{
        return AddValue(Section,Ident,Value);
      }

}
bool   ByDBConfig::WriteBool(const string Section, const string Ident, bool Value)
{
      return WriteString(Section,Ident,Value?"1":"0");

}
bool   ByDBConfig::ReadBool(const string Section, const string Ident, bool Default)
{
      std::string tmp_value = ReadString(Section,Ident,"none");
      int ret_value         = Default;
      if(tmp_value == "none")
      {

      }else{
          if(tryParse(tmp_value,ret_value))
          {

          }
      }
      return (ret_value!=0)?true:false;

}
bool   ByDBConfig::ValueExists(const string Section, const string Ident)
{


}
bool   ByDBConfig::SectionExists(const string Section)
{
     return m_DB.tableExists(Section.c_str());

}
void ByDBConfig::formatError(CppSQLite3Exception& e)
{

     m_lastErr = std::string(e.errorCodeAsString(e.errorCode())) + " : "  + std::string(m_lastSql.data());
}
bool ByDBConfig::AddValue(const string Section,const string Ident, const string Value)
{
    bool ret = false;

    m_lastSql.format("Insert or rollback into %s (key,value) values(%Q,%Q);", \
                        Section.c_str(),Ident.c_str(),Value.c_str());
    try{
        int rows = m_DB.execDML(m_lastSql);
        if (rows) {
          ret = true;
        }
    }
    catch (CppSQLite3Exception& e) {
      ret = false;
      formatError(e);
      DB_DBG("%s",m_lastErr.c_str());
    }
    
    return ret;

}
bool ByDBConfig::UpdateValue(const string Section,const string Ident, const string Value)
{
        bool ret = false;


    m_lastSql.format("Update or rollback %s SET value=%Q where key=%Q;", \
                        Section.c_str(),Value.c_str(),Ident.c_str());
    try{
        int rows = m_DB.execDML(m_lastSql);
        if (rows) {
          ret = true;
        }
    }
    catch (CppSQLite3Exception& e) {
      ret = false;
      DB_DBG("%s",m_lastErr.c_str());
    }
    
    return ret;
}
bool ByDBConfig::ExistKey(const string Section,const string Ident)
{
  bool find = false;
  try{

    m_lastSql.format("select * from %s where key =%Q",Section.c_str(),Ident.c_str());
    
    CppSQLite3Query qry = m_DB.execQuery(m_lastSql);
    if (!qry.eof()) {
       find = true;
    }
    qry.finalize();
  }catch (CppSQLite3Exception& e) {
     DB_DBG("error:  %s\n",e.errorCodeAsString(e.errorCode()));
  }
  return find;
}
bool ByDBConfig::CreateTable(const std::string& table)
{
    
     try{
            m_lastSql.format("CREATE TABLE  if not exists %s (key TEXT NOT NULL, value TEXT NOT NULL); CREATE INDEX 'key' on %Q (key ASC);",table.c_str(),table.c_str());
            int rows = m_DB.execDML(m_lastSql);
            return true;
      }
      catch (CppSQLite3Exception& e) {
              formatError(e);
      }
      return false;
}

bool   ByDBConfig::setProperty(const std::string& name, const std::string& value)
{
     if(name=="transation")
     {
        if(value=="begin")
        {
             m_DB.execDML("begin transation");

        }else if(value=="stop")
        {
             m_DB.execDML("commit transation");

        }
     }

}
