/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Dice (I)
	Algorithm    :  DP
	Complexity   :	O(N*S) */
#include<stdio.h>

int main(){
    int i, j, cases, caseno=0, N, k, S, curr, prev;
    __int64 mod = 100000007, dp[2][15010], result, stupor;
    scanf("%d",&cases);
    while(cases--){
        scanf("%d %d %d",&N,&k,&S);
        for( i = 0; i <= S; i++ ) dp[1][i] = 1;
        curr = 0, prev = 1;
        for( i = 0; i < N ; i++ ){
            for( j = 1, dp[curr][0] = 0; j <= S; j++ ){
                if(j-k-1>=0) stupor = dp[prev][j-k-1];
                else stupor = 0;
                dp[curr][j] = (dp[curr][j-1] + dp[prev][j-1] - stupor + mod) % mod;
            }curr^=1, prev^=1;
        }
        if(S==0) result = 0;
        else result = (dp[prev][S] - dp[prev][S-1] + mod) % mod;
        printf("Case %d: %lld\n",++caseno,result);
    }
}
