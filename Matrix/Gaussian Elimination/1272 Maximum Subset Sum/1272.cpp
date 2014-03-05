/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Maximum Subset Sum
	Algorithm    :  Gaussian Elimination
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

const int SIZ = 103;

int N;
lint ar[SIZ];

int pivot( int x, int y ){
    int i;
    for( i = x + 1; i < N; i++ ){
        if( ( ar[i] & (1LL<<y) )  != 0 ){
            swap( ar[x], ar[i] );
            return 1;
        }
    }
    return 0;
}

lint elim(){
    int i, j = 62, k;
    while( j > 0 && ( ar[0] & (1LL<<j) ) == 0 ) j--;
    if( j == 0 ) return ar[0];
    lint res = 0;
    for( i = 0; i < N && j > -1; i++, j-- ){
        while( j > -1 && ( ar[i] & (1LL<<j) )  == 0 ){
            if( pivot( i, j ) ) break;
            j--;
        }
        if( j == -1 ) break;
        for( k = i + 1; k < N; k++ ) if( ( ar[k] & (1LL<<j) ) != 0 ) ar[k] ^= ar[i];
        if( ( res & ( 1LL<< j ) ) == 0 ) res ^= ar[i];
    }
    return res;
}

struct compare{ bool operator()( lint a, lint b ){ return a > b; } }cmp;

int main(){
    int cases, caseno = 0, i, j;
	lint res;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d", &N);
	    for( i = 0; i < N; i++ ) scanf("%lld", &ar[i]);
        sort( ar, ar + N, cmp );
	    res = elim();
		printf("Case %d: %lld\n", ++caseno, res);
	}
	return 0;
}
