/* 하노이의 탑 - 12946 */

#include <vector>

using namespace std;

/*
    Follow opposite parity order
    Only 1 even/odd disk may be on top 
*/

vector<vector<int>> solution(int n) {
    int min_move = min_move = (1 << n) - 1;
    
    vector<vector<int>> record(min_move, vector<int>(2));
    for (int m = 1; m <= min_move; ++m) {
        int from = (m & m - 1) % 3 + 1;
        int to = ((m | m - 1) + 1) % 3 + 1;
        
        if (n % 2 == 0) {
            if (from > 1) from ^= 1;
            if (to > 1) to ^= 1;
        }

        record[m - 1][0] = from;
        record[m - 1][1] = to;

    }

    return record;
}