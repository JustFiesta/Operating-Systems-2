#include <stdio.h>
#include <stdlib.h>

// divide and conquer
int fibo1(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return fibo1(n-1) + fibo1(n-2);
}

// ramka trójzębna
int fibo2(int n) {
    int r0 = 1, r1 = 1, r2;
    if (n == 0 || n == 1) return 1;
    for (int i = 2; i <= n; i++) {
        r2 = r0 + r1;
        r0 = r1;
        r1 = r2;
    }
    return r2;
}

// ramka dwuzębna
int fibo3(int n) {
    int r0 = 1, r1 = 1, pom;
    if (n == 0 || n == 1) return 1;
    for (int i = 2; i <= n; i++) {
        pom = r0;
        r0 = r1;
        r1 = r0 + pom;
    }
    return r1;
}

// iteracyjnie
int fibo_iter(int n) {
    int a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

// dynamicznie z tablicą "podaną"
int fibo_memo(int n, int *memo) {
    if (memo[n] != -1) return memo[n];
    if (n <= 1) return 1;
    memo[n] = fibo_memo(n-1, memo) + fibo_memo(n-2, memo);
    return memo[n];
}

// dynamicznie z tablicą tworzoną przy iteracji
int fibo_tab(int n) {
    int tab[n+1];
    tab[0] = tab[1] = 1;
    for (int i = 2; i <= n; i++) {
        tab[i] = tab[i-1] + tab[i-2];
    }
    return tab[n];
}

int main() {
    int n = 6;  

    printf("fibo1(%d) = %d\n", n, fibo1(n));
    printf("fibo2(%d) = %d\n", n, fibo2(n));
    printf("fibo3(%d) = %d\n", n, fibo3(n));
    
    // alokacja pamięci dla tablicy w podejściu dynamicznym
    int *memo = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;  // Inicjalizacja pamięci
    }
    printf("fibo_memo(%d) = %d\n", n, fibo_memo(n, memo));
    free(memo);

    printf("fibo_iter(%d) = %d\n", n, fibo_iter(n));
    printf("fibo_tab(%d) = %d\n", n, fibo_tab(n));

    return 0;
}
