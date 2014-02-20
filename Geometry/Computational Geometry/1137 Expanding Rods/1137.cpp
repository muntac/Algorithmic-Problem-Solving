/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Bisection Method/Binary Search
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

const int SIZ = 100100;
const int INF = (1<<29);
const double EPS = 1e-11;

int N, caseno = 0;

int main(){
	//	freopen("in.txt", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, i, j;
	scanf("%d", &cases);
	while( cases-- ){
	    double L, Lnew, n, c;
	    scanf("%lf %lf %lf", &L, &n, &c);
	    Lnew = ( 1 + ( n * c ) ) * L;
	    double res;
	    if( n == 0 || c == 0 ) res = 0;
	    else{
            double low = 0, high = Lnew * 1000, mid;
            for( i = 0; i < 100; i++ ){
                mid = ( low + high ) / 2;
                double x = ( (2* mid * mid) - (L * L) ) / ( 2 * mid * mid );
                if( x < -1 ) x = -1;
                else if( x > 1 ) x = 1;
                double angle = acos( x );
                x = angle * mid;
                if( x < Lnew ) high = mid;
                else low = mid;
            }
            res = mid - sqrt( (mid * mid) - ( ( L * L )/ 4 ) );
        }
		printf("Case %d: %.10lf\n", ++caseno, res);
	}
	return 0;
}
