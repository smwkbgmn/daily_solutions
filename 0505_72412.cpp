#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <unordered_map>
// #include <algorithm>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
    unordered_map<string, bitset<50000>> table[4];
    
    vector<int> scores(info.size());
    int n = 0;
    
    for (auto& s: info) {
        stringstream ss(s);
        
        string token;
        for (auto i = 0; i < 4; ++i) {
            ss >> token;
            table[i][token].set(n);
        }
        
        int score;
        ss >> score;
        scores[n++] = score;
    }
    
    vector<int> matches;
    for (auto s: query) {
        stringstream ss(s);
        
        bitset<50000> crit;
        crit.set();
        
        string token;
        for (auto i = 0; i < 4; ++i) {
            ss >> token;
            if (token != "-") {
                crit &= table[i][token];
            }
            
            // remove "and"
            if (i + 1 < 4) {
                ss >> token;
            }
        }
        
        int score;
        ss >> score;
        
        int match = crit.count();
        if (match > info.size()) {
            match = 0;
            for (auto& n: scores) {
                if (n < score) ++match;
            }
            matches.push_back(info.size() - match);
        } else {
            for (auto count = match, i = 0; count > 0; --count, ++i) {
                while (i < info.size() && !crit[i]) {
                    ++i;
                }                
                if (scores[i] < score) --match;
            }
            matches.push_back(match);
        }
    }
    
    return matches;
}
