#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

int main() {
    // key insight: If a representation contains two fibonacci numbers A and B, these cannot be adjacent
    //              because then A+B would be part of the representation instead. So, we count the number
    //              of ways of choosing three non-adjacent fibonacci numbers whose sum is below 53,316,291,173.
    int n_fib = 0;
    ull a = 1, b = 1, lim = 53316291173ull;
    while (b < lim) {
        n_fib += 1;
        tie(a, b) = make_tuple(b, a + b);
    }
    ull answer = 0;
    for (int i=0; i<n_fib; i++) {
        for (int j=i+2; j<n_fib; j++) {
            for (int k=j+2; k<n_fib; k++) {
                answer += 1;
            }
        }
    }
    cout << answer << "\n";
    return 0;
}