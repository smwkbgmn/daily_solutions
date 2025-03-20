/* 다리를 지나는 트럭 - 42583 */

#include <vector>
#include <queue>

using namespace std;
 
int solution(int length, int weight, vector<int> trucks) {
    queue<int> time_q;
    int pop = 0, push = 0, sum = 0, time = 0;
    
    while (pop < trucks.size()) {
        if (!time_q.empty() && time - time_q.front() >= length) {
            sum -= trucks[pop++];
            time_q.pop();
        }
        
        if (sum + trucks[push] <= weight) {
            sum += trucks[push++];
            time_q.push(time);
        }
        
        ++time;
    }
    
    return time;
}
