/* 광물 캐기 - 172927 */

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int solution(vector<int> picks, vector<string> minerals) {
    map<string, int> hsher = {
		{"diamond", 1 << 8}, {"iron", 1 << 4}, {"stone", 1}
    };
    
    size_t mineable = min(minerals.size(), static_cast<size_t>(picks[0] + picks[1] + picks[2]) * 5);

    vector<int> groups(mineable / 5 + static_cast<size_t>(mineable % 5 != 0));
    for (auto i = 0; i < mineable; ++i) {
        groups[i / 5] += hsher[minerals[i]];
    }

    sort(groups.begin(), groups.end(), greater<int>());
    
    int fatigue = 0, pick = 0, mask = 0b1111;
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

