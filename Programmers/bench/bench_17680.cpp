#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <bitset>
#include <set>
#include <algorithm>
#include <cctype>
#include <random>

using namespace std;
using namespace std::chrono;

// Version 1: map + bitset
class Hasher {
public:
    int get(string key) {
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return tolower(c); });
        
        auto it = table.find(key);
        
        if (it != table.end()) {
            return it->second;
        } else {
            return table[key] = size++;
        }
    }
private:
    unordered_map<string, int> table;
    size_t size = 0;
};

int solution1(int cache_size, const vector<string>& cities) {
    Hasher hs;
    
    list<int> cache;
    bitset<100000> cache_hit;
    
    int runtime = 0;
    
    for (auto s: cities) {
        int id = hs.get(s);
        
        if (cache_hit[id]) {
            cache.remove(id);
            cache.push_back(id);
            
            runtime += 1;
        } else {
            cache_hit.set(id, true);
            cache.push_back(id);
            
            if (cache_size == 0) {
                cache_hit.set(cache.front(), false);
                cache.pop_front();
            } else {
                --cache_size;
            }
            
            runtime += 5;
        }
    }
    
    return runtime;
}

// Version 2: set
int solution2(int cache_size, const vector<string>& cities) {
    set<string> cache_hit;
    list<string> cache;
    
    int runtime = 0;
    
    for (auto s: cities) {
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        
        if (cache_hit.insert(s).second) {
            runtime += 5;
        } else {
			cache.remove(s);        
            runtime += 1;
        }

		cache.push_back(s);

		if (cache.size() > static_cast<size_t>(cache_size)) {
			cache_hit.erase(cache.front());
			cache.pop_front();
		}
    }
    
    return runtime;
}

// Test case generator
vector<string> generate_cities(size_t count, size_t string_length) {
    vector<string> cities;
    cities.reserve(count);

    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> char_dist(0, sizeof(alphanum) - 2);
    
    // Different distributions for testing different scenarios
    // This creates realistic cache behavior with some repeated cities
    uniform_int_distribution<> repeat_dist(0, 3); // Controls repetition frequency

    for (size_t i = 0; i < count; ++i) {
        // Sometimes reuse an existing city for cache hits
        if (i > 0 && repeat_dist(gen) == 0 && !cities.empty()) {
            size_t index = gen() % cities.size();
            cities.push_back(cities[index]);
        } else {
            // Generate a new random city name
            string city;
            city.reserve(string_length);
            
            for (size_t j = 0; j < string_length; ++j) {
                city += alphanum[char_dist(gen)];
            }
            
            cities.push_back(city);
        }
    }
    
    return cities;
}

// Benchmark function
void benchmark(const vector<string>& cities, int cache_size) {
    // Warmup
    solution1(cache_size, cities);
    solution2(cache_size, cities);
    
    // Version 1: map + bitset
    auto start1 = high_resolution_clock::now();
    solution1(cache_size, cities);
    auto end1 = high_resolution_clock::now();
    
    // Version 2: set
    auto start2 = high_resolution_clock::now();
    solution2(cache_size, cities);
    auto end2 = high_resolution_clock::now();
    
    auto duration1 = duration_cast<microseconds>(end1 - start1);
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    
    cout << "Version 1 (map + bitset): " << duration1.count() << " ms" << endl;
    cout << "Version 2 (set): " << duration2.count() << " ms" << endl;
    cout << "Ratio (Version 2 / Version 1): " << (double)duration2.count() / duration1.count() << endl;
    cout << endl;
}

int main() {
    cout << "LRU Cache Implementation Benchmark" << endl;
    cout << "==================================" << endl;

    // Test with different parameters
    vector<pair<string, vector<string>>> test_cases = {
        {"Small cache, short strings", generate_cities(1000, 10)},
        {"Small cache, long strings", generate_cities(1000, 100)},
        {"Large cache, short strings", generate_cities(10000, 10)},
        {"Large cache, long strings", generate_cities(10000, 100)}
    };
    
    vector<int> cache_sizes = {10, 100, 1000};
    
    for (const auto& test_case : test_cases) {
        cout << "\nTest case: " << test_case.first << endl;
        
        for (int cache_size : cache_sizes) {
            cout << "Cache size: " << cache_size << endl;
            benchmark(test_case.second, cache_size);
        }
    }
    
    return 0;
}