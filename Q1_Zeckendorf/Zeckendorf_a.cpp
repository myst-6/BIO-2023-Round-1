#include <bits/stdc++.h>

using namespace std;

// 1 1  2  3 5 8 13 21 34 ...
// a b a+b
//   a  b

int greatest_fib(int lim) {
    int a = 1, b = 1;
    while (b <= lim) {
        tie(a, b) = make_tuple(b, a + b);
    }
    return a;
}

int main() {
    // key insight: The Zeckendorf representation for n always includes the largest number from the Fibonacci sequence 
    //              that is no greater than n.
    int n;
    cin >> n;
    while (n > 0) {
        int next = greatest_fib(n);
        cout << next << " ";
        n -= next;
    }
    cout << "\n";
    return 0;
}