/* 점프와 순간 이동_12980 */

#include <bitset>

using namespace std;

int solution(int n) {
    int battery = 0;

    bitset<32> n_bit(n);
    while (n_bit.any()) {
        if (n_bit.test(0)) {
            n_bit.set(0, false);
            ++battery;
        }
        n_bit >>= 1;
    }

    return battery;
}