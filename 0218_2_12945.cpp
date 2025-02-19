/* 피보나치 수_12945 */

using namespace std;

int solution(int n) {
    /* Problem ensures input n is above 1, no need to handle */
    int pre_2 = 0, pre_1 = 1;
    while (--n) {
        int curnt = (pre_2 + pre_1) % 1234567;
        
        pre_2 = pre_1;
        pre_1 = curnt;
    }
    
    return pre_1;
}
