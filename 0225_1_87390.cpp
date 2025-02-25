/* n^2 배열 자르기 - 87390 */

#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    
    int x_l = left % n, x_r = right % n;
    int y_l = left / n, y_r = right / n;

    for (auto y = y_l; y <= y_r; ++y) {

		int x_min = (y == y_l)? x_l : 0;
		int x_max = (y == y_r)? x_r : n - 1;
        for (auto x = x_min; x <= x_max; ++x) {
            answer.push_back(max(x, y) + 1);
        }
    }
    return answer;
}

/* DIV and MOD */

#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    
    for (long long i = left; i <= right; ++i) {
		answer.push_back(max(i % n, i / n) + 1);
	}
    return answer;
}


/*
i % n: x, i / n: y

0, 0 = 0

0, 1 = 1
1, 0 = 1
1, 1 = 1

2, 0 = 2
2, 1 = 2
2, 2 = 2
0, 2 = 2
1, 2 = 2
2, 2 = 2
*/