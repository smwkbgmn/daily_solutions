#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <memory>

using namespace std;
using namespace std::chrono;

// ==================== BITSET APPROACH ====================
vector<int> solutionBitset(const vector<string>& info, const vector<string>& query) {
    unordered_map<string, bitset<50000>> table[4];
    
    vector<int> scores(info.size());
    int n = 0;
    
    for (const auto& s: info) {
        stringstream ss(s);
        
        string token;
        for (auto i = 0; i < 4; ++i) {
            ss >> token;
            table[i][token].set(n);
        }
        
        int score;
        ss >> score;
        scores[n++] = score;
    }
    
    vector<int> matches;
    for (const auto& s: query) {
        stringstream ss(s);
        
        bitset<50000> crit;
        crit.set();
        
        string token;
        for (auto i = 0; i < 4; ++i) {
            ss >> token;
            if (token != "-") {
                crit &= table[i][token];
            }
            
            // Remove "and"
            if (i + 1 < 4) {
                ss >> token;
            }
        }
        
        int score;
        ss >> score;
        
        // Fixed approach: directly count valid matches
        int match = 0;
        for (size_t i = 0; i < info.size(); i++) {
            if (crit[i] && scores[i] >= score) {
                match++;
            }
        }
        
        matches.push_back(match);
    }
    
    return matches;
}

// ==================== NESTED DICTIONARY APPROACH ====================
class Node {
public:
    unordered_map<string, Node*> children;
    vector<int> scores;
    
    ~Node() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
    
    void addScore(int score) {
        scores.push_back(score);
    }
    
    void sortScores() {
        sort(scores.begin(), scores.end());
    }
    
    int countScoresAbove(int target) {
        if (scores.empty()) return 0;
        
        // Binary search to find first element >= target
        auto it = lower_bound(scores.begin(), scores.end(), target);
        return scores.end() - it;
    }
};

vector<int> solutionNestedDict(const vector<string>& info, const vector<string>& query) {
    Node* root = new Node();
    unique_ptr<Node> rootPtr(root); // For automatic cleanup
    
    vector<vector<string>> categories = {
        {"java", "python", "cpp"},
        {"backend", "frontend"},
        {"junior", "senior"},
        {"chicken", "pizza"}
    };
    
    // Build dictionary
    for (const auto& s : info) {
        stringstream ss(s);
        vector<string> parts;
        string token;
        
        for (int i = 0; i < 5; i++) { // 4 categories + score
            ss >> token;
            parts.push_back(token);
        }
        
        // Insert into nested dictionary
        Node* current = root;
        for (int i = 0; i < 4; i++) {
            if (current->children.find(parts[i]) == current->children.end()) {
                current->children[parts[i]] = new Node();
            }
            current = current->children[parts[i]];
        }
        
        // Add score at leaf node
        current->addScore(stoi(parts[4]));
    }
    
    // Sort scores for binary search
    function<void(Node*)> sortScoresRecursive = [&](Node* node) {
        node->sortScores();
        for (auto& pair : node->children) {
            sortScoresRecursive(pair.second);
        }
    };
    
    sortScoresRecursive(root);
    
    // Process queries
    function<int(Node*, const vector<vector<string>>&, int)> findHelper = 
        [&](Node* node, const vector<vector<string>>& queryStack, int level) {
            if (level == 4) {
                // At leaf level, count scores above target
                int target = stoi(queryStack[4][0]);
                return node->countScoresAbove(target);
            }
            
            int count = 0;
            
            // Process all values at this level based on query
            for (const string& value : queryStack[level]) {
                if (node->children.find(value) != node->children.end()) {
                    count += findHelper(node->children[value], queryStack, level + 1);
                }
            }
            
            return count;
        };
    
    vector<int> results;
    for (const auto& q : query) {
        stringstream ss(q);
        vector<string> parts;
        string token;
        
        // Parse query
        for (int i = 0; i < 8; i++) { // 4 criteria + 3 "and" + score
            ss >> token;
            if (token != "and") {
                parts.push_back(token);
            }
        }
        
        // Convert to query stack format
        vector<vector<string>> queryStack;
        for (int i = 0; i < 4; i++) {
            if (parts[i] == "-") {
                queryStack.push_back(categories[i]);
            } else {
                queryStack.push_back({parts[i]});
            }
        }
        
        // Add score requirement
        queryStack.push_back({parts[4]});
        
        // Process query
        int count = findHelper(root, queryStack, 0);
        results.push_back(count);
    }
    
    return results;
}

// ==================== TEST DATA GENERATION ====================
vector<string> generateInfoData(int size) {
    vector<string> languages = {"java", "python", "cpp"};
    vector<string> positions = {"backend", "frontend"};
    vector<string> levels = {"junior", "senior"};
    vector<string> foods = {"chicken", "pizza"};
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> langDist(0, languages.size() - 1);
    uniform_int_distribution<> posDist(0, positions.size() - 1);
    uniform_int_distribution<> levelDist(0, levels.size() - 1);
    uniform_int_distribution<> foodDist(0, foods.size() - 1);
    uniform_int_distribution<> scoreDist(1, 100000);
    
    vector<string> info;
    for (int i = 0; i < size; i++) {
        string entry = languages[langDist(gen)] + " " +
                      positions[posDist(gen)] + " " +
                      levels[levelDist(gen)] + " " +
                      foods[foodDist(gen)] + " " +
                      to_string(scoreDist(gen));
        info.push_back(entry);
    }
    
    return info;
}

vector<string> generateQueryData(int size) {
    vector<string> languages = {"java", "python", "cpp", "-"};
    vector<string> positions = {"backend", "frontend", "-"};
    vector<string> levels = {"junior", "senior", "-"};
    vector<string> foods = {"chicken", "pizza", "-"};
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> langDist(0, languages.size() - 1);
    uniform_int_distribution<> posDist(0, positions.size() - 1);
    uniform_int_distribution<> levelDist(0, levels.size() - 1);
    uniform_int_distribution<> foodDist(0, foods.size() - 1);
    uniform_int_distribution<> scoreDist(1, 100000);
    
    vector<string> queries;
    for (int i = 0; i < size; i++) {
        string query = languages[langDist(gen)] + " and " +
                      positions[posDist(gen)] + " and " +
                      levels[levelDist(gen)] + " and " +
                      foods[foodDist(gen)] + " " +
                      to_string(scoreDist(gen));
        queries.push_back(query);
    }
    
    return queries;
}

// ==================== BENCHMARK FUNCTION ====================
void runBenchmark(int infoSize, int querySize, int iterations) {
    cout << "=====================================================" << endl;
    cout << "Running benchmark with:" << endl;
    cout << "  - Info size: " << infoSize << " entries" << endl;
    cout << "  - Query size: " << querySize << " queries" << endl;
    cout << "  - Iterations: " << iterations << endl;
    cout << "=====================================================" << endl;
    
    // Generate test data once
    vector<string> info = generateInfoData(infoSize);
    vector<string> query = generateQueryData(querySize);
    
    // Variables to store timing results
    long long bitsetTotalNs = 0;
    long long dictTotalNs = 0;
    
    // Run benchmarks
    for (int iter = 0; iter < iterations; iter++) {
        // Benchmark Bitset Approach
        auto bitsetStart = high_resolution_clock::now();
        vector<int> bitsetResults = solutionBitset(info, query);
        auto bitsetEnd = high_resolution_clock::now();
        
        // Benchmark Nested Dictionary Approach
        auto dictStart = high_resolution_clock::now();
        vector<int> dictResults = solutionNestedDict(info, query);
        auto dictEnd = high_resolution_clock::now();
        
        // Calculate timings
        auto bitsetTime = duration_cast<nanoseconds>(bitsetEnd - bitsetStart).count();
        auto dictTime = duration_cast<nanoseconds>(dictEnd - dictStart).count();
        
        // Add to totals
        bitsetTotalNs += bitsetTime;
        dictTotalNs += dictTime;
        
        // Verify results match
        bool resultsMatch = (bitsetResults == dictResults);
        
        // Print iteration results
        cout << "Iteration #" << (iter + 1) << ":" << endl;
        cout << "  - Bitset approach: " << fixed << setprecision(3) 
             << (bitsetTime / 1000000.0) << " ms" << endl;
        cout << "  - Nested Dict approach: " << fixed << setprecision(3) 
             << (dictTime / 1000000.0) << " ms" << endl;
        cout << "  - Results match: " << (resultsMatch ? "YES" : "NO") << endl;
        
        if (!resultsMatch) {
            cout << "  - MISMATCH DETECTED! Sample differences:" << endl;
            int diffCount = 0;
            for (size_t i = 0; i < min(bitsetResults.size(), dictResults.size()); i++) {
                if (bitsetResults[i] != dictResults[i]) {
                    cout << "    Query #" << i << ": Bitset=" << bitsetResults[i] 
                         << ", Dict=" << dictResults[i] << endl;
                    if (++diffCount >= 5) break;
                }
            }
        }
        cout << endl;
    }
    
    // Calculate and print averages
    double bitsetAvgMs = (bitsetTotalNs / iterations) / 1000000.0;
    double dictAvgMs = (dictTotalNs / iterations) / 1000000.0;
    double speedup = dictAvgMs / bitsetAvgMs;
    
    cout << "=====================================================" << endl;
    cout << "BENCHMARK SUMMARY:" << endl;
    cout << "  - Average Bitset time: " << fixed << setprecision(3) << bitsetAvgMs << " ms" << endl;
    cout << "  - Average Nested Dict time: " << fixed << setprecision(3) << dictAvgMs << " ms" << endl;
    cout << "  - Speedup (Bitset vs Dict): " << fixed << setprecision(2) << speedup << "x" << endl;
    
    if (bitsetAvgMs < dictAvgMs) {
        cout << "  - WINNER: Bitset approach is " << speedup << "x faster!" << endl;
    } else {
        cout << "  - WINNER: Nested Dict approach is " << (1.0/speedup) << "x faster!" << endl;
    }
    cout << "=====================================================" << endl;
}

// ==================== MAIN FUNCTION ====================
int main() {
    cout << "BENCHMARK: BITSET VS NESTED DICTIONARY APPROACH" << endl;
    cout << "==============================================" << endl;
    
    // Small test case
    runBenchmark(100, 50, 5);
    
    // Medium test case
    runBenchmark(1000, 200, 3);
    
    // Large test case
    runBenchmark(10000, 500, 2);
    
    // Very large test case (if memory permits)
    if (sizeof(void*) == 8) { // Only on 64-bit systems
        try {
            runBenchmark(50000, 50000, 1);
        } catch (const bad_alloc&) {
            cout << "Not enough memory for the very large test case." << endl;
        }
    }
    
    return 0;
}