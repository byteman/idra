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
        TGroupBox *grp4;
        TListBox *lstStatus;
        TGroupBox *grp5;
        TMemo *mmoInfo;
        TRzStatusPane *statusName;
        TRzStatusPane *statusUC;
        TRzStatusPane *rzstspn3;
        TPopupMenu *pm1;
        TMenuItem *mmKeyAdd;
        TBitBtn *btnRecord;
        TLabel *lbl1;
        TComboBox *cbbDevice;
        TBitBtn *btnNew;
        TBitBtn *btnDel;
        TBitBtn *btnModify;
        TMenuItem *mmDelDev;
        TBitBtn *btnLearn;
        TShape *shpIdra;
        TPopupMenu *pm2;
        TMenuItem *mmKeyDel;
        TMenuItem *mmKeyAdd2;
        TMenuItem *mmMDev;
        TMenuItem *mmLearnKey;
        TMenuItem *N1;
        TMenuItem *mmLog;
        TMenuItem *mmLogClear;
        TPopupMenu *pm3;
        TMenuItem *mmUCDel;
        TMenuItem *mmUCDelAll;
        TTimer *tmr1;
    TPanel *pnl1;
    TBitBtn *btnUp;
    TBitBtn *btnDown;
    TBitBtn *btnDelKey;
    TBitBtn *btnModifyKey;
    TLabeledEdit *edtKeyTime;
        TMenuItem *N2;
        TMenuItem *mmRecUc;
        TMenuItem *mmAddUc;
        TButton *btnSave;
        TPopupMenu *pm4;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall onKeyClick(TObject *Sender);
        void __fastcall onButtonSelect(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnModifyClick(TObject *Sender);
        void __fastcall cbbDeviceChange(TObject *Sender);
        void __fastcall grpUserKeyMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall mmKeyAddClick(TObject *Sender);
        void __fastcall mmKeyDelClick(TObject *Sender);
        void __fastcall mmKeyMClick(TObject *Sender);
        void __fastcall mmKeyAdd2Click(TObject *Sender);
        void __fastcall mmAddDevClick(TObject *Sender);
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall mmDelDevClick(TObject *Sender);
        void __fastcall mmMDevClick(TObject *Sender);
        void __fastcall btnLearnClick(TObject *Sender);
        void __fastcall mmLogClearClick(TObject *Sender);
    void __fastcall btnRecordClick(TObject *Sender);
    void __fastcall lstUserCaseClick(TObject *Sender);
        void __fastcall lstUserCaseMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall mmUCDelClick(TObject *Sender);
        void __fastcall btnPlayClick(TObject *Sender);
        void __fastcall tmr1Timer(TObject *Sender);
        void __fastcall btnPauseClick(TObject *Sender);
    void __fastcall mmLearnKeyClick(TObject *Sender);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall mmIdraClick(TObject *Sender);
        void __fastcall mmRecUcClick(TObject *Sender);
        void __fastcall lstStatusClick(TObject *Sender);
        void __fastcall mmAddUcClick(TObject *Sender);
        void __fastcall btnDownClick(TObject *Sender);
        void __fastcall btnUpClick(TObject *Sender);
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall btnDelKeyClick(TObject *Sender);
        void __fastcall btnModifyKeyClick(TObject *Sender);
        void __fastcall lstStatusMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        //void __fastcall onMouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);

private:	// User declarations
    TButton* __fastcall addKeyButton(AnsiString name,TWinControl *parent,int left, int top,int w, int h);
    void __fastcall loadKeys(void);
    bool __fastcall changeDevice(AnsiString name);
    void __fastcall updateDeviceList();
    void __fastcall updateCurrDevice();
    void __fastcall updateIdraStatus(bool on);
    void __fastcall disableWork(bool yes);
    void __fastcall updateKeyStatus();
    void __fastcall enableAllKey(bool en=true);
    void __fastcall addDevice(TObject *Sender);
    void __fastcall addUserKey(TObject *Sender);
    void __fastcall delDevice(TObject *Sender);
    void __fastcall modifyDevice(TObject *Sender);
    void __fastcall learnKey(TObject *Sender);
    int  __fastcall findItem(AnsiString item);
    void __fastcall updateUserCaseList();
    void __fastcall updateUcKeyList(AnsiString &ucName);
    void __fastcall createUserCase();

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
