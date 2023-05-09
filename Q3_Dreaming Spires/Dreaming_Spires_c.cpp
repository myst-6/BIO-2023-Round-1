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
    map<string, int> dist;
    queue<string> q;
    q.push("1 2 3 4");
    dist["1 2 3 4"] = 0;
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        set<string> adj = moves(curr);
        for (string next : adj) {
            if (dist.count(next) == 0) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }
    int ans_2 = 0, ans_4 = 0;
    for (pair<string,int> entry : dist) {
        // key insight: If we can get somewhere in N moves, we can get there in N+1 moves. Take the last move of a ball from A
        //              to B. Replace that single move with two moves: from A to a different peg C, then to B. Now we have 
        //              reached the same state in N+1 moves. So we count all the states reachable by <=2 and <=4 moves.
        if (entry.second <= 2) ans_2 += 1;
        if (entry.second <= 4) ans_4 += 1;
    }
    cout << ans_2 << "\n";
    cout << ans_4 << "\n";
    return 0;
}