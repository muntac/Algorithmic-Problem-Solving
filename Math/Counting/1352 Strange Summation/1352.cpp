/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :
	Algorithm    :
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

const int SIZ = 66;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, caseno = 0, len1, len2;
lint powr[SIZ], len[SIZ][SIZ], sum[SIZ][SIZ];
lint res1[SIZ], res2[SIZ];

void precal(){
    int i, j;
    powr[0] = 1;
    memset( len, 0, sizeof(len) ), memset( sum, 0, sizeof(sum) );
    for( i = 1; i < 64; i++ ) powr[i] = 2 * powr[i - 1];
    for( i = 0; i < 64; i++ ){
        len[i][0] = sum[i][0] = powr[i];
        if( i > 0 ) sum[i][0] += sum[i-1][0];
        for( j = 1; j < i + 1; j++ ){
            len[i][j] = sum[i][j] = powr[i] / 2;
            if( i > 0 ) sum[i][j] += sum[i-1][j];
        }
    }
}

void cal1( lint x ){
    int i, j, lim;
    len1 = 0;//ch
    lint z = x;
    while( z != 0 ) z /= 2, len1++;//ch
    lim = len1;//ch
    memset( res1, 0, sizeof(res1) );//ch
    if( lim == 0 ) return;
    if( lim == 1 ){res1[0] = 1; return;}
    for( i = 0; i < lim - 1; i++ ) res1[i] += sum[lim - 2][i];//ch
    lint num = x - powr[lim - 1] + 1, div = 1;
    res1[0] += num;
    for( i = lim - 1; i > 0; i-- ){
        div *= 2;
        lint fs = (num / div) * ( div / 2 );
        lint add = (num % div) - (div / 2);
        if( add > 0 ) fs += add;
        res1[i] += fs;//ch
    }
}

void cal2( lint x ){
    int i, j, lim;
    len2 = 0;//ch
    lint z = x;
    while( z != 0 ) z /= 2, len2++;//ch
    lim = len2;//ch
    memset( res2, 0, sizeof(res2) );//ch
    if( lim == 0 ) return;
    if( lim == 1 ){res2[0] = 1; return;}
    for( i = 0; i < lim - 1; i++ ) res2[i] += sum[lim - 2][i];//ch
    lint num = x - powr[lim - 1] + 1, div = 1;
    res2[0] += num;
    for( i = lim - 1; i > 0; i-- ){
        div *= 2;
        lint fs = (num / div) * ( div / 2 );
        lint add = (num % div) - (div / 2);
        if( add > 0 ) fs += add;
        res2[i] += fs;//ch
    }
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j;
	precal();
	scanf("%d", &cases);
	while( cases-- ){
	    lint a, b, res = 0;
	    scanf("%lld %lld", &a, &b);
	    cal1( a - 1 ), cal2( b );
	    for( i = 0; i < len1; i++ ) res2[i] -= res1[i];
	    for( i = 0; i < len2; i++ ){
            if( res2[i] % 2 != 0 ) res = res + powr[len2 - i - 1];
	    }
        printf("Case %d: %lld\n", ++caseno, res);
	}
	return 0;
}
