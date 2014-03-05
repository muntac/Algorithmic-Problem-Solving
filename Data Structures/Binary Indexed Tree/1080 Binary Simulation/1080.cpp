#include <cstdio>
#include <cstring>

const int MAX = 100005;

int cases, caseno, n, B[MAX];
char a[MAX];

void updateBit( int x, int val ) {
	while( x <= n ) {
		B[x] += val;
		x += ( x & -x );
	}
}

int queryBit( int x ) {
	int val = 0;
	while( x >= 1 ) {
		val += B[x];
		x -= ( x & -x );
	}
	return val;
}

int main() {
	//freopen("a.txt", "r", stdin);
	scanf("%d", &cases);
	while( cases-- ) {
		scanf("%s", a);
		int i, q, j;
		n = strlen(a);

		for( i = 1; i <= n; i++ ) B[i] = 0;

		int s = 0;
		for( i = 1; i <= n; i++ ) {
			if( a[i-1] - 48 != (s & 1) ) {
				s++;
				updateBit( i, 1 );
			}
		}
		printf("Case %d:\n", ++caseno);
		scanf("%d", &q);
		while( q-- ) {
			char c;
			scanf( " %c", &c );
			if( c == 'I' ) {
				scanf("%d %d", &i, &j);
				updateBit( i, 1 );
				updateBit( j+1, 1 );
			}
			else {
				scanf("%d", &i);
				int res = queryBit(i);
				printf("%d\n", res & 1);
			}
		}
	}
	return 0;
}

