/* 전화번호 목록 - 42577 */

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end(), [](string& a, string& b) {
        return a.length() < b.length();
    });
        
    set<size_t> sizes;
    set<string> prefix;
    
    sizes.insert(phone_book.front().length());
    prefix.insert(phone_book.front());
                    
    for (auto it = phone_book.begin() + 1; it != phone_book.end(); ++it) {
        for (auto size: sizes) {
            if (prefix.find(it->substr(0, size)) != prefix.end()) {
                return false;
            }
        }
        
        sizes.insert(it->length());
        prefix.insert(*it);
    }
                    
    return true;
}