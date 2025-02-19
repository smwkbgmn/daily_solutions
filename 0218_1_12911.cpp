/* 다음 큰 숫자_12911 */

#include <bitset>

using namespace std;

int solution(int n) {
    bitset<24> bit(n);
    
    /* Move mask to first occurence of setd' bit */
    bitset<24> mask(0b1);
    while (!(bit & mask).any()) {
        mask <<= 1;
    }
    
    /* Move maks to first unsetd' bit while counting how many setd' bits are and turning these bits off */
    int one = 0;
    while ((bit & mask).any()) {
        ++one;
        bit ^= mask;
        mask <<= 1;
    }
    
    /* Return the decimal number by adding mask, which is holding where to set upper bit, and rest of setd' bits from right side as many as counted before */
    return static_cast<int>(bitset<24>(bit | mask | bitset<24>((0b1 << one - 1) - 1)).to_ulong());
}