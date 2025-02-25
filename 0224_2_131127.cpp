/* 할인 행사 - 131127 */

#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    map<string, int> hs;
    
    int size = want.size();
    for (int i = 0; i < size; ++i) {
        hs.insert(pair<string, int>(want[i], i));
    }
    
    vector<int> v_disc(size, 0);
    bitset<10> stsfy;
    
    for (int i = 0; i < 10; ++i) {
        auto it_hs = hs.find(discount[i]);
        if (it_hs != hs.end() && ++v_disc[it_hs->second] == number[it_hs->second]) {
            stsfy[it_hs->second] = true;
        }
    }
    
    int day = static_cast<int>(stsfy.count() == size);
    
    map<string, int>::iterator it_hs;
    for (auto it = discount.begin(); it + 10 != discount.end(); ++it) {
        it_hs = hs.find(*it);
        if (it_hs != hs.end() && --v_disc[it_hs->second] < number[it_hs->second]) {
            stsfy[it_hs->second] = false;
        }
        
        it_hs = hs.find(*(it + 10));
        if (it_hs != hs.end() && ++v_disc[it_hs->second] == number[it_hs->second]) {
            stsfy[it_hs->second] = true;   
        }
        
        day += static_cast<int>(stsfy.count() == size);
    }
 
    return day;
}