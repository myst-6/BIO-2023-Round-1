#include <bits/stdc++.h>

using namespace std;

struct PointSet {
    vector<pair<int,int>> pts;

    static PointSet fromLetter(char letter);

    #define fromLetter PointSet::fromLetter // put in global scope

    void add(vector<pair<int,int>> &pts) {
        for (pair<int,int> pt : pts) {
            this->pts.push_back(pt);
        }
    }

    void add(pair<int,int> pt) {
        pts.push_back(pt);
    }

    tuple<int,int,int,int> bounds() {
        int minX = pts[0].first, minY = pts[0].second;
        int maxX = minX, maxY = minY;
        for (pair<int,int> pt : pts) {
            minX = min(minX, pt.first);
            minY = min(minY, pt.second);
            maxX = max(maxX, pt.first);
            maxY = max(maxY, pt.second);
        }
        return {minX, minY, maxX, maxY};
    }

    pair<int,int> size() {
        int minX, minY, maxX, maxY;
        tie(minX, minY, maxX, maxY) = bounds();
        return {maxX - minX + 1, maxY - minY + 1};
    }

    void normalise() {
        int minX, minY, maxX, maxY;
        tie(minX, minY, maxX, maxY) = bounds();
        shift(-minX, -minY);
    }

    bool equivalent(const PointSet &other) {
        if (pts.size() != other.pts.size()) return false;
        for (pair<int,int> pt : pts) {
            if (find(other.pts.begin(), other.pts.end(), pt) == other.pts.end()) {
                return false;
            }
        }
        return true;
    }

    bool touch(PointSet &other) {
        for (pair<int,int> pt : pts) {
            for (pair<int,int> pt2 : other.pts) {
                int dist = abs(pt.first - pt2.first) + abs(pt.second - pt2.second);
                if (dist == 1) {
                    return true;
                }
            }
        }
        return false;
    }

    bool overlap(PointSet &other) {
        for (pair<int,int> pt : pts) {
            if (other.contains(pt)) {
                return true;
            }
        }
        return false;
    }

    bool contains(pair<int,int> pt2) {
        for (pair<int,int> pt : pts) {
            if (pt == pt2) {
                return true;
            }
        }
        return false;
    }

    void shift(int dX, int dY) {
        for (pair<int,int> &pt : pts) {
            pt.first += dX;
            pt.second += dY;
        }
    }

    bool outside(int x, int y) {
        int minX, minY, maxX, maxY;
        tie(minX, minY, maxX, maxY) = bounds();
        if (x < minX || x > maxX || y < minY || y > maxY) return true;
        return false;
    }

    bool hole_at(int x, int y) {
        if (outside(x, y)) return false;
        for (pair<int,int> next : (vector<pair<int,int>>){{x-1,y},{x+1,y},{x,y-1},{x,y+1}}) {
            if (!contains(next)) {
                pts.push_back({x,y});
                bool ans = hole_at(next.first, next.second);
                pts.pop_back();
                if (ans == false) return false;
            }
        }
        return true;
    }

    bool holey() {
        int minX, minY, maxX, maxY;
        tie(minX, minY, maxX, maxY) = bounds();
        for (int x=minX+1; x<=maxX-1; x++) {
            for (int y=minY+1; y<=maxY-1; y++) {
                if (contains({x,y})) continue;
                if (hole_at(x, y)) {
                    return true;
                }
            }
        }
        return false;
    }

    vector<PointSet> overlay(PointSet &other) {
        vector<PointSet> ans;
        normalise(); 
        other.normalise();
        pair<int,int> size1 = size(), size2 = other.size();
        for (int dx=-size2.first; dx<=size1.first; dx++) {
            for (int dy=-size2.second; dy<=size1.second; dy++) {
                PointSet copy;
                copy.add(other.pts);
                copy.shift(dx, dy);
                if (touch(copy) && !overlap(copy)) {
                    copy.add(pts);
                    copy.normalise();
                    if (find(ans.begin(), ans.end(), copy) == ans.end()) {
                        ans.push_back(copy);
                    }
                }
            }
        }
        return ans;
    }

    vector<PointSet> overlay(vector<PointSet> &AB) {
        vector<PointSet> ABC;
        for (PointSet shape : AB) {
            vector<PointSet> moreShapes = overlay(shape);
            for (PointSet extraShape : moreShapes) {
                if (find(ABC.begin(), ABC.end(), extraShape) == ABC.end()) {
                    ABC.push_back(extraShape);
                }
            }
        }
        return ABC;
    }

    void print() {
        int minX, minY, maxX, maxY;
        tie(minX, minY, maxX, maxY) = bounds();
        for (int y=minY-1; y<=maxY+1; y++) {
            for (int x=minX-1; x<=maxX+1; x++) {
                if (contains({x,y})) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool operator==(const PointSet &other) {
        return equivalent(other);
    }
};

struct Pentomino {
    // the maximum size of each letter is five tall and three wide
    vector<bool> data;

    void loadLetter(char letter) {
        if (letter == 'F') data = {0,1,1,1,1,0,0,1,0,0,0,0,0,0,0};
        if (letter == 'G') data = {1,1,0,0,1,1,0,1,0,0,0,0,0,0,0};
        if (letter == 'I') data = {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0};
        if (letter == 'L') data = {1,0,0,1,0,0,1,0,0,1,1,0,0,0,0};
        if (letter == 'J') data = {0,1,0,0,1,0,0,1,0,1,1,0,0,0,0};
        if (letter == 'N') data = {0,1,0,1,1,0,1,0,0,1,0,0,0,0,0};
        if (letter == 'M') data = {1,0,0,1,1,0,0,1,0,0,1,0,0,0,0};
        if (letter == 'P') data = {1,1,0,1,1,0,1,0,0,0,0,0,0,0,0};
        if (letter == 'Q') data = {1,1,0,1,1,0,0,1,0,0,0,0,0,0,0};
        if (letter == 'T') data = {1,1,1,0,1,0,0,1,0,0,0,0,0,0,0};
        if (letter == 'U') data = {1,0,1,1,1,1,0,0,0,0,0,0,0,0,0};
        if (letter == 'V') data = {1,0,0,1,0,0,1,1,1,0,0,0,0,0,0};
        if (letter == 'W') data = {1,0,0,1,1,0,0,1,1,0,0,0,0,0,0};
        if (letter == 'X') data = {0,1,0,1,1,1,0,1,0,0,0,0,0,0,0};
        if (letter == 'Z') data = {1,1,0,0,1,0,0,1,1,0,0,0,0,0,0};
        if (letter == 'S') data = {0,1,1,0,1,0,1,1,0,0,0,0,0,0,0};
        if (letter == 'Y') data = {0,1,0,1,1,0,0,1,0,0,1,0,0,0,0};
        if (letter == 'A') data = {0,1,0,0,1,1,0,1,0,0,1,0,0,0,0};
    }

    PointSet points() {
        PointSet set;
        for (int y=0; y<5; y++) {
            for (int x=0; x<3; x++) {
                int idx = y*3 + x;
                if (data[idx]) {
                    set.add({x,y});
                }
            }
        }
        return set;
    }
};

PointSet fromLetter(char letter) {
    Pentomino P;
    P.loadLetter(letter);
    return P.points();
}