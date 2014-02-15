/*	Author       :	Muntasir Muzahid Chowhdury
	Problem Name :  Weird Advertisement (LOJ 1204)
	Algorithm    :  Variation On Orthogonal Range Search
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

#define left 2*idx+1
#define right 2*idx+2

typedef long long lint;
//typedef unsigned __int64 ulint;

const int INF = (1<<29);

set <int> Sx, Sy;

struct rectangle {
      int xlow, ylow, xhigh, yhigh;
	  int index;
}R[30101];

int segarr[60101], K;

struct tree{    int idx, low, high, ar[11], covered, arlow, arhigh, armid;    } S[351072];

void makeTree( int idx, int low, int high, int arlow, int arhigh ){
    S[idx].low = low, S[idx].high = high, S[idx].covered = 0;
    S[idx].armid = (arhigh + arlow) / 2;
    S[idx].arlow = arlow, S[idx].arhigh = arhigh;
    for( int i = 0; i <= K; i++ ) S[idx].ar[i] = 0;
    if( arlow != arhigh ){
        int armid = S[idx].armid;
        makeTree( left, low, segarr[armid], arlow, armid );
        makeTree( right, segarr[armid] + 1, segarr[arhigh], armid + 1, arhigh );
    }
    else if( low != high && arlow != -1 ){
        makeTree( left, low, segarr[arlow] - 1, -1, -1 );
        makeTree( right, segarr[arlow], segarr[arlow], arlow, arlow);
    }
}

void insert( int idx, int p, int q ){
    if( S[idx].armid==-1 ) return;
    else if( p == S[idx].low && q == S[idx].high ){
        ++S[idx].covered;
        if( S[idx].covered <= K ){
            S[idx].ar[0] = S[idx].high - S[idx].low + 1;
            for( int i = K; i > 0; i-- ) S[idx].ar[i] = S[idx].ar[i-1];
            S[idx].ar[0] = 0;
        }
        if( S[idx].low == S[idx].high ) return;
        int j = S[idx].covered;
        if( S[left].arlow == -1 ) for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[right].ar[z];
        else for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[left].ar[z] + S[right].ar[z];
        return;
    }
    else{
        int mid = segarr[S[idx].armid];
        if( S[idx].arhigh == S[idx].arlow && p==q ) insert( right, p, q );
        else{
            if( p <= mid ) insert( left, p, min( mid, q ) );
            if( q > mid ) insert( right, max( p, mid + 1), q );
        }
        int j = S[idx].covered;
        if( S[left].arlow == -1 ) for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[right].ar[z];
        else for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[left].ar[z] + S[right].ar[z];
    }
}

void remove( int idx, int p, int q ){
    if( S[idx].armid==-1 ) return;
    else if( p == S[idx].low && q == S[idx].high ){
        --S[idx].covered;
        if( S[idx].covered < K ){
            for( int i = 1; i < K; i++ ) S[idx].ar[i] = S[idx].ar[i+1];
            S[idx].ar[K] = 0;
        }
        if( S[idx].low == S[idx].high ) return;
        int j = S[idx].covered;
        if( S[left].arlow == -1 ) for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[right].ar[z];
        else for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[left].ar[z] + S[right].ar[z];
        return;
    }
    else{
        int mid=segarr[S[idx].armid];
        if( S[idx].arhigh == S[idx].arlow && p==q ) remove( right, p, q );
        else{
            if( p <= mid ) remove( left, p, min( mid, q ) );
            if( q > mid ) remove( right, max( p, mid + 1 ), q );
        }
        int j = S[idx].covered;
        if( S[left].arlow == -1 ) for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[right].ar[z];
        else for( int i = j + 1, z = 1; i <= K; i++, z++ ) S[idx].ar[i] = S[left].ar[z] + S[right].ar[z];
    }
}

void genRectangles( int n ){
    for( int i = 0; i < n; i++ ) {
        scanf("%d %d %d %d", &R[i].xlow, &R[i].ylow, &R[i].xhigh, &R[i].yhigh);
        Sx.insert(R[i].xlow);Sx.insert(R[i].xhigh);
		Sy.insert(R[i].yhigh);Sy.insert(R[i].ylow);
    }
}

struct compare{  //for sorting xlow
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.xlow<b.xlow;	}
}cmp;

struct compare2{  //for sorting xhigh
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.xhigh<b.xhigh;	}
}cmp2;

struct compare3{ //for sorting xhigh
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.index<b.index;	}
}cmp3;

struct partitions{
	int x;
	vector<int>start;
	vector<int>end;
}X[60101];

int main() {
	  int cases, caseno = 0, n;
      scanf("%d", &cases);
      while( cases-- ) {
			Sx.clear();Sy.clear();
            scanf("%d %d", &n, &K);
            genRectangles( n );

 			memset( X, 0, sizeof(X) ); memset( segarr, 0, sizeof(segarr) );
			int parts=0, partsy=0;
			set<int>::iterator sud;
			for( sud = Sx.begin(); sud != Sx.end(); sud++ ) X[parts++].x = *sud;
			for( sud = Sy.begin(); sud != Sy.end(); sud++ ) segarr[partsy++] = *sud;
			//------Preprocessing Starting and Ending points
			int i = 0, j;
			sort( R, R + n, cmp );//sort with respect to xlow
		 	for( i = 0; i < n; i++ ) R[i].index=i;
			i = 0; j = 0;
			while( i < n ){
                //X[] is the partitions. contains start points and end points
				if( R[i].xlow == X[j].x ) X[j].start.push_back(i++);
				//{X[j].start.push_back(R[i].index);i++;}//believe it's the same thing
				else j++;
			}
			sort( R, R + n, cmp2 ), i = 0, j = 0;//sort with respect to xhigh
			while( i < n ){
				if( R[i].xhigh == X[j].x ) X[j].end.push_back(R[i++].index);
				else j++;
			}
			sort( R, R + n, cmp3 );
			//------Tree Work----------------------------------------
			makeTree(0, segarr[0], segarr[partsy-1], 0, partsy-1);
			for( j = 0; j < X[0].start.size(); j++ ) insert( 0, R[X[0].start[j]].ylow, R[X[0].start[j]].yhigh );

            lint area = 0, y, tempy, add;

            y = S[0].ar[K];
            for( i = 1; i < parts; i++ ){
				area += ( X[i].x - X[i-1].x ) * y;
				for( j = 0; j < X[i].start.size(); j++ ) insert( 0, R[X[i].start[j]].ylow, R[X[i].start[j]].yhigh );
				tempy = S[0].ar[K]; add = 0;
				for( j = 0; j < X[i].end.size(); j++ ){
				    remove( 0, R[X[i].end[j]].ylow, R[X[i].end[j]].yhigh );
				    if( tempy > S[0].ar[K] ) add += tempy - S[0].ar[K], tempy = S[0].ar[K];
                }
                area += add;
                y = S[0].ar[K];
            }
			printf("Case %d: %lld\n", ++caseno, area);
      }
      return 0;
}
