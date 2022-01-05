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

using namespace std;
struct ftype
{
    FILE *filename;
    int current; // to detemrmine where i have ended last time **still under progress
};
struct dat
{
    int num;
    char c;
};
pthread_t threads[5];
vector<dat> v[100];
int fun(string s, int idx)
{
    int n = s.size();
    int cnt = 1;
    for (int i = 1; i < n; i++)
    {
        if (s[i] != s[i - 1])
        {
            dat psh;
            psh.num = cnt;
            psh.c = s[i - 1];
            v[idx].push_back(psh);
            cnt = 1;
        }
        else
        {
            cnt++;
        }
    }
    dat psh;
    psh.num = cnt;
    psh.c = s[n - 1];
    v[idx].push_back(psh);
    cnt = 1;
    return 0;
}
void *zip(void *arg)
{
    clock_t b = clock();
    ftype f = *(ftype *)arg;
    int cur = f.current;
    char c;

    c = getchar();
    string s;
    while (c != EOF)
    {
        s += c;
        c = getchar();
    }
    fun(s, cur);
    clock_t e = clock();
    e -= b;
    // double f=(double)e/CLOCKS_PER_SEC;
    return 0;
    // to zip file
    // detemine where it is possible to have race condition
    // make locks for this race condition
    // be aware of that the declration of any variable here is vanished after it return
    // instead of lock we may use pthread_cond this will make it easier to code
}
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "wzip: file1 [file2 ...]\n";
        return 1;
    }
    // declare every input file in struct
    ftype files[argc];
    for (int i = 1; i < argc; i++)
    {
        files[i].filename = freopen(argv[i], "r", stdin);
        files[i].current = i;
        pthread_create(&threads[i], NULL, zip, &files[i]);
    }
    // make threads for every input file
    /*for(int i=1; i<argc; i++)
    {

        //pthread_join(threads[i],NULL);// create thread for each input file
    }*/
    // cout<<"W";
    for (int i = 1; i < argc; i++)
    {
        pthread_join(threads[i], NULL); // make the main wait untill the thread is done the compression us done
    }
    cout << v[1][0].num << endl;

    cout << v[2][0].num << endl;
    cout << v[3][0].num << endl;
    for (int i = 2; i < argc; i++)
    {
        int sz1 = v[i - 1].size() - 1;
        if (v[i - 1][sz1].c == v[i][0].c)
        {
            v[i][0].num += v[i - 1][sz1].num;
            v[i - 1].pop_back();
        }
    }
    // FILE* fpp=freopen("out.out","w",stdout);
    for (int i = 1; i < argc; i++)
    {
        for (auto x : v[i])
        {
            fwrite(&x.num, 1, sizeof(x.num), stdout);
            fwrite(&x.c, 1, sizeof(x.c), stdout);
        }
    }
    //    fclose(fpp);
    return 0;
}
