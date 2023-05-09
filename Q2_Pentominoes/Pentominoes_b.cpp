#include <bits/stdc++.h>
#include "Pentominoes_lib.cpp"

using namespace std;

int main() {
    int ans = 0;
    PointSet X = fromLetter('X'), W = fromLetter('W');
    vector<PointSet> XW = X.overlay(W);
    string letters = "FGILJNMPQTUVWXZSYA";
    for (int i=0; i<(int)letters.size(); i++) {
        for (int j=i; j<(int)letters.size(); j++) {
            if (letters[i] != 'W' || letters[j] != 'X') {
                PointSet A = fromLetter(letters[i]), B = fromLetter(letters[j]);
                vector<PointSet> AB = A.overlay(B);
                for (PointSet P : AB) {
                    auto it = find(XW.begin(), XW.end(), P);
                    if (it != XW.end()) {
                        ans += 1;
                        XW.erase(it); // don't count duplicates
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}