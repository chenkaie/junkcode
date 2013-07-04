// ---------------------------------------------
// file open/close test
// ---------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define EXAMPLE
void FileOpenCloseTest(void)
{
    FILE *fptr;

    fptr = fopen("test.dat", "rb");
    if(fptr == NULL)
    {
        return;
    }
    fwrite("1234", 1, 4, fptr);
    fclose(fptr);
    // write after closed
    fwrite("1234", 1, 4, fptr);

    if((fptr = fopen("test.dat", "rb")) != NULL)
    {
        // did not close it after open
        //fclose(fptr);
    }
}

int main (int argc, char const* argv[])
{
    FileOpenCloseTest();
    return EXIT_SUCCESS;
}

