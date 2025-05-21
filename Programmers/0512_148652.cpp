/* 유사 칸토어 비트열 (Pesudo Cantor Set Bit Sequence) - 148652 */

using namespace std;

int solution(int n, long long l, long long r) {
    int count = 0;
    --l;
    
    while (l < r) {
        for (auto i = l; (i - 2) % 5 != 0; i /= 5) {
            if (i < 5 && i != 2) {
                ++count;
                break;
            }
        }
        ++l;
    }

    return count;
}
