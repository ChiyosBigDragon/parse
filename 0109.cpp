#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int ans;
    const struct ex {
        vector<char> _012;
        ex() {
            _012.resize(10);
            for(int i = 0; i < 10; ++i) {
                _012[i] = char('0' + i);
            }
        }
    } ex;
    // <expr> ::= <term> [ +<term> | -<term> ]*
    // <term> ::= <fact> [ *<fact> | /<fact> ]*
    // <fact> ::= <numb> | (<expr>)
    // <numb> ::= [1-9] [0-9]*
    Parser(const string &s) {
        now = s.begin();
        ans = expr(now);
    }
    // <expr> ::= <term> { +<term> | -<term> }*
    int expr(itr &now) {
        int ret = term(now);
        while(1) {
            if(*now == '+') {
                next(now, '+');
                ret += term(now);
            } else if(*now == '-') {
                next(now, '-');
                ret -= term(now);
            } else {
                return ret;
            }
        }
    }
    // <term> ::= <fact> { *<fact> | /<fact> }*
    int term(itr &now) {
        int ret = fact(now);
        while(1) {
            if(*now == '*') {
                next(now, '*');
                ret *= fact(now);
            } else if(*now == '/') {
                next(now, '/');
                ret /= fact(now);
            } else {
                return ret;
            }
        }
    }
    // <fact> ::= <numb> | (<expr>)
    int fact(itr &now) {
        if(*now == '(') {
            next(now, '(');
            int ret = expr(now);
            next(now, ')');
            return ret;
        } else {
            return numb(now);
        }
    }
    // <numb> ::= [1-9][0-9]*
    int numb(itr &now) {
        int ret = 0;
        while(1) {
            if('0' <= *now and *now <= '9') {
                ret *= 10;
                ret += (*now) - '0';
                next(now, ex._012);
            } else {
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

int main() {
    int n; cin >> n;
    while(n--) {
        string s; cin >> s;
        Parser parse(s);
        cout << parse.ans << endl;
    }
    return 0;
}
