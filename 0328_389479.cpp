/* 서버 증설 횟수 - 389479 */

#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> players, int m, int k) {
    queue<int> server_q;

    int result = 0;
    for (auto i = 0; i < players.size(); ++i) {
        while (!server_q.empty() && i - server_q.front() == k) {
            server_q.pop();
        }
   
        while (players[i] >= (server_q.size() + 1) * m) {
            server_q.push(i);
            ++result;
        }
    }

    return result;
}