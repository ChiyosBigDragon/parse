#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int ans;
    map<char, bool> mp;
    const struct ex {
        vector<char> TFabc;
        ex() {
            TFabc.resize(28);
            TFabc[0] = 'T';
            TFabc[1] = 'F';
            for(int i = 0; i < 26; ++i) {
                TFabc[i + 2] = char('a' + i);
            }
        }
    } ex;
    // <formula> ::= T | F |
    //               a | b | c | d | e | f | g | h | i | j | k |
    //               -<formula> |
    //               (<formula>*<formula>) | (<formula>+<formula>) | (<formula>-><formula>)
    Parser(const string &s, const map<char, bool> &mp)
        : mp(mp)
        {
            now = s.begin();
            ans = formula(now);
        }
    bool formula(itr &now) {
        // <formula> ::= -<formula>
        if(*now == '-') {
            next(now, '-');
            return (not formula(now));
        }
        // <formula> ::= (<formula>*<formula>) | (<formula>+<formula>) | (<formula>-><formula>)
        if(*now == '(') {
            next(now, '(');
            bool ret = formula(now);
            // <formula> ::= (<formula>*<formula>)
            if(*now == '*') {
                next(now, '*');
                ret &= formula(now);
            }
            // <formula> ::= (<formula>+<formula>)
            if(*now == '+') {
                next(now, '+');
                ret |= formula(now);
            }
            // <formula> ::= (<formula>-><formula>)
            if(*now == '-') {
                next(now, '-');
                next(now, '>');
                ret = (not ret) | formula(now);
            }
            next(now, ')');
            return ret;
        }
        // <formula> ::= T | F | a | b | c | d | e | f | g | h | i | j | k
        bool ret = mp[*now];
        next(now, ex.TFabc);
        return ret;
    }
    void next(itr &now, const char expected) {
        vector<char> req = {expected};
        next(now, req);
    }
    void next(itr &now, const vector<char> &expected) {
        for(char c: expected){
            if(*now == c){
                now++;
                return;
            }
        }
        // デバッグ用
        fprintf(stderr, "Expected: ");
        for(char c: expected) fprintf(stderr, "%c", c);
        fprintf(stderr, "\nGot: %c\n", *now);
        fprintf(stderr, "Rest: ");
        while(*now) fprintf(stderr, "%c", *now++);
    }
};

void solve(string &s) {
    map<char, bool> mp;
    mp['T'] = true;
    mp['F'] = false;
    string s1, s2;
    for(int i = 0; ; ++i) {
        if(s[i] == '=') {
            s1 = s.substr(0, i);
            s2 = s.substr(i + 1);
            break;
        }
    }
    for(int i = 0; i < (1 << 11); ++i) {
        for(int j = 0; j < 11; ++j) {
            mp['a' + j] = (i >> j) & 1;
        }
        Parser parse1(s1, mp);
        Parser parse2(s2, mp);
        if(parse1.ans != parse2.ans) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" <<endl;
}

int main(){
    string s;
    while(cin >> s and s != "#") {
        solve(s);
    }
    return 0;
}
