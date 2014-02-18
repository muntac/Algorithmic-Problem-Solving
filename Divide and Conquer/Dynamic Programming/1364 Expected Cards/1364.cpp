/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Expected Cards
	Algorithm    :  DP
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

const int SIZ = 15;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, caseno = 0;
int C, D, H, S;

bool validate(){
    int num14 = 0, num15 = 0, gt = 0;
    switch( C ){
        case 14: gt++, num14++; break;
        case 15: gt++, num15++; break;
    }
    switch( D ){
        case 14: gt++, num14++; break;
        case 15: gt++, num15++; break;
    }
    switch( H ){
        case 14: gt++, num14++; break;
        case 15: gt++, num15++; break;
    }
    switch( S ){
        case 14: gt++, num14++; break;
        case 15: gt++, num15++; break;
    }
    if( gt > 2 ) return false;
    if( gt == 2 ) return (num14 == 2 && num15 == 0);
    return true;
}

int done[SIZ][SIZ][SIZ][SIZ][5][5];
double mem[SIZ][SIZ][SIZ][SIZ][5][5];

double f( int c, int d, int h, int s, int j1, int j2 ){
    int cneed = C - ( (13 - c) + (j1 == 1) + (j2 == 1) );
    int dneed = D - ( (13 - d) + (j1 == 2) + (j2 == 2) );
    int hneed = H - ( (13 - h) + (j1 == 3) + (j2 == 3) );
    int sneed = S - ( (13 - s) + (j1 == 4) + (j2 == 4) );
    if( cneed <= 0 && dneed <= 0 && hneed <= 0 && sneed <= 0 ) return 0;

    int not1 = ( cneed > 0 && ( (c + (j1 == 0) + (j2 == 0) - cneed) < 0 ) );
    int not2 = ( dneed > 0 && ( (d + (j1 == 0) + (j2 == 0) - dneed) < 0 ) );
    int not3 = ( hneed > 0 && ( (h + (j1 == 0) + (j2 == 0) - hneed) < 0 ) );
    int not4 = ( sneed > 0 && ( (s + (j1 == 0) + (j2 == 0) - sneed) < 0 ) );
    if( not1 || not2 || not3 || not4 ) return INF;

    int &dn = done[c][d][h][s][j1][j2];
    double &ret = mem[c][d][h][s][j1][j2];
    if( dn == caseno ) return ret;

    //normal
    double total = c + d + h + s + (j1 == 0) + (j2 == 0);
    double res = 0;
    if( c > 0 ) res += ( ( c / total ) * ( f( c - 1, d, h, s, j1, j2 ) + 1 ) );
    if( d > 0 ) res += ( ( d / total ) * ( f( c, d - 1, h, s, j1, j2 ) + 1 ) );
    if( h > 0 ) res += ( ( h / total ) * ( f( c, d, h - 1, s, j1, j2 ) + 1 ) );
    if( s > 0 ) res += ( ( s / total ) * ( f( c, d, h, s - 1, j1, j2 ) + 1 ) );

    //jokers
    if( j1 == 0 || j2 == 0 ){
        double tj = (j1 == 0) + (j2 == 0);
        double tres = INF;
        tj /= total;
        if( j1 == 0 ){
             tres = min( tres, tj * ( f( c, d, h, s, 1, j2 ) + 1 ) );
             tres = min( tres, tj * ( f( c, d, h, s, 2, j2 ) + 1 ) );
             tres = min( tres, tj * ( f( c, d, h, s, 3, j2 ) + 1 ) );
             tres = min( tres, tj * ( f( c, d, h, s, 4, j2 ) + 1 ) );
        }
        else{
            tres = min( tres, tj * ( f( c, d, h, s, j1, 1 ) + 1 ) );
            tres = min( tres, tj * ( f( c, d, h, s, j1, 2 ) + 1 ) );
            tres = min( tres, tj * ( f( c, d, h, s, j1, 3 ) + 1 ) );
            tres = min( tres, tj * ( f( c, d, h, s, j1, 4 ) + 1 ) );
        }
        res += tres;
    }
    dn = caseno;
    return ret = res;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j;
	double res;
	memset( done, -1, sizeof(done) );
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %d %d %d", &C, &D, &H, &S);
	    if( !validate() ) printf("Case %d: -1\n", ++caseno);
	    else printf("Case %d: %.10lf\n", ++caseno, f( 13, 13, 13, 13, 0, 0 ));
	}
	return 0;
}
