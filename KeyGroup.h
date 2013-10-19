//---------------------------------------------------------------------------

#ifndef KeyGroupH
#define KeyGroupH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vector>

//---------------------------------------------------------------------------
class KeyGroup
{
public:
        //KeyGroup(TGroupBox* container,TNotifyEvent _notify);
        KeyGroup(TGroupBox* container,  int rowNum, int colNum, int w=50, int h=40);
        void RegisterButtonClickEvent(TNotifyEvent _notify);
        void RegisterButtonMouseUpEvent(TMouseEvent _mouseNotify);
        TButton*  addKeyButton(AnsiString btnName,int left, int top,int w, int h);
        //��������Ӱ���
        TButton*  addKeyButton(AnsiString btnName);
        int       addKeyButtonGroup(const char* keyNameList[], int size);
        int       addKeyButtonGroup(std::vector<AnsiString> &nameList);
        void      clearButtons();
        TButton*  getButton(AnsiString name);
        void      enableButton(AnsiString name,bool yes);
        //����ָ�����Ƶİ�ť�����ò����б��еİ�ť
        void      enableButtonByNameList(std::vector<AnsiString> &nameList);
        void      enableAll(bool yes);
        bool      existButtonName(AnsiString name);
        int       maxKeyNum();
        int       leftKeyNum();
        int       getKeyNum();
private:
        TButton* addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h);
        TGroupBox* m_container;
        TNotifyEvent notify;
        TMouseEvent  mouseNofify;
        int      m_max_row;
        int      m_max_col;
        int      m_w;
        int      m_h;
};
#endif
