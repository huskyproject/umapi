/* umapisdm.c - *.MSG messagebase */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "typesize.h"
#include "umapi.h"
#include "umapisdm.h"
#include "umdate.h"

tSdmMsgHdr *sdmIntReadMsgHdr(FILE *f)
{
  tSdmMsgHdr *hdr;
  UCHAR b1, b2;

  hdr = malloc(sizeof(tSdmMsgHdr));

  rewind(f);
  fread(hdr->fromUserName, 36, 1, f);
  hdr->fromUserName[36] = 0;
  fread(hdr->toUserName, 36, 1, f);
  hdr->toUserName[36] = 0;
  fread(hdr->subject, 72, 1, f);
  hdr->subject[72] = 0;
  fread(hdr->dateTime, 20, 1, f);
  hdr->dateTime[20] = 0;

  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->timesRead = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->destNode = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->origNode = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->cost = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->origNet = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->destNet = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->destZone = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->origZone = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->destPoint = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->origPoint = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->replyTo = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->attrib = (b2 * 256) + b1;
  fread(&b1, 1, 1, f); fread(&b2, 1, 1, f);
  hdr->nextReply = (b2 * 256) + b1;

  return hdr;
}

tUmMsgHdr *sdmIntConvHdr(tSdmMsgHdr *sdmHdr, tUmMsgNr msgNr)
{
  tUmMsgHdr *msgHdr;

  msgHdr = malloc(sizeof(tUmMsgHdr));
  msgHdr->areaType = cUmAreaTypeSdm;
  msgHdr->msgNr = msgNr;
  msgHdr->flags = 0;
  if (sdmHdr->attrib & cSdmMsgFlagPriv) msgHdr->flags |= cUmMsgFlagPriv;
  if (sdmHdr->attrib & cSdmMsgFlagCrash) msgHdr->flags |= cUmMsgFlagCrash;
  if (sdmHdr->attrib & cSdmMsgFlagRcvd) msgHdr->flags |= cUmMsgFlagRead;
  if (sdmHdr->attrib & cSdmMsgFlagSent) msgHdr->flags |= cUmMsgFlagSent;
  if (sdmHdr->attrib & cSdmMsgFlagAttach) msgHdr->flags |= cUmMsgFlagAttach;
  if (sdmHdr->attrib & cSdmMsgFlagIntrans) msgHdr->flags |= cUmMsgFlagIntrans;
  if (sdmHdr->attrib & cSdmMsgFlagOrphan) msgHdr->flags |= cUmMsgFlagOrphan;
  if (sdmHdr->attrib & cSdmMsgFlagKillSent) msgHdr->flags |= cUmMsgFlagKillSent;
  if (sdmHdr->attrib & cSdmMsgFlagLocal) msgHdr->flags |= cUmMsgFlagLocal;
  if (sdmHdr->attrib & cSdmMsgFlagHold) msgHdr->flags |= cUmMsgFlagHold;
  if (sdmHdr->attrib & cSdmMsgFlagFReq) msgHdr->flags |= cUmMsgFlagFReq;
  if (sdmHdr->attrib & cSdmMsgFlagRcptReq) msgHdr->flags |= cUmMsgFlagRcptReq;
  if (sdmHdr->attrib & cSdmMsgFlagRcpt) msgHdr->flags |= cUmMsgFlagRcpt;
  if (sdmHdr->attrib & cSdmMsgFlagAuditReq) msgHdr->flags |= cUmMsgFlagAuditReq;
  if (sdmHdr->attrib & cSdmMsgFlagUpdReq) msgHdr->flags |= cUmMsgFlagUpdReq;

  msgHdr->fromAddr.zone = sdmHdr->origZone;
  msgHdr->fromAddr.net = sdmHdr->origNet;
  msgHdr->fromAddr.node = sdmHdr->origNode;
  msgHdr->fromAddr.point = sdmHdr->origPoint;
  msgHdr->fromAddr.domain = NULL;
  msgHdr->toAddr.zone = sdmHdr->destZone;
  msgHdr->toAddr.net = sdmHdr->destNet;
  msgHdr->toAddr.node = sdmHdr->destNode;
  msgHdr->toAddr.point = sdmHdr->destPoint;
  msgHdr->toAddr.domain = NULL;
  msgHdr->fromName = strdup(sdmHdr->fromUserName);
  msgHdr->toName = strdup(sdmHdr->toUserName);
  msgHdr->subject = strdup(sdmHdr->subject);

  msgHdr->dateWritten = ftscDate2UnixDate(sdmHdr->dateTime);

  msgHdr->dateArrived = 0;
  msgHdr->dateRead = 0;
  msgHdr->replyTo = sdmHdr->replyTo;

  if (sdmHdr->nextReply != 0)
  {
    msgHdr->replies = malloc(sizeof(tUmMsgNr));
    msgHdr->replies[0] = sdmHdr->nextReply;
    msgHdr->numReplies = 1;
  }
  else
  {
    msgHdr->replies = NULL;
    msgHdr->numReplies = 0;
  }

  msgHdr->data = (void *) sdmHdr;

  return msgHdr;
}

tUmArea *sdmAreaOpen(char *areaName)
{
  tUmArea *area;
  tSdmArea *sdmArea;

  if ((areaName == NULL) || (*areaName == 0)) return NULL;

  area = calloc(1, sizeof(tUmArea));
  sdmArea = calloc(1, sizeof(tSdmArea));

  if (areaName[strlen(areaName) - 1] == dirSepC)
  {
    area->areaName = malloc(strlen(areaName));
    strncpy(area->areaName, areaName, strlen(areaName) - 1);
    area->areaName[strlen(areaName) - 1] = 0;
  }
  else area->areaName = strdup(areaName);
  area->areaType = cUmAreaTypeSdm;
  area->data = (void *) sdmArea;

  return area;
}

void sdmAreaClose(tUmArea *area)
{
  free(area->data);
  free(area->areaName);
  free(area);
}

tUmMsg *sdmAreaEmptyMsg(tUmArea *area)
{
  tUmMsg *msg;
  tSdmMsg *sdmMsg;
  tUmMsgHdr *hdr;
  tSdmMsgHdr *sdmHdr;

  msg = calloc(1, sizeof(tUmMsg));
  sdmMsg = calloc(1, sizeof(tSdmMsg));
  hdr = calloc(1, sizeof(tUmMsgHdr));
  sdmHdr = calloc(1, sizeof(tSdmMsgHdr));
  msg->data = (void *) sdmMsg;
  msg->msgHdr = hdr;
  hdr->dateWritten = time(NULL);
  hdr->areaType = cUmAreaTypeSdm;
  hdr->data = (void *) sdmHdr;

  return msg;
}

tUmMsgHdr *sdmAreaReadMsgHdr(tUmArea *area, tUmMsgNr msgNr)
{
  tSdmMsgHdr *sdmHdr;
  tUmMsgHdr *msgHdr;
  FILE *f;
  char *fname;

  fname = malloc(strlen(area->areaName)+11); // %u: max. 65535
  sprintf(fname, "%s%c%u.msg", area->areaName, dirSepC, msgNr);
  f = fopen(fname, "r");
  free(fname);

  if (f == NULL) return NULL;

  sdmHdr = sdmIntReadMsgHdr(f);
  fclose(f);

  msgHdr = sdmIntConvHdr(sdmHdr, msgNr);
  // don't dispose sdmHdr, because it's in msgHdr now

  return msgHdr;
}

tUmMsg *sdmAreaReadMsg(tUmArea *area, tUmMsgNr msgNr)
{
  tUmMsg *msg;
  tSdmMsg *sdmMsg;
  tSdmMsgHdr *sdmHdr;
  tUmMsgHdr *msgHdr;
  FILE *f;
  char *fname;
  char buf[1024];
  char *msgBuf;
  char *msgBufPos;
  size_t br;
  UINT32 msgBufSize;

  fname = malloc(strlen(area->areaName)+11); // %u: max. 65535
  sprintf(fname, "%s%c%u.msg", area->areaName, dirSepC, msgNr);
  f = fopen(fname, "r");
  free(fname);

  if (f == NULL) return NULL;

  sdmHdr = sdmIntReadMsgHdr(f);

  msgHdr = sdmIntConvHdr(sdmHdr, msgNr);
  // don't dispose sdmHdr, because it's in msgHdr now

  msg = malloc(sizeof(tUmMsg));
  sdmMsg = malloc(sizeof(tSdmMsg));
  msg->msgHdr = msgHdr;
  msg->kludges = NULL;
  msg->body = NULL;
  msg->data = (void *) sdmMsg;

  // read whole message into memory
  msgBuf = NULL;
  msgBufSize = 0;
  fseek(f, 0xbeL, SEEK_SET);
  while (feof(f) == 0)
  {
    // read message in 1k-blocks
    br = fread(buf, 1, 1024, f);
    if (br > 0)
    {
      msgBuf = realloc(msgBuf, msgBufSize + br + 1);
      msgBufPos = &msgBuf[msgBufSize];
      strncpy(msgBufPos, buf, br);
      msgBufSize += br;
      msgBuf[msgBufSize] = 0;
    }
  }
  fclose(f);

  // split into kludge- and body-lines
  msgBufPos = msgBuf;
  msg->numKludges = 0;
  msg->numBody = 0;
  while (*msgBufPos != 0)
  {
    char *crPos;

    // CR gets filtered out (no trailing CR)
    crPos = strchr(msgBufPos, 13);

    // kludge or body?
    if (*msgBufPos == 1)
    {
      if (crPos != NULL)
      {
	msg->numKludges++;
	msg->kludges = realloc(msg->kludges,
			       msg->numKludges * sizeof(char *));
	msg->kludges[msg->numKludges - 1] = malloc((crPos - msgBufPos) + 1);
	strncpy(msg->kludges[msg->numKludges - 1],
		msgBufPos, crPos - msgBufPos);
	msg->kludges[msg->numKludges - 1][crPos - msgBufPos] = 0;
      }
      else
      {
	msg->numKludges++;
	msg->kludges = realloc(msg->kludges,
			       msg->numKludges * sizeof(char *));
	msg->kludges[msg->numKludges - 1] = malloc(strlen(msgBufPos) + 1);
	strncpy(msg->kludges[msg->numKludges - 1],
		msgBufPos, strlen(msgBufPos));
	msg->kludges[msg->numKludges - 1][strlen(msgBufPos)] = 0;
      }
    }
    else
    {
      if (crPos != NULL)
      {
	msg->numBody++;
	msg->body = realloc(msg->body,
			       msg->numBody * sizeof(char *));
	msg->body[msg->numBody - 1] = malloc((crPos - msgBufPos) + 1);
	strncpy(msg->body[msg->numBody - 1],
		msgBufPos, crPos - msgBufPos);
	msg->body[msg->numBody - 1][crPos - msgBufPos] = 0;
      }
      else
      {
	msg->numBody++;
	msg->body = realloc(msg->body,
			       msg->numBody * sizeof(char *));
	msg->body[msg->numBody - 1] = malloc(strlen(msgBufPos) + 1);
	strncpy(msg->body[msg->numBody - 1],
		msgBufPos, strlen(msgBufPos));
	msg->body[msg->numBody - 1][strlen(msgBufPos)] = 0;
      }
    }

    if (crPos != NULL) msgBufPos = crPos + 1;
    else msgBufPos = &msgBufPos[strlen(msgBufPos)];
  }

  free(msgBuf);

  return msg;
}

CHAR sdmAreaChangeMsgHdr(tUmArea *area, tUmMsgNr msgNr, tUmMsgHdr *msgHdr)
{

}

CHAR sdmAreaChangeMsg(tUmArea *area, tUmMsgNr msgNr, tUmMsg *msg)
{

}

tUmMsgNr sdmAreaAppendMsg(tUmArea *area, tUmMsg *msg)
{

}

CHAR sdmAreaDeleteMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

CHAR sdmAreaLock(tUmArea *area)
{

}

CHAR sdmAreaUnlock(tUmArea *area)
{

}

CHAR sdmAreaLockMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

CHAR sdmAreaUnlockMsg(tUmArea *area, tUmMsgNr msgNr)
{

}

tUmMsgNr sdmAreaGetLastread(tUmArea *area, tUmUserNr userNr)
{

}

CHAR sdmAreaSetLastread(tUmArea *area, tUmUserNr userNr, tUmMsgNr msgNr)
{

}

tUmMsgNr sdmAreaNumMsgs(tUmArea *area)
{

}

// allocates needed memory
tUmMsgNr *sdmAreaMsgList(tUmArea *area, tUmMsgNr *numMsgs)
{

}

void sdmMsgDispose(tUmMsg *msg)
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

void sdmMsgHdrDispose(tUmMsgHdr *msgHdr)
{
  free(msgHdr->data);
  free(msgHdr->fromName);
  free(msgHdr->toName);
  free(msgHdr->subject);
  free(msgHdr->replies);
  free(msgHdr);
}


