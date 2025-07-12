#include <bits/stdc++.h>
using namespace std;

int levenshteinDistance(const string& s1, const string& s2){
    int m = s1.size(), n = s2.size();
    vector<int> prev(n + 1), curr(n + 1);
    
    for (int j = 0; j <= n; ++j){

        prev[j] = j;
    }
    
    for (int i = 1; i <= m; ++i ) {
        curr[0] = i;
        for (int j = 1; j <= n; ++j) {
            curr[j] = s1[i-1] == s2[j-1] ? prev[j-1] : min({prev[j-1] + 1, prev[j] + 1, curr[j-1] + 1});
        }
        swap(prev, curr);
    }

    return prev[n];
}
vector<pair<int, string>> findMatchingSubstrings(const string& pattern,const string& text,  int maxErrors){

    vector<pair<int, string>> result;
    int pLen = pattern.size(), tLen = text.size();
    
    for (int i = 0; i < tLen; ++i) {
        for (int len = max(1, pLen - maxErrors); len <= pLen + maxErrors && i + len <= tLen; ++len) {

            string substr = text.substr(i, len);
            if (levenshteinDistance(pattern, substr) <= maxErrors) {
                result.emplace_back(i, substr);

            }
        }
    }

    return result;
}

int main() {
    string pattern = "apple", text = "axple baxplee pplee apple";

    int maxErrors = 1;
    
    auto matches = findMatchingSubstrings(pattern, text, maxErrors);
    
    for (size_t i = 0; i < matches.size(); ++i) {

        cout << "(" << matches[i].first << ", \"" << matches[i].second << "\")";

        if (i < matches.size() - 1) cout << ", ";
    }
    cout << endl;
    
    return 0;
}