//---------------------------------------------------------------------------


#pragma hdrstop

#include "IdraDevice.h"
#include "PCOMM.h"
#include "bylogger.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

enum CMD_IDRA{
   CMD_LEARN_ACK=0x83,
   CMD_LEARN_NACK=0x8F,
   CMD_LEARN_NO_SAVE= 0x85,   //学习按键不保存
   CMD_SEND_NO_SAVE,          //发送按键编码不保存
};

IDraDevice::IDraDevice()
{
    cmd[0] = 1;
    cmd[1] = 3;
    cmd[2] = 6;
    cmd[6] = 0xD;
    cmd[7] = 0xA;

    m_ok = false;
    m_port = -1;
}
IDRA_ERR IDraDevice::openDev(int port ,int bps)
{
     int ret =  sio_open(port) ;

     if(ret == SIO_BADPORT) return IDRA_BADPORT;
     if(ret == IDRA_OPENFAIL) return IDRA_OPENFAIL;

     if( ret == SIO_OK)
     {
        m_port = port;
        m_bps  = bps;
        ret = sio_baud(m_port, bps);
        if(ret == SIO_BADPORT) return IDRA_BADPORT;
        if(ret == IDRA_OPENFAIL) return IDRA_OPENFAIL;

        return IDRA_ERR_OK;
     }

     return IDRA_UNKNOWN;

}
IDRA_ERR IDraDevice::closeDev()
{
     sio_close(m_port);

     return IDRA_ERR_OK;
}


IDRA_ERR IDraDevice::learnKey(unsigned char codec[128],int timeoutS)
{

      cmd[3] = CMD_LEARN_NO_SAVE;
      cmd[4] = 0; //固定为0，因为不保存
      cmd[5] = cmd[1] + cmd[2] + cmd[3] + cmd[4];

      if(m_port != -1)
      {
         sio_flush(m_port,2); //flush input and output;
         sio_write(m_port, cmd, 8);  //send learn cmd

         sio_SetReadTimeouts(m_port, timeoutS*1000, 100);

         int size = sio_read(m_port, cmd , 136);

         if(size == 136) //学习到了数据
         {
              memcpy(codec, cmd+8, 128);
              
              return IDRA_ERR_OK;
         }
         else if(size == 8)
         {
             if(cmd[3] == CMD_LEARN_NACK)
             {
                   return IDRA_INVALID;
             }

              
         }

         return IDRA_TIMEOUT;
         
      }
      return IDRA_OPENFAIL;
      
}
IDRA_ERR IDraDevice::sendKey(unsigned char codec[128])
{
     cmd[3] = CMD_SEND_NO_SAVE;
     cmd[4] = 0; //固定为0，因为不保存
     cmd[5] = cmd[1] + cmd[2] + cmd[3] + cmd[4];

     memcpy(cmd + 8, codec, 128);

     if(m_port != -1)
     {
         sio_flush(m_port,2); //flush input and output;
         sio_write(m_port, cmd, 136);

         sio_SetReadTimeouts(m_port, 1000, 100);

         int size = sio_read(m_port, cmd , 8);

         if(size == 8)
         {
             if(cmd[3] == CMD_LEARN_ACK)
                return IDRA_ERR_OK;
             else if(cmd[3] == CMD_LEARN_NACK)
                return IDRA_INVALID;
         }
         return IDRA_TIMEOUT;
     }
     return IDRA_OPENFAIL;
}
