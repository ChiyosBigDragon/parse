#include <bits/stdc++.h>
using namespace std;

inline long long mod(long long n,long long m){return(n%m+m)%m;}
struct Parser {
    using itr = string::const_iterator;
    itr now;
    long long ans;
    const long long MOD;
    const struct ex {
        vector<char> _012;
        ex() {
            _012.resize(10);
            for(long long i = 0; i < 10; ++i) {
                _012[i] = char('0' + i);
            }
        }
    } ex;
    // <expr> ::= <term> [ +<term> | -<term> ]*
    // <term> ::= <fact> [ *<fact> | /<fact> ]*
    // <fact> ::= <numb> | (<expr>)
    // <numb> ::= [1-9] [0-9]*
    Parser(const string &s, const long long MOD)
        : MOD(MOD)
        {
            now = s.begin();
            ans = mod(expr(now), MOD);
        }
    // <expr> ::= <term> { +<term> | -<term> }*
    long long expr(itr &now) {
        long long ret = term(now);
        while(1) {
            if(*now == '+') {
                next(now, '+');
                ret += term(now);
                ret = mod(ret, MOD);
            } else if(*now == '-') {
                next(now, '-');
                ret -= term(now);
                ret = mod(ret, MOD);
            } else {
                return ret;
            }
        }
    }
    // <term> ::= <fact> { *<fact> | /<fact> }*
    long long term(itr &now) {
        long long ret = fact(now);
        while(1) {
            if(*now == '*') {
                next(now, '*');
                ret *= mod(fact(now), MOD);
                ret = mod(ret, MOD);
            } else if(*now == '/') {
                next(now, '/');
                long long inv = mod(inverse(fact(now)), MOD);
                ret *= inv;
                ret = mod(ret, MOD);
            } else {
                return ret;
            }
        }
    }
    // <fact> ::= <numb> | (<expr>)
    long long fact(itr &now) {
        if(*now == '(') {
            next(now, '(');
            long long ret = expr(now);
            next(now, ')');
            return ret;
        } else {
            return mod(numb(now), MOD);
        }
    }
    // <numb> ::= [1-9][0-9]*
    long long numb(itr &now) {
        long long ret = 0;
        while(1) {
            if('0' <= *now and *now <= '9') {
                ret *= 10;
                ret += (*now) - '0';
                ret = mod(ret, MOD);
                next(now, ex._012);
            } else {
                return mod(ret, MOD);
            }
        }
    }
    long long inverse(long long x) {
        x = mod(x, MOD);
        if(x == 0) throw "NG";
        long long m = MOD - 2;
        long long ret = 1;
        while(m > 0) {
            if(m & 1) {
                ret = mod(ret * x, MOD);
            }
            x = mod(x * x, MOD);
            m >>= 1;
        }
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

int main() {
    int MOD;
    char colon;
    while(cin >> MOD >> colon && MOD != 0) {
        string s; getline(cin, s);
        string expr;
        for(char c: s) {
            if(c != ' ') {
                expr += c;
            }
        }
        try {
            Parser parse(expr, MOD);
            cout << expr;
            printf(" = %d (mod %d)\n", (int)parse.ans, MOD);
        }
        catch(...) {
            cout << "NG" << endl;
        }
    }
    return 0;
}
