/* 더 맵게 - 42626 */

#include <vector>
#include <algorithm>

using namespace std;

void heap_pop(vector<int>& holder) {
    pop_heap(holder.begin(), holder.end(), greater<int>());
}

void heap_push(vector<int>& holder, unsigned long val) {
    *holder.rbegin() = val;
    push_heap(holder.begin(), holder.end(), greater<int>());
}

int solution(vector<int> scoville, int k) {
	make_heap(scoville.begin(), scoville.end(), greater<int>());
    
    int rst = 0;
    while (scoville.front() < k && scoville.size() != 1) {
        unsigned long scv = scoville.front();
        heap_pop(scoville);
        scoville.pop_back();
        
        scv += (scoville.front() << 1);
        heap_pop(scoville);
        
        heap_push(scoville, scv);
        
        ++rst;
    }
    
    return (scoville.size() == 1 && scoville.front() < k)? -1 : rst;
}