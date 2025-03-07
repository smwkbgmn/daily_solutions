/* 최솟값 만들기_12941 */

#include <vector>
#include <algorithm>

using namespace std;

int multi_min(vector<int>&, vector<int>&);

int solution(vector<int> a, vector<int> b)
{
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end());
    
    return multi_min(a, b);
}

int multi_min(vector<int>& a, vector<int>& b) {
    if (a.empty()) {
        return 0;
    } else {
        int rst = a.back() * b.back();
        a.pop_back();
        b.pop_back();
        return rst + multi_min(a, b);
    }
}