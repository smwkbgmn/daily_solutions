/* 모음 사전 - 84512 */

#include <vector>
#include <unordered_map>

using namespace std;

int solution(string word) {
    const int w_pos[5] = {
        781, 156, 31, 6, 1
    };

    unordered_map<char, int> w_char = {
        {'A', 1},
        {'E', 2},
        {'I', 3},
        {'O', 4},
        {'U', 5},
    };

    int result = 0;
    for(int i = 0; i < word.size(); ++i) {
        result += (w_char[word[i]] - 1) * w_pos[i] + 1;
    }

    return result;
}
