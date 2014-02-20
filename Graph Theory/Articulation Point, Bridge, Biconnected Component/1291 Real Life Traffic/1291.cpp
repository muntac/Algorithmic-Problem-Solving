/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Real Life Traffic
	Algorithm    :  DFS, Bridge
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

const int SIZ = 10010;
const int INF = (1<<29);

int N, M;

struct edge{
    int v, flag;
    edge(){};
    edge( int vv, int ff ){ v = vv, flag = ff; }
}E[20020];

vector< edge > V[SIZ];
vector< int > T[SIZ];
set< pair< int, int > > S;

int timez, start[SIZ], low[SIZ];//for Bridge
int color[SIZ], bcc[SIZ], indeg[SIZ], outdeg[SIZ], comp;


void Bridge( int v, int u ){
	low[v] = start[v] = ++timez;
	int i;
	for( i = 0; i < V[v].size(); i++ ){
        int w = V[v][i].v;
        if( w != u ){//if w is not v's parent
            if( start[w] == -1 ){ //for tree edge
                Bridge( w, v );
                low[v] = min( low[v], low[w] );
                if( low[w] > start[v] ){
                     V[v][i].flag = 1;//Bridge
                     S.insert( make_pair( v, w ) );
                }
            }
            else low[v] = min( low[v], start[w] );//for other edges
        }
    }
}

void dfs_visit( int u ){
    int i, j;
    bcc[u] = comp;
    for( i = 0; i < V[u].size(); i++ ){
        int v = V[u][i].v;
        if( V[u][i].flag == 0 && bcc[v] == 0 ) dfs_visit( v );
    }
}

void make_bcc(){
    int i;
    for( i = 0; i < N; i++ ) bcc[i] = 0;
    for( i = 0, comp = 0; i < N; i++ ) if( bcc[i] == 0 ) ++comp, dfs_visit( i );
}

void dfs_visit2( int u ){
    color[u] = 1;
    for( int i = 0; i < V[u].size(); i++ ){
        int v = V[u][i].v;
        if( color[v] == 0 ){
            if( bcc[u] != bcc[v] ){
                T[bcc[u]].push_back( bcc[v] ), T[bcc[v]].push_back( bcc[u] );
                outdeg[bcc[u]]++, indeg[bcc[v]]++, outdeg[bcc[v]]++, indeg[bcc[u]]++;
            }
            dfs_visit2( v );
        }
    }
}

int make_tree(){
    int i, j, cnt = 0;
    for( i = 0; i < N; i++ ) color[i] = 0;
    for( i = 1; i <= comp; i++ ) outdeg[i] = 0, indeg[i] = 0;
    for( i = 0; i < N; i++ ) if( color[i] == 0 ) dfs_visit2( i );
    for( i = 1; i <= comp; i++ ) if( indeg[i] <= 1 || outdeg[i] <= 1) cnt++;
    if( (cnt & 1) == 0 ) return cnt / 2;
    else return ( cnt + 1 )/ 2;
}

int main(){
	//	freopen( "", "r", stdin);
	//	freopen( "", "w", stdout);
	int i, j, cases, caseno = 0, u, v, res;
	scanf("%d", &cases);
	while( cases-- ){
		scanf("%d %d", &N, &M);
	    edge temp;
	    for( i = 0, temp.flag = 0; i < M; i++ ) scanf("%d %d", &u, &temp.v), V[u].push_back( temp ), swap( temp.v, u ), V[u].push_back( temp );

        memset( start, -1, sizeof( start ) ), timez = 0;
		for( i = 0; i < N; i++ ) if( start[i] == -1 ) Bridge( i, 0 );

		for( i = 0; i < N; i++ )
            for( j = 0; j < V[i].size(); j++ )
                if( V[i][j].flag == 0 ){
                    if( S.find( make_pair( V[i][j].v, i ) ) != S.end() ) V[i][j].flag = 1;
                }

        //for( i = 0; i < N; i++ ) for( j = 0; j < V[i].size(); j++ ) if( V[i][j].flag == 1 ) printf("%d -> %d\n", i, V[i][j].v);
		make_bcc();
		//cout<<"Comp: "<<comp<<endl;
		if( comp == 1 ) res = 0;
		else res = make_tree();
		printf("Case %d: %d\n", ++caseno, res);
        for( i = 0; i <= N; i++ ) V[i].clear();
        for( i = 0; i <= comp; i++ ) T[i].clear();
        S.clear();
	}
	return 0;
}
