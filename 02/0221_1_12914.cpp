/* 멀리 뛰기_12914 */

#include <vector>

using namespace std;

/*
1 1
2 2
3 3
4 5
5 8
*/

long long solution(int n) {
    if (n < 4) {
        return n;
    }
    n -= 3;
    
    long long pre_2 = 2, pre_1 = 3;
    while (n--) {
        long long curnt = (pre_2 + pre_1) % 1234567;
        
        pre_2 = pre_1;
        pre_1 = curnt;
    }
    
    return pre_1;
}