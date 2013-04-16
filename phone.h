#ifndef _PHONE_H_
#define _PHONE_H_

//number of yexiaobo: 18318281127
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