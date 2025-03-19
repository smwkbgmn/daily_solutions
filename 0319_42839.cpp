/* 소수 찾기 - 42839 */

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    if (num < 4) {
        return true;
    }
    
    for (auto div = 2; div <= sqrt(num); ++div) {
        if (num % div == 0) {
            return false;
        }
    }
    return true;
}

int solution(string numbers) {    
    unordered_set<int> primes;
    
    vector<int> nums(numbers.length());
    for (auto i = 0; i < numbers.length(); ++i) {
        nums[i] = numbers[i] - '0';
    }
    
    sort(nums.begin(), nums.end());
    
    
    for (auto next = true; next; next = next_permutation(nums.begin(), nums.end())) {
        int num = 0;
        for (auto i = 0; i < nums.size(); ++i) {
            num = (num * 10) + nums[i];
            
            if (is_prime(num)) {
                primes.insert(num);
            }
        }
    }
    
    return primes.size();
}