/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Truchet Tiling
	Algorithm    :  Simulation
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

const int SIZ = 410;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, caseno = 0;
int R, C;
const double PI = acos( -1.0 );
const double A1 = PI / 4.0;
const double A2 = 1 - A1;

double tiles[SIZ][SIZ], vis[SIZ][SIZ], dist[SIZ][SIZ];

double mot1[4][4] = { A1, 0, 0.25, 0.25, 0, A2, 0.25, 0.25, 0.25, 0.25, A2, 0, 0.25, 0.25, 0, A1 };
double mot2[4][4] = { 0.25, 0.25, 0, A1, 0.25, 0.25, A2, 0, 0, A2, 0.25, 0.25, A1, 0, 0.25, 0.25 };

void fix( int x, int y, char p ){
    int i, j;
    x *= 4, y *= 4;
    if( p == '0' ){
        for( i = x; i < x + 4; i++ )
            for( j = y; j < y + 4; j++ )
                tiles[i][j] = mot1[i % 4][j % 4];
    }
    else{
        for( i = x; i < x + 4; i++ )
            for( j = y; j < y + 4; j++ )
                tiles[i][j] = mot2[i % 4][j % 4];
    }
}

int moves[4][2] = { 0, 1, 1, 0, -1, 0, 0, -1 };
int test;

bool isValid( pair< int, int > tmp2 ){
    if( tmp2.first < 0 || tmp2.first >= R * 4 ) return false;
    if( tmp2.second < 0 || tmp2.second >= C * 4 ) return false;
    if( vis[tmp2.first][tmp2.second] == test ) return false;
    if( tiles[tmp2.first][tmp2.second] == 0 ) return false;
    return true;
}

void bfs( int sx, int sy ){
    int i, j;
    double res = 0;
    queue< pair< int, int > > Q;
    Q.push( make_pair( sx, sy ) );
    vis[sx][sy] = test;
    while( !Q.empty() ){
        pair< int, int > tmp2, tmp = Q.front();
        Q.pop();
        res += tiles[tmp.first][tmp.second];
        for( i = 0; i < 4; i++ ){
            tmp2 = tmp;
            tmp2.first += moves[i][0], tmp2.second += moves[i][1];
            if( isValid( tmp2 ) ) Q.push( tmp2 ), vis[tmp2.first][tmp2.second] = test;
        }
    }
    test++;
    Q.push( make_pair( sx, sy ) );
    vis[sx][sy] = test;
    while( !Q.empty() ){
        pair< int, int > tmp2, tmp = Q.front();
        Q.pop();
        dist[tmp.first][tmp.second] = res;
        for( i = 0; i < 4; i++ ){
            tmp2 = tmp;
            tmp2.first += moves[i][0], tmp2.second += moves[i][1];
            if( isValid( tmp2 ) ) Q.push( tmp2 ), vis[tmp2.first][tmp2.second] = test;
        }
    }
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j, Q;
	char g[SIZ][SIZ];
	scanf("%d", &cases);
	while( cases-- ){
	    memset( tiles, 0, sizeof(tiles) ), memset( vis, 0, sizeof(vis) );
	    memset( dist, 0, sizeof(dist) );
	    scanf("%d %d", &R, &C);
	    for( i = 0; i < R; i++ )
            scanf("%s", g[i]);
        for( i = 0; i < R; i++ )
            for( j = 0; j < C; j++ )
                fix( i, j, g[i][j] );
        scanf("%d", &Q);
        int x, y;
        printf("Case %d:\n", ++caseno);
        for( i = 0, test = 0; i < R * 4; i++ )
            for( j = 0; j < C * 4; j++ ){
                if( dist[i][j] == 0 && tiles[i][j] != 0 ) test++, bfs( i, j );
            }

        for( i = 0; i < Q; i++ ){
            scanf("%d %d", &x, &y);
            if( (x + y) % 2 != 0 ) printf("0\n");
            else{
                x *= 2, y *= 2;
                if( x != 0 ) x--;
                if( y != 0 ) y--;
                printf("%.10lf\n", dist[x][y]);
            }
        }
	}
	return 0;
}
