using namespace std;

int solution(int n) {
    int answer = 1;
    
    for (int i = n - 1; i > 1; --i) {
        int sum = i;

        for (int num = i - 1; sum < n && num > 0; --num) {
            sum += num;
        }

        if (sum == n) {
            ++answer;
        }
    }
    
    return answer;
}
