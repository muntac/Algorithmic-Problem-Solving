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

const int SIZ = 10100;
const int INF = (1<<29);
const lint mod = 1000000007;
const double EPS = 1e-11;

int N, caseno = 0;

int primes[1000], status[SIZ/2], plln;

void sieve( int x ){
    int i, j, sqrtD;
    int D = x;
    sqrtD = (int)sqrt((double)D);
    memset( status, 0, sizeof(status) );
    for( i = 3; i <= sqrtD; i += 2 ){
        if( status[(i-1)/2] == 0 ){
            for( j = i * i; j <= D; j += 2 * i ) status[(j-1)/2] = 1;
        }
    }
    primes[0] = 2;
    for( i = 3, plln = 1; i <= D; i += 2 ) if( !status[(i-1)/2] ) primes[plln++] = i;
}

lint mem[510][510], zem[510][510], pfact[510];

lint f( int x, int P ){
    if( x == 0 ) return 1;
    lint &ret = zem[x][P];
    if( ret != -1 ) return ret;
    lint res = 0;
    for( int i = P - 1; i >= 0; i-- )
        res = ( res + (( primes[i] * f( x - 1, i + 1 ) ) % mod) ) % mod;
    return ret = res;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	sieve( 4000 );
	int cases, i, j, res;

	pfact[0] = 1;
	for( i = 1; i < 501; i++ ) pfact[i] = ( (primes[i] - 1) * pfact[i - 1] ) % mod;

	memset( zem, -1, sizeof(zem) );
		for( i = 1; i <= 500; i++ )
        for( j = 1; j <= i; j++ )
            mem[i][j] = (pfact[j - 1] * f( i - j, j )) % mod;
	scanf("%d", &cases);

	while( cases-- ){
        int K, P;
        scanf("%d %d", &K, &P);
        printf("Case %d: %lld\n", ++caseno, mem[K][P]);
	}
	return 0;
}
