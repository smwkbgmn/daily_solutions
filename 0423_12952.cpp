/* N-Queen - 12952 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(int n) {
    auto valid = [&](const vector<int>& queen, int c) -> bool {
        /* Validate Horizonal(column) and Vertical(row) */ 
        if (!queen.empty() && abs(queen.back() - c) < 2 ||
            find(queen.begin(), queen.end(), c) != queen.end()) {
            return false;
        }
        
        /* Validate Diagonal */
        for (size_t i = 0, pos = queen.size(); i < queen.size(); ++i) {
            if (pos - i == abs(queen[i] - c)) {
                return false;
            }
        }
        return true;
    };

    auto dfs = [&](auto& self, int r, const vector<int>& queen) -> int {
        if (r == n) return 1;
        
        int sum = 0;
        for (auto c = 0; c < n; ++c) {
            if (!valid(queen, c)) continue;
            
            vector<int> queen_cpy = queen;
            queen_cpy.push_back(c);
            
            sum += self(self, r + 1, queen_cpy);
        }
        return sum;
    };
    
    return dfs(dfs, 0, vector<int>());
}