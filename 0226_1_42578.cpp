/* 의상 - 42578 */

#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    map<string, int> table;
    
    for (auto v: clothes) {
        ++table[v[1]];
    }

    int sum = 1;
    for (auto p: table) {
        /* +1 for the case of wearing nothing */
        sum *= (p.second + 1);
    }
    
    /* -1 for the case of wearing nothing from any category */
    return sum - 1;
}

