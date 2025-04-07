/* 괄호 변환 - 60058 */

#include <string>
#include <vector>

using namespace std;

string correct(string u) {
    if (u.empty()) {
        return "";
    }
    
    string v;
    for (auto i = 0, n = 0; i < u.length(); ++i) {
        n += (u[i] == '('? 1 : -1);

		if (n == 0) {
            v = correct(u.substr(i + 1));
            u.erase(i + 1);
            
            if (u.front() == '(') {
                return u + v;
            }
            break;
        }
    }

	for (auto i = 0; i + 2 < u.length(); ++i) {
		u[i] = u[i + 1] ^ 1;
	}
	u.erase(u.length() - 2, 2);
    
    return '(' + v + ')' + u;
}

string solution(string p) {
    return correct(p);
}





