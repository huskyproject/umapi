/* date.c - date conversions */

#include <time.h>
#include <stdio.h>
#include <ctype.h>

static int isdst = -1;

static void initDst()
{
  time_t now;

  now = time(NULL);
  isdst = !!(localtime(&now)->tm_isdst);
}

time_t ftscDate2UnixDate(char *ftscDate)
{
  struct tm tm;
  char monthS[21]; // in case the date-field is trashed
  int i;

  if (isdst == -1) initDst();

  sscanf(ftscDate, "%d %s %d %d:%d:%d", &tm.tm_mday, monthS,
	 &tm.tm_year, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
  if ((tm.tm_mday < 1) || (tm.tm_mday > 31)) tm.tm_mday = 1;
  if ((tm.tm_year < 0) || (tm.tm_year > 99)) tm.tm_year = 0;
  if ((tm.tm_hour < 0) || (tm.tm_hour > 23)) tm.tm_hour = 0;
  if ((tm.tm_min < 0) || (tm.tm_min > 59)) tm.tm_min = 0;
  if ((tm.tm_sec < 0) || (tm.tm_sec > 59)) tm.tm_sec = 0;
  if (tm.tm_year < 80) tm.tm_year += 100; // years since 1900 !
  monthS[3] = 0;
  for (i = 0; i < 3; i++) monthS[i] = tolower(monthS[i]);
  if (strcmp(monthS, "jan") == 0) tm.tm_mon = 0;
  else if (strcmp(monthS, "feb") == 0) tm.tm_mon = 1;
  else if (strcmp(monthS, "mar") == 0) tm.tm_mon = 2;
  else if (strcmp(monthS, "apr") == 0) tm.tm_mon = 3;
  else if (strcmp(monthS, "may") == 0) tm.tm_mon = 4;
  else if (strcmp(monthS, "jun") == 0) tm.tm_mon = 5;
  else if (strcmp(monthS, "jul") == 0) tm.tm_mon = 6;
  else if (strcmp(monthS, "aug") == 0) tm.tm_mon = 7;
  else if (strcmp(monthS, "sep") == 0) tm.tm_mon = 8;
  else if (strcmp(monthS, "oct") == 0) tm.tm_mon = 9;
  else if (strcmp(monthS, "nov") == 0) tm.tm_mon = 10;
  else if (strcmp(monthS, "dec") == 0) tm.tm_mon = 11;
  else tm.tm_mon = 0;
  tm.tm_isdst = isdst;
  
  return mktime(&tm);
}

