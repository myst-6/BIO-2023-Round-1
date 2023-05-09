#include <bits/stdc++.h>
#include "Pentominoes_lib.cpp"

using namespace std;

int main() {
    PointSet I = fromLetter('I'), L = fromLetter('L'), V = fromLetter('V');
    vector<PointSet> II = I.overlay(I);
    cout << "III: " << I.overlay(II).size() << "\n";
    vector<PointSet> IV = I.overlay(V);
    vector<PointSet> LIV = L.overlay(IV);
    vector<PointSet> LV = L.overlay(V); // !!
    for (PointSet P : I.overlay(LV)) {
        if (find(LIV.begin(), LIV.end(), P) == LIV.end()) {
            LIV.push_back(P);
        }
    }
    cout << "LIV: " << LIV.size() << "\n";
    return 0;
}