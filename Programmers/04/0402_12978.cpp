/* 배달 - 12978 */

#include <vector>
#include <cmath>

using namespace std;

int solution(int n, vector<vector<int> > road, int k) {
    /* 
        int can not handle value of INFINITY 
        Replacing it with INT_MAX also can occur overflow
        when distance comes over INT_MAX / 2
    */
    const int INF = INFINITY / 2;
    vector<vector<int>> d(n, vector<int>(n, INF));
    
    for (auto i = 0; i < n; ++i) {
        d[i][i] = 0;
    }
    
    for (auto& v: road) {
        int a = v[0] - 1;
        int b = v[1] - 1;
        int dist = v[2];
        
        d[a][b] = min(d[a][b], dist);
        d[b][a] = min(d[b][a], dist);
    }
    
    /* Floyd Warshall */
    for (auto m = 0; m < n; ++m) {
        for (auto s = 0; s < n; ++s) {
            for (auto e = 0; e < n; ++e) {
                if (d[s][m] < INF && d[m][e] < INF) {
                    d[s][e] = min(d[s][e], d[s][m] + d[m][e]);
                }
            }
        }
    }
    
    int result = 0;
    for (auto i = 0; i < n; ++i) {
        if (d[0][i] <= k) {
            ++result;
        }
    }
    
    return result;
}