/*
a)	skriv funktionen badFib(int n) som returnerar fibbonacitalet för n.
	funktionen ska vara rekursiv och göra två anrop per funktionsanrop.

b)	skriv funktionen goodFib(int n) som returnerar fibbonacitalet för n.
	goodFib() ska inte vara rekursiv, utan den ska ropa på 
	fibSub(int a, int b, int n) som är rekursiv och räknar ut fibbonacitalet för n.

	tips: anropet från goodFib() till fibSub() är antagligen något i stil med
	fibSub(0, 1, n)

    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55...n
*/

#include <stdio.h>

// int badFib(int n) {
//     if (n == 0) return 0;
//     if (n == 1) return 1;
//     return badFib(n - 1) + badFib(n - 2);
// }

int fibSub(int a, int b, int n) {
    return fibSub(a, b, n) + fibSub(a, b, n - 1);
}

int goodFib(int n) { // 6 == 8
    int a = n - 1;
    int b = n - 2;
    return fibSub(a, b, n);
}

int main() {
    int n;
    scanf("%d", &n);
    // for (int i = 0; i < n; i++) {
    //     printf("%d: %d\n", i, badFib(i));
    // }
    printf("%d", badFib(n));
    return 0;
}
