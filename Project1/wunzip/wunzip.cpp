#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
   /*freopen(argv[0],"r",stdin);
   freopen(argv[1],"w",stdout);*/
   // freopen("output.txt","w",stdout);

   if (argc == 1)
   {
      cout << "wunzip: file1 [file2 ...]\n";
      return 1;
   }

   char c;
   int num = 0;
   for (int i = 1; i < argc; i++)
   {
      FILE *fp;
      fp = freopen(argv[i], "r", stdin);
      
      while (fread(&num,  sizeof(num),1, fp)==1)
      {

         fread(&c,  sizeof(c),1, fp);
         for (int j = 0; j < num; j++)
            cout << c;
         
      }
      fclose(fp);
   }
   return 0;
}
