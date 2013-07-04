#include <stdio.h>
#include "cyg-profile.h"

int
function1 (void)
{
  return 0;
}

int
function2 (void)
{
  return function1 () + 1;
}

int
function3 (void)
{
  return function2 () + 1;
}

int
main (void)
{
  printf ("Logfile: %s\n", cygprofile_getfilename ());
  cygprofile_enable ();
  return function3 ();
}
