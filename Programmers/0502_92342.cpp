/* 양궁대회 - 92342 */

#include <vector>

using namespace std;

vector<int> solution(int n, vector<int> info) {
    vector<int> win;
    int diff = 0;
    
    vector<int> record(11);
    auto dfs = [&](auto& self, int d, int arrow, int my, int op) {
        auto is_greater_count_on_lower_grade = [&](void) -> bool {
            if (win.empty()) return false;
            
            for (auto i = 10; i >= 0; --i) {
                if (win[i] == record[i]) continue;
                else if (win[i] < record[i]) return true;
                return false;
            }
        };
        
        if (d == 10 || arrow == 0) {
            record[10] = arrow;
            if (my - op > diff || my - op == diff && is_greater_count_on_lower_grade()) {
                diff = my - op;
                win = record;
            }
            return;
        }
        
        int shot = info[d] + 1;
        if (arrow - shot >= 0) {
            record[d] = shot;
            
            int score = 10 - d;
            self(self, d + 1, arrow - shot, my + score, (shot == 1)? op : op - score);
        }
        
        record[d] = 0;
        self(self, d + 1, arrow, my, op);
    };
    
    int op_score = 0;
    for (auto i = 0; i < 11; ++i) {
        if (info[i] > 0) {
            op_score += (10 - i);   
        }
    }
    
    dfs(dfs, 0, n, 0, op_score);
    
    if (win.size() == 0) {
        return vector<int>(1, -1);
    }
    
    return win;
}