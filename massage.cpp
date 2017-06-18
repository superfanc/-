#include "massage.h"

massage::massage()
{
    Startup();
    PortWriteByte(PORT8251INST, 0);     //空操作？
    PortWriteByte(PORT8251INST, 0x40);  //内部复位
    PortWriteByte(PORT8251INST, 0xcf);  //方式命令字，2位停止位、无奇偶校验、字符长8位、波特率因子x64
    PortWriteByte(PORT8251INST, 0x37);  //工作命令字，接收、发送允许
}

void massage::run()
{
    receiveByte();
}


char massage::receiveByte()
{
    while (1) {

  char data;
        if (!PortReadByte(PORT8251INST, (BYTE *)&data)) {//没请求休息10ms
            Sleep(0.1);
            continue;
        }
        if (data & 0x38)       //接收出错
            continue;

        if (!(data & 2)) {       //未准备好接收
            Sleep(0.1);
            continue;
        }

        PortReadByte(PORT8251DATA, (BYTE *)&data);
        return data;
    }
}

void massage::sendByte(char toSend)
{
    char data;

    while (1) {
        PortReadByte(PORT8251INST, (BYTE *)&data);
        if (!(data & 1)) {    //未准备好写
           Sleep(0.1);
            continue;
        }

        PortWriteByte(PORT8251DATA, toSend);
        break;
    }
}
