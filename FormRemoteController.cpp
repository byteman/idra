//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormRemoteController.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRemoteDev *frmRemoteDev;
//---------------------------------------------------------------------------
__fastcall TfrmRemoteDev::TfrmRemoteDev(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmRemoteDev::FormShow(TObject *Sender)
{
       isOk = false;
       devName = "";
       lblEdtName->Text = "";

}
//---------------------------------------------------------------------------
void __fastcall TfrmRemoteDev::btnOkClick(TObject *Sender)
{
        isOk = true;
        devName = lblEdtName->Text;
        this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRemoteDev::btnCancelClick(TObject *Sender)
{
        isOk = false;
        this->Close();
}
//---------------------------------------------------------------------------
