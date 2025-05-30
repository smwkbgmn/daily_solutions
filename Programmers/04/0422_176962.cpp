/* 과제 진행하기 - 176962 */

#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<string> solution(vector<vector<string>> plans) {
    sort(plans.begin(), plans.end(), [](vector<string>& a, vector<string>& b) -> bool {
       return a[1] < b[1]; 
    });

    vector <string> record;

    stack<pair<int, string>> task;
    int current = 0;
    
    for (auto& v: plans) {
        int next = stoi(v[1].substr(0, 2)) * 60 + stoi(v[1].substr(3, 2));
        
        while (!task.empty()) {
            auto& prev = task.top();
            
            int remain = (current + prev.first) - next;
            if (remain > 0) {
                prev.first = remain;
                break;
            } else {
                current += prev.first;
                record.push_back(prev.second);
                task.pop();
            }
        }
        
        current = next;
        task.push({ stoi(v[2]), v[0] });
    }
    
    while (!task.empty()) {
        record.push_back(task.top().second);
        task.pop();
    }
    
    return record;
}