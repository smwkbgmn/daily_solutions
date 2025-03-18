/* 쿼드압축 후 개수 세기 - 68936 */

#include <vector>

using namespace std;

int compress(vector<vector<int>>& arr, int y, int x, int d, vector<int>& rst) {
    if (d == 0) {
        return arr[y - 1][x - 1];
    }

    int sum = 
        compress(arr, y, x, d / 2, rst) +
        compress(arr, y, x - d, d / 2, rst) +
        compress(arr, y - d, x, d / 2, rst) +
        compress(arr, y - d, x - d, d / 2, rst);

    if (sum == 0 || sum == 4) {
        return sum / 4;
    }

    int mod = sum % 4, div = (sum < 0)? -(sum / 4) : sum / 4;
    if (mod < 0) {
        mod += 4;
        ++div;
    }

    rst[0] += 4 - div - mod;
    rst[1] += mod;
    return -4;
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> rst = {0, 0};

	int last = compress(arr, arr.size(), arr[0].size(), arr.size() / 2, rst);
    if (last == 0 || last == 1) {
		++rst[last];
	}

    return rst;
}
