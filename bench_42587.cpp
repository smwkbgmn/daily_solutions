#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>

using namespace std;
using namespace std::chrono;

// Implementation with deque
int solution1(vector<int> priority, int location) {
    deque<int> que(priority.begin(), priority.end());
    int prime = *max_element(que.begin(), que.end());
    int n_th = 1;
    
    while (!que.empty()) {
        if (que.front() != prime) {
            que.push_back(que.front());
			que.pop_front();
        } else {
            if (location == 0) {
                return n_th;
            }
            
            que.pop_front();
            ++n_th;
            
            if (find(que.begin(), que.end(), prime) == que.end()) {
                prime = *max_element(que.begin(), que.end());
            }
        }
        
        if (location != 0) {
            --location;   
        } else {
            location = que.size() - 1;
        }
    }
    
    return n_th;
}

// Implementation with queue + priority_queue
int solution2(vector<int> priorities, int location) {	
    queue<pair<int, int>> q;
    priority_queue<int> pq;
    
    for (auto i = 0; i < (int)priorities.size(); ++i) {
        q.push(pair<int, int>(priorities[i], i));
        pq.push(priorities[i]);
    }
    
    int n_th = 1;
    while (!q.empty()) {
        int p = q.front().first;
        int i = q.front().second;
        q.pop();
        
        if (p == pq.top()) {
            if (i == location) {
                return n_th;
            }
            
            pq.pop();
            ++n_th;
        } else {
            q.push(pair<int, int>(p, i));
        }
    }
    
    return n_th;
}

// Function to generate random test cases
vector<vector<int>> generateTestCases(int numCases, int minSize, int maxSize, int minPriority, int maxPriority) {
    vector<vector<int>> testCases;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sizeDist(minSize, maxSize);
    uniform_int_distribution<> priorityDist(minPriority, maxPriority);
    
    for (int i = 0; i < numCases; ++i) {
        int size = sizeDist(gen);
        vector<int> priorities;
        for (int j = 0; j < size; ++j) {
            priorities.push_back(priorityDist(gen));
        }
        testCases.push_back(priorities);
    }
    
    return testCases;
}

// Function to run benchmark
void runBenchmark(int numCases, int minSize, int maxSize, int minPriority, int maxPriority) {
    cout << "Generating " << numCases << " test cases with sizes between " << minSize 
         << " and " << maxSize << ", priorities between " << minPriority 
         << " and " << maxPriority << "..." << endl;
    
    auto testCases = generateTestCases(numCases, minSize, maxSize, minPriority, maxPriority);
    
    vector<int> locations;
    random_device rd;
    mt19937 gen(rd());
    
    for (const auto& testCase : testCases) {
        uniform_int_distribution<> locationDist(0, testCase.size() - 1);
        locations.push_back(locationDist(gen));
    }
    
    cout << "Running benchmarks..." << endl;
    
    // Benchmark original implementation
    auto start1 = high_resolution_clock::now();
    vector<int> results1;
    
    for (size_t i = 0; i < testCases.size(); ++i) {
        results1.push_back(solution1(testCases[i], locations[i]));
    }
    
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    
    // Benchmark optimized implementation
    auto start2 = high_resolution_clock::now();
    vector<int> results2;
    
    for (size_t i = 0; i < testCases.size(); ++i) {
        results2.push_back(solution2(testCases[i], locations[i]));
    }
    
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    
    // Verify results match
    bool resultsMatch = true;
    for (size_t i = 0; i < results1.size(); ++i) {
        if (results1[i] != results2[i]) {
            resultsMatch = false;
            cout << "Results mismatch at test case " << i << ": Version1=" 
                 << results1[i] << ", Version2=" << results2[i] << endl;
            break;
        }
    }
    
    // Print benchmark results
    cout << "\nBenchmark Results:" << endl;
    cout << "Implementation version 1 (deque): " << duration1.count() << " ms" << endl;
    cout << "Implementation version 2 (queue + priority_queue): " << duration2.count() << " ms" << endl;
    cout << "Speed improvement: " << (double)duration1.count() / duration2.count() << "x" << endl;
    cout << "Results match: " << (resultsMatch ? "Yes" : "No") << endl;
}

int main() {
    // Small test cases
    cout << "=== Small Test Cases ===" << endl;
    runBenchmark(1000, 10, 100, 1, 100000);
    
    // Medium test cases
    cout << "\n=== Medium Test Cases ===" << endl;
    runBenchmark(100, 100, 1000, 1, 100000);
    
    // Large test cases
    cout << "\n=== Large Test Cases ===" << endl;
    runBenchmark(10, 1000, 10000, 1, 100000);
    
    // Very large test cases
    cout << "\n=== Very Large Test Cases ===" << endl;
    runBenchmark(5, 10000, 100000, 1, 100000);
    
    return 0;
}