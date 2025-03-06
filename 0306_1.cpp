#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(string msg) {
    unordered_map<string, int> table;
    for (auto i = 0; i < 26; ++i) {
        table[string(1, 'A' + i)] = i + 1;
    };
    
    vector<int> answer;

    string key;
    key += msg.front();
    
    int val = 27;
    for (auto it = msg.begin() + 1; it != msg.end(); ++it) {
        key += *it;
        
        if (table[key] == 0) {
            table[key] = val++;
            
            key.pop_back();
            answer.push_back(table[key]);
            
            key.clear();
            key += *it;
        } 
    }
    answer.push_back(table[key]);
    
    return answer;
}