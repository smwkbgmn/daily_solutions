/* 수식 최대화 - 67257 */

#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>

using namespace std;
using fn_operation = long long (*)(long long, long long);

long long mlt(long long a, long long b) { return a * b; }
long long add(long long a, long long b) { return a + b; }
long long sub(long long a, long long b) { return a - b; }

deque<pair<long long, char>>& operate(deque<pair<long long, char>> & q, char operand) {
    fn_operation fn;
    switch (operand) {
        case 1: fn = mlt; break;
        case 2: fn = add; break;
        case 4: fn = sub; break;
    }
    
    q.push_back(q.front());
    q.pop_front();
    
    while (q.front().second != 's') {
        if (q.front().second == operand) {
            q.back().first = fn(q.back().first, q.front().first);
        } else {
            q.push_back(q.front());
        }
        q.pop_front();
    }
    
    return q;
}

long long dfs(deque<pair<long long, char>>& q, char used) {
    if (used == 7) {
        return q.front().first;
    }
    
    long long max = 0;
    for (auto i = 0; i < 3; ++i) {
        int op = 1 << i;
        
        if ((used & op) == 0) {
            auto q_cpy = q;
             
            long long rst = abs(dfs(operate(q_cpy, op), used | op));
            if (max < rst) {
                max = rst;
            }
        }
    }
    
    return max;
}

long long solution(string expression) {
    stringstream ss(expression);
    
    long long n;
    ss >> n;
    
    deque<pair<long long, char>> q;
    q.push_back({n, 's'});
    
    while (!ss.eof()) {
        char c;
        ss >> c;
        ss >> n;
        
        q.push_back({n, c - '*' + 1});
    }
    
    return dfs(q, 0);
}
