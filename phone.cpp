#include "phone.h"
#include <TimerOne.h>
#if PHONESOFTSERIAL
#include <SoftwareSerial.h>
#endif
#include <Arduino.h>
#include "UI_ArduinoPhone.h"

#if PHONESOFTSERIAL
SoftwareSerial mySerial(7, 8);
#endif

void phone::init()
{
#if PHONESOFTSERIAL
    mySerial.begin(19200);               // the Serial1 baud rate   
#else
    Serial.begin(19200);
#endif

    Serial.println("ATH");
}

void phone::msgSend()
{

    Serial.print("AT+CMGF=1\r");
    delay(100);
   // Serial.println("AT + CMGS = \"+8613425171053\"");
    Serial.print("AT + CMGS = \"");
    Serial.print(UI.msgNum);
    Serial.println("\"");

    
    delay(100);

    Serial.println(UI.msg);


    Serial.println((char)26);

    //delay(100);

    Serial.println();

}

void phone::makeCall()
{
#if PHONESOFTSERIAL
    mySerial.print("ATD + ");
#else
   // Serial.print("ATD + ");
    Serial.print("ATD");
#endif

#if PHONESOFTSERIAL
    mySerial.println(UI.callNum);
#else

    Serial.println(UI.callNum);
#endif
    //delay(100);
#if PHONESOFTSERIAL
    mySerial.println();
#else
    Serial.println();
#endif
}

bool phone::isMsg(char *str)       // check if get some message
{
    if(strCmp(8, str, "CMTI: \"SM\","))return 1;
    else return 0;
}

bool phone::isMsgSendOver()
{
    // add code here
    delay(1000);
    return 1;
}

bool phone::strCmp(unsigned char n, char *p1, const char *p2)
{
    char *pt = p1;
    while(*(pt)<'A' || *(pt)>'Z')
    {   
        pt++;
    }
    
    for(int i = 0; i<n; i++)
    {
        if(*(pt+i) == *(p2+i))continue;
        else return 0;
    }
    return 1;
}

bool phone::isCall(char *str)      // check if some one call
{
    if(strCmp(4, str, "RING"))return 1;
    return 0;
}

bool phone::isCallOver(char *str)    // check if call over
{
    // add code here
    if(strCmp(5, str, "NO CARRIER"))return 1;
    return 0;
}

// hand up a call
void phone::handUpCall()   
{
#if PHONESOFTSERIAL
    mySerial.println("ATH");
#else
    Serial.println("ATH");
#endif
}

void phone::acceptCall()
{
#if PHONESOFTSERIAL
    mySerial.println("ATA");
#else
    Serial.println("ATA");
#endif
}


phone Phone;