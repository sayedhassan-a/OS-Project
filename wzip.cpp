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
    for(int i=1;i<n&&s[i]!='\n';i++)
    {
        if(s[i]!=s[i-1])
        {
            dat psh;
            psh.num=cnt;
            psh.c=s[i-1];
            v.push_back(psh);
            cnt=1;
//            cout<<"#"<<s[i]<<"#";
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

        p=freopen(argv[1],"r",stdin);
        c='b';
        while(c!=EOF)
        {
            chk=c;
            c=getchar();
            if(c==-1)continue;
            if(chk=='\n'&&c=='\n')
            {
                int sze=v.size();
                v[sze-1].num++;
                continue;
            }
            if(c=='\n')
            {

                fun();
                dat temp;
                temp.num=1;
                temp.c='\n';
                v.push_back(temp);
                s.clear();
                continue;
            }
            s+=c;

        }
        fclose(p);
    }

    if(!s.empty())fun();
    for(auto x:v){
        //cout<<x.num<<" "<<x.c<<endl;
        fwrite(&x.num, 1 , sizeof(x.num) , stdout );
        fwrite(&x.c , 1 , sizeof(x.c) , stdout );


    }

    return 0;
}
