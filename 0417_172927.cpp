/* 광물 캐기 - 172927 */

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int solution(vector<int> picks, vector<string> minerals) {
    map<string, int> hsher = {
        {"diamond", 1 << 8},
        {"iron", 1 << 4},
        {"stone", 1}
    };
    
    size_t mine_max = min(minerals.size(), static_cast<size_t>(picks[0] + picks[1] + picks[2]) * 5);
    if (minerals.size() > mine_max) {
        minerals.erase(minerals.begin() + mine_max, minerals.end());
    }
    
    vector<int> groups(minerals.size() / 5 + static_cast<size_t>(minerals.size() % 5 != 0));
    for (auto i = 0; i < minerals.size(); ++i) {
        groups[i / 5] += hsher[minerals[i]];
    }
    
    sort(groups.begin(), groups.end(), greater<int>());
    
    int pick = 0, fatigue = 0, mask = 0b1111;
    for (auto& sum: groups) {
        while (picks[pick] == 0) ++pick;

        for (auto i = 0; i < 3; ++i) {
            int grade_diff = pick - i, amount = sum >> ((2 - i) * 4) & mask;
            fatigue += (grade_diff > 0? pow(5, grade_diff) : 1) * amount;
        }
        --picks[pick];
    }
    
    return fatigue;
}
