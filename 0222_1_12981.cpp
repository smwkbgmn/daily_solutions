/* 영어 끝말잇기_12981 */

#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer = { 0, 0 };

	set<string> used = { words[0] };
    
    size_t i = 0;
    while (++i < words.size()
		&& words[i].front() == words[i - 1].back()
		&& used.insert(words[i]).second);

	/* The used.insert() returns a pair<iterator, bool>, 
	which contains iterator pointing to the inserted element as first,
	and boolean indicating succession of insertion as second. */
	
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }
	
    return answer;
}
