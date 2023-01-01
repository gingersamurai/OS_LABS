#include "mymath.h"

float get_pi(int k) {
    float ans = 1;
    for (int n = 1; n <= k; n++) {
        ans *= ((2.0 * n) / (2.0 * n - 1.0)) * ((2.0 * n) / (2.0 * n + 1.0));
    }
    ans *= 2;
    return ans;
}

float get_e(int x) {
    int fact[x+1];
    fact[0] = 1;
    for (int i = 1; i <= x; i++) {
        fact[i] = fact[i-1] * i;
    }

    float ans = 0;
    for (int n = 0; n <= x; n++) {
        ans += 1.0 / fact[n];
    }
    return ans;
}
