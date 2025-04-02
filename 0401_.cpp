


#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;

// Define a custom comparator for the priority queue with ascending order
struct BitsetComparator {
    // For ascending order (smaller counts have higher priority)
    bool operator()(const pair<int, bitset<26>>& a, const pair<int, bitset<26>>& b) const {
        // Return true if a should come after b in the queue
        // Since priority_queue pops highest priority first, 
        // we need to reverse the comparison for ascending order
        return a.first < b.first;
    }
};

void dfs(bitset<26> comb, size_t i, vector<bitset<26>>& bits, vector<int>& course, priority_queue<pair<int, bitset<26>>, vector<pair<int, bitset<26>>>, BitsetComparator>& high_q) {
    // Process current combination
    if (find(course.begin(), course.end(), comb.count()) != course.end()) {
        size_t count = 0;
        for (auto& bit: bits) {
            if ((bit & comb) == comb) {
                ++count;
            }
        }
        if (count >= 2) {
            high_q.push({count, comb});
        }
    }

    // Move to next bit position
    while (i < 26 && !comb[i]) {
        ++i;
    }
    
    if (i < 26) {
        // Skip this bit (keep it set)
        dfs(comb, i + 1, bits, course, high_q);
        
        // Flip this bit (exclude it) and explore
        comb.flip(i);
        dfs(comb, i + 1, bits, course, high_q);
        // No need to flip back since we don't reuse comb after this
    }
}

// void dfs(bitset<26> comb, size_t i, vector<bitset<26>>& bits, vector<int>& course, priority_queue<pair<int, bitset<26>>, vector<pair<int, bitset<26>>>, BitsetComparator>& high_q) {
// 	while (i < 26 && !comb[i]) {
//         ++i;
//     }

// 	if (i != 26) {
// 		dfs(comb, i + 1, bits, course, high_q);
// 		if (comb[i]) {
// 			dfs(comb.flip(i), i + 1, bits, course, high_q);
// 			comb.flip(i);
// 		}
// 	}

//     if (comb[i] ||
// 		find(course.begin(), course.end(), comb.count()) == course.end()) {
//         return;
//     }

//     size_t count = 0;
//     for (auto& bit: bits) {
//         if ((bit & comb) == comb) {
//             ++count;
//         }
//     }

//     if (count > 1) {
//         high_q.push({count, comb});
//     }
// }

vector<string> solution(vector<string> orders, vector<int> course) {
	vector<bitset<26>> bits;
    for (auto& s: orders) {
        bitset<26> bit;
        for (auto& c: s) {
            bit.set(c - 'A');
        }
        bits.emplace_back(bit);
    }
    
    bitset<26> full_union = bits.front();
    for (size_t i = 1; i < bits.size(); ++i) {
        full_union |= bits[i];
    }
    
    // Using a priority queue with custom comparator for ascending order
    priority_queue<pair<int, bitset<26>>, vector<pair<int, bitset<26>>>, BitsetComparator> high_q;
    
    dfs(full_union, 0, bits, course, high_q);
	
    vector<string> result;
	vector<int> max(course.back() + 1);
    
    while (!high_q.empty()) {
        int count = high_q.top().first;
        bitset<26> comb = high_q.top().second;
        high_q.pop();
        
        if (max[comb.count()] == 0) {
            max[comb.count()] = count;
        }
        
        if (max[comb.count()] == count) {
            string s;
            for (auto i = 0; i < 26; ++i) {
                if (comb[i]) {
                    s += i + 'A';
                }
            }
            result.push_back(s);
        } else {
            max[comb.count()] = -1;
        }
        
        if (upper_bound(max.begin(), max.end(), -1) == max.end()) {
            break;
        }
    }
    
    sort(result.begin(), result.end());
    return result;
}

// int main() {
// 	vector<string> test_order = {
// 		"ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"
// 		// "ACZ"
// 	};
// 	vector<int> test_course = {
// 		2, 3, 5
// 	};
// 	vector<string> answer = solution(test_order, test_course);

// 	for (auto& s: answer) {
// 		cout << s << ", ";
// 	}
// 	cout << "\n";
	
	
// 	return 0;
// }





// #include <string>
// #include <vector>
// #include <queue>
// #include <unordered_map>
// #include <unordered_set>
// #include <algorithm>
// #include <bitset>

// using namespace std;

// #include <iostream>

// vector<string> solution(vector<string> orders, vector<int> course) {
//     vector<bitset<26>> bits;
    
//     for (auto& s: orders) {
//         bitset<26> bit;
//         for (auto& c: s) {
//             bit.set(c - 'A');
//         }
//         bits.emplace_back(bit);
//     }
    
//     unordered_map<bitset<26>, int> inter_counts;
    
//     for (auto l = bits.begin(); l != bits.end(); ++l) {
//         bitset<26> inter = *l;
//         int len = 2;
        
//         for (auto r = l + 1; r != bits.end(); ++r) {
//             inter |= *r;
//             if (inter_counts[inter] < len) {
//                 inter_counts[inter] = len;
//             }
//             ++len;
//         }
//     }
    
//     priority_queue<pair<int, bitset<26>>> high_q;
    
//     for (auto& [inter, count]: inter_counts) {
//         if (find(course.begin(), course.end(), inter.count()) != course.end()) {
//             high_q.push({count, inter});
//         }
//     }
    
//     vector<string> result;
//     vector<int> max(course.back());
    
//     while (!high_q.empty()) {
//         int count = high_q.top().first;
//         bitset<26> inter = high_q.top().second;
//         high_q.pop();
        
//         if (max[inter.count()] == 0) {
//             max[inter.count()] = count;
//         }
        
//         if (max[inter.count()] == count) {
//             string s;
//             for (auto i = 0; i < 26; ++i) {
//                 if (inter[i]) {
//                     s += i + 'A';
//                 }
//             }
//             result.push_back(s);
//         } else {
//             max[inter.count()] = -1;
//         }
        
//         if (upper_bound(max.begin(), max.end(), -1) == max.end()) {
//             break;
//         }
//     }
    
//     sort(result.begin(), result.end());
    
//     return result;
// }


















// #include <string>
// #include <vector>
// #include <queue>
// #include <unordered_map>
// #include <unordered_set>
// #include <algorithm>
// #include <bitset>
// #include <iostream>
// using namespace std;

// // Define a custom comparator for the priority queue with ascending order
// struct BitsetComparator {
//     // For ascending order (smaller counts have higher priority)
//     bool operator()(const pair<int, bitset<26>>& a, const pair<int, bitset<26>>& b) const {
//         // Return true if a should come after b in the queue
//         // Since priority_queue pops highest priority first, 
//         // we need to reverse the comparison for ascending order
//         return a.first > b.first;
//     }
// };

// vector<string> solution(vector<string> orders, vector<int> course) {
//     // sort(orders.begin(), orders.end());
    
//     vector<bitset<26>> bits;
//     for (auto& s: orders) {
//         bitset<26> bit;
//         for (auto& c: s) {
//             bit.set(c - 'A');
//         }
//         bits.emplace_back(bit);
//     }
    
//     sort(bits.begin(), bits.end(), [](bitset<26>& a, bitset<26>& b) -> bool {
//         return a.count() < b.count();
//     });

//     for (auto& bit: bits) {
//         cout << bit << "\n";
//     }
//     cout << "\n";
    
//     unordered_map<bitset<26>, int> inter_counts;

//     for (auto l = bits.begin(); l != bits.end(); ++l) {
//         unordered_map<bitset<26>, int> holder;
        
//         for (auto r = l + 1; r != bits.end(); ++r) {
//             ++holder[*l & *r];
//             // ++inter_counts[*l & *r];
//         }
        
//         for (auto& [inter, count]: holder) {
//             if (inter_counts[inter] < count) {
//                 inter_counts[inter] = count;
//             }
//         }
//     }
    
//     for (auto& [inter, count]: inter_counts) {
//         cout << inter << ": " << count << "\n";
//     }
//     cout << "\n";
    
//     // Using a priority queue with custom comparator for ascending order
//     priority_queue<pair<int, bitset<26>>, vector<pair<int, bitset<26>>>, BitsetComparator> high_q;
    
//     for (auto& [inter, count]: inter_counts) {
//         if (find(course.begin(), course.end(), inter.count()) != course.end()) {
//             high_q.push({count, inter});
//         }
//     }
    
//     vector<string> result;
//     vector<int> max(course.back() + 1, 0);
    
//     while (!high_q.empty()) {
//         int count = high_q.top().first;
//         bitset<26> inter = high_q.top().second;
//         high_q.pop();
        
//         if (max[inter.count()] == 0) {
//             max[inter.count()] = count;
//         }
        
//         if (max[inter.count()] == count) {
//             string s;
//             for (auto i = 0; i < 26; ++i) {
//                 if (inter[i]) {
//                     s += i + 'A';
//                 }
//             }
//             result.push_back(s);
//         } else {
//             max[inter.count()] = -1;
//         }
        
//         if (upper_bound(max.begin(), max.end(), -1) == max.end()) {
//             break;
//         }
//     }
    
//     sort(result.begin(), result.end());
//     return result;
// }


// // vector<string> solution(vector<string> orders, vector<int> course) {
// //     vector<string> answer;
    
// //     unordered_map<char, int> counts;
// //     for (auto& s: orders) {
// //         for (auto& c: s) {
// //             ++counts[c];
// //         }
// //     }
    
// //     vector<pair<int, char>> high_table;
// //     for (auto& [c, n]: counts) {
// //         high_table.push_back({n, c});
// //     }
    
// //     sort(high_table.begin(), high_table.end(), [](pair<int, char>& p1, pair<int, char>& p2) -> bool {
// //         return p1.first > p2.first;
// //     });
    
// //     for (auto& p: high_table) {
// //         cout << p.first << ", " << p.second << "\n";
// //     }
    
// //     return answer;
// // }





#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;

// Generate all subsets of a given size from a bitset
void generateSubsets(bitset<26> bits, int index, int count, int targetSize, 
                    bitset<26> current, unordered_map<bitset<26>, int>& combinations) {
    cout << "subset: " << current << "\n";
    // If we have the target number of bits set
    if (count == targetSize) {
        combinations[current]++;
        return;
    }
    
    // If we've gone past the end or can't get enough bits
    if (index >= 26 || count + (26 - index) < targetSize) {
        return;
    }
    
    // Try including the current bit if it's set in the original bitset
    if (bits[index]) {
        bitset<26> withCurrent = current;
        withCurrent.set(index);
        generateSubsets(bits, index + 1, count + 1, targetSize, withCurrent, combinations);
    }
    
    // Try excluding the current bit
    generateSubsets(bits, index + 1, count, targetSize, current, combinations);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    // Convert orders to bitsets
    vector<bitset<26>> orderBits;
    for (const auto& order : orders) {
        bitset<26> bits;
        for (char c : order) {
            bits.set(c - 'A');
        }
        orderBits.push_back(bits);
    }
    
    // For each course size, find the combinations with the highest frequency
    vector<string> result;
    for (int size : course) {
        cout << "looking for course size " << size << "\n";
        unordered_map<bitset<26>, int> combinations;
        
        // Generate all possible combinations of the current size for each order
        for (const auto& bits : orderBits) {
            cout << bits << "\n";
            // Skip if this order doesn't have enough items
            if (bits.count() < size) continue;
            
            // Generate all subsets of the required size
            unordered_map<bitset<26>, int> orderCombinations;
            generateSubsets(bits, 0, 0, size, bitset<26>(), orderCombinations);
            
            // Add to the overall combinations (only count once per order)
            for (const auto& [combination, _] : orderCombinations) {
                cout << "combination: " << combination << "\n";
                combinations[combination]++;
            }
        }
        
        // Find the maximum frequency for this course size
        int maxFreq = 0;
        for (const auto& [_, freq] : combinations) {
            maxFreq = max(maxFreq, freq);
        }
        
        // Only consider combinations with at least 2 occurrences
        if (maxFreq >= 2) {
            // Add all combinations with the maximum frequency
            for (const auto& [combination, freq] : combinations) {
                if (freq == maxFreq) {
                    // Convert bitset to string
                    string courseItem;
                    for (int i = 0; i < 26; i++) {
                        if (combination[i]) {
                            courseItem += char('A' + i);
                        }
                    }
                    result.push_back(courseItem);
                }
            }
        }
    }
    
    // Sort the result
    sort(result.begin(), result.end());
    return result;
}



#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

// Helper function to generate all combinations of a string
void generateCombinations(string order, int position, string current, 
                         map<string, int>& combinations, int minLength, int maxLength) {
    // Skip if current is too long
    if (current.length() > maxLength) return;
    
    // Add current combination if it's of appropriate length
    if (current.length() >= minLength && current.length() <= maxLength) {
        // Sort characters in the combination to ensure consistent ordering
        string sortedCurrent = current;
        sort(sortedCurrent.begin(), sortedCurrent.end());
        combinations[sortedCurrent]++;
    }
    
    // Base case: reached the end of order
    if (position >= order.length()) return;
    
    // Recursive case 1: include current character
    generateCombinations(order, position + 1, current + order[position], 
                        combinations, minLength, maxLength);
    
    // Recursive case 2: exclude current character
    generateCombinations(order, position + 1, current, 
                        combinations, minLength, maxLength);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    // Sort individual orders
    for (string& order : orders) {
        sort(order.begin(), order.end());
    }
    
    // Find min and max course sizes
    int minCourse = *min_element(course.begin(), course.end());
    int maxCourse = *max_element(course.begin(), course.end());
    
    // Generate all possible combinations for each order
    map<string, int> combinationCount;
    for (const string& order : orders) {
        cout << "seeing order " << order << "\n";
        map<string, int> tempCombinations;
        generateCombinations(order, 0, "", tempCombinations, minCourse, maxCourse);
        
        // Merge with main combinations map
        for (const auto& [combination, count] : tempCombinations) {
            if (count > 0) {  // Only count combinations that appeared
                combinationCount[combination]++;
            }
        }
    }
    
    // Find the most popular combinations for each course size
    vector<string> result;
    map<int, int> maxCountByLength;  // Maps course length to max count
    
    // First, find the maximum count for each course size
    for (const auto& [combination, count] : combinationCount) {
        int len = combination.length();
        // Only consider course sizes that were requested
        if (find(course.begin(), course.end(), len) != course.end() && count >= 2) {
            maxCountByLength[len] = max(maxCountByLength[len], count);
        }
    }
    
    // Then, collect combinations with the maximum count for each course size
    for (const auto& [combination, count] : combinationCount) {
        int len = combination.length();
        if (find(course.begin(), course.end(), len) != course.end() && 
            count == maxCountByLength[len] && count >= 2) {
            result.push_back(combination);
        }
    }
    
    // Sort the result alphabetically
    sort(result.begin(), result.end());
    
    return result;
}



















#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

// Function to generate all combinations of a given size from a string
void generateCombinations(const string& order, int start, string& current, int targetSize, 
                          unordered_map<string, int>& combFreq) {
    if (current.size() == targetSize) {
        // Sort the combination to ensure consistent ordering
        string sortedComb = current;
        sort(sortedComb.begin(), sortedComb.end());
        combFreq[sortedComb]++;
        return;
    }
    
    for (int i = start; i < order.size(); i++) {
        current.push_back(order[i]);
        generateCombinations(order, i + 1, current, targetSize, combFreq);
        current.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> result;
    
    // Process each course size
    for (int size : course) {
        unordered_map<string, int> combFreq;
        
        // Generate combinations for each order
        for (const string& order : orders) {
            string current;
            generateCombinations(order, 0, current, size, combFreq);
        }
        
        // Find the max frequency for this course size
        int maxFreq = 1;  // Start at 1 because we need at least 2 occurrences
        for (const auto& pair : combFreq) {
            maxFreq = max(maxFreq, pair.second);
        }
        
        // Add combinations with the max frequency to the result
        if (maxFreq >= 2) {
            for (const auto& pair : combFreq) {
                if (pair.second == maxFreq) {
                    result.push_back(pair.first);
                }
            }
        }
    }
    
    sort(result.begin(), result.end());
    return result;
}





