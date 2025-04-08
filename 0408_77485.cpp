/* 행렬 테두리 회전하기 - 77485 */

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<vector<int>> matrix(rows + 1, vector<int>(columns + 1)); 
    
    int n = 1;
    for (auto r = 1; r <= rows; ++r) {
        for (auto c = 1; c <= columns; ++c) {
            matrix[r][c] = n++;
        }
    }
    
    vector<int> result;
    auto fn_rotate = [&](vector<int>& qry) -> void {
        int minimal = rows * columns;
        
        int rs = qry[0], cs = qry[1], re = qry[2], ce = qry[3];
        int& holder = matrix[rs][cs];
        
        for (auto i = cs + 1; i <= ce; ++i) {
            minimal = min(minimal, holder);
            swap(matrix[rs][i], holder);
        }
        
        for (auto i = rs + 1; i <= re; ++i) {
            minimal = min(minimal, holder);
            swap(matrix[i][ce], holder);
        }
        
        for (auto i = ce - 1; i >= cs; --i) {
            minimal = min(minimal, holder);
            swap(matrix[re][i], holder);
        }
        
        for (auto i = re - 1; i >= rs; --i) {
            minimal = min(minimal, holder);
            swap(matrix[i][cs], holder);
        }
        
        result.push_back(minimal);
    };
    
    for (auto& v: queries) {
        fn_rotate(v);
    }
    
    return result;
}