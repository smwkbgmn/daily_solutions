/* 전력망을 둘로 나누기 - 86971 */

#include <vector>
#include <unordered_map>

using namespace std;

int dfs(unordered_map<int, vector<int>>& tree, int node, int parent, int& ans) {
    int sum = 1;
    vector<int>& adj = tree[node];
    
    for (auto& child: adj) {
        if (child == parent) {
            continue;
        }
        
        int cnt = dfs(tree, child, node, ans);
        if (abs(cnt * 2 - static_cast<int>(tree.size())) < ans) {
            ans = abs(cnt * 2 - static_cast<int>(tree.size()));
        }
        
        sum += cnt;
    }
    
    return sum;
}

int solution(int n, vector<vector<int>> wires) {
    unordered_map<int, vector<int>> tree;

    for (const auto& v: wires) {
        tree[v[0]].push_back(v[1]);
        tree[v[1]].push_back(v[0]);
    }

    dfs(tree, 1, 0, n); 
    
    return n;
}
