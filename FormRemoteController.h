//---------------------------------------------------------------------------

#ifndef FormRemoteControllerH
#define FormRemoteControllerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmRemoteDev : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *grp1;
        TLabeledEdit *lblEdtName;
        TBitBtn *btnOk;
        TBitBtn *btnCancel;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmRemoteDev(TComponent* Owner);
        bool isOk;
        AnsiString devName;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRemoteDev *frmRemoteDev;
//---------------------------------------------------------------------------
#endif
