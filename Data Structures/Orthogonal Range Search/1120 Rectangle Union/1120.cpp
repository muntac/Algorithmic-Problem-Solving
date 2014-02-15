//HEADERFILE
//#pragma warning (disable : 4786)
#include<set>
#include<cmath>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;

const int INF = (1<<29);

void SWAP(int &a, int &b){	a = a^b; b = a^b; a = a^b;	}
//int min(int a,int b) {	return a<b?a:b;	}
//int max(int a,int b) {	return a>b?a:b;	}

const int MAX = (1 << 17);

set <int> Sx;set <int> Sy;

struct rectangle {
      int xlow, ylow, xhigh, yhigh;
	  int index;
};

rectangle R[MAX];
int segarr[100005];

struct tree
{
	int low;
	int high;
	int covered;
	int count;
	int armid;
	int arlow,arhigh;
}S[530000];

void makeTree(int idx,int low,int high,int arlow,int arhigh)
{
	S[idx].low=low;
	S[idx].high=high;
	S[idx].armid=(arlow + arhigh)/2;
	S[idx].arhigh=arhigh;S[idx].arlow=arlow;
	if(S[idx].arhigh-S[idx].arlow>1)
	{
		int armid=S[idx].armid;
		makeTree(2*idx+1,low,segarr[armid],arlow,armid);
		makeTree(2*idx+2,segarr[armid],segarr[arhigh],armid,arhigh);
	}
	S[idx].covered=0;S[idx].count=0;
}

void updateTree(int idx,int a,int b,int param)
{
	if(a<=S[idx].low && b>=S[idx].high)
	{
		if(!param)
			S[idx].covered++;
		else
		{
			S[idx].covered--;
			if(S[idx].covered<=0)	S[idx].covered=0;
		}
	}
	else
	{
		int mid=segarr[S[idx].armid];
		int left,right;
		if(a<mid)
			updateTree(2*idx+1,a,min(b,mid),param);
		if(b>mid)
			updateTree(2*idx+2,max(a,mid),b,param);
		left=S[2*idx+1].count;
		right=S[2*idx+2].count;
		if(S[2*idx+1].covered)
			left=S[2*idx+1].high-S[2*idx+1].low;
		if(S[2*idx+2].covered)
			right=S[2*idx+2].high-S[2*idx+2].low;
		S[idx].count=left+right;
	}
}

void genRectangles( int n ) {
      for( int i = 0; i < n; i++ ) {
            scanf("%d %d %d %d",&R[i].xlow,&R[i].ylow,&R[i].xhigh,&R[i].yhigh);
			Sx.insert(R[i].xlow);Sx.insert(R[i].xhigh);
			Sy.insert(R[i].yhigh);Sy.insert(R[i].ylow);
      }
}

struct compare  //for sorting xlow
{
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.xlow<b.xlow;	}
}cmp;

struct compare2  //for sorting xhigh
{
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.xhigh<b.xhigh;	}
}cmp2;

struct compare3  //for sorting xhigh
{
	bool operator () (const rectangle &a,const rectangle &b)const{
		return a.index<b.index;	}
}cmp3;

struct partitions
{
	int x;
	vector<int>start;
	vector<int>end;
}X[100005];

int main() {
	//freopen("1120.in.txt","r",stdin);
	//freopen("out2.txt","w",stdout);
	  int cases, caseno = 0, n, LIMIT;

	  scanf("%d", &cases);
      while( cases-- ) {
			Sx.clear();Sy.clear();
            scanf("%d", &n);
            genRectangles( n );

 			memset(X,0,sizeof(X));memset(segarr,0,sizeof(segarr));
			int parts=0,partsy=0;
			set<int>::iterator sud;
			for(sud=Sx.begin();sud!=Sx.end();sud++) X[parts++].x=*sud;
			for(sud=Sy.begin();sud!=Sy.end();sud++) segarr[partsy++]=*sud;
			//------Preprocessing Starting and Ending points
			int i=0,j;
			sort(R,R+n,cmp);//sort with respect to xlow
		 	for(i=0;i<n;i++)
				R[i].index=i;
			i=0;j=0;
			while(i<n)
			{                               //X[] is the partitions. contains start points and end points
				if(R[i].xlow==X[j].x)
				{X[j].start.push_back(i);i++;}
				//{X[j].start.push_back(R[i].index);i++;}//believe it's the same thing
				else
					j++;
			}
			sort(R,R+n,cmp2);i=0;j=0;//sort with respect to xhigh
			while(i<n)
			{
				if(R[i].xhigh==X[j].x)
				{X[j].end.push_back(R[i].index);i++;}
				else
					j++;
			}
			sort(R,R+n,cmp3);
			//------Tree Work
			makeTree(0,segarr[0],segarr[partsy-1],0,partsy-1);
			for(j=0;j<X[0].start.size();j++)
					updateTree(0,R[X[0].start[j]].ylow,R[X[0].start[j]].yhigh,0);

			__int64 area=0,y;
			for(i=1;i<parts;i++)
			{
				if(S[0].covered)
					y=S[0].high-S[0].low;
				else
					y=S[0].count;
				area+=(X[i].x-X[i-1].x)*y;
				for(j=0;j<X[i].start.size();j++)
					updateTree(0,R[X[i].start[j]].ylow,R[X[i].start[j]].yhigh,0);//insert
				for(j=0;j<X[i].end.size();j++)
					updateTree(0,R[X[i].end[j]].ylow,R[X[i].end[j]].yhigh,1);//remove
			}
			printf("Case %d: %lld\n",++caseno,area);
		}
      return 0;
}
