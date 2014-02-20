/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Unlucky Strings
	Algorithm    :  KMP with Matrix Expo.
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

typedef unsigned lint;

const int SIZ = 100000;
const int INF = (1<<29);

int m, Pi[60], length, mem[1232][60];
char B[60], alph[28];
const int MAX = 60;

void computeFailure(){
    Pi[1] = 0;
    for( int i = 2, k = 0; i <= m; i++ ){
        while( k > 0 && B[k+1] != B[i] ) k = Pi[k];
        if( B[k+1] == B[i] ) k++;
        Pi[i] = k;
    }
}

struct matrix{
    int r, c;
    lint mat[MAX][MAX];
    void identity(){
        memset( mat, 0, sizeof(mat) );
        for(int i = 0; i < r; i++) mat[i][i] = 1;
    }
    matrix operator * ( const matrix &b )const {
        lint i, j, k; matrix temp;
        if( c != b.r ){ temp.identity(); return temp; }
        temp.r = r; temp.c = b.c;
        for( i = 0; i < r; i++ ) for( j = 0; j < b.c; j++ ) for( k = 0, temp.mat[i][j] = 0; k < c; k++ ) temp.mat[i][j] =( mat[i][k] * b.mat[k][j] + temp.mat[i][j] );
        return temp;
    }
}bmx, mplier, resmx;

matrix bigmod( int p ){
	matrix res, x = bmx;
	res.r = bmx.r, res.c = bmx.c, res.identity();
	while( p ){
	    if( p & 1 )	res = ( res * x );
        x = x * x; p >>= 1;
	}return res;
}

lint dp( int s, int k ){
    //if( k == m ) return 0;
    //if( s == 0 ) return 1;
    //if( mem[s][k] != -1 ) return mem[s][k];
    int i, j = 0, prevk;
    lint res = 0;
    for( i = 0; i < strlen(alph); i++ ){
        prevk = k;
        while( prevk > 0 && B[prevk + 1] != alph[i] ) prevk = Pi[prevk];
        if( B[prevk + 1] == alph[i] ) prevk++;
        if( prevk != m ) res++, bmx.mat[k][prevk]++;
        //res += dp( s - 1, prevk );
    }
    //return mem[s][k] = res;
    return res;
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, caseno = 0, i, j;
	lint res;
	scanf("%d", &cases);
	while( cases-- ){
	    //memset( mem, -1, sizeof(mem) );
	    scanf("%d", &length);
	    getchar(); gets(alph);
	    scanf("%s", B + 1 );
	    m = strlen( B + 1 );
	    computeFailure();

	    bmx.r = bmx.c = m;
	    mplier.r = resmx.r = m; mplier.c = resmx.c = 1;
	    for( i = 0; i < mplier.r; i++ ) mplier.mat[i][0] = 0, resmx.mat[i][0] = 0;
	    for( i = 0; i < bmx.r; i++ ) for( j = 0; j < bmx.c; j++ ) bmx.mat[i][j] = 0;
	    for( i = 0; i < m; i++ ) mplier.mat[i][0] = dp( length, i );

	    resmx = bigmod( length - 1 ) * mplier;
	    res = resmx.mat[0][0];
	    //res = dp( length, 0 );
	    printf("Case %d: %u\n", ++caseno, res);
	}
	return 0;
}
