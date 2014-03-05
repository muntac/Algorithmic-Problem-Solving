//HEADERFILE
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

const int MAX = 1 << 17;
int edges[MAX][3], query[MAX][2];

struct edge { int p,minw,maxw; } Ancestors[100100][19];
vector< pair<int,int> > V[100100];
int N,color[100100],depth[100100];

int INF=(1<<29);

int maxim(int a,int b){ return a>b?a:b; }
int minim(int a,int b){ return a<b?a:b; }

void genEdges( int n ) {
      for( int s = 1; s < n; s++ ) {
            //int j = myrand() % i;
            //int k = myrand() % 100000 + 1;
            int i,j,k;
            scanf("%d %d %d",&i,&j,&k);
            V[i-1].push_back(pair<int,int>(j-1,k));
            V[j-1].push_back(pair<int,int>(i-1,k));
      }
}
void genQuery( int n, int q ) {
      for( int i = 0; i < q; i++ ) {
            int u, v;
            /*while(1) {
                  u = myrand() % n;
                  v = myrand() % n;
                  if( u != v ) break;
            }*/
            scanf("%d %d",&u,&v);
            query[i][0] = u-1;
            query[i][1] = v-1;
      }
}

void BFS(){
    int i,source;
    for(i=0;i<=N;i++) color[i]=0,depth[i]=1;
    color[0]=1;depth[0]=1;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int u=Q.front();Q.pop();
        for(i=0;i<V[u].size();i++){
            int curr=V[u][i].first;
            if(color[curr]==0){
               color[curr]=1;Q.push(curr);
               depth[curr]=depth[u]+1;
               Ancestors[curr][0].p=u;
               Ancestors[curr][0].minw=Ancestors[curr][0].maxw=V[u][i].second;
            }
        }V[u].clear();
    }
}

pair<int,int> queryFunc(int s,int t)
{
    int result1,result2,diff,maxs=0,mins=INF,d;
    if(depth[s]!=depth[t]) {
        if(depth[s]<depth[t]) swap(s,t);
        while(depth[s]!=depth[t]) {
            diff=depth[s]-depth[t];
            d=int(floor(log(diff)/log(2)));
            mins=minim(mins,Ancestors[s][d].minw);
            maxs=maxim(maxs,Ancestors[s][d].maxw);
            s=Ancestors[s][d].p;
         }
    }
    if(s==t) return pair<int,int>(mins,maxs);
    d=0; result1=mins;result2=maxs;
    while(Ancestors[s][d].p!=Ancestors[t][d].p) ++d;
    if(d==0){
        mins=minim(minim(Ancestors[s][d].minw,Ancestors[t][d].minw),result1); //i.e. both s and t's immediate parent is the LCA
        maxs=maxim(maxim(Ancestors[s][d].maxw,Ancestors[t][d].maxw),result2);
        return pair<int,int>(mins,maxs);
    }
    --d;
    result1=minim(minim(Ancestors[s][d].minw,Ancestors[t][d].minw),result1);
    result2=maxim(maxim(Ancestors[s][d].maxw,Ancestors[t][d].maxw),result2);
    s=Ancestors[s][d].p;
    t=Ancestors[t][d].p;
    if(s==t) return pair<int,int>(result1,result2);
    else{
        pair<int,int> P;
        P=queryFunc(s,t);
        result1=minim(result1,P.first);
        result2=maxim(result2,P.second);
        return pair<int,int>(result1,result2);
    }
}

int main(){
      int cases, caseno = 0, n, q;
      int i,j;
      scanf("%d", &cases);
      while( cases-- ) {
            scanf("%d", &n);N=n;
            genEdges( n );
            scanf("%d",&q);
            genQuery( n, q );
            BFS();
            int D=int(log(N)/log(2))+1;
            for(i=0;i<=D;i++) Ancestors[0][i].p=Ancestors[0][i].minw=Ancestors[0][i].maxw=0;
            for(i=1;i<=D;i++){ //preprocessing
                for(j=0;j<N;j++){
                    Ancestors[j][i].p=Ancestors[Ancestors[j][i-1].p][i-1].p;
                    Ancestors[j][i].minw=minim(Ancestors[j][i-1].minw,Ancestors[Ancestors[j][i-1].p][i-1].minw);
                    Ancestors[j][i].maxw=maxim(Ancestors[j][i-1].maxw,Ancestors[Ancestors[j][i-1].p][i-1].maxw);
                }
            }printf("Case %d:\n",++caseno);
            for(i=0;i<q;i++){
                pair<int,int> result;
                result=queryFunc(query[i][0],query[i][1]);
                printf("%d %d\n",result.first,result.second);
            }
            for(i=0;i<N;i++) V[i].clear();
      }
      return 0;
}
