/* 리코쳇 로봇 - 169199 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int solution(vector<string> board) {
    int r_max = board.size(), c_max = board.front().length();
    
    queue<int> q;
    unordered_set<int> record;

	int goal;
    for (auto r = 0; r < r_max; ++r) {
        for (auto c = 0; c < c_max; ++c) {
            if (board[r][c] == 'R') {
                q.push(r * 100 + c);
				record.insert(r * 100 + c);
            } else if (board[r][c] == 'G') {
				goal = r * 100 + c;
			}
        }
    }
    
	const int dirs[4] = {100, 1, -100, -1};

    auto slide = [&](int pos, int dir) -> int {
        int r = pos / 100, c = pos % 100;

        while (0 <= r && r < r_max &&
               0 <= c && c < c_max &&
               board[r][c] != 'D') {
            r += dir / 100;
            c += dir % 100;
        }
        
        int next = r * 100 + c;
        return (next != pos)? next - dir : pos;
    };
    
    int move = 0;
    while (!q.empty()) {
        for (size_t i = 0, size = q.size(); i < size; ++i) {
            int pos = q.front();
            q.pop();

            if (pos == goal) {
                return move;
            }
            
            for (auto i = 0; i < 4; ++i) {
				int next = slide(pos, dirs[i]);
                if (record.insert(next).second) {
                    q.push(next);
                }
            }
        }
        ++move;
    }
    
    return -1;
}

