/* umaddr.c - universal message API - address functions */

#include <stdlib.h>
#include <stdio.h>
#include "typesize.h"
#include "umapi.h"

char *umAddr2Str(tUmAddr addr)
{
  char *addrstr;

  if ((addr.domain != NULL) && (*addr.domain != 0))
  {
    addrstr = malloc(strlen(addr.domain) + 25);

    if (addr.point != 0)
      sprintf(addrstr, "%u:%u/%u.%u@%s", addr.zone, addr.net, addr.node,
	      addr.point, addr.domain);
    else
      sprintf(addrstr,"%u:%u/%u@%s", addr.zone, addr.net, addr.node,
	      addr.domain);
  }
  else
  {
    addrstr = malloc(24); // 65535:65535/65535.65535

    if (addr.point != 0)
      sprintf(addrstr, "%u:%u/%u.%u", addr.zone, addr.net, addr.node,
	      addr.point);
    else
      sprintf(addrstr,"%u:%u/%u", addr.zone, addr.net, addr.node);
  }

  return addrstr;
}

tUmAddr umStr2Addr(char *str)
{
  // ***FIXME*** - to be written :)
}

CHAR umAddrComp(tUmAddr a1, tUmAddr a2)
{
  if ((a1.zone != a2.zone) && (a1.zone != 0) && (a2.zone != 0))
    return 0;
  if ((a1.domain != NULL) && (a2.domain != NULL) &&
      (*a1.domain != 0) && (*a2.domain != 0) &&
      (strcmp(a1.domain, a2.domain) != 0))
    return 0;
  if ((a2.net != a2.net) || (a1.node != a2.node) || (a1.point != a2.point))
    return 0;

  return 1;
}

