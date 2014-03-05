/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Testing Mailboxes
	Algorithm    :  DP
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

const int INF = (1<<29);

int N,mem[111][111][111];

int f(int i, int j, int mb){
    if(mb==1) return ((j)*(j+1))/2 - ((i-1)*(i))/2;
    if(i>j) return 0;
    if(mem[i][j][mb]!=-1) return mem[i][j][mb];
    int res1, res2, res=INF;
    for(int k = i; k <= j; k++){
        res1 = f( i, k-1, mb-1) + k;
        res2 = f( k+1, j, mb) + k;
        res1 = max(res1, res2);
        res = min(res, res1);
    }
    return mem[i][j][mb]=res;
}

int main(){
	int cases,caseno=0,i,j,res,k,m;
	scanf("%d", &cases);
	memset(mem,-1,sizeof(mem));
	while(cases--){
	    scanf("%d %d",&k,&m);
	    res=f(1,m,k);
		printf("Case %d: %d\n", ++caseno, res);
	}
	return 0;
}
