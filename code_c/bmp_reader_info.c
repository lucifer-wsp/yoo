#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define null NULL

BITMAPFILEHEADER bmpfile;
BITMAPINFOHEADER bmpinfo;

int main ()
{
  FILE* fp = null;
  
  fp = fopen ("DATA5611.BMP","rb");
  if (fp != null){
  	fread (&bmpfile,sizeof (bmpfile),1,fp);
  	fread (&bmpinfo.biSize,sizeof (DWORD),1,fp);
  	fread (&bmpinfo.biWidth,sizeof (LONG),1,fp);
  	fread (&bmpinfo.biHeight,sizeof (LONG),1,fp);
  	
  	printf ("bmp file width = %d,height = %d.\n",bmpinfo.biWidth,bmpinfo.biHeight);
  }

  return 0;
}