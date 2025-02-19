/* 짝지어 제거하기_12973 */

#include <string>
#include <stack>

using namespace std;

int solution(string s) {
    if (s.length() % 2 == 1) {
        return static_cast<int>(false);
    }
    
    stack<char> stack_c;
    for (auto c: s) {
        if (stack_c.empty() || stack_c.top() != c) {
            stack_c.push(c);
        } else {
            stack_c.pop();
        }
    }
    
    return stack_c.empty();
}
