/* 예상 대진표_12985 */

#include <bitset>

using namespace std;

int solution(int n, int a, int b) {
	/* The input N can be used to determine the size of bit representation.
	However because it's only size 20 as following constraints, and declaring bitset with 
	variable size is not allowed, just going with fixed size is fully okay. */
	(void)n;

	/* Get bit representing how far A is from B in binary.
	Since the input A and B is expressed with n-th, which is
	starting from 1, subtract 1 before get this bit */
    bitset<20> bit(bitset<20>(a - 1) ^ bitset<20>(b - 1));

	/* The position of first setd' bit tell how many rounds are needed */
    int i = 20;
    while (--i > 0 && !bit[i]);

	/* Add 1 back since the answer represent the position with n-th */
    return i + 1;
}
