//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "YbCommDevice.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include "RzStatus.hpp"
#include "RemoteController.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TYbCommDevice *com1;
        TMainMenu *mm1;
        TMenuItem *mmIdra;
        TMenuItem *mmCtrl;
        TMenuItem *mmUserCase;
        TGroupBox *grp2;
        TGroupBox *grp1;
        TRzStatusBar *rzstsbr1;
        TGroupBox *grpRemoter;
        TGroupBox *grpStandKey;
        TGroupBox *grpUserKey;
        TMenuItem *mmAddDev;
        TListBox *lstUserCase;
        TGroupBox *grp3;
        TBitBtn *btnPlay;
        TBitBtn *btnPause;
        TBitBtn *btnResume;
        TGroupBox *grp4;
        TListBox *lstStatus;
        TGroupBox *grp5;
        TMemo *mmoInfo;
        TRzStatusPane *statusName;
        TRzStatusPane *rzstspn2;
        TRzStatusPane *rzstspn3;
        TPopupMenu *pm1;
        TMenuItem *N1;
        TMenuItem *mmAddUC;
        TBitBtn *btnRecord;
        TLabel *lbl1;
        TComboBox *cbbDevice;
        TBitBtn *btnNew;
        TBitBtn *btnDel;
        TBitBtn *btnModify;
        TMenuItem *mmAddKey;
        TBitBtn *btnLearn;
        TShape *shpIdra;
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall mmIdraClick(TObject *Sender);
        void __fastcall mmAddKeyClick(TObject *Sender);
        void __fastcall btnLearnClick(TObject *Sender);
        void __fastcall onKeyClick(TObject *Sender);
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall btnDelClick(TObject *Sender);
    void __fastcall btnModifyClick(TObject *Sender);
        void __fastcall cbbDeviceChange(TObject *Sender);
        void __fastcall btnAddUserKeyMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall grpUserKeyMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N1Click(TObject *Sender);

private:	// User declarations
    TButton* __fastcall addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h);
    void __fastcall loadKeys(void);
    void __fastcall updateDeviceList();
    void __fastcall updateDeviceStatus();
    void __fastcall updateIdraStatus(bool on);
    void __fastcall disableWork(bool yes);
    void __fastcall updateKeyStatus();
    void __fastcall enableAllKey(bool en=true);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
