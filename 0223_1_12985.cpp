/* 예상 대진표_12985 */

#include <bitset>

using namespace std;

int solution(int n, int a, int b) {
	/* Get bit representing how A is far from B in binary.
	Since the input A and B is expressed with n-th, which is
	starting from 1, subtract 1 before get this bit */
    bitset<20> bit(bitset<20>(a - 1) ^ bitset<20>(b - 1));

	/* The position of first setd' bit tell how many rounds are needed */
    int i = 20;
    while (--i > 0 && !bit[i]);

	/* Add 1 since the answer represent the position with n-th */
    return i + 1;
}
