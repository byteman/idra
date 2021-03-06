//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("FormMain.cpp", Form1);
USEFORM("FormIdraSet.cpp", frmIdraSet);
USEFORM("FormKey.cpp", Form2);
USEFORM("FormRemoteController.cpp", frmRemoteDev);
USEFORM("FormUcSave.cpp", OKBottomDlg);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TfrmIdraSet), &frmIdraSet);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TfrmRemoteDev), &frmRemoteDev);
                 Application->CreateForm(__classid(TOKBottomDlg), &OKBottomDlg);
                 Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
