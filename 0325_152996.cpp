/* 시소 짝궁 - 152996 */

#include <vector>
#include <map>

using namespace std;

long long solution(vector<int> weights) {
    long rst = 0; 
    
    map<int, long> w_map;
    for (auto& n: weights) {
        ++w_map[n << 2];
    }

    for (auto& [w, cnt]: w_map) {
        rst += (cnt - 1) * cnt / 2;

        float wf = static_cast<float>(w);
        rst += cnt * (w_map.find(wf / 2.f * 3) == w_map.end()? 0 : w_map[wf / 2.f * 3]);
        rst += cnt * (w_map.find(wf / 3.f * 4) == w_map.end()? 0 : w_map[wf / 3.f * 4]);
        rst += cnt * (w_map.find(w * 2) == w_map.end()? 0 : w_map[w * 2]);
    }
    
    return rst;
}
