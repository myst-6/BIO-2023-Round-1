#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

int main() {
    // key insight: If we can reach a number that contains 701,408,733 in its Zeckendorf representation,
    //              then that number will also contain 701,408,733. So, we can find what ranges of numbers
    //              DO contain 701,408,733, and then subtract the total range from this to get the answer.
    ull lo = 1000000000ull, hi = 5000000000ull, answer = 0;
    ull a = 1, b = 1, lim = 701408733ull;
    while (a < lim) {
        tie(a, b) = make_tuple(b, a + b);
    }
    vector<pair<ull,ull>> ranges = {{a, b-1}};
    while (b < hi) {
        tie(a, b) = make_tuple(b, a + b);
        for (pair<ull,ull> range : ranges) {
            if (range.first < b) {
                ranges.push_back({range.first + b, range.second + b});
            }
        }
    }
    for (pair<ull,ull> range : ranges) {
        cout << range.first << " -> " << range.second << "\n";
        if (range.first > hi || range.second < lo) continue;
        ull begin = max(range.first, lo);
        ull end = min(range.second, hi);
        ull size = end - begin + 1;
        answer += size;
    }
    ull size = hi - lo + 1;
    cout << size - answer << "\n";
    return 0;
}