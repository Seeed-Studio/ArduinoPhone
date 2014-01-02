#include "UI_ArduinoPhone.h"
#include "UI_ArduinoPhone.h"
#include <SeeedTouchScreen.h>
#include <stdio.h>
#include <Wire.h>
#include <Arduino.h>
#include "UI_ArduinoPhone_dfs.h"

#include <TFT.h>
#include <SPI.h>

TouchScreen ts = TouchScreen(XP, YP, XM, YM);

const short __xyButton[12][2] PROGMEM = {
    {KB_X1, KB_Y1},{KB_X2, KB_Y1},{KB_X3, KB_Y1},
    {KB_X1, KB_Y2},{KB_X2, KB_Y2},{KB_X3, KB_Y2},
    {KB_X1, KB_Y3},{KB_X2, KB_Y3},{KB_X3, KB_Y3},
    {KB_X1, KB_Y4},{KB_X2, KB_Y4},{KB_X3, KB_Y4}

};

void UI_ArduinoPhone::drawButton(int x, int y)
{
    unsigned char up1[3]    = {KB_BUTTON_COLOR_UPR1, KB_BUTTON_COLOR_UPG1, KB_BUTTON_COLOR_UPB1};
    unsigned char down1[3]  = {KB_BUTTON_COLOR_DOWNR1, KB_BUTTON_COLOR_DOWNG1, KB_BUTTON_COLOR_DOWNB1};
    unsigned char up2[3]    = {KB_BUTTON_COLOR_UPR2, KB_BUTTON_COLOR_UPG2, KB_BUTTON_COLOR_UPB2};
    unsigned char down2[3]  = {KB_BUTTON_COLOR_DOWNR2, KB_BUTTON_COLOR_DOWNG2, KB_BUTTON_COLOR_DOWNB2};
    unsigned char r     = 0;
    unsigned char g     = 0;
    unsigned char b     = 0;
    unsigned int color  = 0;
    for(int i = 0; i<KB_BUTTON_HIGH/2; i++)
    {
        r = map(i, 0, 29, up1[0], down1[0]);
        g = map(i, 0, 29, up1[1], down1[1]);
        b = map(i, 0, 29, up1[2], down1[2]);
        
        color = r;
        color = color<<6;
        color |= g;   
        color = color<<5;
        color |= b;
        
        Tft.drawHorizontalLine(x, y+i,KB_BUTTON_LEN, color);
    }
    for(int i = 0; i<KB_BUTTON_HIGH/2; i++)
    {
        r = map(i, 0, 29, up2[0], down2[0]);
        g = map(i, 0, 29, up2[1], down2[1]);
        b = map(i, 0, 29, up2[2], down2[2]);
        
        color = r;
        color = color<<6;
        color |= g;   
        color = color<<5;
        color |= b;
        
        Tft.drawHorizontalLine(x, y+i+KB_BUTTON_HIGH/2,KB_BUTTON_LEN, color);
    }
}

void UI_ArduinoPhone::drawButtonNumber()
{
    int x, y;
  
    // draw 1-9
    for(int i = 1; i<10; i++)
    {
        x = pgm_read_word(&__xyButton[i-1][0]);
        y = pgm_read_word(&__xyButton[i-1][1]);
        Tft.drawNumber(i, x+KB_NUMBER_X, y+KB_NUMBER_Y, 3, WHITE);
    }
    // draw 0
    x = pgm_read_word(&__xyButton[10][0]);
    y = pgm_read_word(&__xyButton[10][1]);
    Tft.drawNumber(0, x+KB_NUMBER_X, y+KB_NUMBER_Y, 3, WHITE);
}

void UI_ArduinoPhone::drawButtonAbc()
{
    int x, y;
    char str[9][5] = {KB_ABC_STR1,KB_ABC_STR2,KB_ABC_STR3,KB_ABC_STR4,KB_ABC_STR5,
                      KB_ABC_STR6,KB_ABC_STR7,KB_ABC_STR8,KB_ABC_STR9};
    // draw 1-9
    for(int i = 1; i<10; i++)
    {
        x = pgm_read_word(&__xyButton[i-1][0]);
        y = pgm_read_word(&__xyButton[i-1][1]);
        Tft.drawString(str[i-1],x+KB_ABC_X, y+KB_ABC_Y, 1, WHITE);
    }
}

void UI_ArduinoPhone::drawButtons()
{
    for(int i = 0; i<12; i++)        
    {
        drawButton(pgm_read_word(&__xyButton[i][0]), pgm_read_word(&__xyButton[i][1]));
    }
}

void UI_ArduinoPhone::drawDialogBox()
{
    Tft.fillScreen(DIABOX_X, DIABOX_X+DIABOX_LONG, DIABOX_Y, DIABOX_Y+DIABOX_HIGH, DIABOX_COLOR);
}

void UI_ArduinoPhone::drawMsgDialogBox()
{
    
    Tft.fillScreen(MSG_DIABOX_NUM_X, MSG_DIABOX_NUM_X+MSG_DIABOX_NUM_LONG, MSG_DIABOX_NUM_Y, MSG_DIABOX_NUM_Y+MSG_DIABOX_NUM_HIGH, DIABOX_COLOR);
    Tft.fillScreen(MSG_DIABOX_NUM_X, MSG_DIABOX_NUM_LONG+MSG_DIABOX_NUM_X, MSG_DIABOX_TXT_Y-KB_Y_SPACE, MSG_DIABOX_TXT_Y, BLACK);
    Tft.fillScreen(MSG_DIABOX_TXT_X, MSG_DIABOX_TXT_X+MSG_DIABOX_TXT_LONG, MSG_DIABOX_TXT_Y, MSG_DIABOX_TXT_Y+MSG_DIABOX_TXT_HIGH, DIABOX_COLOR);
    
}

void UI_ArduinoPhone::init()
{

   // Tft.TFTinit();
   Tft.init();
  //  TFT_BL_ON;

#if !MSGTEST
    state       = ST_TIME;//ST_TIME  ST_MSG_GETMSG
#else
    state       = ST_MSG_GETMSG;
#endif
    state_buf   = state;
    msgCount    = 0;
    callCount   = 0;
    msgNumCount = 0;
    callNum[0]  = '\0';
    msgNum[0]   = '\0';
    msg[0]      = '\0';
    
#if !MSGTEST
    msgReadCodeMax = 1;
    msgReadCodeNow = 1;
#else
    msgReadCodeMax = 5;
    msgReadCodeNow = 5;
#endif
    msgReadNewMsg  = 0;
    
    second  = 0;
    minute  = 0;
    minute_buf = 0;
    hour    = 0;
    day     = 0;
    month   = 0;
    year    = 0;

    memcpy(msgReadNum, "+8613410110991", sizeof("+8613410110991"));
    memcpy(msgReadTime, "12/09/17,11:07:14", sizeof("12/09/17,11:07:14"));
    memcpy(msgReadTxt, "arduino phone", sizeof("arduino phone"));
    
}

void UI_ArduinoPhone::msgAdd(char let)
{
    if(msgCount > 69) return ;

    unsigned char y[4] = {MSG_Y1, MSG_Y2, MSG_Y3, MSG_Y4};
    int line    = msgCount/18;
    int way     = msgCount%18;
    int x       = MSG_X + way*MSG_CHARSPACE;
    
    msg[msgCount++] = let;
    msg[msgCount]   = '\0';
    Tft.fillScreen(x+1, x+MSG_CHARSPACE, y[line], y[line] + 16, DIABOX_COLOR);
    Tft.drawChar(let, x, y[line], 2, MSG_COLOR);
    msgShowCount();
}

void UI_ArduinoPhone::msgAdd(char let, unsigned int color)
{
    if(msgCount > 69) return;
    unsigned char y[4] = {MSG_Y1, MSG_Y2, MSG_Y3, MSG_Y4};
    int line    = msgCount/18;
    int way     = msgCount%18;
    int x       = MSG_X + way*MSG_CHARSPACE;
    
    Tft.fillScreen(x+1, x+MSG_CHARSPACE, y[line], y[line] + 16, DIABOX_COLOR);
    Tft.drawChar(let, x, y[line], 2, color);
    
}
void UI_ArduinoPhone::msgDel()
{
    if(msgCount>0)
    {
        unsigned char y[4] = {MSG_Y1, MSG_Y2, MSG_Y3, MSG_Y4};
        msgCount--;
        msg[msgCount] = '\0';
        
        int line = msgCount/18;
        int way  = msgCount%18;
        int x    = MSG_X + way*MSG_CHARSPACE;
        
        
        Tft.fillScreen(x+1, x+MSG_CHARSPACE, y[line], y[line] + 16, DIABOX_COLOR);
        msgShowCount();
    }
}

void UI_ArduinoPhone::msgShowCount()
{
    Tft.fillScreen(MSG_SHOWCOUNTX, MSG_SHOWCOUNTX+2*MSG_CHARSPACE, MSG_SHOWCOUNTY, MSG_SHOWCOUNTY + 16, DIABOX_COLOR);
    if(msgCount>60)
        Tft.drawNumber(70-msgCount,MSG_SHOWCOUNTX+MSG_CHARSPACE, MSG_SHOWCOUNTY, 2, RED);
    else
        Tft.drawNumber(70-msgCount,MSG_SHOWCOUNTX, MSG_SHOWCOUNTY, 2, RED);

}

void UI_ArduinoPhone::callAdd(unsigned char num)
{
    //if(callCount > 11) return ;

    int x       = CALL_X + callCount*CALL_CHARSPACE;
    
    if(num == 15) //  +
    {
        callNum[callCount++] = '+';
        Tft.drawChar('+', x, CALL_Y, 2, CALL_COLOR);
    }
    else    // num
    {
        callNum[callCount++] = num+'0';
        Tft.drawNumber(num, x, CALL_Y, 2, CALL_COLOR);
    }
    callNum[callCount]      = ';';
    callNum[callCount+1]    = '\0';
    
}

void UI_ArduinoPhone::callDel()
{
    if(callCount < 1)return;
    callCount--;
    callNum[callCount]      = ';';
    callNum[callCount+1]    = '\0';
    int x   = CALL_X + callCount*CALL_CHARSPACE;  
    Tft.fillScreen(x+1, x+CALL_CHARSPACE, CALL_Y, CALL_Y+16, DIABOX_COLOR);
}

void UI_ArduinoPhone::msgNumAdd(char n)
{
    if(msgNumCount > 18)return ;
    int x = MSG_DIABOX_TXT_X+10+msgNumCount*MSG_DIABOX_CHARSPACE;
    int y = MSG_DIABOX_NUM_Y+6;
    
    if(n == 15)
    {
        msgNum[msgNumCount++] = '+';
        Tft.drawChar('+', x, y, 2, CALL_COLOR);
    }
    else
    {
        msgNum[msgNumCount++]   = n+'0';
        Tft.drawNumber(n, x, y, 2, CALL_COLOR);
    }
        
    msgNum[msgNumCount]     = '\0';

    
    
}

void UI_ArduinoPhone::msgNumDel()
{
    if(msgNumCount<1)return ;
    int x = MSG_DIABOX_TXT_X+10+(msgNumCount-1)*MSG_DIABOX_CHARSPACE;
    int y = MSG_DIABOX_NUM_Y+6;
   // Tft.drawNumber(msgNum[msgNumCount-1], x, y, 2, DIABOX_COLOR);

    msgNumCount--;
    msgNum[msgNumCount]     = '\0';


    Tft.fillScreen(x+1, x+MSG_DIABOX_CHARSPACE, y, y+MSG_DIABOX_CHARHIGH, DIABOX_COLOR);
    
}

void UI_ArduinoPhone::TouchDrvInit()
{
	Slide_Det = 0;
	Slide_Dir = -1;
	Button_Det = 0;
	Button_x = -1,Button_y = -1;

	touch_status = TOUCH_STATUS_NONE;
	touch_x = -1,touch_y = -1;
	touch_dir = -1;
	touch_time=0;
	touch_release=0;	
}

int UI_ArduinoPhone::GetSlideDirect(int x1,int y1,int x2,int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int abs_dx = abs(dx);
	int abs_dy = abs(dy)*2;
	if((abs_dx < TOUCH_NEARBY_X_DET) && abs_dy < TOUCH_NEARBY_Y_DET*2)
		return TOUCH_DIRECT_NEARBY;
	if(abs_dx > abs_dy)
	{
		if(dx > 0 )
			return TOUCH_DIRECT_EAST;
		else
			return TOUCH_DIRECT_WEST;
	}
	else
	{
		if(dy > 0 )
			return TOUCH_DIRECT_NORTH;
		else
			return TOUCH_DIRECT_SOUTH;
	}
	return TOUCH_DIRECT_NONE;
}

void UI_ArduinoPhone::TouchTimerIrq(int in_button,int in_x,int in_y)
{
	if(touch_status == TOUCH_STATUS_NONE)
	{
		if(in_button)
		{
			touch_status = TOUCH_STATUS_TOUCH;
			touch_dir = TOUCH_DIRECT_NONE;
			touch_time = 1;
			touch_release = 0;
			touch_x = in_x;
			touch_y = in_y;
		}
	}
	else if(touch_status == TOUCH_STATUS_TOUCH)
	{

		if(!in_button)
		{
			if(touch_release>TOUCH_RELEASE_DET)
			{
				if(touch_time >= TOUCH_BUTTON_DET)
				{
					Button_x = touch_x;
					Button_y = touch_y;
					Button_Det = 1;
				}
				touch_status = TOUCH_STATUS_NONE;
			}
			touch_release++;
		}
		else
		{
			int tmp_x,tmp_y;
			int tmp_dir;
			tmp_x = in_x;
			tmp_y = in_y;
			tmp_dir = GetSlideDirect(touch_x,touch_y,tmp_x,tmp_y);
			if(tmp_dir == TOUCH_DIRECT_NEARBY)
			{
				touch_x = (touch_x*4 + tmp_x)/5;
				touch_y = (touch_y*4 + tmp_y)/5;
				touch_time++;
			}
			else
			{
				touch_dir = tmp_dir;
				touch_x = tmp_x;
				touch_y = tmp_y;
				touch_time = 0;
				touch_status = TOUCH_STATUS_SLIDE;
			}
			touch_release >>= 1;
		}
	}
	else if(touch_status == TOUCH_STATUS_SLIDE)
	{
		if(!in_button)
		{
			if(touch_release >= TOUCH_RELEASE_DET)
			{
				if(touch_dir != TOUCH_DIRECT_CANCEL)
				{
					Slide_Dir = touch_dir;
					Slide_Det = 1;
				}
				touch_status = TOUCH_STATUS_NONE;
			}
			touch_release++;
		}
		else
		{
			int tmp_x,tmp_y;
			int tmp_dir;
			tmp_x = in_x;
			tmp_y = in_y;
			tmp_dir = GetSlideDirect(touch_x,touch_y,tmp_x,tmp_y);
			if((tmp_dir!=TOUCH_DIRECT_NEARBY) && tmp_dir != touch_dir)
			{
				touch_time++;
				if(touch_time > SLIDE_CANCEL_DET)
					touch_dir = TOUCH_DIRECT_CANCEL;
			}
			else if(tmp_dir!=TOUCH_DIRECT_NEARBY)
			{
				touch_x = tmp_x;
				touch_y = tmp_y;
				touch_release >>= 1;
			}
		}
	}
}

#define TOUT 15
unsigned char UI_ArduinoPhone::getTouch(unsigned char *type/*, unsigned char *times*/)
{
    int to = 0;
    while(1)
    {

        Point p = ts.getPoint();
        
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
        
        if(p.z < __PRESURE)  to++;
        else to = 0;
        
        if(to>TOUT)return 0;

        TouchTimerIrq((p.z > __PRESURE),p.x,p.y);
        
        
        *type = TOUCH_NOTHING;
        
        if(Slide_Det)
        {
          Slide_Det = 0;

          if(Slide_Dir == 1)
          {
            *type = TOUCH_DRAG_RIGHT;
            return TOUCH_DRAG_RIGHT;
          }
          else if(Slide_Dir == 3)
          {
            *type = TOUCH_DRAG_LEFT;
            return TOUCH_DRAG_LEFT;
          }
        }
        
        if(Button_Det)
        {
            if(Button_y < KB_Y1)return 0;
            Button_Det = 0;

            int x1 = Button_x/80;
            int y1 = (Button_y - 140)/(KB_BUTTON_HIGH+KB_X_SPACE);
            *type = x1 + 3*y1 + 1;
            
            return *type;
        }
        delay(1);
        
//        return 0;
    }
}

bool UI_ArduinoPhone::isTouch()
{
    Point p = ts.getPoint();
    if(p.z > __PRESURE)return 1;
    else return 0;
}

// show main page: call or sms
void UI_ArduinoPhone::showMainPage()
{

    Tft.drawRectangle(12, 200, 100, 70, GREEN);
    Tft.drawString("CALL", 12+13, 200+23, 3, GRAY1);
    Tft.drawRectangle(128,200,100,70,YELLOW);
    Tft.drawString("SMS", 128+22, 200+23, 3, GRAY2);
}

// touch when main page : 0: nothing, 1, call 2, sms
int UI_ArduinoPhone::touchMainPage()
{
    Point p = ts.getPoint();
    
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
    if(p.z < __PRESURE)return 0;
    if(p.x > 12 && p.x < 112 && p.y > 100 && p.y < 210) return 1;
    else if(p.x > 128 && p.x < 228 && p.y > 100 && p.y < 210)return 2;
    else return 0;
}

void UI_ArduinoPhone::showPageKB()
{
    drawButtons();
    drawButtonNumber();
    drawButtonAbc();
    Tft.drawString("DEL", KB_X3+5, KB_Y4+10, 3, BLACK);     // del
}

void UI_ArduinoPhone::showMsg()
{
    Tft.drawString("70/70", MSG_SHOWCOUNTX, MSG_SHOWCOUNTY, 2, RED);
    drawButton(pgm_read_word(&__xyButton[9][0]), pgm_read_word(&__xyButton[9][1]));
    Tft.drawString("MSG", KB_X1+5, KB_Y4+10, 3, YELLOW);    // msg
}

void UI_ArduinoPhone::showCall()
{
    drawButton(pgm_read_word(&__xyButton[9][0]), pgm_read_word(&__xyButton[9][1]));
    Tft.drawString("CAL", KB_X1+5, KB_Y4+10, 3, YELLOW);    // del
}

bool UI_ArduinoPhone::getTouchRect(int XL, int YU, int XR, int YD)
{
    if(!isTouch())return 0;
    Point p = ts.getPoint();
    
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
    
    if(p.z < __PRESURE)return 0;
    
    if(p.x > XL && p.x < XR && p.y > YU && p.y < YD)return 1;
    return 0;
}

void UI_ArduinoPhone::drawReadMsgTxt()
{
    int x = 5;
    int y = 67;
    for(int i = 0; msgReadTxt[i]; i++)
    {
        if(msgReadTxt[i] == '\r' && msgReadTxt[i+1] == '\n')
        {
            i++;
            x = 5; y += 16;
        }
        
        else if(msgReadTxt[i] == '\n')
        {
            x = 5; y+=16;
        }
        else
        {
            Tft.drawChar(msgReadTxt[i], x, y, 2, GRAY2);
            x+=12;
        }
        
        if(x > (240-12))
        {
            x = 5;
            y += 16;
        }
        
    }
}
void UI_ArduinoPhone::drawReadMsg()
{
    Tft.fillRectangle(65, 0, 240, 30, GRAY1);
    Tft.fillRectangle(0, 30, 240, 30, GRAY2);
    Tft.fillRectangle(0, 60, 240, 210, GRAY1);
    Tft.drawString(msgReadNum, 5+12*5, 7, 2, WHITE);
    Tft.drawString(msgReadTime, 5, 7+30, 2, BLACK);
    //Tft.drawString(msgReadTxt, 5, 7+60, 2, GRAY2);
    drawReadMsgTxt();
}

void UI_ArduinoPhone::drawReadMsgPage()
{
    Tft.fillRectangle(0, 0, 240, 30, GRAY1);
    Tft.drawString("From:", 5, 7, 2, BLUE);
    Tft.fillRectangle(0, 30, 240, 30, GRAY2);
    Tft.fillRectangle(0, 60, 240, 210, GRAY1);
    Tft.fillRectangle(0, 270, 240, 50, GRAY2);
    Tft.drawString("RETURN", 50, 270+13, 4, RED);
}

//+CMGR: "REC READ","+8613824127513","","12/09/17,11:07:14+32"
bool  UI_ArduinoPhone::getReadMsgTimeAndFrom(char * src1,char * num, char * time)
{
	int i,j=0;
    char *src = src1;
    unsigned char flag = 0;
    for(i=0; src[i]; i++)
    {
        if(src[i+0] == 'C' && src[i+1] == 'M' && src[i+2] == 'G' && src[i+3] == 'R' && src[i+4] == ':')
        {
            flag = 1;
            break;
        }
    }
    
    if(!flag)return false;
    
	for(i;src[i];i++)// first \"
	{
		if(src[i] == '\"')
			break;
	}
	for(i++;src[i];i++)// 2 \"
	{
		if(src[i] == '\"')
			break;
	}
	for(i++;src[i];i++) //3 \"
	{
		if(src[i] == '\"')
			break;
	}
	for(i++;src[i] && src[i]!='\"';i++) // 4 \"
	{
		num[j++] = src[i];
	}
	num[j] = '\0';
	j = 0;
	for(i++;src[i];i++)  // 5 \"
	{
		if(src[i] == '\"')
			break;
	}
    
	for(i++;src[i];i++)  // 6 \"
	{
		if(src[i] == '\"')
			break;
	}
    
	for(i++;src[i];i++)  // 7 \"
	{
		if(src[i] == '\"')
			break;
	}
	for(i++;src[i] && src[i]!='+';i++)
	{
		time[j++] = src[i];
	}
	time[j] = '\0';
     
    return true;
    
}

unsigned char UI_ArduinoPhone::getReadMsgMsg(char * src1)
{
    int i = 0;
   for(i = 0; src1[i]; i++)
   {
        msgReadTxt[i] = src1[i]; 
   }
   msgReadTxt[i] = '\0';  
   
   return i;
}

void UI_ArduinoPhone::drawTimeDate(int x, int y)
{
    char strTime[6];
    char strDate[9];
 
    if(hour<10)sprintf(strTime, "0%d:", hour);
    else sprintf(strTime, "%d:", hour);
    
    if(minute<10)sprintf(&strTime[3], "0%d", minute);
    else sprintf(&strTime[3], "%d", minute);
    strTime[5] = '\0';
    
    if(day<10)sprintf(strDate, "0%d/", day);
    else sprintf(strDate, "%d/", day);
    
    if(month<10)sprintf(&strDate[3], "0%d/", month);
    else sprintf(&strDate[3], "%d/", month);
    
    if(year<10)sprintf(&strDate[6], "0%d", year);
    else sprintf(&strDate[6], "%d", year);
    
    strDate[8] = '\0';
    
    Tft.fillRectangle(x, y, 180, 48, BLACK);
    Tft.drawString(strTime, x, y, 6, GRAY1);
    Tft.drawString(strDate, x+85, y+60, 2, GRAY2);

}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}

void UI_ArduinoPhone::getTime()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
 
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 
  // A few of these need masks because certain bits are control bits
  minute_buf = minute;
  
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  byte dayOfWeek  = bcdToDec(Wire.read());
  day        = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());

}

// 1: num 2: txt
unsigned char UI_ArduinoPhone::getMsgInputState()
{
    Point p = ts.getPoint();
    if(p.z < __PRESURE)return 0;
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
   /* char s[30];
    sprintf(s, "p.z = %d\tp.y = %d\r\n", p.z, p.y);
    I2C_Uart(s);*/
    delay(10);
    if(p.y < (MSG_DIABOX_NUM_HIGH+MSG_DIABOX_NUM_Y))return 1;
    else if(p.y < (MSG_DIABOX_TXT_Y+MSG_DIABOX_TXT_HIGH)) return 2;
    else return 0;
    
}


#if I2CUART

/*
eg:  char s[20];
     sprintf(s, "a = %d, b = %d\r\n", a, b);
     I2C_Uart(s);
*/
void UI_ArduinoPhone::I2C_Uart(char *p)
{
    int cnt=0;
    char tmp[33];
    for(int i = 0; *(p+i); i++)
    {
        cnt++;
    }
    cnt++;
    
    int cnt_t = cnt/32;
    for(int i = 0; i<cnt_t; i++)
    {
        memcpy(tmp, &p[32*i], 32);
        tmp[33] = '\0';
        Wire.beginTransmission(4);      // transmit to device #4
        Wire.write(tmp);                // sends one byte  
        Wire.endTransmission();         // stop transmitting   
    }
    memcpy(tmp, &p[32*cnt_t], cnt%32);
    tmp[cnt] = '\0';
    Wire.beginTransmission(4);          // transmit to device #4
    Wire.write(tmp);                    // sends one byte  
    Wire.endTransmission();         // stop transmitting
    //delay(5);
}


#endif
UI_ArduinoPhone UI;
