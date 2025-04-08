/* 프로세스 - 42587 */

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int solution(vector<int> priority, int location) {
    deque<int> que(priority.begin(), priority.end());
    int prime = *max_element(que.begin(), que.end());
    int n_th = 1;
    
    while (!que.empty()) {
        if (que.front() != prime) {
            que.push_back(que.front());
            que.pop_front();
        } else {
            if (location == 0) {
                return n_th;
            }
            
            que.pop_front();
            ++n_th;
            
            if (find(que.begin(), que.end(), prime) == que.end()) {
                prime = *max_element(que.begin(), que.end());
            }
        }
        
        if (location != 0) {
            --location;   
        } else {
            location = que.size() - 1;
        }
    }
    
    return n_th;
}