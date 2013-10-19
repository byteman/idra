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
#include "KeyGroup.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "YbCommDevice"
#pragma link "RzPanel"
#pragma link "RzStatus"
#pragma resource "*.dfm"
TForm1 *Form1;

static bool bLearn = false;
static KeyGroup* keyGroupUser = NULL;
static KeyGroup* keyGroupStand = NULL;
static TButton*  pSelectButton = NULL;
typedef std::map<AnsiString,TButton*> TButtonMap;
static const char* gStandKeyList[] =
{
        "����","����","��ҳ","�˵�","ȷ��",
        "����","����","����","����","����",
        "�˳�","1",   "2",   "3",   "4",
        "5",   "6",   "7",   "8",   "9",
        "0",  "ɾ��"
};


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::loadKeys(void)
{
     TKeyNameList nameList;
     if(keyGroupStand->getKeyNum() == 0)
     {
         RemoteControllerMgr::get()->getStandKeyList(nameList);
         keyGroupStand->addKeyButtonGroup(nameList);
     }

     nameList.clear();
     RemoteControllerMgr::get()->listKey(nameList, TYPE_USER);
     keyGroupUser->clearButtons();
     keyGroupUser->addKeyButtonGroup(nameList);

     updateKeyStatus(); //���°���״̬
}

int  __fastcall TForm1::findItem(AnsiString item)
{
    for(int i = 0; i < cbbDevice->Items->Count; i++)
    {
       if(item == cbbDevice->Items->Strings[i])
            return i;
    }
    return -1;
}
void __fastcall TForm1::updateCurrDevice()
{
     AnsiString deviceName;

     updateDeviceList();
     if( RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName) )
     {
        cbbDevice->ItemIndex = findItem(deviceName);
        statusName->Caption      = "��ǰң����Ϊ:"+deviceName;
     }
     else statusName->Caption = "û��ѡ��ң����";
}
void __fastcall TForm1::updateDeviceList()
{
     TDeviceNameList devList;

     size_t num = RemoteControllerMgr::get()->listAllDevice(devList);
     cbbDevice->Clear();
     for(size_t i = 0; i < num ; i++)
     {
        cbbDevice->AddItem(devList.at(i), this);
     }
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
      keyGroupUser  = new KeyGroup(grpUserKey, 5,3,50,40);
      keyGroupStand = new KeyGroup(grpStandKey,5,5,50,40);

      keyGroupUser->RegisterButtonClickEvent(onKeyClick);
      keyGroupUser->RegisterButtonMouseUpEvent(onButtonSelect);

      
      keyGroupStand->RegisterButtonClickEvent(onKeyClick);
      
      if(!RemoteControllerMgr::get()->openDevice(6))
      {

          updateIdraStatus(false);
          disableWork(true);
          //Application->Terminate();
      }
      else
      {
          RemoteControllerMgr::get()->load();
          updateCurrDevice();
          updateIdraStatus(true);
          disableWork(false);
      }

      //cbbDevice->Handle


}
void __fastcall TForm1::learnKey(TObject *Sender)
{
     if(bLearn)
     {
         btnLearn->Caption = "��ʼѧϰ";
         updateKeyStatus();
     }
     else
     {
         btnLearn->Caption = "ֹͣѧϰ";
         enableAllKey(true);

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


          if(RemoteControllerMgr::get()->learnKey(btn->Caption, 5))
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
          if(!RemoteControllerMgr::get()->sendKey(btn->Caption))
          {
              ShowMessage("����ʧ��");
          }
      }
}

void __fastcall TForm1::addDevice(TObject *Sender)
{
     AnsiString newDeviceName = "";
     frmRemoteDev->ShowModal();
     newDeviceName = frmRemoteDev->devName;
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(newDeviceName))
         {
            ShowMessage("��ң�����Ѿ�������");
         }
         else
         {
            if(RemoteControllerMgr::get()->createNewCtrlDevice(newDeviceName))
            {
                
                if(!changeDevice(newDeviceName))
                {
                    ShowMessage("�л�ʧ��");
                }
                //ShowMessage("ң�����½��ɹ�");
            }
            else
            {
                ShowMessage("ң�����½�ʧ��");
            }
         }

     }
     //updateDeviceList();

}
void __fastcall TForm1::delDevice(TObject *Sender)
{

    switch (Application->MessageBox("ȷ��ɾ����ǰң����", "��ʾ", MB_OKCANCEL 
        + MB_ICONQUESTION)) {
        case IDOK: {

            break;
        }
        case IDCANCEL: {
        
            return;
            break;
        }
    }

    if(RemoteControllerMgr::get()->deleteCtrlDevice(cbbDevice->Text))
    {
        //ShowMessage("ɾ���ɹ�");
    }
    else  ShowMessage("ɾ��ʧ��");

    if(cbbDevice->Items->Count > 0)
    {
        changeDevice(cbbDevice->Items->Strings[0]);
    }

}
void __fastcall TForm1::btnDelClick(TObject *Sender)
{
     delDevice(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::modifyDevice(TObject *Sender)
{
     frmRemoteDev->ShowModal();
     if(frmRemoteDev->isOk)
     {
         if(RemoteControllerMgr::get()->existDevice(cbbDevice->Text))
         {
             if(RemoteControllerMgr::get()->updateDeviceName(cbbDevice->Text,frmRemoteDev->devName))
             {
                  changeDevice(frmRemoteDev->devName);
             }
         }


     }

}
void __fastcall TForm1::btnModifyClick(TObject *Sender)
{
      modifyDevice(Sender);
}

void __fastcall TForm1::enableAllKey(bool en)
{
    keyGroupStand->enableAll(en);
    keyGroupUser->enableAll(en);
}
void __fastcall TForm1::updateKeyStatus()
{
    TKeyNameList keyList;
    RemoteControllerMgr::get()->listKey(keyList);
    keyGroupStand->enableButtonByNameList(keyList);
    keyList.clear();
    RemoteControllerMgr::get()->listKey(keyList,TYPE_USER);      //��ȡ�Զ��尴��
    keyGroupUser->enableButtonByNameList(keyList);

}
//---------------------------------------------------------------------------
bool __fastcall TForm1::changeDevice(AnsiString name)
{
     if( !RemoteControllerMgr::get()->setCurrentCtrlDevice(name))
     {
         return false;
     }

     loadKeys(); //���ذ���GUI
     updateCurrDevice();   //����


     return true;
}

void __fastcall TForm1::cbbDeviceChange(TObject *Sender)
{
    if(!changeDevice(cbbDevice->Text))
    {
        ShowMessage("�л�ʧ��");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::grpUserKeyMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       if(Button == mbRight)
       {
           mmKeyAdd->Enabled = true;
           TPoint pt(X,Y);
           TPoint pt2 = grpUserKey->ClientToScreen(pt);
           pm1->Popup(pt2.x,pt2.y);
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyAddClick(TObject *Sender)
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
             AnsiString   deviceName;

             if(!RemoteControllerMgr::get()->getCurrentCtrlDeviceName(deviceName))
             {
                 ShowMessage("û��ѡ��ң����");
                 return;
             }
             if(keyGroupUser->existButtonName(name))
             {
                 ShowMessage("�İ����Ѿ�����");
                 return;
             }
             keyGroupUser->addKeyButton(name);
          }
     }
     else
     {
         
     }
     
}
//---------------------------------------------------------------------------
void __fastcall TForm1::onButtonSelect(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{

       if(Button == mbRight)
       {
           TPoint pt(X,Y);

           
           TControl* pCtrl = (TControl*) Sender;
           TPoint pt2 = pCtrl->ClientToScreen(pt);

           //ShortString str = "TButton";

           if(AnsiString(pCtrl->ClassName()) == AnsiString("TButton"))
           {

                pSelectButton =  (TButton*) Sender;
                pm2->Popup(pt2.x,pt2.y);
           }

       }

}
void __fastcall TForm1::mmKeyDelClick(TObject *Sender)
{

   if(pSelectButton)
   {
        ShowMessage(pSelectButton->Caption);
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyMClick(TObject *Sender)
{
    //
     if(pSelectButton)
   {
        ShowMessage(pSelectButton->Caption);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmKeyAdd2Click(TObject *Sender)
{
     mmKeyAddClick(Sender);   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmAddDevClick(TObject *Sender)
{
    addDevice(Sender);
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnNewClick(TObject *Sender)
{
     addDevice(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmDelDevClick(TObject *Sender)
{
     delDevice(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mmMDevClick(TObject *Sender)
{
      modifyDevice(Sender);  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnLearnClick(TObject *Sender)
{
      learnKey(Sender);
}
//---------------------------------------------------------------------------


