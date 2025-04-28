/* 혼자 놀기의 달인 - 131130 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> cards) {
    vector<int> counts;
    
    for (auto i = 0; i < cards.size(); ++i) {
        if (cards[i] == 0) continue;
        
        int count = 0;
        for (auto curr = i, next = cards[i] - 1; cards[curr] > 0; curr = next, next = cards[curr] - 1) {
            cards[curr] = 0;
            ++count;
        }
        counts.push_back(count);
    }
    
    if (counts.size() == 1) {
        counts.push_back(0);
    } else {
        sort(counts.begin(), counts.end(), greater<int>());
    }
    
    return counts[0] * counts[1];
}