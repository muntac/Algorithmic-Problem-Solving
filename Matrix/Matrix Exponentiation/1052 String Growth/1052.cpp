#include<set>
#include<map>
#include<list>
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

const int SIZ = 100000;
const int INF = (1<<30);

#define MAX 4

typedef   unsigned __int64 lint;
typedef   __int64 vint;
struct matrix
{
	lint r,c;

	lint mat[MAX][MAX];

	matrix(){}

	void identity()
	{
		int i,j;

		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				if(i==j) mat[i][j]=1;
				else mat[i][j]=0;
			}

		}
	}

	matrix operator + (const matrix &b)const
	{
		lint i,j;

		matrix temp;
		temp.r =r;
		temp.c =c;

		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				temp.mat[i][j] = mat[i][j]+b.mat[i][j];
			}
		}
		return temp;
	}

	matrix operator * (const matrix &b)const
	{
		lint i,j,k;

		matrix temp;

		if(c!=b.r)
		{
			temp.identity();
			return temp;
		}
		temp.r =r;
		temp.c =b.c;

		for(i=0;i<r;i++)
		{
			for(j=0;j<b.c;j++)
			{
				temp.mat[i][j] = 0;
				for(k=0;k<c;k++)
				{
					temp.mat[i][j] =(mat[i][k]*b.mat[k][j] +temp.mat[i][j])%1000000007;
					//temp.mat[i][j] =(mat[i][k]*b.mat[k][j] +temp.mat[i][j] ) % 1000000007;
				}
			}
		}

		return temp;

	}
};

matrix mat1,mat2,mat3,ident;

matrix bigmod(vint p)
{
	matrix res = mat1;
	int n=p;
	res.identity();

	matrix x = mat1;

	while(p)
	{

		if(p&1)	res = (res*x);
		x = x*x;
		p>>=1;
	}
	return res;
}

int main()
{
    //freopen("1052.in","r",stdin);
	vint N,X,M,Y,K,x1,y1,x2,y2,m,n;
	int T,ind;
	scanf("%d",&T);
	mat1.mat[0][0]=1;mat1.mat[0][1]=1;mat1.mat[1][0]=1;mat1.mat[1][1]=0;   //mat1 is da base that will undergo exponentiation
	mat1.r=mat1.c=2;

	mat2.r=2;mat2.c=1;  //contains T(1) [bottom row] and T(2) term of fibonacci series : 1 and 1
	mat2.mat[1][0]=1;
	mat2.mat[0][0]=1;


	mat3.r=2;mat3.c=1;  //mat3 will hold a certain term of the fibonacci series

	ident.identity();
	for(ind=1;ind<=T;ind++)
	{
		//scanf("%d%d%d%d%d",&N,&X,&M,&Y,&K);
		scanf("%I64d %I64d %I64d %I64d %I64d",&N,&X,&M,&Y,&K);

		mat3=bigmod(N-1)*mat2;   //getting T (N) and T (N+1) term
		x1=mat3.mat[1][0];
		y1=mat3.mat[0][0];

		mat3=bigmod(M-1)*mat2;   //getting T (M) and T (M+1) term
		x2=mat3.mat[1][0];
		y2=mat3.mat[0][0];

		//equations: x1*m + y1*n = X  and x2*m + y2*n = Y

		n=((x2*X)-(x1*Y))/((x2*y1)-(x1*y2)); //solving simultaneous equations by substitution
		m=(X-(y1*n))/x1;

		if(m>=0 && n>=0 && (((x1*m) + (y1*n)) == X) && (((x2*m) + (y2*n)) == Y))
		{
			mat3=bigmod(K-1)*mat2;  //getting T (K) and T (K+1) term
			lint result=((mat3.mat[1][0]*m)+(mat3.mat[0][0]*n))%1000000007;
			printf("Case %d: %llu\n",ind,result);
		}
		else
			printf("Case %d: Impossible\n",ind);
	}
	return 0;

}
