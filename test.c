/* test.c - test the umapi lib */

#include <stdio.h>
#include <time.h>
#include "typesize.h"
#include "umapi.h"

#define areaName "/husky/echo/umapi.test"

void printMsgHdr(tUmMsgHdr *msgHdr)
{
  int i;

  printf("msgNr: %d\n", msgHdr->msgNr);
  printf("flags: %d\n", msgHdr->flags);
  printf("fromAddr: %s\n", umAddr2Str(msgHdr->fromAddr));
  printf("toAddr: %s\n", umAddr2Str(msgHdr->toAddr));
  printf("fromName: %s\n", msgHdr->fromName);
  printf("toName: %s\n", msgHdr->toName);
  printf("subject: %s\n", msgHdr->subject);
  printf("dateWritten: %s", asctime(gmtime(&msgHdr->dateWritten)));
  printf("dateArrived: %s", asctime(gmtime(&msgHdr->dateArrived)));
  printf("dateRead: %s", asctime(gmtime(&msgHdr->dateRead)));
  printf("replyTo: %d\n", msgHdr->replyTo);
  printf("numReplies: %d\n", msgHdr->numReplies);
  for (i = 0; i < msgHdr->numReplies; i++)
  {
    printf("  reply: %d\n", msgHdr->replies[i]);
  }
}

void printMsg(tUmMsg *msg)
{
  int i;

  printMsgHdr(msg->msgHdr);

  if (msg->numKludges != 0)
  {
    printf("Kludges:\n");
    for (i = 0; i < msg->numKludges; i++)
      printf("  %s\n", msg->kludges[i]);
  }

  if (msg->numBody != 0)
  {
    printf("Body:\n");
    for (i = 0; i < msg->numBody; i++)
      printf("  %s\n", msg->body[i]);
  }

  printf("---\n");
}
  
int main(int argc, char *argv[])
{
  tUmArea *area;
  tUmMsg *msg;
  tUmMsgHdr *msgHdr;

  area = umAreaOpen(cUmAreaTypeSdm, areaName);

  msgHdr = umAreaReadMsgHdr(area, 1);
  if (msgHdr == NULL)
  {
    printf("could not read header of msg #1!\n");
  }
  else
  {
    printMsgHdr(msgHdr);
    umMsgHdrDispose(msgHdr);
  }
  printf("\n");

  msg = umAreaReadMsg(area, 1);
  if (msg == NULL)
  {
    printf("could not read msg #1!\n");
  }
  else
  {
    printMsg(msg);
    umMsgDispose(msg);
  }
  printf("\n");

  umAreaClose(area);
}

