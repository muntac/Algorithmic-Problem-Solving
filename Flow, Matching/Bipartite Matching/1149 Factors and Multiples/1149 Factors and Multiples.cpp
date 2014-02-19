/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Factors and Multiples
	Algorithm    :  Bipartite Matching
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

const int SIZ = 105;
const int INF = (1<<29);
const double EPS = 1e-11;
//5:02
int M, N, caseno = 0;

int visited[SIZ], R[SIZ];
vector<int> V[SIZ];

int bpm( int u ){
	int j, curr;
	for( j = 0; j < V[u].size(); j++ ){
		curr = V[u][j];
		if( !visited[curr] ){
			visited[curr] = 1;
			if( R[curr] == -1 || bpm( R[curr] ) ){
				R[curr] = u;
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j, res, ar[SIZ], br[SIZ];
	scanf("%d", &cases);
	while( cases-- ){

	    scanf("%d", &N);
	    for( i = 0; i < N; i++ ) scanf("%d", &ar[i]), ar[i] = abs(ar[i]);

	    scanf("%d", &M);
	    for( i = 0; i < M; i++ ) scanf("%d", &br[i]), br[i] = abs(br[i]);

	    for( i = 0; i < N; i++ ){
            for( j = 0; j < M; j++ ){
                if( ar[i] != 0 && (br[j] % ar[i] != 0 ) ) continue;
                V[i].push_back( j );
            }
	    }
	    memset( R, -1, sizeof(R) );
	    res = 0;
	    for( i = 0; i < N; i++ ){
            memset( visited, 0, sizeof(visited) );
            if( bpm( i ) ) res++;
	    }
		printf("Case %d: %d\n", ++caseno, res);
		for( i = 0; i < N; i++ ) V[i].clear();
	}
	return 0;
}
