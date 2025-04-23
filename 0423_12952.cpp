/* N-Queen - 12952 */

#include <vector>
#include <algorithm>

using namespace std;

bool valid(const vector<int>& queen, int c, int n) {
    for (size_t i = 0, pos = queen.size(); i < queen.size(); ++i) {
        if (queen[i] == c || pos - i == abs(queen[i] - c)) {
            return false;
        }
    }
    return true;
}

int dfs(vector<int>& queen, int r, int n) {
    if (r == n) return 1;

    int sum = 0;
    for (auto c = 0; c < n; ++c) {
        if (!valid(queen, c, n)) continue;

        queen.push_back(c);
        sum += dfs(queen, r + 1, n);
        queen.erase(queen.begin() + r, queen.end());
    }
    return sum;
}

int solution(int n) {
    vector<int> holder;
    return dfs(holder, 0, n);
}