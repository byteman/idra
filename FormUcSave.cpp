//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormUcSave.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TOKBottomDlg *OKBottomDlg;
//---------------------------------------------------------------------
__fastcall TOKBottomDlg::TOKBottomDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TOKBottomDlg::FormShow(TObject *Sender)
{
      //
      save = false;
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg::OKBtnClick(TObject *Sender)
{
       save = true;
       Close();
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg::CancelBtnClick(TObject *Sender)
{
      save = false;
      Close();
}
//---------------------------------------------------------------------------

