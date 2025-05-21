/* n진수 게임 - 17687 */

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

const char digit[17] = "0123456789ABCDEF";

string itos_base(int n, int b) {
	if (n == 0) {
		return "0";
	}

    string s;
    
    while (n != 0) {
        s += digit[n % b];
        n /= b;
    }
    
    reverse(s.begin(), s.end());
    return s;
}

string solution(int base, int amount, int person, int nth) {
    string rst;
    
    int n = 0, incr = base, len = 1, t = nth;

    while (true) {
        while (n != incr) {

            if (t <= len) {
                string ns = itos_base(n, base);
                
                auto i = t - 1;
                while (i < len) {
                    rst += ns[i];

                    if (--amount == 0) {
						return rst;
					}
                    
                    i += person;
                }
                
                t = person - (len - (i - person)) + 1;
            } else {
				t -= len;
			}
            
            ++n;
        }
        
        incr *= base;
        ++len;
    }
    
    return rst;
}
