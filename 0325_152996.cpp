/* 시소 짝궁 - 152996 */

#include <vector>
#include <unordered_map>

using namespace std;

long long solution(vector<int> weights) {
    long rst = 0; 
    
    unordered_map<int, long> w_map;
    for (auto& n: weights) {
        ++w_map[n << 2];
    }

    for (auto& [w, cnt]: w_map) {
        rst += (cnt - 1) * cnt / 2;		
        rst += cnt * (w_map.find(w * 3 / 2) == w_map.end()? 0 : w_map[w * 3 / 2]);
        rst += cnt * (w_map.find(w * 4 / 3) == w_map.end()? 0 : w_map[w * 4 / 3]);
        rst += cnt * (w_map.find(w * 2) == w_map.end()? 0 : w_map[w * 2]);
    }
    
    return rst;
}
