#include <bits/stdc++.h>
#include "Pentominoes_lib.cpp"

using namespace std;

int main() {
    int ans = 0;
    string letters = "FGILJNMPQTUVWXZSYA";
    for (int i=0; i<(int)letters.size(); i++) {
        for (int j=i; j<(int)letters.size(); j++) {
            PointSet A = fromLetter(letters[i]), B = fromLetter(letters[j]);
            vector<PointSet> AB = A.overlay(B);
            for (PointSet P : AB) {
                if (P.holey()) {
                    ans++;
                    break;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}