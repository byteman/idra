//---------------------------------------------------------------------------


#pragma hdrstop

#include "bylogger.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

void bylog(const char* fmt,...)
{
  #define PF_SIZE 1024
      static char buf[PF_SIZE];
	  va_list ap;
	  int n;

	  memset(buf,0,PF_SIZE);
	  va_start(ap, fmt);
	  n = vsnprintf(buf, PF_SIZE, fmt, ap);
		  if (n < 0) {
		  	n = 0;
	  }
      else if (n >= (int) (PF_SIZE)) {
	  		n = (int) PF_SIZE - 1;
	  }
	  buf[n] = '\0';

	  va_end(ap);
	  GUI_OUTPUT(buf);
}

