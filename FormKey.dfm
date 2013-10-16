object Form2: TForm2
  Left = 432
  Top = 138
  Width = 524
  Height = 502
  Caption = #28155#21152#25353#38190
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object grp1: TGroupBox
    Left = 0
    Top = 0
    Width = 516
    Height = 363
    Align = alClient
    Caption = 'grp1'
    TabOrder = 0
    object lst1: TListBox
      Left = 2
      Top = 15
      Width = 199
      Height = 346
      Align = alLeft
      ItemHeight = 13
      TabOrder = 0
    end
    object lst2: TListBox
      Left = 304
      Top = 15
      Width = 210
      Height = 346
      Align = alRight
      ItemHeight = 13
      TabOrder = 1
    end
    object btn1: TButton
      Left = 216
      Top = 136
      Width = 75
      Height = 25
      Caption = '>>'
      TabOrder = 2
    end
    object btn2: TButton
      Left = 216
      Top = 192
      Width = 75
      Height = 25
      Caption = '<<'
      TabOrder = 3
    end
  end
  object TGroupBox
    Left = 0
    Top = 363
    Width = 516
    Height = 105
    Align = alBottom
    TabOrder = 1
    object btnSaveKey: TButton
      Left = 136
      Top = 48
      Width = 75
      Height = 25
      Caption = #20445#23384#25353#38190
      TabOrder = 0
    end
    object btnCancelKey: TButton
      Left = 296
      Top = 48
      Width = 75
      Height = 25
      Caption = #21462#28040#20445#23384
      TabOrder = 1
    end
  end
end
