/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  15 Puzzle
	Algorithm    :  IDA* Search
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

const int SIZ = 16;
const int lim = 4, N = 4;
int caseno = 0, depth, dis;
int board[lim][lim], temp[lim][lim], sol[lim][lim], D[18];
pair< int, int > S[18], cord[18];//S is position of piece, cord is position piece is supposed to be in
int moves[4][2] = { 1, 0,  0, -1,  0, 1,  -1, 0 };
char mv[4] = {  'D', 'L', 'R', 'U' };
stack< int > plates;

int imp(){
    int i, j;
    for( i = 0; i < N; i++ ) for( j = 0; j < N; j++ ) temp[i][j] = board[i][j];
    i = S[SIZ].first, j = S[SIZ].second;
    while( i < N - 1 ) swap( temp[i][j], temp[i+1][j] ), i++;
    while( j < N - 1 ) swap( temp[i][j], temp[i][j+1] ), j++;
    int cnt = 0, k, m;
    for( i = 0; i < N; i++ )
        for( j = 0; j < N; j++ ){
            if( temp[i][j] == sol[i][j] ) continue;
            int x = sol[i][j];
            for( k = 0; k < N; k++ ){
                 for( m = 0; m < N; m++ ) if( temp[k][m] == x ) break;
                 if( k != N && temp[k][m] == x ) break;
            }
            swap( temp[i][j], temp[k][m] );
            cnt++;
        }
    return (cnt & 1 ) != 0;
}

int mandis( ){
    int i, j, res = 0, k, m;
    memset( D, 0, sizeof(D) );
    for( i = 1; i < SIZ; i++ ){
        if( S[i].first == cord[i].first && S[i].second == cord[i].second ) continue;
        D[i] = abs(S[i].first - cord[i].first) + abs(S[i].second - cord[i].second);
        res += D[i];
    }
    return res;
}

void printBoard(){
    int i, j;
    for( i = 0; i < N; i++ ){
        for( j = 0; j < N; j++ ) printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool f( int move, int lastx, int lasty ){
    if( dis == 0 ) return true;
    if( move + dis > depth ) return false;

    int mx = S[SIZ].first, my = S[SIZ].second;//position of blank

    for( int i = 0; i < 4; i++ ){
        int x = mx + moves[i][0], y = my + moves[i][1];

        if( x < 0 || y < 0 || x >= lim || y >= lim || ( lastx == x && lasty == y ) ) continue;

        int MP = board[x][y];
        int nc = abs( mx - cord[MP].first ) + abs( my - cord[MP].second );

        swap( board[mx][my], board[x][y] ), swap( S[SIZ], S[MP] ), dis = dis + nc - D[MP];
        swap( D[MP], nc );
        plates.push(i);
        if( f( move + 1, mx, my ) ) return true;
        plates.pop();
        swap( D[MP], nc );
        swap( board[mx][my], board[x][y] ), swap( S[SIZ], S[MP] ), dis = dis - nc + D[MP];
    }
    return false;
}

int ida(){
    dis = mandis( );
    for( depth = dis; ; depth++ ) if( f( 0, -1, -1 ) || depth > 35 ) break;
    return depth;
}


int main(){
    //  freopen("in.txt", "r", stdin);
	//	freopen("outIDA2D", "w", stdout);
	int cases, i, j, res;
	scanf("%d", &cases);
	int x = 1;
	for( i = 0; i < N; i++ ) for( j = 0; j < N; j++ ) cord[x].first = i, cord[x++].second = j;
	for( i = 0, x = 1; i < N; i++ ) for( j = 0; j < N; j++ ) sol[i][j] = x++;
	while( cases-- ){
	    while(!plates.empty()) plates.pop();
	    for( i = 0; i < N; i++ ){
	         for( j = 0; j < N; j++ ){
	              scanf("%d", &board[i][j]);
	              if( board[i][j] == 0 ) board[i][j] = SIZ;
	              int x = board[i][j];
	              S[x].first = i, S[x].second = j;//current position of x
	         }
	    }
        if( imp() ) printf("Case %d: This puzzle is not solvable.\n", ++caseno);
        else{
            res = ida();
            if( res == 36 ) printf("Case %d: This puzzle is not solvable.\n", ++caseno);
            else{
                printf("Case %d: ", ++caseno);
                int ar[40], k = 0;
                while( !plates.empty() ) ar[k++] = plates.top(), plates.pop();
                for( i = k - 1; i >= 0; i-- ) printf("%c", mv[ar[i]]);
                printf("\n");
            }
        }
	}
	return 0;
}
