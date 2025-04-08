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






#include <vector>
#include <queue>

using namespace std;

int solution(int length, int weight, vector<int> trucks) {
    queue<pair<int, int>> bridge;
	int time = 1, sum = 0, on = 0, result = 0;

	auto i = 0;
    while (i < trucks.size()) {
        if (length == on || sum + trucks[i] > weight) {
            pair<int, int> truck = bridge.front();
            bridge.pop();

            sum -= truck.first;
            on -= 1;

            if (time < truck.second + length) {
                time = truck.second + length; 
            }
        } else {
            ++on;
            sum += trucks[i];
            bridge.emplace(trucks[i], time);

            ++time;
			++i;
        }
    }

    while(!bridge.empty())
    {
        time = bridge.front().second + length;
        bridge.pop();
    }

    return time;
}












