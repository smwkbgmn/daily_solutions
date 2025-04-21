/* 퍼즐 게임 챌린지(Puzzle Game Chalange) - 340212 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> puzzle, vector<int> duration, long long limit) {
    int lv_min = 1, lv_max = *max_element(puzzle.begin(), puzzle.end());
    
    auto valid = [&](int level) -> bool {
        long long sum = 0;
        
        for (auto i = 0; i < puzzle.size(); ++i) {
            int lv_diff = puzzle[i] - level;
            sum += duration[i] + (lv_diff > 0? (duration[i] + duration[i - 1]) * lv_diff : 0);
            
            if (sum > limit) return false;
        }
        return true;
    };
    
    while (lv_min <= lv_max) {
        int level = (lv_min + lv_max) / 2;
        
        if (valid(level)) {
            lv_max = level - 1;
        } else {
            lv_min = level + 1;
        }
    }
    
    return lv_min;
}
