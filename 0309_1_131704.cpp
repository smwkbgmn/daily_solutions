/* 택배상자 - 131704 */

#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    stack<pair<int, int>> sub;
    
    int belt = 1, rst = 0;
    for (auto n: order) {
        if (n > belt) {
            sub.push({n - 1, belt});
            belt = n;
        }
        
        if (n == belt) {
            ++belt;
            ++rst;
        } else if (n == sub.top().first) {
            if (sub.top().first-- == sub.top().second) {
                sub.pop();
            }
            ++rst;
        } else {
            break;
        }
    }
    
    return rst;
}