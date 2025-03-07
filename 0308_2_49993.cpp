/* 스킬트리 - 49993 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
    unordered_map<char, int> skill_map;
    
    auto i = 0;
    for (auto c: skill) {
        skill_map[c] = i++;
    }
    
    int rst = 0;
    for (auto s: skill_trees) {
        
        int tree = 0;
        for (auto c: s) {
            if (skill_map.find(c) != skill_map.end()) {
                if (skill_map[c] > tree) {
                    tree = -1;
                    break;
                } else if (++tree == skill.length()) {
                    break;
                }
            }
        }
        
        rst += static_cast<int>(tree != -1);
    }
    
    return rst;
}