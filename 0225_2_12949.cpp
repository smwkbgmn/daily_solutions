/* 행렬의 곱셉 - 12949 */

#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    int m = arr1.size(), n = arr1[0].size(), o = arr2[0].size();
    
    vector<vector<int>> answer(m, vector<int>(o, 0));
    
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < o; x++) {
            for (int d = 0; d < n; d++) {
                answer[y][x] += arr1[y][d] * arr2[d][x];
            }
        }
    }
    
    return answer;
}