/* umapisdm.h - *.MSG messagebase */

#ifndef __UMAPISDM_H__
#define __UMAPISDM_H__

typedef struct _tSdmMsgHdr
{
  char fromUserName[37]; // 36+1: ensure there really IS a trailing 0
  char toUserName[37];
  char subject[73];
  char dateTime[21];
  UINT16 timesRead;
  UINT16 destNode;
  UINT16 origNode;
  UINT16 cost;
  UINT16 origNet;
  UINT16 destNet;
  UINT16 destZone;
  UINT16 origZone;
  UINT16 destPoint;
  UINT16 origPoint;
  UINT16 replyTo;
  UINT16 attrib;
  UINT16 nextReply;
} tSdmMsgHdr;

typedef struct _tSdmArea
{
  int dummy;

} tSdmArea;

typedef struct _tSdmMsg
{
  int dummy;

} tSdmMsg;

#define cSdmMsgFlagPriv                 0x0001
#define cSdmMsgFlagCrash                0x0002
#define cSdmMsgFlagRcvd                 0x0004
#define cSdmMsgFlagSent                 0x0008
#define cSdmMsgFlagAttach               0x0010
#define cSdmMsgFlagIntrans              0x0020
#define cSdmMsgFlagOrphan               0x0040
#define cSdmMsgFlagKillSent             0x0080
#define cSdmMsgFlagLocal                0x0100
#define cSdmMsgFlagHold                 0x0200
#define cSdmMsgFlagUnused               0x0400
#define cSdmMsgFlagFReq                 0x0800
#define cSdmMsgFlagRcptReq              0x1000
#define cSdmMsgFlagRcpt                 0x2000
#define cSdmMsgFlagAuditReq             0x4000
#define cSdmMsgFlagUpdReq               0x8000

tUmArea *sdmAreaOpen(char *areaName);
void sdmAreaClose(tUmArea *area);
tUmMsg *sdmAreaEmptyMsg(tUmArea *area);
tUmMsgHdr *sdmAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr);
tUmMsg *sdmAreaReadMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sdmAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr);
CHAR sdmAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg);
tUmMsgNr sdmAreaAppendMsg(tUmArea *area, tUmMsg *msg);
CHAR sdmAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sdmAreaLock(tUmArea *area);
CHAR sdmAreaUnlock(tUmArea *area);
CHAR sdmAreaLockMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sdmAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr);
tUmMsgNr sdmAreaGetLastread(tUmArea *area, tUmUserNr userNr);
CHAR sdmAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr);
tUmMsgNr sdmAreaNumMsgs(tUmArea *area);
tUmMsgNr *sdmAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs); // allocates needed memory

void sdmMsgHdrDispose(tUmMsgHdr *msgHdr);
void sdmMsgDispose(tUmMsg *msg);

#endif

