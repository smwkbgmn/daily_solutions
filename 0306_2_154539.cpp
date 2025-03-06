/* 뒤에 있는 큰 수 찾기 - 154539 */

#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> numbers) {
    vector<int> rst(numbers.size(), -1);
    
    stack<int> stk;
    for (auto i = 0; i < numbers.size(); ++i) {
        while (!stk.empty() && numbers[stk.top()] < numbers[i]) {
            rst[stk.top()] = numbers[i];
            stk.pop();
        }
        stk.push(i);
    }
    
    return rst;
}