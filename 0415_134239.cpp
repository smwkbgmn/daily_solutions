/* 우박수열 정적분 - 134239 */

#include <vector>

using namespace std;

vector<double> solution(int k, vector<vector<int>> ranges) {
    vector<double> area(1, 0.0);
    while (k != 1) {
        int next = (k % 2 == 0)? k / 2 : (k * 3) + 1;

        area.push_back(area.back() + (static_cast<double>(k + next) / 2.0));
        k = next;
    }
    
    vector<double> result;
    for (auto& v: ranges) {
        auto a = area.begin() + v[0];
        auto b = area.end() + v[1] - 1;

        result.push_back((a > b)? -1 : *b - *a);
    }
    
    return result;
}
