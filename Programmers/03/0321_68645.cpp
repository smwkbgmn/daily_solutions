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


/* Version: 2d array + recursive */
#include <algorithm>

void fill(vector<vector<int>>& snail, int n, int d, int num) {
    if (n > 3) {
    	fill(snail, n - 3, d + 1, num + ((n - 1) * 3));
    }

	int r = d * 2;

    for (auto i = 0; i < n - 1; ++i) {
        snail[r++][d] = num++;
    }
    
    for (auto i = 0; i < n; ++i) {
        snail[r][d + i] = num++;
    }
	--num;

    int size = snail[r].size();
    for (auto i = 0; i < n - 1; ++i) {
        snail[r--][size-- - d - 1] = num++;
    }
}

vector<int> solution(int n) {
    vector<vector<int>> snail;

    for (auto r = 0; r < n; ++r) {
        snail.push_back(vector<int>(r + 1));
    }

    fill(snail, n, 0, 1);

	snail[0].resize(n * (n + 1) / 2);

	int end = 1;
	for (auto r = 1; r < n; ++r) {
		move(snail[r].begin(), snail[r].end(), snail[0].begin() + end);
		end += r + 1;
	}
    
    return snail[0];
}
