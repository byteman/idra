//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "FormIdraSet.h"
#include "FormKey.h"
#include "IdraDevice.h"
#include "CppSQLite3.h"
#include "RemoteControllerMgr.h"
#include "FormRemoteController.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "YbCommDevice"
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma resource "*.dfm"
TForm1 *Form1;

static bool bLearn = false;
static RemoteController* gDev = NULL;

static RemoteControllerMgr rcmgr;

typedef std::map<AnsiString,TButton*> TButtonMap;
static const char* gStandKeyList[] =
{
        "����","����","��ҳ","�˵�","ȷ��",
        "����","����","����","����","����",
        "�˳�","1",   "2",   "3",   "4",
        "5",   "6",   "7",   "8",   "9",
        "0",  "ɾ��"
};
#define STAND_KEY_NUM (sizeof(gStandKeyList)/sizeof(char*))
static TButtonMap buttonList;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::loadKeys(void)
{
       TKeyNameList keyList;

       int left ,top;
       int w = 60;
       int h = 50;
       int n = 5;
       int left_align = (grpStandKey->Width  - (n*w) )/2 ;
       int top_align  = (grpStandKey->Height - (n*h) )/2 ;
       for(int i = 0; i < STAND_KEY_NUM; i++)
       {
             addKeyButton(gStandKeyList[i], grpStandKey, left_align +(i%n)*w, top_align +(i/n)*h,w,h);
       }
}

void __fastcall TForm1::updateDeviceStatus()
{
     RemoteController* pDev = rcmgr.getCurrentCtrlDevice();
     if(pDev)
     {
        cbbDevice->Text = pDev->m_name;
        statusName->Caption      = "��ǰң����Ϊ:"+pDev->m_name;
     }
     else statusName->Caption = "û��ѡ��ң����";
}
void __fastcall TForm1::updateDeviceList()
{
     TDeviceNameList devList;

     size_t num = rcmgr.listAllDevice(devList);
     cbbDevice->Clear();
     for(size_t i = 0; i < num ; i++)
     {
        cbbDevice->AddItem(devList.at(i), this);
     }
     updateDeviceStatus();

}

void __fastcall TForm1::updateIdraStatus(bool on)
{
     if(on)
     {
        shpIdra->Brush->Color = clGreen;

     }
     else
     {
        shpIdra->Brush->Color = clRed;
        statusName->Caption = "�����豸��ʧ��";
     }
}
void __fastcall TForm1::disableWork(bool yes)
{
     btnNew->Enabled = !yes;
     btnDel->Enabled = !yes;
     btnModify->Enabled = !yes;
     btnLearn->Enabled = !yes;
     btnPlay->Enabled = !yes;
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
      if(!rcmgr.openDevice(6))
      {
         
          updateIdraStatus(false);
          disableWork(true);
          //Application->Terminate();
      }
      else
      {
          rcmgr.load();
          updateDeviceList();
          loadKeys();
          updateIdraStatus(true);
          disableWork(false);
      }


}
//---------------------------------------------------------------------------


void __fastcall TForm1::mmIdraClick(TObject *Sender)
{
    frmIdraSet->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAddKeyClick(TObject *Sender)
{
      Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnLearnClick(TObject *Sender)
{
     if( bLearn)
     {
         btnLearn->Caption = "��ʼѧϰ";

         updateKeyStatus();
     }
     else
     {
         btnLearn->Caption = "ֹͣѧϰ";
         enableAllKey();
     }
     bLearn = !bLearn;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::onKeyClick(TObject *Sender)
{
      TButton* btn  = (TButton*)Sender;  
      if(bLearn)
      {
          unsigned char codec[128];

          btn->Enabled = false;


          if(rcmgr.learnKey(btn->Caption, 5))
          {
             ShowMessage("ѧϰ�ɹ�");
          }
          else
          {
             ShowMessage("ѧϰʧ��");
          }
          btn->Enabled = true;
      }
      else
      {
          if(!rcmgr.sendKey(btn->Caption))
          {
              ShowMessage("����ʧ��");
          }
      }
}
//---------------------------------------------------------------------------
TButton* __fastcall TForm1::addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h)
{

      
      TButton* btn = new TButton(this);

      btn->Parent = parent;
      
      btn->Width  = w;
      btn->Height = h;


      btn->Left =  left;
      btn->Top =   top;
      btn->Caption = name;

      btn->OnClick =  onKeyClick;
      btn->Show();

      buttonList[name] = btn;

      return btn;
}

void __fastcall TForm1::btnNewClick(TObject *Sender)
{
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(rcmgr.existDevice(frmRemoteDev->devName))
         {
            ShowMessage("��ң�����Ѿ�������");
         }
         else
         {
            if(rcmgr.createNewCtrlDevice(frmRemoteDev->devName))
            {
                cbbDevice->Text = frmRemoteDev->devName;
                ShowMessage("ң�����½��ɹ�");
            }
            else
            {
                ShowMessage("ң�����½�ʧ��");
            }
         }

     }
     updateDeviceList();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDelClick(TObject *Sender)
{
   //
    if(rcmgr.deleteCtrlDevice(cbbDevice->Text))
    {
        ShowMessage("ɾ���ɹ�");
    }
    else  ShowMessage("ɾ��ʧ��");

    updateDeviceList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnModifyClick(TObject *Sender)
{
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(rcmgr.existDevice(cbbDevice->Text))
         {
            rcmgr.updateDeviceName(cbbDevice->Text,frmRemoteDev->devName);
         }


     }
     updateDeviceList();
}

void __fastcall TForm1::enableAllKey(bool en)
{

     for(size_t i = 0; i < STAND_KEY_NUM; i++)
    {

       // buttonList[gStandKeyList[i]]->Enabled = en;

    }
    TButtonMap::iterator it;
    for(it=buttonList.begin();it!=buttonList.end();++it)
    {
         it->second->Enabled = en;
    }
}
void __fastcall TForm1::updateKeyStatus()
{
    TKeyNameList keyList;
    rcmgr.getCurrentCtrlDevice()->listKey(keyList);

    for(size_t i = 0; i < STAND_KEY_NUM; i++)
    {
        bool find = false;
        for(size_t j = 0; j < keyList.size(); j++)
        {
            AnsiString key1 =  gStandKeyList[i] ;
            AnsiString key2 =  keyList.at(j);
            if( key1 == key2)
            {

                 find = true;
                 break;
            }
        }

        buttonList[gStandKeyList[i]]->Enabled = find;

    }
    keyList.clear();
    rcmgr.getCurrentCtrlDevice()->listKey(keyList,TYPE_USER);      //��ȡ�Զ��尴��


}
//---------------------------------------------------------------------------


void __fastcall TForm1::cbbDeviceChange(TObject *Sender)
{
    //
     if( rcmgr.setCurrentCtrlDevice(cbbDevice->Text))
     {

         //ShowMessage("�л��ɹ�");

         TKeyNameList keyList;
         rcmgr.getCurrentCtrlDevice()->listKey(keyList);
         cbbDevice->Text = rcmgr.getCurrentCtrlDevice()->m_name;
         for(size_t i = 0; i < keyList.size();i++)
         {
             mmoInfo->Lines->Add(keyList.at(i));
         }


     }
     else
     {
         ShowMessage("�л�ʧ��");
     }

     updateDeviceStatus();
     updateKeyStatus();
       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnAddUserKeyMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       //
      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::grpUserKeyMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       if(Button == mbRight)
       {
           TPoint pt(X,Y);
           TPoint pt2 = grpUserKey->ClientToScreen(pt);
           pm1->Popup(pt2.x,pt2.y);
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
     //

     Form2->ShowModal();
     if(Form2->ret)
     {
          AnsiString name = Form2->keyName;
          if(name.Length() == 0)
          {
              ShowMessage("�����밴������");
          }
          else
          {
             //rcmgr.getCurrentCtrlDevice()->addKey()
             TKeyNameList keyList;
             RemoteController* pDev = rcmgr.getCurrentCtrlDevice();
             if(pDev == NULL)
             {
                 ShowMessage("û��ѡ��ң����");
                 return;
             }
             pDev->listKey(keyList,TYPE_USER);


             size_t i = grpUserKey->ControlCount;
             int left ,top;
             int w = 60;
             int h = 50;
             int n = 5;
             int left_align = (grpUserKey->Width  - (n*w) )/2 ;
             int top_align  = (grpUserKey->Height - (3*h) )/2 ;



             TButton* btn = addKeyButton(name, grpUserKey, left_align +(i%n)*w, top_align +(i/n)*h,w,h);
             //btn->Enabled = false;

          }
     }
     else
     {
         
     }
     
}
//---------------------------------------------------------------------------

