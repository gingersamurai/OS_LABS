#include "mymath.h"

float get_pi(int k) {
    float ans = 0;
    for (int i = 0; i < k; i++) {
        float add = 1.0 / (1.0 + i * 2);
        if (i % 2 == 0) {
            ans += add;
        } else {
            ans -= add;
        }
    }
    ans *= 4;
    return ans;
}

float get_e(int x) {
    return pow(1.0 + (1.0 / x), x);
}
