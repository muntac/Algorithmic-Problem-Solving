/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Placing Lampost
	Algorithm    :  DP on rooted tree
	Complexity   :	O( 2V ) */

//HEADERFILE
#include<iostream>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<set>
#include<map>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<cstring>
#include<ctime>
#include<cassert>
#include<string>
#include<algorithm>

using namespace std;

const int SIZ = 1002;

int N, color[SIZ], fcaller;
pair<int,int> mem[SIZ][2];
vector<int> V[SIZ], T[SIZ];

pair<int,int> f( int i, int pstate ){
    if( mem[i][pstate].first != -1 ) return mem[i][pstate];
    int j;
    pair<int,int> res1, res2, res, temp;
    if( pstate == 0 ){
        for( j = 0, res.first = 1, res.second = 0; j < T[i].size(); j++ ){
             temp = f( T[i][j], 1 );
             res.first += temp.first, res.second += temp.second;
        }
    }
    else{
        for( j = 0, res1.first = 0, res1.second = 0; j < T[i].size(); j++ ){
            temp = f( T[i][j], 0 );
            res1.first += temp.first, res1.second += temp.second;
        }
        i == fcaller ? res2.second = 0 : res2.second = 1;
        for( j = 0, res2.first = 1; j < T[i].size(); j++ ){
            temp = f( T[i][j], 1 );
            res2.first += temp.first, res2.second += temp.second;
        }
        if( res1.first < res2.first ) res = res1;
        else if( res1.first > res2.first ) res = res2;
        else{
            res.first = res1.first, res.second = max( res1.second, res2.second );
        }
    }
    return mem[i][pstate] = res;
}

void dfs( int u ){
    for( int i = 0; i < V[u].size(); i++ ){
        if( color[V[u][i]] == 0 ){
            color[V[u][i]] = 1;
            dfs( V[u][i] );
            T[u].push_back(V[u][i]);
        }
    }
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, caseno = 0, i, root, M, u, v, cnt;
	scanf("%d", &cases);
	while( cases-- ){
	    memset( mem, -1, sizeof(mem) );
	    scanf("%d %d", &N, &M);
	    for( i = 0; i < M; i++ ) scanf("%d %d", &u, &v), V[u].push_back(v), V[v].push_back(u);
	    memset( color, 0, sizeof(color) );
	    pair<int,int> res, temp;
	    for( i = 0, res.first = 0, res.second = 0; i < N; i++ ){
	        if( color[i] == 0 ){
	            color[i] = 1; dfs( i );
	            fcaller = i;
                temp = f( i, 1 );
                res.first += temp.first, res.second += temp.second;
	        }
        }
	    printf("Case %d: %d %d %d\n", ++caseno, res.first, res.second, M - res.second);
		for( i = 0; i <= N; i++ ) V[i].clear(), T[i].clear();
	}
	return 0;
}
