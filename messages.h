
#ifndef _MESSAGES_
#define _MESSAGES_

#include <tcp.h>

enum echoclient_states
{
    ES_NOT_CONNECTED = 0,
    ES_CONNECTED, //=1
    ES_RECEIVED,
    ES_CLOSING,
};

//struct  strLocData
//{

//};

struct echoclient
{
    enum echoclient_states state; /* connection status */
    struct tcp_pcb *pcb;          /* pointer on the current tcp_pcb */
    struct pbuf *p_tx;            /* pointer on pbuf to be transmitted */
};
// ************* 
struct strMsgHeader
{
    quint8 msgType;
    quint8 payloadLength[2];
    quint8 rezerv;
} ;

struct strEmgReport // = 6+7
{
    struct strMsgHeader header;
    quint8 typeMsg;
    quint8 rzrv;
    quint8 Alarm_State;
    quint8 req_id[4];

};

struct strTcp_marker 
{
    struct strMsgHeader header;
    quint8 marker;
};

struct strARSmsg  // len = 4 + 6 = 10
{
    struct strMsgHeader header;//0-3
    quint8 arsMsgType;// 4
    quint8 userId[4];// 5-8
    quint8 csbk; // 9
#ifdef HYTRA
    quint8 req_id[4];
#endif
};


struct strRMRpt{ // registr msg report=26

    struct strMsgHeader header;
    quint8 type;
    quint8 none;
    //quint8 version[2];
    quint8 len[2] ;
    quint8 ser_num[10];
    quint8 zone[2];
    quint8 channel[2];
    quint8 reg_unreg_state;
    quint8 radio_id[4];
    quint8 signal_mode;
};

struct strRldRpl{ // reload replay msg =7
    struct strMsgHeader header;//  0-3  27.7.17
    quint8 type; // 4
    quint8 none; // 5
    quint8 reqid[4]; // 6-9
    quint8 result; // 10
};

struct strCCRpt{ // chan change report= 7
    struct strMsgHeader header;//  27.7.17
    quint8 type;
    quint8 none;
    quint8 newZone[2];
    quint8 newChan[2] ;
    quint8 signal_mode;
};

struct strCCRpl{ // chan change replay = 7
    struct strMsgHeader header;//  27.7.17
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 result;
};

struct strCtrlRpl
{ // ctrl replay = 8 + 4
    struct strMsgHeader header;// 27.7.17
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 result;
    quint8 req_type;
#ifdef HYTRA
    quint8 radio_id[4];
#endif
};

struct strCtrlRequest
{
    quint8 typeMsg[2];// 041C
    quint8 feature;
    quint8 function;
    quint8 rmtAdressType;//1
    quint8 rmtAdressSize;//3
    quint8 rmtAdress[3];
    quint8 rmtPort[2];
};


struct strCRpt{ // call report = 12
    struct strMsgHeader header;//  27.7.17
    quint8 type;//=5
    quint8 none;//=0
    quint8 callType;
    quint8 calledId[4] ;
    quint8 receivedId[4];
    quint8 callState;
};

struct strCRp{ // call reply = 7
    struct strMsgHeader header;// 27.7.17
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 requestResult;
};

struct strCSRp{ // call stop reply = 7
    struct strMsgHeader header;//  27.7.17
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 replyResult;
};

struct strMRRpt{ // modem type report = 4+5
    struct strMsgHeader header;//  27.7.17
    quint8 Msgtype;
    quint8 none;
    quint8 ver[2];
    quint8 ModemType;
};

struct strERpl{ // = 7
    struct strMsgHeader header;//  27.7.17
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 replyResult;
};

struct strPUINPUT
{
    quint8 Opcode[2];
    quint8 PUI_Source;
    quint8 PUI_Type;
    quint8 PUI_ID[2];
    quint8 PUI_State;
    quint8 PUI_State_Min;
    quint8 PUI_State_Max;
};

// ************** Text Messages **************
struct strTxtMsg_SrvAv
{
    struct strMsgHeader header;
    quint8 TxtMsgType = 0;
    quint8 ReceiverId[4];
    quint8 SenderId[4];
};

struct strTxtMsg_SrvAvAck
{
    struct strMsgHeader header;
    quint8 TxtMsgType = 1;
    quint8 ReceiverId[4];
    quint8 SenderId[4];
};

struct strTxtMsg_Ack
{
    struct strMsgHeader header;
    quint8 TxtMsgType = 2;
    quint8 ReceiverId[4];
    quint8 SenderId[4];
    bool result;
    quint8 SeqNumber;
};

struct strTxtMsg_SimpMsg
{
    struct strMsgHeader header;//0-3
    quint8 TxtMsgType = 3; //4
    quint8 ReceiverId[4]; // 5-8
    quint8 SenderId[4];  // 9-12
    quint8 ReceiverType;// – 13 Тип получателя,
    bool IsAckRequired;// – 14 Требуется ли подтверждение,
    quint8 SequenceNumber;// 15 – Последовательный номер,
    quint8 Text[140];// –  16-... Текстовое сообщение
};

//  *************** Location messages ***********************
struct strLocMsgType_ImdReq
{
    struct strMsgHeader header;//0-3
    quint8 LocMsgType = 0; //4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4]; // 9-12
    bool useCSBK;        // 13
};

struct strLocMsgType_ImdRep
{
    struct strMsgHeader header; // 0-3
    quint8 LocMsgType = 2;//4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4];// 9-12
    quint8 Result[4];   // 13-16

    quint8 Latitude[4];// – 17..20 Широта,
    quint8 Longitude[4]; // 21-24 - Долгота,
    quint8 Altitude[4]; // 25-28  - Высота,
    quint8 Heading[4]; //  29-32 - Направление,
    quint8 Radius[4]; //- 33-36  Радиус,
    quint8 Speed[4]; //=  37-40  Скорость // 14...
};

struct strLocMsgType_TrgReq
{
    struct strMsgHeader header;//0-3
    quint8 LocMsgType = 2; // 4
    quint8 RadioId[4];    // 5-8
    quint8 RequestId[4];  // 9-12
    quint8 Interval[2];  // 13-14
    bool useCSBK;         //15
};

struct strLocMsgType_TrgAnsw
{
    struct strMsgHeader header;// 0-3
    quint8 LocMsgType = 4;  // 4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4]; // 9-12
    quint8 Result[4];   // 13-16
};

struct strLocMsgType_TrgRep
{
    struct strMsgHeader header;// 0-3
    quint8 LocMsgType = 5;  // 4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4]; // 9-12
    quint8 Result[4];   // 13-16

    quint8 Latitude[4];// – 17..20 Широта,
    quint8 Longitude[4]; // 18-21 - Долгота,
    quint8 Altitude[4]; // 22-25  - Высота,
    quint8 Heading[4]; //  26-29 - Направление,
    quint8 Radius[4]; //- 30-33  Радиус,
    quint8 Speed[4]; //=  34-47  Скорость // 14...  // 14...
};

struct strLocMsgType_TrgStopReq
{
    struct strMsgHeader header; // 0-3
    quint8 LocMsgType = 5; // 4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4]; // 9-12
};

struct strLocMsgType_TrgStopAnsw
{
    struct strMsgHeader header; // 0-3
    quint8 LocMsgType = 7; // 4
    quint8 RadioId[4];  // 5-8
    quint8 RequestId[4]; // 9-12
    quint8 Result[4];// 13-16  see enum TrgLocationResult;
};

struct strMsgType_Ping
{
    struct strMsgHeader header; // 0-3
    quint8 Ping = 1; // 1
};


// ************** for Radio *****************

struct strSendMsg // len = 15 + payload
{ 
    quint8 commandDataSessionReq[2];//0x041D
    quint8 function;//01
    quint8 rawData;//0x50
    quint8 addressType;// 02 ip
    quint8 addressLen; // 04
    quint8 destIP[4];
    quint8 destPort[2];
    quint8 sessionID;
    quint8 payloadLen[2];
    quint8 payload[32];
    // + payload (ping , data, ...)
};

struct strCCR{ // chan change req = 8
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 newZone[2];
    quint8 newChan[2] ;
};

struct strCRq{ // call req = 11
    quint8 type;
    quint8 none;
    quint8 reqid[4];
    quint8 callType;
    quint8 receivedId[4];
};

struct strCSRq{ // call stop req = 6
    quint8 type;
    quint8 none;
    quint8 reqid[4];
};

// ******* send to uart********
struct strCZC{ //  = 7
    quint8 typeMsg[2];
    quint8 func;
    quint8 zone[2];
    quint8 chan[2];
} ;

struct strCallControl{ //  = 15
    quint8 typeMsg[2];// 041E
    quint8 func;
    quint8 calltype;
    quint8 rmtAdressType;//1
    quint8 rmtAdressSize;//3
    quint8 rmtAdress[3];
    quint8 rmtPort[2];
    quint8 groupIdSize;
    quint8 groupId[3];
} ;



#endif

