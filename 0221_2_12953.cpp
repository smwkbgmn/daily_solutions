/* N개의 최소공배수_12953 */

#include <vector>
#include <map>

using namespace std;

int solution(vector<int> arr) {
    vector<int> prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    
    map<int, int> common;
    for (auto p: prime) {
        common.insert(pair<int, int>(p, 0));
    }
    
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        map<int, int> factor;
        
        /* Prime Factorization */
        auto it_p = prime.begin();
        while (*it_p <= *it && it_p != prime.end()) {
            if (*it % *it_p == 0) {
                if (factor.find(*it_p) == factor.end()) {
                    factor.insert(pair<int, int>(*it_p, 1));
                } else {
                    ++factor[*it_p];
                }
                *it /= *it_p;
            } else {
                ++it_p;
            }
        }
        
        /* Assign Common Factors */
        for (auto f: factor) {
            if (common[f.first] < f.second) {
                common[f.first] = f.second;
            }
        }
    }
    
    /* Cal LCM */ 
    int lcm = 1;
    for (auto c: common) {
        while (c.second > 0) {
            lcm *= c.first;
            --(c.second);
        }
    }
    
    return lcm;
}

/* 최대공약수를 이용한 다른사람의 풀이 */
int gcd(int x, int y) {
	// cout << "gcm: " << x << ", " << y << '\n';
	return x % y == 0 ? y : gcd(y, x % y);
}

int lcm(int x, int y) { 
	// cout << "lcm: " << x << ", " << y << '\n';
	return x * y / gcd(x, y);
}

int solution_else(vector<int> arr) {
    int answer = arr[0];
    for (auto it = arr.begin() + 1; it != arr.end(); ++it) {
		// cout << "n: " << *it << '\n';
        answer = lcm(answer, *it);
	}
    return answer;
}

// int main() {
// 	vector<int> input = {2, 6, 8, 14};
// 	cout << solution(input) << "\n\n";
// 	cout << solution_else(input) << "\n";

// 	return 0;
// }