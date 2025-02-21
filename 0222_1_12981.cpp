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
	&& !used.insert(words[i]).second);
    
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }
    return answer;
}



#include <string>
#include <vector>
#include <map>

using namespace std;

/* Map */
vector<int> solution(int n, vector<string> words) {
    vector<int> answer = { 0, 0 };
    
    map<string, bool> used = { pair<string, bool>(words[0], true) };
    
    size_t i = 0;
    while (++i < words.size()
        && words[i].front() == words[i - 1].back()
        && !used[words[i]]) {
        used[words[i]] = true;
    }
    
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }

    return answer;
}

