/* 후보키 - 42890 */

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int solution(vector<vector<string>> relation) {
    size_t len_max = relation.front().size();
    
    vector<bool> attr_used(len_max, false);
    vector<vector<int>> candidate_keys;
    
    auto is_unique = [&](const vector<int>& attrs) -> bool {
        unordered_set<string> unique_tuples;
        for (const auto& row: relation) {    
            
            string combined_key = "";
            for (int attr: attrs) {
                combined_key += row[attr] + "#";
            }
            
            if (unique_tuples.find(combined_key) != unique_tuples.end()) {
                return false;
            }
            unique_tuples.insert(combined_key);
        }
        return true;
    };
    
    auto is_minimal = [&](const vector<int>& attrs) -> bool {
        for (const auto& existing_key: candidate_keys) {
            
            bool is_subset = true;
            for (int attr: existing_key) {
                if (find(attrs.begin(), attrs.end(), attr) == attrs.end()) {
                    is_subset = false;
                    break;
                }
            }
            
            if (is_subset) {
                return false;
            }
        }
        return true;
    };
    
    auto comb = [&](auto& fn_self, vector<int> attrs, int attr) -> void {
        if (attr >= len_max) {
            if (!attrs.empty() && is_unique(attrs) && is_minimal(attrs)) {
                candidate_keys.push_back(attrs);
            }
            return;
        }
        
        fn_self(fn_self, attrs, attr + 1);
        
        attrs.push_back(attr);
        fn_self(fn_self, attrs, attr + 1);
    };
    
    int key = 0;
    vector<int> initial_attrs;
    comb(comb, initial_attrs, 0);
    
    return candidate_keys.size();
}