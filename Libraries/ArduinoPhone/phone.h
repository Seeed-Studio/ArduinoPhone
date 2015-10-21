/*
  phone.h

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
#ifndef _PHONE_H_
#define _PHONE_H_


// number of yexiaobo: 18318281127
// when make a call, if the guy handup, the return "NO CARRIER"
// when call in, "RING"
// when get sms, "+CMTI: "SM",30" , the number means: num of msg
// how to read msg: AT+CMGR=index    index: num of msg, 
// GET MST:
/*

+CMGR: "REC READ","+8613824127513","","12/09/17,11:07:14+32"
uu

OK

*/

/*
cnt = 0
AT+CMGR=5
cnt = 1

cnt = 2
+CMGR: "REC READ","+8613682509556","","12/09/19,16:24:26+32"
cnt = 3
1624
cnt = 4

cnt = 5
OK

*/

class phone
{
    private:

    int msgCount;

    public:
    
    void init();

    bool strCmp(unsigned char n, char *p1, const char *p2);
    void msgSend();
    void makeCall();
    bool isMsg(char *str);           // check if get some message
    bool isMsgSendOver();   // check if msg send over
    bool isCall(char *str);          // check if some one call
    bool isCallOver(char *str);      // check if call over
    void handUpCall();       
    void acceptCall();

};

extern phone Phone;
#endif