#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
struct dat
{
    int num;
    char c;
};
string s;
vector<dat> v;
int fun()
{
    int n=s.size();
    int cnt=1;
    for(int i=1;i<n;i++)
    {
        if(s[i]!=s[i-1])
        {
            dat psh;
            psh.num=cnt;
            psh.c=s[i-1];
            v.push_back(psh);
            cnt=1;
        }
        else
        {
            cnt++;
        }
    }
    dat psh;
    psh.num=cnt;
    psh.c=s[n-1];
    v.push_back(psh);
    cnt=1;
    return 0;
}
int main(int argc, char** argv)
{

    char c,chk='a';
    if(argc==1)
    {
        cout<<"wzip: file1 [file2 ...]\n";
        return 1;
    }
    for(int i=1;i<argc;i++)
    {
        FILE* p;

        p=freopen(argv[i],"r",stdin);
        c=getchar();
        while(c!=EOF)
        {

            s+=c;
            c=getchar();
        }
        fclose(p);
    }
    fun();
    for(auto x:v){
        fwrite(&x.num, 1 , sizeof(x.num) , stdout );
        fwrite(&x.c , 1 , sizeof(x.c) , stdout );


    }

    return 0;
}
