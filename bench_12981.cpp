#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

// Version 1: Using set with clever insert check
vector<int> solution1(int n, vector<string> words) {
    vector<int> answer = { 0, 0 };
	
	set<string> used = { words[0] };
    
    size_t i = 0;
    while (++i < words.size()
	&& words[i].front() == words[i - 1].back()
	&& used.insert(words[i]).second);
    
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }
    return answer;
}

// Version 2: Using map
vector<int> solution2(int n, vector<string> words) {
    vector<int> answer = { 0, 0 };

    map<string, bool> used = { pair<string, bool>(words[0], true) };
    
    size_t i = 0;
    while (++i < words.size()
    && words[i].front() == words[i - 1].back()
    && !used[words[i]]) {
        used[words[i]] = true;
    }
    
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }
    return answer;
}

// Version 3: Using vector with find
vector<int> solution3(int n, vector<string> words) {
    vector<int> answer = { 0, 0 };

    vector<string> used = { words[0] };
    
    size_t i = 0;
    while (++i < words.size()
    && words[i].front() == used.back().back()
    && find(used.begin(), used.end(), words[i]) == used.end()) {
        used.push_back(words[i]);
    }
    
    if (i != words.size()) {
        answer[0] = (i % n) + 1;
        answer[1] = (i / n) + 1;
    }
    return answer;
}

// Test helper functions remain the same as before...
string generateRandomString(int length) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    return result;
}

vector<string> generateTestData(int size, int stringLength) {
    vector<string> result;
    result.reserve(size);
    string prev = generateRandomString(stringLength);
    result.push_back(prev);
    for (int i = 1; i < size; ++i) {
        string next = generateRandomString(stringLength - 1);
        next = prev.back() + next;
        result.push_back(next);
        prev = next;
    }
    return result;
}

int main() {
    srand(time(0));
    vector<int> testSizes = {100, 1000, 10000, 100000}; 
    
    for (int size : testSizes) {
        cout << "\nTesting with " << size << " words:" << endl;
        vector<string> testWords = generateTestData(size, 5);
        int n = 3;
        
        // Test all three versions
        for (int version = 1; version <= 3; ++version) {
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; ++i) {
                switch(version) {
                    case 1: solution1(n, testWords); break;
                    case 2: solution2(n, testWords); break;
                    case 3: solution3(n, testWords); break;
                }
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count() / 100.0;
            
            string versionName = version == 1 ? "Set" : (version == 2 ? "Map" : "Vector");
            cout << versionName << " version average time: " << duration << " ms" << endl;
        }
    }
    return 0;
}