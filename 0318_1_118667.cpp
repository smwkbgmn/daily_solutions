/* 두 큐 합 같게 만들기 - 118667 */

#include <string>
#include <vector>

using namespace std;

int solution(vector<int> q1, vector<int> q2) {
    int size = q1.size();
    
    unsigned long long total = 0, q1_sum = 0;
    for (auto i = 0; i < size; i++) {
        total += q1[i] + q2[i];
        q1_sum += q1[i];
    }
    
    unsigned long long half = total / 2;
    int i1 = 0, i2 = 0, rst = 0;
    bool over = false;
    
    while (i1 < size && i2 < size) {
        if (q1_sum == half)
            return rst;
        
        if (q1_sum < half) {
            q1_sum += q2[i2++];
        }
        else if (!over) {
            q1_sum -= q1[i1++];

            if (i1 == size) {
                i1 = 0;
                over = true;
            }
        } else {
            q1_sum -= q2[i1++];
        }
        
        ++rst;
    }
    
    return -1;
}