object Form1: TForm1
  Left = 182
  Top = 24
  Width = 1025
  Height = 728
  Caption = #36965#25511#22120#27169#25311#22120'V1.0'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mm1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object grp2: TGroupBox
    Left = 606
    Top = 0
    Width = 403
    Height = 651
    Align = alRight
    Caption = #29992#20363#27979#35797#65306
    TabOrder = 0
    object grp3: TGroupBox
      Left = 2
      Top = 15
      Width = 399
      Height = 105
      Align = alTop
      TabOrder = 0
      object btnPlay: TBitBtn
        Left = 24
        Top = 32
        Width = 75
        Height = 25
        Caption = #36816#34892#29992#20363
        TabOrder = 0
        OnClick = btnPlayClick
      end
      object btnPause: TBitBtn
        Left = 134
        Top = 32
        Width = 75
        Height = 25
        Caption = #26242#20572
        TabOrder = 1
      end
      object btnResume: TBitBtn
        Left = 272
        Top = 32
        Width = 75
        Height = 25
        Caption = #32487#32493
        TabOrder = 2
      end
      object btnRecord: TBitBtn
        Left = 24
        Top = 72
        Width = 75
        Height = 25
        Caption = #24405#21046#29992#20363
        TabOrder = 3
      end
    end
    object grp4: TGroupBox
      Left = 2
      Top = 120
      Width = 399
      Height = 289
      Align = alTop
      Caption = #25191#34892#27493#39588#65306
      TabOrder = 1
      object lstStatus: TListBox
        Left = 2
        Top = 15
        Width = 395
        Height = 272
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
    end
    object grp5: TGroupBox
      Left = 2
      Top = 409
      Width = 399
      Height = 240
      Align = alClient
      Caption = #24037#20316#35760#24405#65306
      TabOrder = 2
      object mmoInfo: TMemo
        Left = 2
        Top = 15
        Width = 395
        Height = 223
        Align = alClient
        TabOrder = 0
      end
    end
  end
  object grp1: TGroupBox
    Left = 0
    Top = 0
    Width = 249
    Height = 651
    Align = alLeft
    Caption = #29992#20363#21015#34920
    TabOrder = 1
    object lstUserCase: TListBox
      Left = 2
      Top = 15
      Width = 245
      Height = 634
      Align = alClient
      ItemHeight = 13
      Items.Strings = (
        #27979#35797#29992#20363'1'
        #27979#35797#29992#20363'2'
        #27979#35797#29992#20363'3'
        #27979#35797#29992#20363'4'
        #27979#35797#29992#20363'5')
      ScrollWidth = 1
      TabOrder = 0
    end
  end
  object rzstsbr1: TRzStatusBar
    Left = 0
    Top = 651
    Width = 1009
    Height = 19
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    TabOrder = 2
    object rzstspn1: TRzStatusPane
      Left = 0
      Top = 0
      Width = 249
      Height = 19
      Align = alLeft
      Caption = #24403#21069#36965#25511#22120#65306'ZCX100'
    end
    object rzstspn2: TRzStatusPane
      Left = 249
      Top = 0
      Width = 368
      Height = 19
      Align = alLeft
      Caption = #24403#21069#29992#20363#65306'UserCase1'
    end
    object rzstspn3: TRzStatusPane
      Left = 617
      Top = 0
      Width = 376
      Height = 19
      Align = alLeft
      Caption = #25191#34892#32467#26524':'
    end
  end
  object grpRemoter: TGroupBox
    Left = 249
    Top = 0
    Width = 357
    Height = 651
    Align = alClient
    Caption = #36965#25511#22120#21517#31216#65306
    TabOrder = 3
    object lbl1: TLabel
      Left = 16
      Top = 43
      Width = 84
      Height = 13
      Caption = #36873#25321#36965#25511#22120':       '
    end
    object grpStandKey: TGroupBox
      Left = 2
      Top = 129
      Width = 353
      Height = 336
      Align = alBottom
      Caption = #26631#20934#25353#38190#65306
      TabOrder = 0
    end
    object grpUserKey: TGroupBox
      Left = 2
      Top = 465
      Width = 353
      Height = 184
      Align = alBottom
      Caption = #33258#23450#20041#25353#38190#65306
      TabOrder = 1
    end
    object cbbDevice: TComboBox
      Left = 104
      Top = 40
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = #36965#25511#22120'1'
      OnDropDown = cbbDeviceDropDown
      Items.Strings = (
        #36965#25511#22120'1'
        #36965#25511#22120'2'
        #36965#25511#22120'3')
    end
    object btn23: TBitBtn
      Left = 280
      Top = 40
      Width = 73
      Height = 25
      Caption = #20999#25442#36965#25511#22120
      TabOrder = 3
      OnClick = btn23Click
    end
    object btnNew: TBitBtn
      Left = 24
      Top = 88
      Width = 75
      Height = 25
      Caption = #26032#24314#36965#25511#22120
      TabOrder = 4
      OnClick = btnNewClick
    end
    object btnDel: TBitBtn
      Left = 112
      Top = 88
      Width = 75
      Height = 25
      Caption = #21024#38500#36965#25511#22120
      TabOrder = 5
      OnClick = btnDelClick
    end
    object btnModify: TBitBtn
      Left = 192
      Top = 88
      Width = 75
      Height = 25
      Caption = #20462#25913
      TabOrder = 6
      OnClick = btnModifyClick
    end
  end
  object btn24: TBitBtn
    Left = 528
    Top = 88
    Width = 75
    Height = 25
    Caption = #24320#22987#23398#20064
    TabOrder = 4
    OnClick = btn24Click
  end
  object com1: TYbCommDevice
    PortNo = 2
    Baud = br115200
    ByteSize = 8
    InBufSize = 8192
    OutBufSize = 8192
    HwInSize = 1200
    HwOutSize = 1200
    QueueSize = 16
    PackageSize = 4096
    Left = 880
    Top = 80
  end
  object mm1: TMainMenu
    Left = 968
    Top = 80
    object mmIdra: TMenuItem
      Caption = #32418#22806#35774#22791#35774#32622
      OnClick = mmIdraClick
    end
    object mmCtrl: TMenuItem
      Caption = #36965#25511#22120#31649#29702
      object mmAddDev: TMenuItem
        Caption = #28155#21152#36965#25511#22120
      end
      object mmAddKey: TMenuItem
        Caption = #28155#21152#25353#38190
        OnClick = mmAddKeyClick
      end
    end
    object mmUserCase: TMenuItem
      Caption = #29992#20363#31649#29702
      object mmAddUC: TMenuItem
        Caption = #28155#21152#29992#20363
      end
    end
  end
  object pm1: TPopupMenu
    Left = 936
    Top = 80
    object N1: TMenuItem
      Caption = #28155#21152#33258#23450#38190
    end
  end
end
