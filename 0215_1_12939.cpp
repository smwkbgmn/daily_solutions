/* 최댓값과 최솟값 */

#include <string>
#include <set>
#include <sstream>

using namespace std;

string solution(string s) {
	stringstream ss(s);
	set<int> numset;
	
	int num;
	while (ss >> num) {
		numset.insert(num);
	}

    ss << *numset.begin() << ' ' << *numset.rbegin();

    return ss.str();
}