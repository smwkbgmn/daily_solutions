/* 택배 배달과 수거하기 (Package Delivery and Pickup) - 150369 */

#include <vector>

using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    auto move = [&](vector<int>& holder, int& i) -> void {
        for (auto sum = 0; i >= 0; sum += holder[i--]) {
            if (sum + holder[i] > cap) {
                holder[i] -= (cap - sum);
                break;
            }
        }
    };
    
    int d = n - 1, p = n - 1;
    while (d >= 0 && deliveries[d] == 0) --d;
    while (p >= 0 && pickups[p] == 0) --p;
    
    long long dist = 0;
    while (d >= 0 || p >= 0) {
        dist += (max(d, p) + 1) * 2;
        
        move(deliveries, d);
        move(pickups, p);
    }
    
    return dist;
}