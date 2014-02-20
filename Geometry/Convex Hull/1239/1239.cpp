/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Convex Fence
	Algorithm    :  Convex Hull
	Complexity   :	O( n * log n )*/

//HEADERFILES
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

const int INF = (1<<30), SIZ = 50100;
const double EPS = 1e-11, PI = acos( -1.0 );
int N, marker;
lint minx, miny;

pair< lint, lint > res[SIZ];

struct points{
    lint x, y, distance;
}pt[SIZ];

int isLeft( lint x1, lint y1, lint x2, lint y2, lint x3, lint y3 ){ //is point (x3,y3) on the left of line (x1,y1) -- (x2,y2)
    lint a = (x1 - x3 ) * ( y2 - y1);
    lint b = (x1- x2) * (y3 - y1);
    if( a > b ) return 1;
    else if( a < b ) return 0;
    else return -1;
}

struct compare{
    bool operator()( points a, points b ){
        int dec = isLeft( minx, miny, a.x, a.y, b.x, b.y );
        if( dec == - 1 ) return a.distance < b.distance;
        if( dec ) return true;
        return false;
    }
}cmp;

void grahamScan(){
    int i; //pt[0] contains minx,miny since its on the line and has distance 0
    pt[N].x = pt[0].x, pt[N].y = pt[0].y;
    res[0].first = pt[0].x, res[0].second = pt[0].y, res[1].first = pt[1].x, res[1].second = pt[1].y;
    marker = 1;
    for( i = 2; i <= N; i++ ){
        if( marker == 1 ){
            if( isLeft( res[marker-1].first, res[marker-1].second, res[marker].first, res[marker].second, pt[i].x, pt[i].y ) == 0 ){
               res[marker].first = pt[i].x, res[marker].second = pt[i].y;continue;
            }
        }
        while( marker > 1 && isLeft( res[marker-1].first, res[marker-1].second, res[marker].first, res[marker].second, pt[i].x, pt[i].y ) <= 0 ){
            --marker;
        }
        ++marker;
        res[marker].first = pt[i].x, res[marker].second = pt[i].y;
    }
}

double cart( int i ){
    double x = ( (res[i].first - res[i+1].first) * (res[i].first - res[i+1].first) ) + ( (res[i].second- res[i+1].second) * (res[i].second - res[i+1].second) );
    return sqrt( x );
}

int main(){
		//freopen("", "r", stdin);
		//freopen("", "w", stdout);
	int cases, caseno = 0, i, j;
	double d;
	scanf("%d", &cases);
	while( cases-- ){
	    scanf("%d %lf", &N, &d);
	    //memset( pt, 0, sizeof( pt ) ), memset( res, 0, sizeof( res ) );
	    for( i = 0, miny = INF, minx = INF; i < N; i++ ){
	        scanf("%lld %lld", &pt[i].x, &pt[i].y);
	        if( miny > pt[i].y ) miny = pt[i].y, minx = pt[i].x;
	        else if( miny == pt[i].y ) minx = min( pt[i].x, minx );
	    }

	    double dist = 2.0 * PI * d;

        if( N == 2 ){
            res[0].first = pt[0].x, res[0].second = pt[0].y, res[1].first = pt[1].x, res[1].second = pt[1].y;
            dist += ( 2* cart( 0 ) );
        }
        else if( N > 2 ){
            for( i = 0; i < N; i++ ) pt[i].distance = ( (pt[i].x - minx)*(pt[i].x - minx) ) + ( (pt[i].y - miny)*(pt[i].y - miny) );

            sort( pt, pt + N, cmp );
            grahamScan();

            if( isLeft( res[0].first, res[0].second, res[1].first, res[1].second, res[marker-1].first, res[marker-1].second) == -1 ){
                //colinear
                res[0].first = pt[0].x, res[0].second = pt[0].y, res[1].first = pt[N-1].x, res[1].second = pt[N-1].y;
                dist += ( 2 * cart(0) );
            }
            else{
                res[marker] = res[0];
                for( i = 0; i < marker; i++ ) dist += cart( i );
            }
        }

        printf("Case %d: %.10lf\n", ++caseno, dist);
    }
    return 0;
}
