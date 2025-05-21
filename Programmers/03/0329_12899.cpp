/* 124 나라의 숫자 - 12899 */

#include <string>
#include <algorithm>

using namespace std;

/*
11 = 42
12 = 44
13 = 111
*/

const char digit[3] = {'1', '2', '4'};

string solution(int n) {
    string result = "";
    
    while (--n > 0) {
        result += digit[n % 3];    
        n /= 3;
    }
    
    if (n == 0) {
        result += '1';
    }
    
    reverse(result.begin(), result.end());

    return result;
}