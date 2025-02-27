/* 기능개발 - 42586 */

#include <vector>
#include <cmath>

using namespace std;

vector<int> solution(vector<int> prog, vector<int> speeds) {
    vector<int> answer;
    
    auto i = 0;
    while (i < prog.size()) {
        
        int day = ceil(static_cast<double>((100 - prog[i])) / static_cast<double>(speeds[i]));
        
        int n = 1;
        for (auto i_procd = i + 1; i_procd < prog.size(); ++i_procd) {
            if (prog[i_procd] + (speeds[i_procd] * day) < 100) {
                break;
            }
            ++n;
        }
        
        answer.push_back(n);
        i += n;
    }
    
    
    return answer;
}