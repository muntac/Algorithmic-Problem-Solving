/*	Author       :	Muntasir Muzahid Chowdhury
	Problem Name :  Forming the Council
	Algorithm    :
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

const int SIZ = 8004;
const int INF = (1<<29);

int N, M, color[2*SIZ], scolor, ansFinal[2*SIZ], taken[2*SIZ], members, present[2*SIZ];
bool flag[2*SIZ];
list <int> L[2*SIZ], ord, Rev[2*SIZ], edgeRev[2*SIZ], elements[2*SIZ];

void dfs_visit( int u ){ //normal dfs
    color[u] = 1;
    for( list<int>::iterator k = L[u].begin(); k != L[u].end(); k++ ) if( color[*k] == 0 ) dfs_visit( *k );
    ord.push_front( u );
}

void scc( int u ){ //finding strongly connected components
    color[u] = scolor;
    for( list<int>::iterator k = Rev[u].begin(); k != Rev[u].end(); k++ ) if( color[*k] == 0 ) scc( *k );
}

void reject( int u ){ //removing nodes taken from topologically ordered set
    if( !flag[u] ) return;
    flag[u] = false;
    for( list<int>::iterator k = edgeRev[u].begin(); k != edgeRev[u].end(); k++ ) reject( *k );
}

int dfs(){
    int i, size;
    list<int>::iterator k;
    ord.clear();

    //get finishing time order
    for( i = 0; i < 2*N; i++ ) color[i] = 0;
    for( i = 0; i < 2*N; i++ ) if(color[i]==0) dfs_visit( i );

    //check for contradiction in strongly connected components
    for( i = 0; i < 2*N; i++ ) color[i] = 0;
    for( k = ord.begin(), scolor = 0; k != ord.end(); k++ ) if( color[*k] == 0 ) ++scolor, scc( *k );
    for( i = 0; i < N; i++ ) if( color[i] == color[i+N] ) return 0;

    //build component graph
    for( i = 0; i < 2*N; i++ ) for( k = L[i].begin(); k != L[i].end(); k++ ) edgeRev[ color[*k] ].push_back( color[i] );
    for( i = 0; i < 2*N; i++ ) elements[ color[i] ].push_back( i );

    for( i = 1; i <= scolor; i++ ) flag[i] = 1;

    int u, negu, j;
    for( i = scolor; i >= 1; i-- ) {
        if( flag[i] ) {
            for( k = elements[i].begin(); k != elements[i].end(); k++ )
                u = *k;
                if( u < N ) negu = u + N;
                else  negu = u - N;
                reject( color[negu] );
        }
    }

    //checking cardinality of taken set, and recording voted members
    for( i = 1, members = 0, j = 0; i <= scolor; i++ ){
        if( flag[i] ){
            for( k = elements[i].begin(); k != elements[i].end(); k++ ){
                j++;
                if( *k < N ) ansFinal[members++] = *k;
            }
        }
    }
    if( j == N ) return 1;
    else return 0;
}

int main(){
	//	freopen("", "r", stdin);
	//	freopen("out.txt", "w", stdout);
	int cases, caseno = 0, i, j, res, u, v, negu, negv;
	scanf("%d", &cases);
	while( cases-- ){
	    memset( present, 0, sizeof(present) );
	    scanf("%d %d", &M, &N); //M number of demands, and N range of candidates
	    for( i = 0; i < M; i++ ){
	        scanf("%d %d", &u, &v);
	        if( u < 0 ) negu = u * -1, u = negu + N;
            else negu = u + N;
            if( v < 0 ) negv = v * -1, v = negv + N;
            else negv = v + N;
            --u, --v, --negu, --negv;
            //cout<<negu+1<<"->"<<v+1<<"   "<<negv+1<<"->"<<u+1<<endl;
            L[negu].push_back(v), L[negv].push_back(u);
            Rev[v].push_back(negu), Rev[u].push_back(negv);
	    }
	    res = dfs();
		if( res ){
            printf("Case %d: Yes\n", ++caseno, res);
            sort( ansFinal, ansFinal + members);
            printf("%d", members);
            for( i = 0; i < members; i++ ) printf(" %d", ansFinal[i]+1);
            printf("\n");
        }
		else printf("Case %d: No\n", ++caseno);
		for( i = 0; i <= 2*N; i++ ) L[i].clear(), Rev[i].clear(),edgeRev[i].clear(),elements[i].clear();
	}
	return 0;
}

