/* 쿼드압축 후 개수 세기 - 68936 */

#include <string>
#include <vector>

using namespace std;

int compress(vector<vector<int>>& arr, int y, int x, int d, vector<int>& holder) {
    if (d == 0) {
        return arr[y - 1][x - 1];
    }
    
    int sum = 
        compress(arr, y, x, d / 2, holder) +
        compress(arr, y, x - d, d / 2, holder) +
        compress(arr, y - d, x, d / 2, holder) +
        compress(arr, y - d, x - d, d / 2, holder);

    if (sum == 0 || sum == 4) {
        return sum / 4;
    }

    int mod = sum % 4;
    if (mod > 0) {
        holder[0] += 4 - sum;
        holder[1] += sum;
    } else if (mod == 0) {
        holder[0] += 4 + (sum / 4);
    } else {
        holder[0] += ((mod + 1) * -1) + (sum / 4);
        holder[1] += 4 + mod;
    }
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