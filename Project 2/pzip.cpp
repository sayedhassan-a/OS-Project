/*
1-if file cannot be opened what will we do ?
2-after every file is compressed should us compin  them or save in seperated files ?

*/
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <mutex>

using namespace std;
struct ftype
{
    FILE *filename;
    int current; // to detemrmine where i have ended last time still under progress
};
struct dat
{
    int num;
    char c;
};
pthread_t threads[100];
vector<dat> v[100];

void *zip(void * arg)
{
    // to zip file
    // detemine where it is possible to have race condition
    // make locks for this race condition
    // be aware of that the declration of any variable here is vanished after it return
    // instead of lock we may use pthread_cond this will make it easier to code
    ftype f= *(ftype*)arg;
    int idx=f.current;
    FILE* fp=f.filename;
    char c;
    //cout<<cur<<endl;
    c=fgetc(fp);
    char curr=c;
    int cnt=0;
    while(c!=EOF)
    {
        if(curr!=c)
        {
            dat psh;
            psh.num=cnt;
            psh.c=curr;
            v[idx].push_back(psh);
            curr=c;
            cnt=1;
            c=fgetc(fp);
            continue;
        }
 
        cnt++;
        c=fgetc(fp);
    }
    dat psh;
    psh.num=cnt;
    psh.c=curr;
    v[idx].push_back(psh);
    curr=c;
    cnt=1;
    return 0;    
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "wzip: file1 [file2 ...]\n";
        return 1;
    }
    //declare every input file in struct
    ftype files[argc];
    for (int i = 1; i < argc; i++)
    {
        files[i].filename = fopen(argv[i], "r");
        files[i].current=i;
        if(i>1)pthread_create(&threads[i],NULL,zip,&files[i]);
        else zip(&files[i]);
    }
    // make threads for every input file
    for(int i=2; i<argc; i++)
    {
        pthread_join(threads[i],NULL);
        fclose(files[i].filename);//make the main wait untill the thread is done the compression us done
    }
    for(int i=2; i<argc; i++)
    {
        int sz1=v[i-1].size()-1;
        if(v[i-1][sz1].c==v[i][0].c)
        {
            v[i][0].num+=v[i-1][sz1].num;
            v[i-1].pop_back();
        }
    }
    for(int i=1; i<argc; i++)
    {

        for(auto x:v[i])
        {
            fwrite(&x.num, 1, sizeof(x.num), stdout );
            fwrite(&x.c, 1, sizeof(x.c), stdout );


        }
    }

//    fclose(fpp);
    return 0;
}
