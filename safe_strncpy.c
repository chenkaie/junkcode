
/****************************************************************
 * 
 * Purpose: Program to demonstrate the 'strncpy' function.
 * Author:  M J Leslie
 * Date:    03-Feb-96
 * 
 ****************************************************************/

#include <string.h>	/* strcpy */
#include <stdio.h>

void SafeCopy(char *Dest, int DestSize, char *Source);

int main()
{
    char Text1[20]="Tracy Sorrell";		/* string buffer	*/
    char Text2[10]="Martin";       		/* string buffer	*/

    printf (" Original string contents are: %s\n", Text2);

    SafeCopy(Text2, sizeof(Text2), Text1);
  
    printf (" New string contents are: %s\n", Text2);

    strcpy(Text2, "Alex");
  
    printf (" Final string contents are: %s\n", Text2);

}

/****************************************************************/

void SafeCopy(
    char     *Dest,                   /* Destination buffer. */
    int       DestSize,
    char     *Source)                 /* Source data. */
{
  
    /* ...	Copy 'Source' into 'Dest'.
     * ...        'Dest' is padded with NULLs if 'Source' is smaller.. */
  
    strncpy(Dest, Source, DestSize);
  
    /* ...	Safety net! Add the NULL just in case 'Source' is larger
     * ...	than 'Dest'.  */
  
    Dest[DestSize-1] = '\0';
}
