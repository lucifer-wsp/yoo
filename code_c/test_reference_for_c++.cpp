#include <cstdio>


void exchange(int& a){
  printf ("**********exchange function********\n");
  printf ("get a = %d.\n",a);
  a=12;
  printf ("after exchanging ,a = %d.\n",a);
}

int main ()
{
  int a=10;
  printf ("*****main function ********\n");
  printf ("a = %d.\n",a);
  exchange(a);
  printf ("after calling exchange ,a = %d.\n",a);

  return 0;
 }