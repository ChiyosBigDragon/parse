#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int X;
    __int128_t ans;
    const struct ex {
        vector<char> _012;
        ex() {
            _012.resize(10);
            for(int i = 0; i < 10; ++i) {
                _012[i] = char('0' + i);
            }
        }
    } ex;
    // <expr> ::= <numb> [ +<numb> ]*
    // <numb> ::= [ 1-9 | X ] [ 0-9 | X ]*
    Parser(const string &s, const int X)
        : X(X)
    {
        now = s.begin();
        ans = expr(now);
    }
    // <expr> ::= <numb> [ +<numb> ]*
    __int128_t expr(itr &now) {
        __int128_t ret = numb(now);
        while(1) {
            if(*now == '+') {
                next(now, '+');
                ret += numb(now);
            } else {
                return ret;
            }
        }
    }
    // <numb> ::= [ 1-9 | X ] [ 0-9 | X ]*
    __int128_t numb(itr &now) {
        __int128_t ret = 0;
        int digit = 0;
        bool top0 = true;
        while(1) {
            ret *= 10;
            if('0' <= *now and *now <= '9') {
                top0 = false;
                ret += (*now) - '0';
                next(now, ex._012);
                ++digit;
            } else if(*now == 'X') {
                if(X != 0) top0 = false;
                ret += X;
                next(now, 'X');
                ++digit;
            } else {
                if(top0 and digit > 1) throw "top0";
                return ret;
            }
        }
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

void solve(const string &s1, const string &s2, const int X) {
    if(X >= 10) {
        cout << "NA" << endl;
        return;
    }
    try {
        Parser parse1(s1, X);
        Parser parse2(s2, X);
        if(parse1.ans != parse2.ans) throw "mismatch";
        cout << X << endl;
    }
    catch(...) {
        solve(s1, s2, X + 1);
    }
}

int main(){
    string s;
    while(cin >> s) {
        int n = s.size();
        string s1, s2;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '=') {
                s1 = s.substr(0, i);
                s2 = s.substr(i + 1);
                break;
            }
        }
        solve(s1, s2, 0);
    }
    return 0;
}
