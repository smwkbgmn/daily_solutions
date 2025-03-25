/* 시소 짝궁 - 152996 */

#include <vector>
#include <unordered_map>

using namespace std;

long long solution(vector<int> weights) {
    long rst = 0; 
    
    unordered_map<int, long> w_map;
    for (auto& n: weights) {
        ++w_map[n];
    }

    for (auto& [w, cnt]: w_map) {
        rst += (cnt - 1) * cnt / 2;		
        rst += cnt * (w_map.find(w * 3 / 2) == w_map.end()? 0 : w_map[w * 3 / 2]);
        rst += cnt * (w_map.find(w * 4 / 3) == w_map.end()? 0 : w_map[w * 4 / 3]);
        rst += cnt * (w_map.find(w * 2) == w_map.end()? 0 : w_map[w * 2]);
    }
    
    return rst;
}

/* Version: pre_allocated vector */
long long solution(vector<int> weights) {
    long rst = 0;

    vector<long> w_cnt(2001,0);
    for (auto& n: weights) {
        ++w_cnt[n];
    }

    for (int i = 100; i <= 1000; ++i) {
        if (w_cnt[i] == 0) {
            continue;
        }

        rst += (w_cnt[i] - 1) * w_cnt[i] / 2;
		rst += w_cnt[i] * ((i * 3) % 2 == 0? w_cnt[i * 3 / 2] : 0);
		rst += w_cnt[i] * ((i * 4) % 3 == 0? w_cnt[i * 4 / 3] : 0);
        rst += w_cnt[i] * w_cnt[i * 2];
    }

    return rst;
}