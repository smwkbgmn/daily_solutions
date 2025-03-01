/* 캐시 - 17680 */

#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <bitset>
#include <algorithm>
#include <cctype>

using namespace std;

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

int solution(int cache_size, vector<string> cities) {
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

/* Version: set */
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <cctype>

using namespace std;

int solution(int cache_size, vector<string> cities) {
    set<string> cache_hit;
    list<string> cache;
    
    int runtime = 0;
    
    for (auto s: cities) {
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        
        if (cache_hit.insert(s).second) {
            cache.push_back(s);

            if (cache_size == 0) {
                cache_hit.erase(cache.front());
                cache.pop_front();    
            } else {
                --cache_size;
            }

            runtime += 5;
        } else {
            cache.remove(s);
            cache.push_back(s);

            runtime += 1;
        }
    }
    
    return runtime;
}