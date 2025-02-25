/* 할인 행사 - 131127 */

#include <string>
#include <vector>
#include <map>

using namespace std;

class Hasher {
    public: 
        int get(string& key) {
            if (table.find(key) == table.end()) {
                table.insert(pair<string, int>(key, size));
                return size++;
            } else {
                return table[key];
            }
        }
    private:
        map<string, int> table;
        int size = 0;
};

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    Hasher hs;
    
    int size = want.size();
    
    for (int i = 0; i < size; ++i) {
        hs.get(want[i]);
    }
    
    vector<int> v_disc(size, 0);
    
    int total = 0;
    for (int i = 0; i < 10; ++i) {
        int i_hs = hs.get(discount[i]);
        if (i_hs < size) {
            ++v_disc[i_hs];
            ++total;
        }
    }
    
    bool stsfy = true;
    if (total > 9) {
        for (auto i = 0; i < size; ++i) {
            if (v_disc[i] < number[i]) {
                stsfy = false;
                break;
            }
        }
    } else {
        stsfy = false;
    }
    
    int day = static_cast<int>(stsfy);
    
    for (auto it = discount.begin(); it + 10 != discount.end(); ++it) {
        int i_hs = hs.get(*it);
        if (i_hs < size) {
            --v_disc[i_hs];
            --total;
        }
        
        i_hs = hs.get(*(it + 10));
        if (i_hs < size) {
            ++v_disc[i_hs];
            ++total;
        }
        
        if (total > 9) {
            stsfy = true;
            for (int i = 0; i < size; ++i) {
                if (v_disc[i] < number[i]) {
                    stsfy = false;
                    break;
                }
            }
            day += static_cast<int>(stsfy);
        }
    }
 
    return day;
}