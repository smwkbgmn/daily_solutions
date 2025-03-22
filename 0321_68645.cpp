/* 삼각 달팽이 - 68645 */

#include <vector>

using namespace std;

vector<int> solution(int n) {
    vector<int> snail(n * (n + 1) / 2);
    
	int i = 0, num = 1;

	for (auto d = 0; d < (n / 3) + (n % 3 != 0) ; ++d) {
		for (auto left = d * 2; left < n - d; ++left) {
			i += left;
			snail[i] = num++;
		}

		for (auto bottom = d + 1; bottom < n - (d * 2); ++bottom) {
			snail[++i] = num++;
		}

		for (auto right = n - d; right > (d + 1) * 2; --right) {
			i -= right;
			snail[i] = num++;
		}
	}

    return snail;
}