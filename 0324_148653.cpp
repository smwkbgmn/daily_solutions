/* 마법의 엘리베이터 - 148653 */

#include <string>

using namespace std;

int solution(int storey) {
    int result = 0;
    
    string s = to_string(storey);
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        if (*it == '5') {
            if (it + 1 == s.rend()) {
                result += 5;
                break;
            }
            
            auto crit = it;
            while (++crit != s.rend() && *crit == '5');
            
            if (crit != s.rend()) {
                *it += (*crit < '5'? -1 : 1);
                ++result;
            }
        }
        
        if (*it < '5' ) {
            result += (*it - '0');
        } else {
            result += 10 - (*it - '0');

            if (it + 1 != s.rend()) {
                ++*(it + 1);
            } else {
                ++result;
            }
        } 
    }
    
    return result;
}

/* Version: DFS for all possible cases and resturn minimal one */
#include <algorithm>

int dfs(int num) {
    if (num < 10) {
        return min(num, 10 - num + 1);
    }
    
    int a = num % 10, b = 10 - num % 10;
    return min(dfs((num - a) / 10) + a, dfs((num + b) / 10) + b);
}

int solution (int storey) {
    return dfs(storey);
}