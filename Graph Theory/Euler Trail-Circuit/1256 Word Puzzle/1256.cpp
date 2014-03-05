/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Word Puzzle
	Algorithm    :  Euler Path
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

const int SIZ = 30;

int N, nodes, indeg[SIZ], outdeg[SIZ], color[SIZ], start, end, any;

struct edges{
    int v;
    char st[SIZ];;
}tempedge;
vector <edges> V[SIZ];
list <string> final;

int check_euler(){
    int i, neq = 0;
    start = -1, end = -1;
    for( i = 0; i < 26; i++ ){
        if( indeg[i] != outdeg[i] ) neq++;
        if( indeg[i] != outdeg[i] && indeg[i] == outdeg[i] - 1 ) start = i;
        else if( indeg[i] != outdeg[i] && indeg[i] == outdeg[i] + 1 ) end = i;
    }
    if( neq == 0 ) return 2;
    else if( neq == 2 && start != -1 && end != -1 ) return 1;
    else return 0;
}

int dfs( int u ){
    color[u] = 1;
    int i, cnt = 1;
    for( i = 0; i < V[u].size(); i++ ){
        if( color[V[u][i].v] == 0 ) cnt += dfs( V[u][i].v );
    }
    return cnt;
}

int check_connectivity( int euler ){
    int res;
    memset( color, 0, sizeof(color) );
    if( euler == 2 ) res = dfs(any);
    else res = dfs( start );
    return ( res == nodes ) ? 1 : 0;
}

int findEuler( int u ){
    while( !V[u].empty() ){
        edges e = V[u].back();
        V[u].pop_back();
        findEuler( e.v );
        final.push_front( e.st );
    }
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, caseno = 0, i, j, res, u, euler;
	set<int> S;
	char temp[SIZ];
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d", &N);
	    memset( indeg, 0, sizeof(indeg) ), memset( outdeg, 0, sizeof(indeg) );
	    for( i = 0; i < N; i++ ){
	         scanf("%s", temp);
	         u = temp[0] - 97; any = u;
             tempedge.v = temp[strlen(temp)-1] - 97;
             S.insert(u), S.insert(tempedge.v);
             strcpy( tempedge.st, temp );
             V[u].push_back( tempedge );
	         outdeg[u]++, indeg[tempedge.v]++;
        }
        nodes = S.size();
        euler = check_euler();
        euler != 0 ? res = 1: res = 0;
	    if( res ) res = res & check_connectivity( euler );
	    if( res ){
            printf("Case %d: Yes\n", ++caseno);
            if( euler == 2 ) start = any;
            findEuler( start );
            j = 0;
            for( list<string>::iterator k = final.begin(); k != final.end(); k++, j++ ){
                string word = *k;
                if( j == 0 ) printf("%s", word.c_str());
                else printf(" %s", word.c_str());
            }
            printf("\n");
	    }
	    else printf("Case %d: No\n", ++caseno);
		for( i = 0; i < SIZ; i++ ) V[i].clear();
		final.clear(), S.clear();
	}
	return 0;
}

