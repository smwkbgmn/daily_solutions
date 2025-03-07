/* 주식가격 - 42584 */

#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> rst(prices.size());
    
    stack<int> stk;
    for (auto i = 0; i != prices.size(); ++i) {
        while (!stk.empty() && prices[stk.top()] > prices[i]) {
            rst[stk.top()] = i - stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    
    while (!stk.empty()) {
        rst[stk.top()] = prices.size() - stk.top() - 1;
        stk.pop();
    }
    
    return rst;
}