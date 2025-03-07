/* 이진 변환 반복하기_70129 */

#include <string>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

void binary_transit(vector<int>&, int);

vector<int> solution(string s) {
    vector<int> answer;
    
    /* Handle exceptional case of no need to proceed */
    if (s.length() == 1 && s.front() == '1') {
        answer.push_back(0);
        answer.push_back(0);
        return answer;
    }
    
    /* Set initial value from input string */
    int zero = 0, one = 0;
    for (auto c: s) {
        if (c == '0') {
            ++zero;
        } else {
            ++one;
        }
    }
    
    answer.push_back(1);
    answer.push_back(zero);
    
    /* Repeat untill it become 1 */
    binary_transit(answer, one);
    
    return answer;
}

void binary_transit(vector<int>& ans, int cnt_one) {
    /* If - cnt_one is NOT power of 2 */
    if ((cnt_one & (cnt_one - 1)) != 0) {
        bitset<32> bit(cnt_one);

        int zero = 0, one = 0;
        while (bit.any()) {
            if ((bit & bitset<32>(1)).any()) {
                ++one;
            } else {
                ++zero;
            }
            bit >>= 1;
        }
        
        ++(ans[0]);
        ans[1] += zero;
        
        binary_transit(ans, one);
        
    /* Else if - cnt_one is power of 2, but larger than 1 */
    } else if (cnt_one > 1) {
        ++(ans[0]);
        ans[1] += log2(cnt_one);
    }
    
    /* Else - cnt_one is 1, it doesn't need any futher operation */
}
