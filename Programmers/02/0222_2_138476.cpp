/* 귤 고르기_138476 */

#include <vector>
#include <map>
#include <queue>

using namespace std;

int solution(int k, vector<int> tangerine) {
    map<int, int> classfied;
    
    for (auto n: tangerine) {
        ++classfied[n];
    }
    
    priority_queue<int> amount;
    for (auto p: classfied) {
        amount.push(p.second);
    }
    
    int answer = 0, sum = 0;
    while (sum < k) {
        sum += amount.top();
        ++answer;
        amount.pop();
    }
        
    return answer;
}


/* On a massive production, below approach might be more efficient in average */

#include <vector>
#include <algorithm>

using namespace std;

int solution(int k, vector<int> tangerine) {
    vector<int> amount(10000001, 0);
	/*	Or 
	vector<int> amount(*max_element(tangerine.begin(), tangerine.end()) + 1, 0);

		It seems make sense, but it shows runtime usage more than 200ms
		in some cases. I guess the max_element could take a lot of resourcese
		more than assigning max size of constraints does.
	*/
    
    for (auto n: tangerine) {
        ++amount[n];
    }
    
    amount.erase(remove(amount.begin(), amount.end(), 0), amount.end());
    sort(amount.begin(), amount.end(), greater<int>());

    int answer = 0, sum = 0;
    while (sum < k) {
        sum += amount[answer++];
    }
        
    return answer;
}