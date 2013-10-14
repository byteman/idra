object Form1: TForm1
  Left = 99
  Top = 88
  Width = 1115
  Height = 620
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lst1: TListBox
    Left = 288
    Top = 152
    Width = 193
    Height = 289
    ItemHeight = 13
    TabOrder = 0
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
    Left = 920
    Top = 88
  end
end
