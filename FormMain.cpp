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

static const char* gStandKeyList[] =
{
        "����","����","��ҳ","�˵�","ȷ��",
        "����","����","����","����","����",
        "�˳�","1",   "2",   "3",   "4",
        "5",   "6",   "7",   "8",   "9",
        "0",  "ɾ��"
};
#define STAND_KEY_NUM (sizeof(gStandKeyList)/sizeof(char*))

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

//
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{


      //db.execDML("create table tbl1 id(Text)");

      if(!rcmgr.openDevice(6))
      {
          ShowMessage("�����豸��ʧ��");
          //Application->Terminate();
      }
     cbbDevice->Clear();

     rcmgr.load();

     for(int i = 0; i < rcmgr.m_device_list.size();i++)
     {
        cbbDevice->AddItem(rcmgr.m_device_list.at(i), this);
     }

     loadKeys();

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





void __fastcall TForm1::btn24Click(TObject *Sender)
{
     if( bLearn)
     {
         btn24->Caption = "��ʼѧϰ";
     }
     else
     {
         btn24->Caption = "ֹͣѧϰ";
     }
     bLearn = !bLearn;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnPlayClick(TObject *Sender)
{
      //
      char buf[10]= {0x11,0x33,0x55,0x77};
      AnsiString text = buf;

}
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
void __fastcall TForm1::addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h)
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

      
}

void __fastcall TForm1::btn23Click(TObject *Sender)
{

     if( rcmgr.setCurrentCtrlDevice(cbbDevice->Text))
     {

         ShowMessage("�л��ɹ�");

         TKeyNameList keyList;
         rcmgr.getCurrentCtrlDevice()->listKey(keyList);

         for(size_t i = 0; i < keyList.size();i++)
         {
             mmoInfo->Lines->Add(keyList.at(i));
         }

        
     }
}
//---------------------------------------------------------------------------





void __fastcall TForm1::btnNewClick(TObject *Sender)
{
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(rcmgr.existDeviceName(frmRemoteDev->devName))
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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDelClick(TObject *Sender)
{
   //     
}
//---------------------------------------------------------------------------

