/* 피로도 - 87946 */

#include <vector>

using namespace std;

int backtrack(int energy, vector<vector<int>>& dungeons, vector<bool>& visited) {
    int maxCount = 0;
    
    for (int i = 0; i < dungeons.size(); i++) {
        if (!visited[i] && energy >= dungeons[i][0]) {
            visited[i] = true;
            
            int count = 1 + backtrack(energy - dungeons[i][1], dungeons, visited);
            maxCount = max(maxCount, count);
            visited[i] = false;
        }
    }
    
    return maxCount;
}

int solution(int k, vector<vector<int>> dungeons) {
    vector<bool> visited(dungeons.size(), false);
    return backtrack(k, dungeons, visited);
}
