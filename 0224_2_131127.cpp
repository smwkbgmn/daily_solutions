/* 할인 행사 - 131127 */

#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    map<string, int> hs;
    
    int size = want.size();
    for (int i = 0; i < size; ++i) {
        hs.insert(pair<string, int>(want[i], i));
    }
    
    vector<int> v_disc(size, 0);
    
    int total = 0;
    for (int i = 0; i < 10; ++i) {
        auto it_hs = hs.find(discount[i]);
        if (it_hs != hs.end()) {
            ++v_disc[it_hs->second];
            ++total;
        }
    }
    
    bool stsfy = (total > 9);
    if (stsfy) {
        for (auto i = 0; i < size; ++i) {
            if (v_disc[i] < number[i]) {
                stsfy = false;
                break;
            }
        }
    }
    
    int day = static_cast<int>(stsfy);
    
    for (auto it = discount.begin(); it + 10 != discount.end(); ++it) {
        auto it_hs = hs.find(*it);
        if (it_hs != hs.end()) {
            --v_disc[it_hs->second];
            --total;
        }
        
        it_hs = hs.find(*(it + 10));
        if (it_hs != hs.end()) {
            ++v_disc[it_hs->second];
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