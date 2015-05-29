#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define M 1000

//it is a replace function and replace oldc by newc
char* exchange (char s[],char oldc,char newc){
	int i;
	for(i=0;i<strlen(s);i++){
		if(s[i]==oldc){
			s[i]=newc;
		}
	}
	strcat(s,".class");
	
	return s;
}
	
	
//this is a get directory path from a given file name 
char* get_dir(char s[],char sep){
	int  i=0;
	
	for(i=strlen(s);i>=0;i--){
		if(s[i]==sep){
			s[i]=0;
			break;
		}
	}	
	
	return s;
}


/*
	this is a simple code and using it to simple jre class.
	using 'java -jar -verbose:class MyJar.jar >> class.txt' command to get all referenced class of MyJar.jar.
	then using system() func to call os's function to copy all class from rt.jar if needed and get final rt.jar and it's simple.	
*/
int main ()
{ 
  FILE* fp;
  FILE* fp2;
  int i;
  char s[7][M],buf[M];
  char copy_file_cmd[M];
  char new_file_name[M];
  char mkdir[M];
  
  fp=fopen("class.txt","r");
  fp2=fopen("rt.txt","rw+");
  
  if(fp != NULL){
		if(fp2!= NULL){
			while(fgets(buf,M,fp)){
				memset(copy_file_cmd,0,M);
				memset(new_file_name,0,M);
				memset(mkdir,0,M);
				
				memcpy(copy_file_cmd,"copy ",5);
				memcpy(new_file_name,"rt\\",3);
				memcpy(mkdir,"md ",3);
				
				sscanf(buf,"%s%s%s%s",s[0],s[1],s[2],s[3]);
				fprintf(fp2,"%s\n",exchange(s[1],'.','\\'));
				
				strcat (copy_file_cmd,s[1]);
				strcat (copy_file_cmd," ");
				
				strcat (new_file_name,s[1]);
				strcat (copy_file_cmd,new_file_name);
				strcat (mkdir,get_dir(new_file_name,'\\'));
				
				system(mkdir);
				system(copy_file_cmd);			
			}
		}
		fclose(fp);
		fclose(fp2);		
  }
  
  return 0;
}