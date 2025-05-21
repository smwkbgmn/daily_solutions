/* 퍼즐 게임 챌린지(Puzzle Game Chalange) - 340212 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> puzzle, vector<int> duration, long long limit) {
    int min = 1, max = *max_element(puzzle.begin(), puzzle.end());
    
    auto valid = [&](int level) -> bool {
        long long sum = 0;
        
        for (auto i = 0; i < puzzle.size(); ++i) {
            int diff = puzzle[i] - level;
            sum += duration[i] + (diff > 0? (duration[i] + duration[i - 1]) * diff : 0);
            
            if (sum > limit) return false;
        }
        return true;
    };
    
    while (min <= max) {
        int level = (min + max) / 2;
        
        if (valid(level)) {
            max = level - 1;
        } else {
            min = level + 1;
        }
    }

    return min;
}
