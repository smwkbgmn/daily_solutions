/* 큰 수 만들기 - 42833 */

#include <string>
 
using namespace std;

string solution(string number, int k) {
    string result = number.substr(k);
    
    for (auto it1 = number.rbegin() + number.size() - k; it1 != number.rend(); ++it1) {
        if (*it1 >= result.front()) {

            auto it2 = result.begin();
            while (it2 + 1 != result.end() && *it2 >= *(it2 + 1)) {
				++it2;
            }            
            while (it2 != result.begin()) {
                *it2 = *(it2 - 1);
                --it2;
            }
            *it2 = *it1;
        } 
    }
    
    return result;
}
