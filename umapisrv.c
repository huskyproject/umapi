/* umapisrv.c - universal message API - server interface */

#include <stdlib.h>
#include <stdio.h>
#include "typesize.h"
#include "umapi.h"
#include "umapisq.h"
#include "umapisdm.h"

tUmArea *umAreaOpen(tUmAreaType areaType, char *areaName)
{
  switch (areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaOpen(areaName);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaOpen(areaName);
    break;

  case cUmAreaTypeJam:
    return NULL;
    break;

  case cUmAreaTypeSql:
    return NULL;
    break;
  }
}

void umAreaClose(tUmArea *area)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    sqAreaClose(area);
    break;

  case cUmAreaTypeSdm:
    sdmAreaClose(area);
    break;

  case cUmAreaTypeJam:
    return;
    break;

  case cUmAreaTypeSql:
    return;
    break;
  }
}

tUmMsg *umAreaEmptyMsg(tUmArea *area)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaEmptyMsg(area);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaEmptyMsg(area);
    break;

  case cUmAreaTypeJam:
    return NULL;
    break;

  case cUmAreaTypeSql:
    return NULL;
    break;
  }
}

tUmMsgHdr *umAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaReadMsgHdr(area, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaReadMsgHdr(area, msgNr);
    break;

  case cUmAreaTypeJam:
    return NULL;
    break;

  case cUmAreaTypeSql:
    return NULL;
    break;
  }
}

tUmMsg *umAreaReadMsg(tUmArea *area, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaReadMsg(area, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaReadMsg(area, msgNr);
    break;

  case cUmAreaTypeJam:
    return NULL;
    break;

  case cUmAreaTypeSql:
    return NULL;
    break;
  }
}

CHAR umAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaChangeMsgHdr(area, msgNr, msgHdr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaChangeMsgHdr(area, msgNr, msgHdr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaChangeMsg(area, msgNr, msg);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaChangeMsg(area, msgNr, msg);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

tUmMsgNr umAreaAppendMsg(tUmArea *area, tUmMsg *msg)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaAppendMsg(area, msg);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaAppendMsg(area, msg);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaDeleteMsg(area, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaDeleteMsg(area, msgNr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaLock(tUmArea *area)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaLock(area);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaLock(area);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaUnlock(tUmArea *area)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaUnlock(area);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaUnlock(area);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaLockMsg(tUmArea *area, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaLockMsg(area, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaLockMsg(area, msgNr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaUnlockMsg(area, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaUnlockMsg(area, msgNr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

tUmMsgNr umAreaGetLastread(tUmArea *area, tUmUserNr userNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaGetLastread(area, userNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaGetLastread(area, userNr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

CHAR umAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaSetLastread(area, userNr, msgNr);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaSetLastread(area, userNr, msgNr);
    break;

  case cUmAreaTypeJam:
    return -1;
    break;

  case cUmAreaTypeSql:
    return -1;
    break;
  }
}

tUmMsgNr umAreaNumMsgs(tUmArea *area)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaNumMsgs(area);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaNumMsgs(area);
    break;

  case cUmAreaTypeJam:
    return 0;
    break;

  case cUmAreaTypeSql:
    return 0;
    break;
  }
}

tUmMsgNr *umAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs)
{
  switch (area->areaType)
  {
  case cUmAreaTypeSquish:
    return sqAreaMsgList(area, numMsgs);
    break;

  case cUmAreaTypeSdm:
    return sdmAreaMsgList(area, numMsgs);
    break;

  case cUmAreaTypeJam:
    return NULL;
    break;

  case cUmAreaTypeSql:
    return NULL;
    break;
  }
}

void umMsgDispose(tUmMsg *msg)
{
  switch (msg->msgHdr->areaType)
  {
  case cUmAreaTypeSquish:
    sqMsgDispose(msg);
    break;

  case cUmAreaTypeSdm:
    sdmMsgDispose(msg);
    break;

  case cUmAreaTypeJam:
    return;
    break;

  case cUmAreaTypeSql:
    return;
    break;
  }
}

void umMsgHdrDispose(tUmMsgHdr *msgHdr)
{
  switch (msgHdr->areaType)
  {
  case cUmAreaTypeSquish:
    sqMsgHdrDispose(msgHdr);
    break;

  case cUmAreaTypeSdm:
    sdmMsgHdrDispose(msgHdr);
    break;

  case cUmAreaTypeJam:
    return;
    break;

  case cUmAreaTypeSql:
    return;
    break;
  }
}

