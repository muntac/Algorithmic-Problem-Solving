/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Lucky Number
	Algorithm    :  Segment Tree
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

const int SIZ = 150100;
const int INF = (1<<29);
const double EPS = 1e-11;
#define left 2 * idx + 1
#define right 2 * idx + 2
int N, Q, caseno = 0, cnt, ar[SIZ];

struct tree{
    int low, high, lt, rt, val, have;
}S[(1<<19) + 10];

int makeTree( int idx, int low, int high ){
    S[idx].low = low, S[idx].high = high, S[idx].val = 0, S[idx].have = 1;
    if( low != high ){
        int mid = ( low + high ) / 2;
        S[idx].lt = makeTree( left, low, mid );
        S[idx].rt = makeTree( right, mid + 1, high );
        return S[idx].lt + S[idx].rt;
    }
    else{
        S[idx].val = ar[low];
        if( low <= N ){ S[idx].have = 1; return 1; }
        S[idx].have = 0;
        return 0;
    }
}

int find( int idx, int x ){
    if( S[idx].low == S[idx].high ) return idx;
    if( x <= S[idx].lt ){
         int res = find( left, x );
         if( S[res].have != 0 ) S[idx].lt--;
         return res;
    }
    else{
        int res = find( right, x - S[idx].lt );
        if( S[res].have != 0 ) S[idx].rt--;
        return res;
    }
}

void add( int idx, int x, int val ){
    if( S[idx].low == S[idx].high ){
        //printf("Add: %d %d %d %d\n", idx, S[idx].val, S[idx].have, x);
        //printf("Adddd: %d %d\n", S[idx].low, S[idx].high);
        S[idx].val = val, S[idx].have = 1; return;
    }
    int mid = (S[idx].low + S[idx].high) / 2;
    if( x <= mid ) S[idx].lt++, add( left, x, val );
    else S[idx].rt++, add( right, x, val );
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j, res;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %d", &N, &Q);
	    memset( ar, 0, sizeof(ar) );
	    for( i = 1; i <= N; i++ ) scanf("%d", &ar[i]);
        makeTree( 0, 1, N + Q );
        int id, next = N + 1;
        char st[4];
        printf("Case %d:\n", ++caseno);
        for( i = 0; i < Q; i++ ){
            scanf("%s %d", st, &id);
            if( st[0] == 'c' ){
                if( id > S[0].lt + S[0].rt ) printf("none\n");
                else{
                    int idx = find( 0, id );
                    if( !S[idx].have ) printf("none\n");
                    else{
                        S[idx].have = 0;
                        printf("%d\n", S[idx].val);
                    }
                }
            }
            else
                add( 0, next++, id );
        }
	}
	return 0;
}
