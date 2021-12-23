#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
struct dat
{
    int num;
    char c;
};
vector<dat> v;
vector<int> lines;
int main()//int argc, char** argv)
{
    /*freopen(argv[0],"r",stdin);
    freopen(argv[1],"w",stdout);*/
    freopen("file.txt","r",stdin);
    //freopen("file2.txt","w",stdout);
    FILE *fp;
    fp = fopen( "file2.txt" , "w" );
    string s;
    char c;
    bool ch=0;
    int cnt2=0;
    while(c!=EOF)
    {

        getline(cin,s);
        int cnt=0;
        char chck;
        if(ch)
        {
            cnt++;
            chck=c;
        }
        else
        {
            chck=s[0];
        }
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==chck)cnt++;
            else
            {
                dat x;
                x.num=cnt;
                x.c=chck;
                if(x.c=='\n') {
                    cnt=1;
                    chck=s[i];
                    ch=1;
                    c=getchar();
                    continue;
                }
                v.push_back(x);
                cnt=1;
                chck=s[i];
                cnt2++;
            }
        }
        if(cnt)
        {
            dat x;
            x.num=cnt;
            x.c=chck;
            if(x.c=='\n') {
                ch=1;
                c=getchar();
                continue;
            }
            v.push_back(x);
            cnt2++;
        }
        lines.push_back(cnt2);
        c=getchar();
        ch=1;

    }
    int i=0,idx=0;
    for(auto x:v){
        i++;
        fwrite(&x , 1 , sizeof(x) , fp );
        //fwrite(&x.c , 1 , sizeof(x.c) , fp );
        if(lines[idx]==i)
        {
            string s="\n";
            fwrite(&s , 1 , sizeof(s) , fp );
            idx++;
        }

    }
    /*cout<<endl;
    i=0;idx=0;
    for(auto x:v)
    {
        i++;
        if(lines[idx]==i)idx++;
        cout<<idx<<" "<<lines[idx]<<" "<<i<<endl;
    }*/
    return 0;
}