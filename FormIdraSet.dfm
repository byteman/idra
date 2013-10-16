object frmIdraSet: TfrmIdraSet
  Left = 455
  Top = 171
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #32418#22806#35774#22791#35774#32622
  ClientHeight = 213
  ClientWidth = 356
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object edtCom: TLabeledEdit
    Left = 128
    Top = 40
    Width = 113
    Height = 21
    EditLabel.Width = 51
    EditLabel.Height = 13
    EditLabel.Caption = #20018#21475#21495#65306' '
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
    Text = '1'
  end
  object edtBps: TLabeledEdit
    Left = 128
    Top = 88
    Width = 113
    Height = 21
    EditLabel.Width = 51
    EditLabel.Height = 13
    EditLabel.Caption = #27874#29305#29575#65306' '
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 1
    Text = '9600'
  end
  object btnAutoDectect: TBitBtn
    Left = 32
    Top = 160
    Width = 81
    Height = 33
    Caption = #26816#27979#35774#22791
    TabOrder = 2
  end
  object btnSaveIdra: TBitBtn
    Left = 136
    Top = 160
    Width = 75
    Height = 33
    Caption = #20445#23384#37197#32622
    TabOrder = 3
  end
  object btnCancel: TBitBtn
    Left = 232
    Top = 160
    Width = 75
    Height = 33
    Caption = #21462#28040
    TabOrder = 4
  end
end
