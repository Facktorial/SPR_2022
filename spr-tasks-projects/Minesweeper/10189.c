/*
 *   10189  -  Minesweeper
 */

#include <stdio.h>

#define MAX  100


char a[MAX+2][MAX+2];
int m,n;


void skipWS()
{
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\n' || c == '\r');
    ungetc(c, stdin);
}


void read()
{
    int i, j;
    for (i = 1; i <= n; i++) {
        skipWS();
        for (j = 1; j <= m; j++) {
            a[i][j] = getchar();
        }
        a[i][m+1] = '.';
    }
    for (j = 1; j <= m+1; j++) {
        a[n+1][j] = '.';
    }
}


int test(int i, int j) 
{
    return (a[i][j] == '*') ? 1 : 0;
}


void solve() 
{
    int i, j, c;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (a[i][j] == '*') {
                putchar('*');
            } else {
                c = test(i-1, j-1) +
                    test(i-1,  j ) +
                    test(i-1, j+1) +
                    test( i , j-1) +
                    test( i , j+1) +
                    test(i+1, j-1) +
                    test(i+1,  j ) +
                    test(i+1, j+1);
                putchar(c + '0');
            }
        }
        putchar('\n');
    }
}


int main()
{
    int count = 0;
    while (scanf("%d %d", &n, &m) == 2) {
        if (m == 0 && n == 0) break;
        read();
        if (count > 0) putchar('\n');
        printf("Field #%d:\n", ++count);
        solve();
    }
    return 0;
}
