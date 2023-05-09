#include <bits/stdc++.h>

using namespace std;
#define bit(n) ((n) == 0 ? 0 : 1)
#define pow2(n) (1 << (n))

int n_states(vector<int> &pegs, int rem, int k) {
    if (rem == 0) return 1;
    int tot = 0;
    for (int j=k; j<8; j++) {
        if (pegs[j] == 0) continue;
        pegs[j] -= 1;
        tot += n_states(pegs, rem-1, j);
        pegs[j] += 1;
    }
    return tot;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // key insight: There are 16777216 ways of arranging the heights of 8 pegs from 1-8 (8 ^ 8). This is not a lot
    //              in computing terms, and we can iterate through all of these in around 10 seconds, as long as the
    //              function we use to count reachable states is fast enough.
    for (int i=0; i<(1<<24); i++) {
        vector<int> pegs(8);
        bool bad = false;
        for (int j=0; j<8; j++) {
            int h = 1;
            h += bit(i & pow2(3*j+0)) << 2;
            h += bit(i & pow2(3*j+1)) << 1;
            h += bit(i & pow2(3*j+2)) << 0;
            pegs[j] = h;
            if (j>0 && pegs[j]<pegs[j-1]) bad = true;
        }
        if (bad) continue;
        int ct = n_states(pegs, 8, 0);
        if (ct == 2023) {
            for (int j=0; j<8; j++) {
                cout << pegs[j] << " ";
            }
            cout << ": " << ct << "\n";
        }
    }
    return 0;
}