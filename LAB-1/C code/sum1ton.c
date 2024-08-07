#include <stdio.h>

int main() {
    int i, sum = 0, n=69;
    for(int i = 1; i <= n; ++i)
    {
        sum += i;
    }

    printf("The sum of numbers from 1 to %d = %d\n", n, sum);
    return 0;
}
