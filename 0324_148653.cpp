/* 마법의 엘리베이터 - 148653 */

#include <algorithm>

using namespace std;

int dfs(int num) {
    if (num < 10) {
        return min(num, 10 - num + 1);
    }
    
    int mod = num % 10;
    return min(dfs(num / 10) + mod,
               dfs(num / 10 + 1) + 10 - mod);
}

int solution (int storey) {
    return dfs(storey);
}