/* 게임 맵 최단거리 - 1844 */

#include <vector>
#include <queue>

using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

int solution(vector<vector<int>> maps) {
    int rows = maps.size();
    int cols = maps[0].size();
    
    if (maps[0][0] == 0 || maps[rows - 1][cols - 1] == 0) {
        return -1;
    }
    
    queue<pair<int, int>> q;
    q.push({0, 0});
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        int dist = maps[r][c];
        
        if (r == rows - 1 && c == cols - 1) {
            return dist;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maps[nr][nc] == 1) {
                maps[nr][nc] = dist + 1;
                q.push({nr, nc});
            }
        }
    }
    
    return -1;
}