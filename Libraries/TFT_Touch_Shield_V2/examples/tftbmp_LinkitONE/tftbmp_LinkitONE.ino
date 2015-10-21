/*
  TFT Touch Shield 2.0 examples - tftbmp2
  
  loovee
  2013-1-21
  
  this demo can show all bmp file in root Directory of Drv card
  please ensure that your image file is 320x240 size. 

  MAX_BMP can config the max file to display
  FILENAME_LEN can config the max length of file name
  
*/

#include <SPI.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

#include "TFTv2.h"

#define MAX_BMP         10                      // bmp file num
#define FILENAME_LEN    20                      // max file name length

#define Drv LFlash


const int PIN_SD_CS = 4;                        // pin of sd card

const long __Gnbmp_height = 320;                 // bmp hight
const long __Gnbmp_width  = 240;                 // bmp width

long __Gnbmp_image_offset  = 0;

int __Gnfile_num = 0;                           // num of file
char __Gsbmp_files[MAX_BMP][FILENAME_LEN];      // file name

LFile bmpFile;

// if bmp file return 1, else return 0
bool checkBMP(char *_name, char r_name[])
{
    int len = 0;

    if(NULL == _name)return false;
    
    while(*_name)
    {
        r_name[len++] = *(_name++);
        if(len>FILENAME_LEN)return false;
    }

    r_name[len] = '\0';

    if(len < 5)return false;

    // if xxx.bmp or xxx.BMP
    if( r_name[len-4] == '.' \
        && (r_name[len-3] == 'b' || (r_name[len-3] == 'B')) \
        && (r_name[len-2] == 'm' || (r_name[len-2] == 'M')) \
        && (r_name[len-1] == 'p' || (r_name[len-1] == 'P')) )
    {
        return true;
    }

    return false;

}

// search root to find bmp file
void searchDirectory()
{
    LFile root = Drv.open("/");                       // root
    while(true) 
    {
        LFile entry =  root.openNextFile();
        
        if (! entry)
        {
            break;
        }

        if(!entry.isDirectory())
        {
            char *ptmp = entry.name();

            char __Name[20];

            if(checkBMP(ptmp, __Name))
            {
                Serial.println(__Name);

                strcpy(__Gsbmp_files[__Gnfile_num++], __Name);
            }
        }
        entry.close();
    }
    
    Serial.print("get ");
    Serial.print(__Gnfile_num);
    Serial.println(" file: ");
    
    for(int i=0; i<__Gnfile_num; i++)
    {
        Serial.println(__Gsbmp_files[i]);
    }
}


void setup()
{

    Serial.begin(115200);
    
    delay(3000);
    
    pinMode(PIN_SD_CS,OUTPUT);
    digitalWrite(PIN_SD_CS,HIGH);

    Tft.TFTinit();

    LTask.begin();
    Drv.begin();
    
    
    Serial.println("Drv OK!");
    
    searchDirectory();

    TFT_BL_ON;
    
    Serial.println("blue");
    Tft.fillScreen(0,239,0,319,BLUE);
    
    delay(2000);
    INT16U __color[70000];
    
   /* for(int i=0; i<38400; i++)
    {
        __color[i] = RED;
    }
    
    for(int i=38400; i<76800; i++)
    {
        __color[i] = GREEN;
    }*/
    
    
    Serial.println("give data ok");
    delay(1000);
    Tft.fillScreen_(__color);
    delay(2000);
    Tft.fillScreen(0,239,0,319,RED);
    while(1);
}


void loop()
{

    static int dirCtrl = 0;
    for(unsigned char i=0; i<__Gnfile_num; i++)
    {
        bmpFile = Drv.open(__Gsbmp_files[i]);
        if (! bmpFile)
        {
            Serial.println("didnt find image");
            
            while(1);
            return;
        }

        if(! bmpReadHeader(bmpFile)) 
        {
            Serial.println("bad bmp");
            while(1);
            return;
        }

        dirCtrl = 1-dirCtrl;
        bmpdraw(bmpFile, 0, 0, dirCtrl);
        bmpFile.close();

        delay(1000);
        
        
    }
    
    while(1);

}

/*********************************************/
// This procedure reads a bitmap and draws it to the screen
// its sped up by reading many pixels worth of data at a time
// instead of just one pixel at a time. increading the buffer takes
// more RAM but makes the drawing a little faster. 20 pixels' worth
// is probably a good place

#define BUFFPIXEL       240                      // must be a divisor of 240 
#define BUFFPIXEL_X3    720                     // BUFFPIXELx3


#define UP_DOWN     1
#define DOWN_UP     0

// dir - 1: up to down
// dir - 2: down to up

uint8_t bmp_buffer[153600];

void bmpdraw(LFile f, int x, int y, int dir)
{

#if 0

    uint8_t __buf[BUFFPIXEL_X3];
    uint16_t __buf_c[BUFFPIXEL];
    
    unsigned long pos_offset = 54;
    
    for(int i=0; i<320; i++)
    {
        bmpFile.seek(54 + BUFFPIXEL*i);
        bmpFile.read(__buf, BUFFPIXEL_X3);
        
        for(int j=0; j<240; j++)
        {
            __buf_c[j] = __buf[3*k+2]>>3;                           // read
            __buf_c[j] = __buf_c[k]<<6 | (__buf[3k+1]>>2);          // green
            __buf_c[j] = __buf_c[k]<<5 | (__buf[3*k]>>3);           // blue
            
            
            bmp_buffer[480*i+2*j] = __buf_c[j] >> 8;
            bmp_buffer[480*i+2*j+1] = __buf_c[j] & 0xff;   
        }
    }
    
    Tft.fillScreen()
    
#else

    if(bmpFile.seek(__Gnbmp_image_offset))
    {
        Serial.print("pos = ");
        Serial.println(bmpFile.position());
    }
    
    uint32_t time = millis();

    uint8_t sdbuffer[BUFFPIXEL_X3];                 // 3 * pixels to buffer

    for (int i=0; i< __Gnbmp_height; i++)
    {
        if(dir)
        {
            bmpFile.seek(__Gnbmp_image_offset+(__Gnbmp_height-1-i)*240*3);
        }

        for(int j=0; j<(240/BUFFPIXEL); j++)
        {
        
            bmpFile.read(sdbuffer, BUFFPIXEL_X3);
            uint8_t buffidx = 0;
            int offset_x = j*BUFFPIXEL;
            
            unsigned int __color[BUFFPIXEL];
            
            for(int k=0; k<BUFFPIXEL; k++)
            {
                __color[k] = sdbuffer[buffidx+2]>>3;                        // read
                __color[k] = __color[k]<<6 | (sdbuffer[buffidx+1]>>2);      // green
                __color[k] = __color[k]<<5 | (sdbuffer[buffidx+0]>>3);      // blue
                
                buffidx += 3;
            }

            Tft.setCol(offset_x, offset_x+BUFFPIXEL);

            if(dir)
            {
                Tft.setPage(i, i);
            }
            else
            {
                Tft.setPage(__Gnbmp_height-i-1, __Gnbmp_height-i-1);
            }

            Tft.sendCMD(0x2c);                                                  
            
            TFT_DC_HIGH;
            TFT_CS_LOW;

            for(int m=0; m < BUFFPIXEL; m++)
            {
                SPI.transfer(__color[m]>>8);
                SPI.transfer(__color[m]);
            }

            TFT_CS_HIGH;
        }
        
    }
    
    Serial.print(millis() - time, DEC);
    Serial.println(" ms");
    
#endif
}

boolean bmpReadHeader(LFile f)
{

#if 0
    // read header
    uint32_t tmp;
    uint8_t bmpDepth;
    
    if (read16(f) != 0x4D42) {
        // magic bytes missing
        
        Serial.println("it is not an bmp file");
        return false;
    }
    
    Serial.println("it is an bmp file");

    // read file size
    tmp = read32(f);
    Serial.print("size 0x");
    Serial.println(tmp, HEX);

    // read and ignore creator bytes
    read32(f);

    __Gnbmp_image_offset = read32(f);
    Serial.print("offset ");
    Serial.println(__Gnbmp_image_offset, DEC);

    // read DIB header
    tmp = read32(f);
    Serial.print("header size ");
    Serial.println(tmp, DEC);
    
    
    int bmp_width = read32(f);
    int bmp_height = read32(f);
    
    Serial.print("width = ");Serial.println(bmp_width);
    Serial.print("height = ");Serial.println(bmp_height);
    
    if(bmp_width != __Gnbmp_width || bmp_height != __Gnbmp_height)      // if image is not 320x240, return false
    {
        return false;
    }

    if (read16(f) != 1)
    return false;

    bmpDepth = read16(f);
    Serial.print("bitdepth ");
    Serial.println(bmpDepth, DEC);

    if (read32(f) != 0) {
        // compression not supported!
        return false;
    }

    Serial.print("compression ");
    Serial.println(tmp, DEC);

    return true;
    
#else

    char __buf[100];
    f.seek(0);
    f.read(__buf, 54);
    
    for(int i=0; i<54; i++)
    {
        Serial.print("0x");
        Serial.print(__buf[i], HEX);
        Serial.print("\t");
    }

    return 1;
    
#endif
}
