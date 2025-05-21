/* 테이블 해시 함수 - 147354 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    --col;
    
    sort(data.begin(), data.end(), [col](const vector<int>& a, const vector<int>& b) -> bool {
        if (a[col] == b[col]) {
            return a[0] > b[0];
        }
        return a[col] < b[col];
    });
    
    int hash = 0;
    for (auto i = row_begin; i <= row_end; ++i) {
        int row_index = i - 1, s_i = 0;
        for (auto n: data[row_index]) {
            s_i += (n % i);
        }
        hash ^= s_i;
    }
    
    return hash;
}