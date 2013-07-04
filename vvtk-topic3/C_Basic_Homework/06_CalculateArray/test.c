#include <stdio.h>

int main()
{
  int nbytes = 100;
  char *my_string;
  int int1, int2, int3;
  int args_assigned;

  args_assigned = 0;

  while (args_assigned != 3)
    {
      puts ("Please enter three integers separated by whitespace.");
      my_string = (char *) malloc (nbytes + 1);
      getline (&my_string, &nbytes, stdin);
      args_assigned = sscanf (my_string, "%d %d %d", &int1, &int2, &int3);
      if (args_assigned != 3)
    puts ("\nInput invalid!");
    }

  printf ("\nThanks!\n%d\n%d\n%d\n", int1, int2, int3);

  return 0;
}

