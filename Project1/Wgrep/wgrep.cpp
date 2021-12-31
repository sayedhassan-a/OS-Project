

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long int ll;
typedef double ld;
const int OO = 0x3f3f3f3f, MOD = 1e9 + 7;
const long double EPS = 1e-8;
const ll loo = 0x3f3f3f3f3f3f3f3f;
ll egcd(ll a, ll b, ll &x, ll &y) /// ax + by = gcd(a,b)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll g = egcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

ll modInverse(ll a, ll m) /// (a/b)%m = ((a%m)*(modInverse(b)%m))%m
{
    ll x, y, g;
    g = egcd(a, m, x, y);
    if (g > 1)
        return -1;
    return (x + m) % m;
}
ll fixMod(ll a, ll m)
{
    return (a + m) % m;
}
ll PushFront(ll h, ll xp, char ch, ll p)
{
    return (h + (xp * ch) % p) % p;
}
ll PopBack(ll h, ll x, char ch, ll p)
{
    return (fixMod(h - ch, p) * modInverse(x, p)) % p;
}
ll PushBack(ll h, ll x, ll p, char ch)
{
    return (((h * x) % p) + ch) % p;
}
ll popFront(ll h, ll xp, ll p, char ch)
{
    return fixMod(h - ((xp * ch) % p), p);
}

int main(int argc, char **argv)
{
    
        ll x = 128,
           p1 = 1e9 + 7, p2 = 1e9 + 9;
    vector<ll> xp1(1e5 + 1), xp2(1e5 + 1);
    xp1[0] = xp2[0] = 1;
    for (int i = 1; i < 100000; i++)
    {
        xp1[i] = (x * xp1[i - 1]) % p1;
        xp2[i] = (x * xp2[i - 1]) % p2;
    }
   if(argc==3)
   { 
   	FILE *num=freopen(argv[2], "r", stdin);
   	if(num==NULL) {
    cout<<"wgrep: cannot open file"<<endl;
    return 1;}
   }
    //cout<<num<<endl;
    if(argc==1){
    cout<<"wgrep: searchterm [file ...]"<<endl;
    return 1;
    }
    
    string z, y;
    y = argv[1];
    if(y.size()==0)return 0;
    int m = y.size();
    ll hy = 0, hy2 = 0;
    for (int i = 0; i < m; i++)
    {
        hy = PushBack(hy, x, p1, y[i]);
        hy2 = PushBack(hy2, x, p2, y[i]);
    }

    char c;
    int ch=0,b=0;
    while (c != EOF)
    {
    if(c=='\n')
    { c= getchar(),b=1;
    continue;}
    
        ll hz = 0, hz2=0;
        getline(cin, z);
        //cout << z << endl;
	if(b)z=c+z;
        int n = z.size();
        for (int i = 0; i < min(n, m); i++)
        {
            hz = PushBack(hz, x, p1, z[i]);
            hz2 = PushBack(hz2, x, p2, z[i]);
        }

        for (int i = m; i < n; i++)
        {
            hz = popFront(hz, xp1[m - 1], p1, z[i - m]);
            hz = PushBack(hz, x, p1, z[i]);
            hz2 = popFront(hz2, xp2[m - 1], p2, z[i - m]);
            hz2 = PushBack(hz2, x, p2, z[i]);
            if (hz == hy && hz2 == hy2)
            {
                if (ch && !b)
                {
                    cout << c;
                }

                cout << z << endl;
                break;
            }
        }
        c = getchar();
      
        ch = 1;
    }
    return 0;
}
