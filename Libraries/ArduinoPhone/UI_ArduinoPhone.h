/*
  UI_ArduinoPhone.h

  Author:Loovee

  2013-9-10
  
  The MIT License (MIT)
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
#ifndef _UI_ARDUINOPHONE_H_
#define _UI_ARDUINOPHONE_H_

#include "UI_ArduinoPhone_dfs.h"
class UI_ArduinoPhone
{
    private:
    char Slide_Det;
    char Slide_Dir;
    char Button_Det;
    int  Button_x,Button_y;

    int touch_status;
    int touch_x,touch_y;
    int touch_dir;
    int touch_time;
    int touch_release; 

    private:
    void TouchDrvInit();
    int  GetSlideDirect(int x1,int y1,int x2,int y2);
    void TouchTimerIrq(int in_button,int in_x,int in_y);

    public:
    unsigned char state;
    unsigned char state_buf;
    
    unsigned char msgReadCodeMax;
    unsigned char msgReadCodeNow;

    char msg[71];
    unsigned char msgCount;
    unsigned char msgNumCount;
    unsigned char callCount;
    char callNum[20];
    char msgNum[20];
    
    char msgReadNum[20];
    char msgReadTime[30];
    char msgReadTxt[70];
    char msgReadNewMsg;
    char state_msg; //0:input phone number   1: input msg txt
    
    // time date
    unsigned char second;
    unsigned char minute;
    unsigned char minute_buf;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned char year;

    private:
    void drawButton(int x, int y);                  // draw a single button, x,y: station
    void drawButtonNumber();                        // draw the number on the button
    void drawButtonAbc();                           // draw the letters on the button

    public:

    void init();
#if I2CUART
    void I2C_Uart(char *p);
#endif
    
    void msgAdd(char let);                          // input msg text
    void msgAdd(char let, unsigned int color);      // input msg test with color
    void msgDel();                                  // delet a letter
    void msgNumAdd(char n);
    void msgNumDel();
    void msgShowCount();                            // show num of msg letter

    void callAdd(unsigned char num);                // input call number
    void callDel();                                 // delet call number

    unsigned char getTouch(unsigned char *type);    // get touch type

    void drawDialogBox();                           // draw the dialog box
    
    void drawMsgDialogBox();                        // draw the msg dialogbox

    void showPageKB();                              // show
    void showMsg();                                 // show msg about
    void showCall();                                // show call about

    void drawButtons();                             // draw all buttons

    bool isTouch();                                 // if something touch
    int  touchMainPage();                           // main page touch, return 1: call return 2 msg
    void showMainPage();                            // show main page
    
    void drawReadMsgPage();
    void drawReadMsg();
    void drawReadMsgTxt();
    bool getReadMsgTimeAndFrom(char * src1,char * num, char * time);
    unsigned char getReadMsgMsg(char * src1);
    bool getTouchRect(int XL, int YU, int XR, int YD);
    
    unsigned char getMsgInputState();
    
    void drawTimeDate(int x, int y);
    void getTime();

};

extern UI_ArduinoPhone UI;
#endif
