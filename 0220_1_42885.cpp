/* 구명보트_42885 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end(), greater<int>());
    
    size_t l = 0;
    size_t r = people.size() - 1;
    
    while (l <= r) {
        if (people[l] + people[r] <= limit) {
            --r;
        } 
        ++l;
        ++answer;
    } 

    return answer;
}
