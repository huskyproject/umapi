/* umapid.c - universal message API - daemon code */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "typesize.h"
#include "umapi.h"
#include "umapisq.h"
#include "umapisdm.h"

int main(int argc, char **argv)
{
  // listen to TCP socket, use select, process client requests

  // in standalone mode (i.e. only the daemon accesses the msgbase)
  // some data (like msg lists) will be cached
}

