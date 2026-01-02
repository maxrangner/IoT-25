/*
a)	skriv en rekursiv funktion sum(int n) som beräknar summan av 
	alla tal upp till och med n. sum(0) ska returnera 0

b)	ändra på sum() så att den också ger följande utskrift (för sum(3)):

sum(3) anropas
sum(2) anropas
sum(1) anropas
sum(1) returnerar 1
sum(2) returnerar 3
sum(3) returnerar 6
*/

#include <stdio.h>

int sum(int n) {
    int result;
    if (n > 0) {
        printf("sum(%d) anropas\n", n);
    }
    if (n == 0) {
        return 0;
    }
    result = n + sum(n - 1);
    printf("sum(%d) returnerar %d\n", n, result);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = sum(n);
    printf("%d", result);
    return 0;
}
