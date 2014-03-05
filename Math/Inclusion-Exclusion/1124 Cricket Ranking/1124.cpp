/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :
	Algorithm    :
	Complexity   :	*/

//HEADERFILE
#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lint;
typedef unsigned long long ulint;

const int SIZ = 100100;
const int INF = (1<<29);
const int MOD = 100000007;
const double EPS = 1e-11;

int K, N, caseno = 0;
int sum, low[12], high[12];
const int lim = 1000010;
lint F[lim];

void fact(){
    F[0] = 1;
    for( int i = 1; i <= lim - 10; i++ ) F[i] = (F[i - 1] * i) % MOD;
}

lint bigMod( lint a, lint p, lint m ) { // a^p % m
	if( p < 0 ) return 1;//depends on problem
	lint res = 1;
	while(p) {
		if( p & 1LL ) res = ( res * a ) % m;
		a = ( a * a ) % m;
		p >>= 1LL;
	}
	return res;
}

lint C( lint a, lint b ){
    lint k = (F[a-b] * F[b]) %MOD;
    k = bigMod( k, MOD - 2, MOD );
    return (F[a] * k) % MOD;
}


int f( int mask ){
    int i, j;
    int x = N, cnt = 0;
    for( i = 0; i < K; i++ ) if( (mask & (1<<i)) ) x -= high[i] + 1, ++cnt;
    if( x >= 0 ){
        x = C( x + K - 1, K - 1 );
        if( (cnt & 1) ) return -x;
        return x;
    }
    return 0;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	fact();
	int cases, i, j, res;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %d", &K, &N);
	    for( i = 0; i < K; i++ ) scanf("%d %d", &low[i], &high[i]), N -= low[i], high[i] -= low[i];
	    if( N < 0 ) res = 0;
	    else{
            for( i = 0, res = 0; i < (1<<K); i++ )
                res = ( ( res + f( i ) ) % MOD + MOD ) % MOD;
	    }
        printf("Case %d: %d\n", ++caseno, res);
	}
	return 0;
}
