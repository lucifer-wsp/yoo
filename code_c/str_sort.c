#include<stdio.h>

#define M 100
#define LEN 30

int main ()
{
	int n,i;
	char get_str[M][LEN];
	
	while(scanf("%d",&n)!=EOF){
	  for(i=0;i<n;i++){
	    scanf("%s",get_str[i]);
	    if(!(i%2)){
	 	    printf ("%s ",get_str[i]);
	 	  }
	  }
	  for(i=n-1;i>0;i--){
	  	if(i%2){
	  		printf ("%s ",get_str[i]);
	  	}
	  }
	  printf ("\n");
	}
  return 0;
}