/* JadenCase 문자열 만들기 */

#include <string>
#include <sstream>
#include <cctype>

using namespace std;

string solution(string s) {
    stringstream ss(s);
    stringstream answer;

    while (ss) {
        string delim;
        while (ss.peek() == ' ') {
            delim += ss.get();
        }

        string word;
        ss >> word;

		if (!word.empty()) {
			*word.begin() = toupper(word.front());

			for (auto it = word.begin() + 1; it != word.end(); ++it) {
				*it = tolower(*it);    
			}
		}

        answer << delim << word;
    }

    return answer.str();
}
