#ifndef _UI_ARDUINOPHONE_DFS_H
#define _UI_ARDUINOPHONE_DFS_H


// test control
#define     PHONESOFTSERIAL     0
#define     MSGTEST             0
#define     I2CUART             0


//
#define DS1307_I2C_ADDRESS 0x68


// key board 
#define     KB_BUTTON_LEN   70
#define     KB_BUTTON_HIGH  40 // 44
#define     KB_X_SPACE      7
#define     KB_Y_SPACE      5   //7

#define     KB_Y1           320-4*(KB_Y_SPACE+KB_BUTTON_HIGH)   //116
#define     KB_Y2           KB_Y1+KB_Y_SPACE+KB_BUTTON_HIGH     //116+7+44 = 167
#define     KB_Y3           KB_Y2+KB_Y_SPACE+KB_BUTTON_HIGH     //168+7+44 = 218
#define     KB_Y4           KB_Y3+KB_Y_SPACE+KB_BUTTON_HIGH     //218+7+44 = 269

#define     KB_X1           8                                   // 8
#define     KB_X2           KB_X1+KB_X_SPACE+KB_BUTTON_LEN      // 8+77 = 85
#define     KB_X3           KB_X2+KB_X_SPACE+KB_BUTTON_LEN      //85+77 = 162

// BUTTON COLOR
#define     KB_BUTTON_COLOR_UPR1        18
#define     KB_BUTTON_COLOR_UPG1        42
#define     KB_BUTTON_COLOR_UPB1        21
#define     KB_BUTTON_COLOR_DOWNR1      15
#define     KB_BUTTON_COLOR_DOWNG1      35
#define     KB_BUTTON_COLOR_DOWNB1      18

#define     KB_BUTTON_COLOR_UPR2        13
#define     KB_BUTTON_COLOR_UPG2        28
#define     KB_BUTTON_COLOR_UPB2        15
#define     KB_BUTTON_COLOR_DOWNR2      8
#define     KB_BUTTON_COLOR_DOWNG2      16
#define     KB_BUTTON_COLOR_DOWNB2      7

// BUTTON NUMBER
#define     KB_NUMBER_X                 3
#define     KB_NUMBER_Y                 13

// BUTTON abc
#define     KB_ABC_X                    30
#define     KB_ABC_Y                    25
#define     KB_ABC_STR1                 ",.!"
#define     KB_ABC_STR2                 "abc"
#define     KB_ABC_STR3                 "def"
#define     KB_ABC_STR4                 "ghi"
#define     KB_ABC_STR5                 "jkl"
#define     KB_ABC_STR6                 "mno"
#define     KB_ABC_STR7                 "pqrs"
#define     KB_ABC_STR8                 "tuv"
#define     KB_ABC_STR9                 "wxyz"


//dialog box
#define     DIABOX_COLOR                0xa515//R: 20 G: 40 B: 21
#define     DIABOX_X                    KB_X1
#define     DIABOX_Y                    KB_Y_SPACE
#define     DIABOX_LONG                 240-2*KB_X1             // 224
#define     DIABOX_HIGH                 KB_Y1-3*KB_Y_SPACE      // 95

// dialog msg
#define     MSG_DIABOX_CHARSPACE        12
#define     MSG_DIABOX_CHARHIGH         18
#define     MSG_DIABOX_NUM_X            KB_X1
#define     MSG_DIABOX_NUM_Y            KB_Y_SPACE
#define     MSG_DIABOX_NUM_LONG         240-2*KB_X1
#define     MSG_DIABOX_NUM_HIGH         28

#define     MSG_DIABOX_TXT_X            KB_X1
#define     MSG_DIABOX_TXT_Y            MSG_DIABOX_NUM_Y+MSG_DIABOX_NUM_HIGH+KB_Y_SPACE
#define     MSG_DIABOX_TXT_LONG         MSG_DIABOX_NUM_LONG
#define     MSG_DIABOX_TXT_HIGH         KB_Y1-3*KB_Y_SPACE-MSG_DIABOX_NUM_HIGH-KB_Y_SPACE          

// show msg
#define     MSG_COLOR                   BLUE
#define     MSG_CHARSPACE               12
#define     MSG_X                       DIABOX_X+2
#define     MSG_Y1                      MSG_DIABOX_TXT_Y+3
#define     MSG_Y2                      MSG_Y1+18
#define     MSG_Y3                      MSG_Y2+18
#define     MSG_Y4                      MSG_Y3+18

#define     MSG_SHOWCOUNTX              MSG_X+12*MSG_CHARSPACE+10
#define     MSG_SHOWCOUNTY              MSG_Y4+20

// show call
#define     CALL_NUMSIZE                2
#define     CALL_COLOR                  BLACK
#define     CALL_CHARSPACE              CALL_NUMSIZE*6
#define     CALL_X                      DIABOX_X+8
#define     CALL_Y                      (DIABOX_HIGH-24)/2+10


//dialog number
#define     SHOWNUM_SIZE                3



// state machine
#define     ST_TIME             0x01
#define     ST_CALL             0x02
#define     ST_CALLING          0x03
#define     ST_GETCALL          0x04
#define     ST_MSG              0x05
#define     ST_SENDSMS          0x06
#define     ST_GETSMS           0x07

// touch return
#define     TOUCH_NOTHING       0x00
#define     TOUCH_KB1           0x01
#define     TOUCH_KB2           0x02
#define     TOUCH_KB3           0x03
#define     TOUCH_KB4           0x04
#define     TOUCH_KB5           0x05
#define     TOUCH_KB6           0x06
#define     TOUCH_KB7           0x07
#define     TOUCH_KB8           0x08
#define     TOUCH_KB9           0x09
#define     TOUCH_KBENT         0x0A
#define     TOUCH_KB0           0x0B
#define     TOUCH_KBDEL         0x0C

#define     TOUCH_DRAG_LEFT     0x10
#define     TOUCH_DRAG_RIGHT    0x20


//touch screen

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 
#endif

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2

// by luther
#define TOUCH_STATUS_NONE		0
#define TOUCH_STATUS_TOUCH		1
#define TOUCH_STATUS_SLIDE		2

#define TOUCH_DIRECT_CANCEL		-2
#define TOUCH_DIRECT_NONE		0 
#define TOUCH_DIRECT_EAST		1
#define TOUCH_DIRECT_SOUTH		2
#define TOUCH_DIRECT_WEST		3
#define TOUCH_DIRECT_NORTH		4
#define TOUCH_DIRECT_NEARBY		5

#define TOUCH_BUTTON_DET        2
#define TOUCH_RELEASE_DET		8
#define SLIDE_CANCEL_DET		2
#define TOUCH_NEARBY_X_DET      14
#define TOUCH_NEARBY_Y_DET      10


// msg state
#define MSG_STATE_NUM           0
#define MSG_STATE_TXT           1

//read msg
#define MSG_READ_NUM_X          0
#define MSG_READ_NUM_Y          0
#define MSG_READ_TIME_X         0
#define MSG_READ_TIME_Y         30
#define MSG_READ_MSG_X          0
#define MSG_READ_MSG_Y          60
#define MSG_READ_RET_X          0
#define MSG_READ_RET_Y          270

#endif
