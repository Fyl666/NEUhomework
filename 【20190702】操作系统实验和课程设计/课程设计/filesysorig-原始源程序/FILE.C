#include "stdio.h"
#include "string.h"
main()
{
   FILE *fp;
   char str[100], ch, c[200];
   int i = 0;
   if ((fp = fopen("test", "w")) == NULL)
   {
      printf("wrong\n");
      exit(0);
   }
   /* fp=fopen("d:\tc2\TURBOC2\test.txt","w");*/

   scanf("%c", &str[i]);
   while (str[i] != '!')
   {
      fputc(str[i], fp);
      i++;
      scanf("%c", &str[i]);
   }
   fclose(fp);
   if ((fp = fopen("test", "r")) == NULL)
   {
      printf("Test is wrong");
      exit(0);
   }
   for (i = 0; (ch = fgetc(fp)) != EOF; i++)
   {
      c[i] = ch;
      putchar(c[i]);
   }
   fclose(fp);
}