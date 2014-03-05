/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Equivalent Boolean Expressions
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

typedef __int64 lint;
typedef unsigned __int64 ulint;

const int SIZ = 200;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, M, caseno = 0, val[12];
char eq[2][SIZ];

int f( int id, int x, int y ){
	int i, j, res = 0, cnt = 0;
	for( i = x; i <= y; i++ ){
		if( eq[id][i] == '(' ) cnt++;
		if( eq[id][i] == ')' ) cnt--;
		if( eq[id][i] == '|' && cnt == 0 ){
			res = f( id, x, i - 1 ) | f( id, i + 1, y );
			return res;
		}
	}
	for( i = x; i <= y; i++ ){
		if( eq[id][i] == '(' ) cnt++;
		if( eq[id][i] == ')' ) cnt--;
		if( eq[id][i] == '&' && cnt == 0 ){
			res = f( id, x, i - 1 ) & f( id, i + 1, y );
			return res;
		}
	}
	if( eq[id][x] == '!' ) return !f( id, x + 1, y );
	if( eq[id][x] == '(' ) return f( id, x + 1, y - 1 );
	j = eq[id][x] - 97;
	return val[j];
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, i, j, res1, res2, res;
	scanf("%d", &cases);
	while( cases-- ){
		scanf("%s", eq[0]), scanf("%s", eq[1]);
		N = strlen( eq[0] ), M = strlen( eq[1] );
		res = 1;
		for( i = 0; i < (1<<10); i++ ){
			for( j = 0; j < 10; j++ ){
				if( (i & (1<<j)) == 0 ) val[j] = 0;
				else val[j] = 1;
			}
			res1 = f( 0, 0, N - 1 );
			res2 = f( 1, 0, M - 1 );
			if( res1 != res2 ){ res = 0; break; }
		}
		if( res ) printf("Case %d: Equivalent\n", ++caseno);
		else printf("Case %d: Not Equivalent\n", ++caseno);
	}
	return 0;
}
