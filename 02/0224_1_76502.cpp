/* 괄호 회전하기 - 76502 */

/* 시간없어서 하드코딩해서 deque 적용한버전으로 다시 짤 예정 (아마도) */

#include <string>
#include <stack>

using namespace std;

int solution(string s) {
    if (s.size() % 2 == 1) {
        return 0;
    }
    
    size_t pos = 0;
    while (s[pos] == ')' || s[pos] == ']' || s[pos] == '}') {
        ++pos;
    }
    
    if (pos == s.size()) {
        return 0;
    }
    
    int answer = 0;
    
    stack<char> stk;
    for (int i = 0; i < s.size(); ++i) {
        
        int pos = i, loop = 0;
        while (loop < s.size()) {
            char c = s[pos++];

            if (c == '(' || c == '[' || c == '{') {
                stk.push(c);
            } else if (stk.empty() || stk.top() + 1 + (stk.top() != '(') != c) {
                break;
            } else {
                stk.pop();
            }

            if (pos == s.size()) {
                pos = 0;
            }
            ++loop;
        }
        
        if (loop == s.size()) {
            ++answer;
        }
        
        while (!stk.empty()) {
            stk.pop();
        }
    }
    
    return answer; 
}