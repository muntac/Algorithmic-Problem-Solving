/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Digit Dancing
	Algorithm    :  BFS Simulation
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

const int SIZ = 100100;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, caseno = 0, ar[9], isPrime[20];

void prime(){
    memset( isPrime, 0, sizeof(isPrime) );
    isPrime[2] = 1;
    for( int i = 3; i <= 13; i += 2 ) isPrime[i] = 1;
    isPrime[9] = 0;
}

struct dance{
    int dn[8];
    bool operator < ( const dance &b )const{
        for( int i = 0; i < 8; i++ ){
            if( abs(dn[i]) == abs( b.dn[i] ) ) continue;
            return abs(dn[i]) < abs( b.dn[i] );
        }
        return false;
    }
};

inline bool isSorted( int br[8] ){
    for( int i = 0; i < 8; i++ ) if( abs( br[i] ) != i + 1 ) return false;
    return true;
}

void change( int x, int y, int ar[8] ){
    int i;
    if( x < y ){
        for( i = x; i < y; i++ )
            swap( ar[i], ar[i + 1] );
    }
    else{
        for( i = x; i > y; i-- )
            swap( ar[i], ar[i - 1] );
    }
}

map< dance, int > M;

int BFS(){
    int i, j;
    queue< pair< dance, int > > Q;
    dance st;
    if( isSorted( ar ) ) return 0;
    for( i = 0; i < 8; i++ ) st.dn[i] = ar[i];
    Q.push( make_pair( st, 0 ) );
    M[st]++;
    while( !Q.empty() ){
        pair< dance, int > T = Q.front();
        int dist = T.second + 1, dpos;
        Q.pop();
        for( i = 0; i < 8; i++ ){
            if( abs(T.first.dn[i]) == i + 1 ) continue;
            for( j = 0; j < 8; j++ ){
                if( i != j && (T.first.dn[i] * T.first.dn[j]) < 0 && isPrime[abs(T.first.dn[i]) + abs(T.first.dn[j])] ){
                    //Go to Left
                    if( i < j ) dpos = j - 1;
                    else dpos = j;
                    if( dpos > -1 && dpos != i && ar[dpos] != dpos + 1 ){
                        dance F = T.first;
                        change( i, dpos, F.dn );
                        if( isSorted( F.dn ) ) return dist;
                        if( M.find( F ) == M.end() ){
                            M[F]++;
                            Q.push( make_pair( F, dist ) );
                        }
                    }
                    //Go to Right
                    if( i > j ) dpos = j + 1;
                    else dpos = j;
                    if( dpos < 8 && dpos != i && ar[dpos] != dpos + 1 ){
                        dance F = T.first;
                        change( i, dpos, F.dn );
                        if( isSorted( F.dn ) ) return dist;
                        if( M.find( F ) == M.end() ){
                            M[F]++;
                            Q.push( make_pair( F, dist ) );
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out3.txt", "w", stdout);
    prime();
	int cases, i, j, res;
	scanf("%d", &cases);
	while( cases-- ){
	    for( i = 0; i < 8; i++ ) scanf("%d", &ar[i]);
	    res = BFS();
	    M.clear();
		printf("Case %d: %d\n", ++caseno, res);
	}
	return 0;
}
