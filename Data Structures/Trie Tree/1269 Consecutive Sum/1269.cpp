/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Consecutive Sum Integer
	Algorithm    :  Trie Tree
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

typedef __int64 lint;
typedef unsigned __int64 ulint;

const int SIZ = 50100;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, P, curr, sum[SIZ];

struct trie{
    int ar[2];
    void clear(){
        ar[0] = -1, ar[1] = -1;
    }
}T[4000000];

int maxTraverse( int i ){
    int j, res = 0, st;
    for( j = 30, P = 0; j >= 0; j-- ){
        (sum[i] & (1<<j)) == 0 ? st = 1 : st = 0;
        if( T[P].ar[st] == - 1 ) P = T[P].ar[st ^ 1], res |= ( ( st ^ 1 ) << j );
        else P = T[P].ar[st], res |= (st<<j);
        //T[P].ar[st] == - 1 ? P = T[P].ar[st ^ 1], res |= ( ( st ^ 1 ) << j ) : P = T[P].ar[st], res |= (st<<j);
    }
    return res;
}

int minTraverse( int i ){
    int j, res = 0, st;
    for( j = 30, P = 0; j >= 0; j-- ){
        (sum[i] & (1<<j)) == 0 ? st = 0 : st = 1;
        if( T[P].ar[st] == - 1 ) P = T[P].ar[st ^ 1], res |= ( ( st ^ 1 ) << j );
        else P = T[P].ar[st], res |= (st<<j);
    }
    return res;
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("was.txt", "w", stdout);
	int cases, caseno = 0, i, j, st, res, ar[SIZ], freenode, curr, maxRes, minRes;
	ar[0] = sum[0] = 0;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d", &N);
	    for( i = 1; i <= N; i++ ) scanf("%d", &ar[i]), sum[i] = sum[i-1] ^ ar[i];
        maxRes = 0, minRes = 2147483647;
        int maxCurr, minCurr;
        T[0].clear();
	    for( i = 0, freenode = 0, res = 0; i <= N; i++ ){
	        if( i != 0 ) maxCurr = maxTraverse( i ), minCurr = minTraverse( i );
            for( j = 30, P = 0; j >= 0; j-- ){
                (sum[i] & (1<<j)) == 0 ? st = 0 : st = 1;
                if( T[P].ar[st] == -1 ){
                    T[P].ar[st] = ++freenode;
                    T[freenode].clear();
                }
                P = T[P].ar[st];
            }
            if( i != 0 ){
                if( (sum[i] ^ maxCurr) > maxRes ) maxRes = sum[i] ^ maxCurr;
                if( (sum[i] ^ minCurr) < minRes ) minRes = sum[i] ^ minCurr;
            }
        }
		printf("Case %d: %d %d\n", ++caseno, maxRes, minRes);
    }
	return 0;
}
