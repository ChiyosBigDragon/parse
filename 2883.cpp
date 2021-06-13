#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int ans;
    map<char, int> mp;
    const struct ex {
        vector<char> op, abc;
        ex() {
            op = {'+', '*', '^'};
            abc.resize(4);
            for(int i = 0; i < 4; ++i) {
                abc[i] = char('a' + i);
            }
        }
    } ex;
    // <Hash> ::= <Letter> | [<Op><Hash><Hash>]
    // <Op> ::= + | * | ^
    // <Letter> ::= a | b | c | d
    Parser(const string &s, const map<char, int> &mp)
        : mp(mp)
        {
            now = s.begin();
            ans = Hash(now);
        }
    // <Hash> ::= <Letter> | [<Op><Hash><Hash>]
    int Hash(itr &now) {
        // <Hash> ::= <Letter>
        if('a' <= *now and *now <= 'd') {
            return Letter(now);
        }
        // <Hash> ::= [<Op><Hash><Hash>]
        next(now, '[');
        char Op = *now;
        next(now, ex.op);
        int ret = Hash(now);
        if(Op == '+') {
            ret |= Hash(now);
        }
        if(Op == '*') {
            ret &= Hash(now);
        }
        if(Op == '^') {
            ret ^= Hash(now);
        }
        next(now, ']');
        return ret;
    }
    // <Letter> ::= a | b | c | d
    int Letter(itr &now) {
        int ret = mp[*now];
        next(now, ex.abc);
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

void solve(string &s, string &p) {
    map<char, int> mp;
    for(int i = 0; i < 4; ++i) {
        mp['a' + i] = p[i] - '0';
    }
    Parser parse(s, mp);
    int ans = parse.ans;
    int cnt = 0;
    for(int i = 0; i < pow(10, 4); ++i) {
        int tmp = i;
        for(int j = 0; j < 4; ++j) {
            mp['a' + j] = tmp % 10;
            tmp /= 10;
        }
        Parser parse1(s, mp);
        if(ans == parse1.ans) {
            cnt++;
        }
    }
    printf("%d %d\n", ans, cnt);
}

int main(){
    string s, p;
    while(cin >> s and s != ".") {
        cin >> p;
        solve(s, p);
    }
    return 0;
}
