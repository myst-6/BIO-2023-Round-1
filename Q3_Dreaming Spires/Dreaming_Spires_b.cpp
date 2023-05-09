#include <bits/stdc++.h>

using namespace std;

string make_hash(vector<string> &pegs) {
    string state = "";
    for (int i=0; i<(int)pegs.size(); i++) {
        state += pegs[i];
        if (i != (int)pegs.size()-1) state += " ";
    }
    return state;
}

vector<string> un_hash(string state) {
    vector<string> pegs;
    int start = 0;
    while (true) {
        int space = state.find(' ', start);
        if (space == (int)string::npos) {
            pegs.push_back(state.substr(start));
            break;
        } else {
            string peg = state.substr(start, space-start);
            pegs.push_back(peg);
            start = space+1;
        }
    }
    return pegs;
}

set<string> moves(string state) {
    set<string> ans;
    vector<string> pegs = un_hash(state);
    for (int i=0; i<(int)pegs.size(); i++) {
        string &peg = pegs[i];
        if (peg == "0") continue;
        char top = peg[peg.size() - 1];
        peg = peg.substr(0, peg.size() - 1);
        if (peg.size() == 0) peg = "0";
        for (int j=0; j<(int)pegs.size(); j++) {
            if (i != j) {
                string tmp = pegs[j];
                if (pegs[j] == "0") pegs[j] = top;
                else pegs[j] += top; 
                string next = make_hash(pegs);
                ans.insert(next);
                pegs[j] = tmp;
            }
        }
        if (peg == "0") peg = top;
        else peg += top;
    }
    return ans;
}

int main() {
    set<string> all_states;
    queue<string> q;
    q.push("1 2 3 4");
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        set<string> adj = moves(curr);
        for (string next : adj) {
            if (all_states.count(next) == 0) {
                all_states.insert(next);
                q.push(next);
            }
        }
    }
    int ans = 0;
    for (string state : all_states) {
        if (moves(state).size() == 9) {
            ans += 1;
        }
    }
    cout << ans << "\n";
    return 0;
}