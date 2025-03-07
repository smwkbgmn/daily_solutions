/* 튜플 - 64065 */

#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>

using namespace std;

vector<int> solution(string s) {
    unordered_map<int, int> freq_map;
    
    int n = 0;
    for (char c : s) {
        if (isdigit(c)) {
            n = n * 10 + (c - '0');
        } else if (n != 0) {
            ++freq_map[n];
            n = 0;
        }
    }

    vector<pair<int, int>> freq_vec(freq_map.begin(), freq_map.end());
    sort(freq_vec.begin(), freq_vec.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    });

    vector<int> result;
    for (const auto &[num, freq] : freq_vec) {
        result.push_back(num);
    }

    return result;
}