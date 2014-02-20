/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Sending Packets
	Algorithm    :  Expected Value + Shortest Path
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

const int SIZ = 200;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, M, S, K, caseno = 0, cnt;
struct edge{
	int u, v;
	double w;
}E[20100];

double path[SIZ];

int relax( int u, int v, double w ){
	if( path[v] < path[u] * w ){
		path[v] = path[u] * w;
		return 1;
	}
	return 0;
}

void bellman_ford( ){
	int i, j, f;
	for( i = 0; i < N; i++ ) path[i] = -INF;
	path[0] = 1;
	for( j = 0; j < N - 1; j++ ){
		f = 0;
		for( i = 0; i < cnt; i++ )
			f = relax( E[i].u, E[i].v, E[i].w );
	}
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, i, j;
	scanf("%d", &cases);
	while( cases-- ){
		scanf("%d %d %d %d", &N, &M, &S, &K);
		int u, v;
		double w;
		for( i = 0, cnt = 0; i < M; i++ ){
			scanf("%d %d %lf", &u, &v, &w);
			w /= 100;
			E[cnt].u = u, E[cnt].v = v, E[cnt].w = w, cnt++;
			E[cnt].u = v, E[cnt].v = u, E[cnt].w = w, cnt++;
		}
		bellman_ford();
		double res = (2 * (lint)K * (lint)S ) / path[N-1];
		printf("Case %d: %.10lf\n", ++caseno, res);
	}
	return 0;
}
