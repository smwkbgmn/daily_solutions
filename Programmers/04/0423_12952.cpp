/* N-Queen - 12952 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(int n) {
    vector<int> queen(n);
    
    auto valid = [&](int r, int c) -> bool {
        for (auto i = 0; i < r; ++i) {
            if (queen[i] == c || r - i == abs(queen[i] - c)) {
                return false;
            }
        }
        return true;
    };
    
    auto dfs = [&](auto& self, int r, int n) -> int {
        if (r == n) return 1;

        int sum = 0;
        for (auto c = 0; c < n; ++c) {
            if (!valid(r, c)) continue;

            queen[r] = c;
            sum += self(self, r + 1, n);
        }
        return sum;
    };

    return dfs(dfs, 0, n);
}