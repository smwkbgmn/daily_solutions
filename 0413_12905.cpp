/* 가장 큰 정사각형 찾기 - 12905 */

#include <vector>

using namespace std;

int solution(vector<vector<int>> board) {
    auto len_r = board.size(), len_c = board.front().size();
    
    int d = 0;
    for (auto r = 1; r < len_r; ++r) {
        for (auto c = 1; c < len_c; ++c) {         
            if (!board[r][c]) continue;
            
            board[r][c] += min(min(board[r][c - 1], board[r - 1][c]), board[r - 1][c - 1]);
            d = max(d, board[r][c]);
        }
    }
    
    if (d != 0) return d * d;
    
    for (auto r = 0; r < len_r; ++r) {
        if (board[r][0]) return 1;
    }
    for (auto c = 1; c < len_c; ++c) {
        if (board[0][c]) return 1;
    }
                
    return 0;
}