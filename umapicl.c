/* umapicl.c - universal message API - client code */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "typesize.h"
#include "umapi.h"
#include "umapisq.h"
#include "umapisdm.h"

tUmArea *umAreaOpen(tUmAreaType areaType, char *areaName)
{
  // use connection-independent code
  // first TCP will be implemented, later something for the DOS systems
}

void umAreaClose(tUmArea *area)
{
  // close connection to server
}

tUmMsg *umAreaEmptyMsg(tUmArea *area)
{
}

tUmMsgHdr *umAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr)
{
}

tUmMsg *umAreaReadMsg(tUmArea *area, tUmMsgNr msgNr)
{
}

CHAR umAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr)
{
}

CHAR umAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg)
{
}

tUmMsgNr umAreaAppendMsg(tUmArea *area, tUmMsg *msg)
{
}

CHAR umAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr)
{
}

CHAR umAreaLock(tUmArea *area)
{
}

CHAR umAreaUnlock(tUmArea *area)
{
}

CHAR umAreaLockMsg(tUmArea *area, tUmMsgNr msgNr)
{
}

CHAR umAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr)
{
}

tUmMsgNr umAreaGetLastread(tUmArea *area, tUmUserNr userNr)
{
}

CHAR umAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr)
{
}

tUmMsgNr umAreaNumMsgs(tUmArea *area)
{
}

tUmMsgNr *umAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs)
{
}

void umMsgDispose(tUmMsg *msg)
{
}

void umMsgHdrDispose(tUmMsgHdr *msgHdr)
{
}

