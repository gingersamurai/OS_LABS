#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[100] = "dexec abc def";
    printf("%ld", strstr(s, "exec") - s);
}