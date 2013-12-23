//---------------------------------------------------------------------------


#pragma hdrstop

#include "KeyGroup.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


KeyGroup::KeyGroup(TGroupBox* container,int rowNum, int colNum, int w, int h):
        notify(NULL),
        mouseNofify(NULL)
{

       m_max_row = rowNum;
       m_max_col = colNum;
       m_w = w;
       m_h = h;
       m_container = container;

}
void KeyGroup::RegisterButtonClickEvent(TNotifyEvent _notify)
{
   notify  = _notify;
}
void KeyGroup::RegisterButtonMouseUpEvent(TMouseEvent _mouseNotify)
{
    mouseNofify = _mouseNotify;
}
TButton* KeyGroup::addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h, bool enable )
{
      TButton* btn = new TButton(this);

      btn->Parent = m_container;
      
      btn->Width  = w;
      btn->Height = h;


      btn->Left =  left;
      btn->Top =   top;
      btn->Caption = name;

      btn->OnClick   =  notify;
      btn->OnMouseUp =  mouseNofify;

      btn->Show();
      btn->Enabled = enable;
      return btn;
}
TButton*  KeyGroup::addKeyButton(AnsiString btnName,bool enable)
{
       int left ,top;
       int w = m_w;
       int h = m_h;
       int r = m_max_row;
       int c = m_max_col;
       int left_align = (m_container->Width  - (r * w) )/2 ;
       int top_align  = (m_container->Height - (c * h) )/2 ;
       int i = m_container->ControlCount;
       return addKeyButton(btnName, m_container, left_align +(i%r)*w, top_align +(i/r)*h,w,h,enable);
}
int       KeyGroup::maxKeyNum()
{
       return m_max_col*m_max_row;
}
int       KeyGroup::leftKeyNum()
{
       return maxKeyNum() - getKeyNum();
}

int       KeyGroup::getKeyNum()
{
       return m_container->ControlCount;
}
int       KeyGroup::addKeyButtonGroup(const char* keyNameList[], int size)
{
        int count = 0;
        for(int i = 0; i < size; i++)
        {
            if(addKeyButton(keyNameList[i]))
            {
               count++;
            }
        }
        return count;

}
int      KeyGroup::addKeyButtonGroup(std::vector<AnsiString> &nameList)
{
       int count = 0;
       for(size_t i = 0; i < nameList.size(); i++)
       {
            if(addKeyButton(nameList[i]))
            {
               count++;
            }
       }
       return count;
}
void      KeyGroup::enableButtonByNameList(std::vector<AnsiString> &nameList)
{
     //
    for(size_t i = 0; i < m_container->ControlCount; i++)
    {
        bool find = false;
        TButton* pBtn   =  (TButton*)m_container->Controls[i];
        for(size_t j = 0; j < nameList.size(); j++)
        {

            AnsiString key1 =  pBtn->Caption;
            AnsiString key2 =  nameList.at(j);
            if( key1 == key2)
            {

                 find = true;
                 break;
            }
        }
        //TButton* pBtn   =  (TButton*)m_container->Controls[i];
        pBtn->Enabled = find;

    }
}
void      KeyGroup::enableAll(bool yes)
{
    for(size_t i = 0; i < m_container->ControlCount; i++)
    {
        TButton* pBtn   =  (TButton*)m_container->Controls[i];
        pBtn->Enabled = yes;
     }
}
bool      KeyGroup::existButtonName(AnsiString name)
{
    for(size_t i = 0; i < m_container->ControlCount; i++)
    {
        TButton* pBtn   =  (TButton*)m_container->Controls[i];
        if(pBtn->Caption == name)
                return true;
    }

    return false;
}
//fix me 这个函数有点问题.
void      KeyGroup::clearButtons()
{

    while(m_container->ControlCount)
    {
         m_container->Controls[0]->Parent = NULL;
    }

}
