/* umapisq.h - squish messagebase */

#ifndef __UMAPISQ_H__
#define __UMAPISQ_H__

typedef struct _tUmAreaSquish
{
  FILE *sqdFile;
  FILE *sqiFile;
  FILE *sqlFile;

} tUmAreaSquish;

tUmArea *sqAreaOpen(char *areaName);
void sqAreaClose(tUmArea *area);
tUmMsg *sqAreaEmptyMsg(tUmArea *area);
tUmMsgHdr *sqAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr);
tUmMsg *sqAreaReadMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sqAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr);
CHAR sqAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg);
tUmMsgNr sqAreaAppendMsg(tUmArea *area, tUmMsg *msg);
CHAR sqAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sqAreaLock(tUmArea *area);
CHAR sqAreaUnlock(tUmArea *area);
CHAR sqAreaLockMsg(tUmArea *area, tUmMsgNr msgNr);
CHAR sqAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr);
tUmMsgNr sqAreaGetLastread(tUmArea *area, tUmUserNr userNr);
CHAR sqAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr);
tUmMsgNr sqAreaNumMsgs(tUmArea *area);
tUmMsgNr *sqAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs); // allocates needed memory

void sqMsgHdrDispose(tUmMsgHdr *msgHdr);
void sqMsgDispose(tUmMsg *msg);

#endif

