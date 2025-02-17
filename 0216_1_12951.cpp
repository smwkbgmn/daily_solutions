/* JadenCase 문자열 만들기 */

#include <string>
#include <cctype>

using namespace std;

/* Adjust Eunwoo's solution with small imporovement */
string solution(string s) {
	string answer;

	if (!s.empty()) {
		answer += toupper(s.front());
	}

    for (auto it = s.begin() + 1; it != s.end(); ++it) {
		if (answer.back() == ' ') {
			answer += toupper(*it);
		} else {
			answer += tolower(*it);
		}
	}

	return answer;
}

// #include <string>
// #include <sstream>
// #include <cctype>

// using namespace std;

// string solution(string s) {
//     stringstream ss(s);
//     stringstream answer;

//     while (ss) {
//         while (ss.peek() == ' ') {
//             answer << static_cast<char>(ss.get());
//         }

//         string word;
//         ss >> word;

// 		if (!word.empty()) {
// 			*word.begin() = toupper(word.front());

// 			for (auto it = word.begin() + 1; it != word.end(); ++it) {
// 				*it = tolower(*it);    
// 			}
// 		}

//         answer << word;
//     }

//     return answer.str();
// }
