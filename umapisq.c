/* umapisq.c - squish messagebase */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "typesize.h"
#include "umapi.h"
#include "umapisq.h"

tUmArea *sqAreaOpen(char *areaName)
{

}

void sqAreaClose(tUmArea *area)
{

}

tUmMsg *sqAreaEmptyMsg(tUmArea *area)
{

}

tUmMsgHdr *sqAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr)
{

}

tUmMsg *sqAreaReadMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

CHAR sqAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr)
{

}

CHAR sqAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg)
{

}

tUmMsgNr sqAreaAppendMsg(tUmArea *area, tUmMsg *msg)
{

}

CHAR sqAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

CHAR sqAreaLock(tUmArea *area)
{

}

CHAR sqAreaUnlock(tUmArea *area)
{

}

CHAR sqAreaLockMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

CHAR sqAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

tUmMsgNr sqAreaGetLastread(tUmArea *area, tUmUserNr userNr)
{

}

CHAR sqAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr)
{

}

tUmMsgNr sqAreaNumMsgs(tUmArea *area)
{

}

// allocates needed memory
tUmMsgNr *sqAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs)
{

}

void sqMsgDispose(tUmMsg *msg)
{
  free(msg->msgHdr->data);
  free(msg->msgHdr->fromName);
  free(msg->msgHdr->toName);
  free(msg->msgHdr->subject);
  free(msg->msgHdr->replies);
  free(msg->msgHdr);
  if (msg->kludges != NULL) free(msg->kludges);
  if (msg->body != NULL) free(msg->body);
  free(msg);
}

void sqMsgHdrDispose(tUmMsgHdr *msgHdr)
{
  free(msgHdr->data);
  free(msgHdr->fromName);
  free(msgHdr->toName);
  free(msgHdr->subject);
  free(msgHdr->replies);
  free(msgHdr);
}


