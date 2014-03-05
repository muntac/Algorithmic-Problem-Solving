/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Going Together
	Algorithm    :  BFS
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

const int SIZ = 11;
int N, caseno = 0;

struct info{
    int Ax, Ay, Bx, By, Cx, Cy;
}G;

char grid[10][10];
int moves[4][2] = { -1, 0,  0, 1,  1, 0,  0, -1 };
int done[SIZ][SIZ][SIZ][SIZ][SIZ][SIZ];

int bfs(){
    done[G.Ax][G.Ay][G.Bx][G.By][G.Cx][G.Cy] = caseno;

    queue< pair< info, int > > Q;
    Q.push( make_pair( G, 0 ) );

    while( !Q.empty() ){
        info R, tmp; int dist;
        R = Q.front().first, dist = Q.front().second;
        Q.pop();
        for( int i = 0; i < 4; i++ ){

            int Ax = R.Ax + moves[i][0], Ay = R.Ay + moves[i][1];
            int Bx = R.Bx + moves[i][0], By = R.By + moves[i][1];
            int Cx = R.Cx + moves[i][0], Cy = R.Cy + moves[i][1];

            if( grid[Ax][Ay] == '#' || Ax < 0 || Ay < 0 || Ax > N - 1 || Ay > N - 1 ) Ax = R.Ax, Ay = R.Ay;
            if( grid[Bx][By] == '#' || Bx < 0 || By < 0 || Bx > N - 1 || By > N - 1 ) Bx = R.Bx, By = R.By;
            if( grid[Cx][Cy] == '#' || Cx < 0 || Cy < 0 || Cx > N - 1 || Cy > N - 1 ) Cx = R.Cx, Cy = R.Cy;

            if( Ax == Bx && Ay == By ) Ax = R.Ax, Ay = R.Ay, Bx = R.Bx, By = R.By;
            else if( Bx == Cx && By == Cy ) Bx = R.Bx, By = R.By, Cx = R.Cx, Cy = R.Cy;
            else if( Cx == Ax && Cy == Ay ) Cx = R.Cx, Cy = R.Cy, Ax = R.Ax, Ay = R.Ay;

            if( Ax == Bx && Ay == By ) Ax = R.Ax, Ay = R.Ay, Bx = R.Bx, By = R.By;
            else if( Bx == Cx && By == Cy ) Bx = R.Bx, By = R.By, Cx = R.Cx, Cy = R.Cy;
            else if( Cx == Ax && Cy == Ay ) Cx = R.Cx, Cy = R.Cy, Ax = R.Ax, Ay = R.Ay;

            if( done[Ax][Ay][Bx][By][Cx][Cy] == caseno ) continue;

            if( grid[Ax][Ay] == 'X' && grid[Bx][By] == 'X' && grid[Cx][Cy] == 'X' ) return dist + 1;

            done[Ax][Ay][Bx][By][Cx][Cy] = caseno;
            tmp.Ax = Ax, tmp.Ay = Ay, tmp.Bx = Bx, tmp.By = By, tmp.Cx = Cx, tmp.Cy = Cy;
            Q.push( make_pair( tmp, dist + 1 ) );
        }
    }
    return -1;
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, i, j, res;
	scanf("%d", &cases);
	memset( done, -1, sizeof(done) );
	while( cases-- ){
	    scanf("%d", &N);
	    for( i = 0; i < N; i++ ) scanf("%s", grid[i]);
	    for( i = 0; i < N; i++ ){
            for( j = 0; j < N; j++ ){
                 if( grid[i][j] == 'A' ) G.Ax = i, G.Ay = j;
                 else if( grid[i][j] == 'B' ) G.Bx = i, G.By = j;
                 else if( grid[i][j] == 'C' ) G.Cx = i, G.Cy = j;
            }
	    }
        res = bfs();
        if( res == -1 ) printf("Case %d: trapped\n", ++caseno);
		else printf("Case %d: %d\n", ++caseno, res);
    }
	return 0;
}
