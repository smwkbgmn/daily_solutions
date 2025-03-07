/* 땅따먹기 - 12913 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> land) {
    for (auto it = land.begin(); it + 1 != land.end(); ++it) {
        int i1 = 0, i2 = 0, max1 = 0, max2 = 0;
        
        for (auto i = 0; i < 4; ++i) {
            if ((*it)[i] > max1) {
                max2 = max1;
                max1 = (*it)[i];
                i2 = i1;
                i1 = i;
            } else if ((*it)[i] > max2) {
                max2 = (*it)[i];
                i2 = i;
            }
        }
        
        for (auto i = 0; i < 4; ++i) {
            (*(it + 1))[i] += (i != i1)? (*it)[i1] : (*it)[i2]; 
        }
    }
    
    return *max_element(land.back().begin(), land.back().end());
}
