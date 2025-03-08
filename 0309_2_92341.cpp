#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    map<string, vector<int>> rec_map;
    
    for (const auto& s: records) {
        string h = s.substr(0, 2);
        string m = s.substr(3, 2);
        string id = s.substr(6, 4);
        
        rec_map[id].push_back(stoi(h) * 60 + stoi(m));
    }
    
    vector<int> rst;
	
    for (auto& [s, v]: rec_map) {
        if (v.size() % 2 == 1) {
            v.push_back(1439);
        }
        
        int time_total = 0;
        for (auto it = v.begin(); it != v.end(); it += 2) {
            time_total += (*(it + 1) - *it);
        }
        
        rst.push_back((time_total > fees[0])? \
        ceil(static_cast<float>(time_total - fees[0]) / static_cast<float>(fees[2])) * fees[3] + fees[1] : \
        fees[1]);
    }
    
    return rst;
}