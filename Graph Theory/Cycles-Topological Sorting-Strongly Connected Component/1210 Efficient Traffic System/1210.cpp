/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :
	Algorithm    :
	Complexity   :	*/

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

typedef __int64 lint;
typedef unsigned __int64 ulint;

const int SIZ = 20001;
const int INF = (1<<29);

int N, m, color[SIZ], in[SIZ], out[SIZ], scolor;
list <int> L[SIZ], ord, Rev[SIZ];

int dfs_visit( int u ){
    color[u] = 1;
    list<int>::iterator k;
    for( k = L[u].begin(); k != L[u].end(); k++ ) if( color[*k] == 0 ) dfs_visit(*k);
    ord.push_front(u);
}

int dfs_visit_rev( int u ){
    color[u] = scolor;
    list<int>::iterator k;
    for( k = Rev[u].begin(); k != Rev[u].end(); k++ ) if( color[*k] == 0 ) dfs_visit_rev(*k);
}

int dfs(){
    int i, ar[SIZ], x = 0, res, u, v, found;
    list<int>::iterator k;
    for( i = 1; i <= N; i++ ) color[i] = 0;
    for( i = 1; i <= N; i++ ) if( color[i] == 0 ) dfs_visit(i);
    for( i = 1; i <= N; i++ ) color[i] = 0;
    for( k = ord.begin(); k != ord.end(); k++ ) ar[x++] = *k;
    for( i = 0, scolor = 0; i < N; i++ ) if( color[ar[i]] == 0 ) ++scolor, dfs_visit_rev(ar[i]);
}

int topsort(){
    ord.clear(), dfs();
    if (scolor == 1) return 0;
    int i, inz = 0, outz = 0;
    list<int>::iterator k;
    for( i = 1; i <= N; i++ ) in[i] = out[i] = 0;
    for( i = 1; i <= N; i++ ) for( k = L[i].begin(); k != L[i].end(); k++ ) if ( color[i] != color[*k] ) ++out[color[i]], ++in[color[*k]];
    for( i = 1; i <= scolor; i++ ){
        if( in[i] == 0 ) ++inz;
        if( out[i] == 0 ) ++outz;
    }
    return max( inz, outz );
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, caseno = 0, i, j, res, u, v;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %d", &N, &m);
	    for( i = 0; i < m; i++ ){
            scanf("%d %d", &u, &v);
            L[u].push_back(v), Rev[v].push_back(u);
	    }
	    if( N == 1 ) res = 0;
        else res = topsort();
		printf("Case %d: %d\n", ++caseno, res);
		for( i = 1; i <= N; i++ ) L[i].clear(), Rev[i].clear();
	}
	return 0;
}
