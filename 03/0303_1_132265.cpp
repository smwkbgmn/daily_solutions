/* 롤케이스 자르기 - 132265 */

#include <vector>

using namespace std;

int solution(vector<int> topping) {
    vector<int> p1(10001, 0), p2(10001, 0);
    int tp1 = 0, tp2 = 0;
    
    for (const auto& n: topping) {
        if (++p2[n] == 1) {
            ++tp2;
        }
    }
    
    auto count = 0;
    for (const auto& n: topping) {
        if (++p1[n] == 1) {
            ++tp1;
        }
        if (--p2[n] == 0) {
            --tp2;
        }
        
        if (tp1 == tp2) {
            ++count;
        }
    }
    
    return count;
}