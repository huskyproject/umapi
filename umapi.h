/* umapi.h - universal message API */

#ifndef __UMAPI_H__
#define __UMAPI_H__

#ifdef UNIX

#ifndef dirSepC
#define dirSepC '/'
#endif
#ifndef dirSepS
#define dirSepS "/"
#endif

#else

#ifndef dirSepC
#define dirSepC '\\'
#endif
#ifndef dirSepS
#define dirSepS "\\"
#endif

#endif

typedef struct _tUmAddr
{
    UINT16 zone;
    UINT16 net;
    UINT16 node;
    UINT16 point;
    char *domain;
} tUmAddr;

typedef UINT16 tUmAreaType;
// lower byte: storage, upper byte: distribution
#define cUmAreaTypeSdm                 0x0001
#define cUmAreaTypeSquish              0x0002
#define cUmAreaTypeJam                 0x0003
#define cUmAreaTypeSql                 0x0004
#define cUmAreaTypeNetmail             0x0100
#define cUmAreaTypeEchomail            0x0200
#define cUmAreaTypeLocal               0x0300

typedef UINT32 tUmMsgNr;
typedef UINT16 tUmUserNr;
typedef UINT64 tUmDateTime; // unix time, UTC

typedef struct tUmArea
{
  tUmAreaType areaType;
  char *areaName;

  void *data; // type-dependant data
} tUmArea;

typedef struct _tUmMsgHdr
{
  tUmMsgNr msgNr;
  UINT32 flags;

  tUmAddr fromAddr;
  tUmAddr toAddr;
  char *fromName;
  char *toName;

  char *subject;

  tUmDateTime dateWritten;
  tUmDateTime dateArrived;
  tUmDateTime dateRead;

  tUmMsgNr replyTo; // this msg is a reply to <replyTo>
  tUmMsgNr *replies; // replies to this msg
  UINT16 numReplies;

  tUmAreaType areaType;
  char *data; // type-dependant data
} tUmMsgHdr;

#define cUmMsgFlagPriv                 0x00000001L
#define cUmMsgFlagLocal                0x00000002L
#define cUmMsgFlagCrash                0x00000004L
#define cUmMsgFlagHold                 0x00000008L
#define cUmMsgFlagDirect               0x00000010L
#define cUmMsgFlagImmed                0x00000020L
#define cUmMsgFlagRead                 0x00000040L
#define cUmMsgFlagSent                 0x00000080L
#define cUmMsgFlagKillSent             0x00000100L
#define cUmMsgFlagKillFileSent         0x00000200L
#define cUmMsgFlagTruncFileSent        0x00000400L
#define cUmMsgFlagAttach               0x00000800L
#define cUmMsgFlagFReq                 0x00001000L
#define cUmMsgFlagUpdReq               0x00002000L
#define cUmMsgFlagRcptReq              0x00004000L
#define cUmMsgFlagRcpt                 0x00008000L
#define cUmMsgFlagAuditReq             0x00010000L
#define cUmMsgFlagCfmReq               0x00020000L
#define cUmMsgFlagRouteHub             0x00040000L
#define cUmMsgFlagRouteHost            0x00080000L
#define cUmMsgFlagRouteZone            0x00100000L
#define cUmMsgFlagIntrans              0x00200000L
#define cUmMsgFlagOrphan               0x00400000L
#define cUmMsgFlagLocked               0x00800000L

typedef struct _tUmMsg
{
  tUmMsgHdr *msgHdr;

  char **kludges;
  UINT16 numKludges; // number of lines
  char **body;
  UINT16 numBody;

  char *data; // type-dependant data, only for internal use
} tUmMsg;


char *umAddr2Str(tUmAddr addr);
tUmAddr umStr2Addr(char *str);
CHAR umAddrComp(tUmAddr a1, tUmAddr a2); // 1 if matching, 0 if not

tUmArea *umAreaOpen(tUmAreaType areaType, char *areaName);
void umAreaClose(tUmArea *area);
tUmMsg *umAreaEmptyMsg(tUmArea *area);
tUmMsgHdr *umAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr);
tUmMsg *umAreaReadMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR umAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr);
CHAR umAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg);
tUmMsgNr umAreaAppendMsg(tUmArea *area, tUmMsg *msg);
CHAR umAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR umAreaLock(tUmArea *area);
CHAR umAreaUnlock(tUmArea *area);
CHAR umAreaLockMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR umAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr);
tUmMsgNr umAreaGetLastread(tUmArea *area, tUmUserNr userNr);
CHAR umAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr);
tUmMsgNr umAreaNumMsgs(tUmArea *area);
tUmMsgNr *umAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs); // allocates needed memory

void umMsgHdrDispose(tUmMsgHdr *msgHdr);
void umMsgDispose(tUmMsg *msg);

#endif

