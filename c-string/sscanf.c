#include <stdio.h>

int main() {
  char name[20], tel[50], field[20], areaCode[20], code[20];
  int age;
  sscanf("name:john age:40 tel:082-313530", "%s", name);
  printf("%s\n", name);
  sscanf("name:john age:40 tel:082-313530", "%8s", name);
  printf("%s\n", name);
  sscanf("name:john age:40 tel:082-313530", "%[^:]", name);
  printf("%s\n", name);
  sscanf("name:john age:40 tel:082-313530", "%[^:]:%s", field, name);
  printf("%s %s\n", field, name);
  sscanf("name:john age:40 tel:082-313530", "name:%s age:%d tel:%s", name, &age, tel);
  printf("%s %d %s\n", name, age, tel);
  sscanf("name:john age:40 tel:082-313530", "%*[^:]:%s %*[^:]:%d %*[^:]:%s", name, &age, tel);
  printf("%s %d %s\n", name, age, tel);

  char protocol[10], site[50], path[50];
  sscanf("http://ccckmit.wikidot.com/cp/list/hello.txt", 
         "%[^:]:%*2[/]%[^/]/%[a-zA-Z0-9._/-]", 
         protocol, site, path);
  printf("protocol=%s site=%s path=%s\n", protocol, site, path);
  return 1;
}
