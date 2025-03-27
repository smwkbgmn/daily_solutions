/* 호텔 대실 - 155651 */

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<vector<string>> book_time) {
    vector<pair<int, int>> books(book_time.size());
    
    for (auto i = 0; i != book_time.size(); ++i) {
        int begin = stoi(book_time[i][0].substr(0, 2)) * 60 + stoi(book_time[i][0].substr(3, 2));
        int end = stoi(book_time[i][1].substr(0, 2)) * 60 + stoi(book_time[i][1].substr(3, 2));
        
        books[i] = {begin, end};
    }
    
    sort(books.begin(), books.end());
    
    priority_queue<int, vector<int>, greater<int>> q;
    
    for (auto& [begin, end]: books) {
        if (!q.empty() && q.top() <= begin) {
            q.pop();
        }
        q.push(end + 10);
    }
    
    return q.size();
}
