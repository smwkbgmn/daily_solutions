/* 뉴스 클러스터링 - 17677 */

#include <string>
#include <set>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

int solution(string s1, string s2) {
    multiset<int> s1_set;
    for (auto i = 0; i < s1.length() - 1; ++i) {
        if (isalpha(s1[i]) && isalpha(s1[i + 1])) {
            /*
            Making it as about handling integer, instead of string: make combination of
            TWO CHARACTERS to a SINGLE INTEGER.
            
            [Bitwise with 037] In ascii table, the distance
            between 'A' and 'a' is 32, which is 40 in octal and 10'0000 in binary.
            With this characteristic, by just operating bitwise &(and) to both letter
            with 31 (= 32 - 1 (dec 31) = 40 - 1 (octal 37) = 10'0000 - 1 (binary 01'1111)),
            it's able to retrieve pure order no matter what letters' case was 
            
            [Bitwise shift with 5] Because we need to take the case of same combination,
            but different order as not the same, multiply 2^5 = 32 at the first letter.
            32 is first bigger number than 26 (letter amount), and number of power of 2 at a time.
            */
            s1_set.insert((s1[i] & 037) << 5 | (s1[i + 1] & 037));
        }
    }
    
    multiset<int> s2_set;
    for (auto i = 0; i < s2.length() - 1; ++i) {
        if (isalpha(s2[i]) && isalpha(s2[i + 1])) {
            s2_set.insert((s2[i] & 037) << 5 | (s2[i + 1] & 037));
        }
    }

    if (s1_set.empty() && s2_set.empty()) {
        return 65536;
    }
    
    vector<int> inter_vec(min(s1_set.size(), s2_set.size()), 0);
    auto inter_it = set_intersection(s1_set.begin(), s1_set.end(), s2_set.begin(), s2_set.end(), inter_vec.begin());
    auto size_inter = distance(inter_vec.begin(), inter_it);
    
    
    return static_cast<float>(size_inter) / static_cast<float>(s1_set.size() + s2_set.size() - size_inter) * 65536;
}