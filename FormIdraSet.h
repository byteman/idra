//---------------------------------------------------------------------------

#ifndef FormIdraSetH
#define FormIdraSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmIdraSet : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *edtCom;
        TLabeledEdit *edtBps;
        TBitBtn *btnSaveIdra;
        TBitBtn *btnCancel;
    void __fastcall btnSaveIdraClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmIdraSet(TComponent* Owner);
        int port;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmIdraSet *frmIdraSet;
//---------------------------------------------------------------------------
#endif
