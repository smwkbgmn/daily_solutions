/* H-index - 42747 */

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int i = 0;
    while (i < citations.size() && citations[i] > i) {
        ++i;
    }

    return i;
}