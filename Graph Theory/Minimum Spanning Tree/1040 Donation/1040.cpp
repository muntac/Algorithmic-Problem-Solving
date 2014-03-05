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
typedef unsigned long ulint;

const int SIZ = 110;
const int INF = (1<<29);
const double ESP = 1e-11;

int N, caseno = 0, parent[SIZ], cnt;

struct edge{
	int u, v, w;
    bool operator < ( const edge &b ) const{
        return w < b.w;
    }
}G[2510];

int findset( int x ){
    if( x != parent[x] ) parent[x] = findset( parent[x] );
    return parent[x];
}

int MST(){
	int i, pu, pv, total = 0;
	for( i = 0; i < N; i++ ) parent[i] = i;
	sort( G, G + cnt + 1 );
	for( i = 0; i < cnt + 1; i++ ){
	    pu = findset( G[i].u );
		pv = findset( G[i].v );
		if( pu != pv ){
			parent[pu] = parent[pv];
			total += G[i].w;
		}
	}
	return total;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j, res;
	scanf("%d", &cases);
	while( cases-- ){
		scanf("%d", &N);
		cnt = -1;
		int w, sum = 0;
		for( i = 0; i < N; i++ ){
            for( j = 0; j < N; j++ ){
		        scanf("%d", &w), sum += w;
		        if( i == j || w == 0 ) continue;
		        ++cnt, G[cnt].u = i, G[cnt].v = j, G[cnt].w = w;
		    }
		}
		res = sum - MST();
		for( i = 0; i < N; i++ ){
            for( j = 0; j < N; j++ ){
                if( findset( i ) != findset(j ) ){res = -1;break;}
            }
		}
		printf("Case %d: %d\n", ++caseno, res);
	}
	return 0;
}
