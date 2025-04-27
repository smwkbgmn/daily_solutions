/* 요격 시스템 - 181188 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> targets) {
    sort(targets.begin(), targets.end(), [](vector<int>& v1, vector<int>& v2) -> bool {
       return v1[0] < v2[0]; 
    });
    
    int missile = 0;
    for (auto i = 0, thres = 100000000; i < targets.size(); ++i) {
        if (targets[i][0] >= thres) {
            ++missile;
            thres = targets[i][1];
        } else if (targets[i][1] < thres) {
            thres = targets[i][1];
        }
    }
    
    return missile + 1;
}