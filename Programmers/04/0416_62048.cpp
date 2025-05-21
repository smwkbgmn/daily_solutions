/* 멀쩡한 사각형 - 62048 */

using namespace std;

int euclid(long long a, long long b) {
    return a % b == 0? b : euclid(b, a % b);
}

long long area(int w, int h) {
    return static_cast<long long>(w) * static_cast<long long>(h);
}

long long solution(int w,int h) {
    /* (w * h) - gcd * ((w + h) / gcd - 1) */
    return area(w, h) - (w + h - euclid(w, h));
}