/* 카펫_42842 */

#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int x = (brown / 4) + 1 + (brown % 4 > 0);
    int y = x - (brown % 4 > 0);
    
    while ((x - 2) * (y - 2) != yellow) {
        ++x;
        --y;
    }
    
    answer.push_back(x);
    answer.push_back(y);
    
    return answer;
}