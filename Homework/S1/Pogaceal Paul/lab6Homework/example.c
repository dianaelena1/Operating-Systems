#include <stdio.h>

void greet() {
    printf("Hello!\n");
}

int calculate(int a, int b) {
    return a + b;
}

int main() {
    greet();
    int result = calculate(5, 10);
    greet();
    return 0;
}