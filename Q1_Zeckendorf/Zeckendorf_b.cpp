#include <bits/stdc++.h>

using namespace std;

int greatest_fib(int lim) {
    int a = 1, b = 1;
    while (b <= lim) {
        tie(a, b) = make_tuple(b, a + b);
    }
    return a;
}

int main() {
    // key insight: If the Zeckendorf representation contains one number, then it must also be a fibonacci number. So,
    //              we calculate the largest fibonacci number below 1,000,000.
    cout << greatest_fib(1e6) << "\n";
    return 0;
}