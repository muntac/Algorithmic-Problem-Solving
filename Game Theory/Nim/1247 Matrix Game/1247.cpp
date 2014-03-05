/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Matrix Game
	Algorithm    :  [Nim Value]
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

int main(){
	//	freopen("", "r", stdin);
	//	freopen("", "w", stdout);
	int cases, caseno = 0, i, j, res, m, n, ar[51], x;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %d", &m, &n);
	    memset( ar, 0, sizeof(ar) );
	    for( i = 0; i < m; i++ ) for( j = 0; j < n; j++) scanf("%d", &x), ar[i] += x;
	    res = 0;
	    for( i = 0; i < m; i++ ) res ^= ar[i];
	    if( res ) printf("Case %d: Alice\n", ++caseno);
	    else printf("Case %d: Bob\n", ++caseno);
	}
	return 0;
}
