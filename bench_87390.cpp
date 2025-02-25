#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <iomanip>

using namespace std;

// Version 1: Nested loops approach
vector<int> solution1(int n, long long left, long long right) {
    vector<int> answer;
    
    int x_l = left % n, x_r = right % n;
    int y_l = left / n, y_r = right / n;
    
    for (auto y = y_l; y <= y_r; ++y) {
        int x_min = (y == y_l) ? x_l : 0;
        int x_max = (y == y_r) ? x_r : n - 1;
        for (auto x = x_min; x <= x_max; ++x) {
            answer.push_back(max(x, y) + 1);
        }
    }
    return answer;
}

// Version 2: Division and modulo approach
vector<int> solution2(int n, long long left, long long right) {
    vector<int> answer;
    
    for (long long i = left; i <= right; ++i) {
		answer.push_back(max(i % n, i / n) + 1);
	}
    return answer;
}

// Function to run benchmark
void runBenchmark(const string& name, 
                 function<vector<int>(int, long long, long long)> solution,
                 int n, long long left, long long right,
                 int iterations) {
    
    double totalTime = 0;
    vector<int> result;
    
    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        result = solution(n, left, right);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> duration = end - start;
        totalTime += duration.count();
    }
    
    cout << name << ":\n";
    cout << "  Average time: " << fixed << setprecision(3) << (totalTime / iterations) << " ms\n";
    cout << "  Result size: " << result.size() << " elements\n";
    cout << "  First few values: ";
    for (int i = 0; i < min(5, static_cast<int>(result.size())); i++) {
        cout << result[i] << " ";
    }
    cout << "...\n\n";
}

int main() {
    // Test cases with different sizes
    vector<tuple<string, int, long long, long long, int>> testCases = {
        // name, n, left, right, iterations
        {"Small input", 3, 2, 5, 1000},
        {"Medium input", 100, 5000, 5500, 100},
        {"Large input", 1000, 500000, 502000, 10},
        {"Very large input", 10000, 50000000, 50005000, 5}
    };
    
    cout << "PERFORMANCE BENCHMARK\n";
    cout << "====================\n\n";
    
    for (const auto& [name, n, left, right, iterations] : testCases) {
        cout << "Test case: " << name << "\n";
        cout << "Parameters: n=" << n << ", range=[" << left << ", " << right << "], " 
             << "range size=" << (right - left + 1) << "\n\n";
        
        runBenchmark("Version 1 (Nested loops)", solution1, n, left, right, iterations);
        runBenchmark("Version 2 (Division and modulo)", solution2, n, left, right, iterations);
        
        cout << "--------------------\n\n";
    }
    
    return 0;
}