#include <bits/stdc++.h>
#include "Pentominoes_lib.cpp"

using namespace std;

int main() {
    string inp;
    cin >> inp;
    PointSet A = fromLetter(inp[0]), B = fromLetter(inp[1]);
    cout << A.overlay(B).size() << "\n";
    return 0;
}