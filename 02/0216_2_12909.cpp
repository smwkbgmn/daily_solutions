/* 올바른 괄호_12909 */

#include <string> 

using namespace std;

bool solution(string s)
{   
    int count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it == '(') {
            ++count;
        } else if (--count < 0) {
			return false;
        }
    }

    return count == 0;
}