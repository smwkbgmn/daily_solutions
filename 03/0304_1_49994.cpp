/* 방문 길이 - 49994 */

#include <string>
#include <unordered_map>
#include <bitset>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

int solution(string dirs) {
    unordered_map<pair<int, int>, bitset<4>, PairHash> history;
    
    int count = 0;
    pair<int, int> crnt = {0, 0};
    
    for (const auto& c: dirs) {
        pair<int, int> next = {crnt.first, crnt.second};
        int dir = 0;
        
        if (c == 'U' && crnt.second > -5) {
            --next.second;
            dir = 0;
        } else if (c == 'D' && crnt.second < 5) {
            ++next.second;
            dir = 1;
        } else if (c == 'R' && crnt.first < 5) {
            ++next.first;
            dir = 2;
        } else if (c == 'L' && crnt.first > -5) {
            --next.first;
            dir = 3;
        } else {
            continue;
        }
        
        if (!history[crnt][dir]) {
            history[crnt][dir] = true;
            history[next][dir ^ 1] = true;
            
            ++count;
        }

        crnt = next;
    }
    
    return count;
}

/* Version: Encoded */
int solution(const string& dirs) {
    unordered_map<int, bool> visited;
    
    int count = 0;
    int x = 0, y = 0;
    int size = 5 * 2 + 1; // Total grid size in one dimension
    
    for (char c : dirs) {
        int nx = x, ny = y;
        
        if (c == 'U' && y > -5) ny--;
        else if (c == 'D' && y < 5) ny++;
        else if (c == 'R' && x < 5) nx++;
        else if (c == 'L' && x > -5) nx--;
        else continue;
        
        // Encode positions: (x,y) -> (x+5) * size + (y+5)
        int start = (x + 5) * size + (y + 5);
        int end = (nx + 5) * size + (ny + 5);
        
        // Create a unique path ID, order doesn't matter
        int pathID = min(start, end) * size * size + max(start, end);
        
        // Check if path is new
        if (!visited[pathID]) {
            visited[pathID] = true;
            count++;
        }
        
        // Update position
        x = nx;
        y = ny;
    }
    
    return count;
}