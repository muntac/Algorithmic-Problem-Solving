/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Snakes and Ladders
	Algorithm    :  Gaussian Elimination
	Complexity   :	O(N^3)*/

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

const int SIZ = 100000;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, sl[101];
double eqn[101][102], varval[102];

void find_replace( int x ){
    int i, k;
    for( i = x + 1; i < 100; i++ ){
        if( fabs( eqn[i][x] ) > EPS ){
            for( k = 1; k < 102; k++ ) swap( eqn[x][k], eqn[i][k] );
        }
    }
}

void forwardElimination(){
    int i, j, k;
    for( i = 1; i < 100; i++ ){
        for( j = i + 1; j < 100; j++ ){
            if( fabs( eqn[i][i] ) <= EPS ) find_replace( i );
            double fract = eqn[j][i] / eqn[i][i]; //eqn[i][i] will never be 0?? if 0 pivot..
            eqn[j][i] = 0;
            for( k = i+1; k < 102; k++ ) eqn[j][k] = eqn[j][k] - ( (fract) * eqn[i][k] );
        }
    }
}

void backwardSubstitution(){
    int i, j;
    double sum;
    memset( varval, 0, sizeof(varval) );
    varval[100] = 0;
    for( i = 99; i >= 1; i-- ){
        for( j = i + 1, sum = 0; j < 101; j++ ) sum += (eqn[i][j] * varval[j]);
        varval[i] = (eqn[i][101] - sum) / eqn[i][i];
    }
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("mat2.out", "w", stdout);
	int cases, caseno = 0, i, j, res, x, y;
	scanf("%d", &cases);
	while( cases-- ){
	    for( i = 0; i < 101; i++ ) sl[i] = i;
	    scanf("%d", &N);
	    for( i = 0; i < N; i++ ) scanf("%d %d", &x, &y), sl[x] = y;
	    memset( eqn, 0, sizeof(eqn) );
        for( i = 1; i < 100; i++ ){

            if( sl[i] != i ){ eqn[i][i] = -1, eqn[i][sl[i]] = 1;  continue;  } //if ladder bottom or snake head at this position

            for( j = i + 1; j <= i + 6 && j < 100; j++ ) eqn[i][j] = 1.0;
            if( i > 94 ) eqn[i][i] = -( 100 - i );
            else eqn[i][i] = -6.0; //1 move for each dice value
            eqn[i][101] = -6.0; //the constant 1 for each
        }
        forwardElimination();
        backwardSubstitution();
		printf("Case %d: %.10lf\n", ++caseno, varval[1]);
    }
	return 0;
}

