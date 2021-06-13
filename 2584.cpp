#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    const int ABC_SIZE = 26;
    string ans;
    const struct ex {
        vector<char> ABCZ;
        ex() {
            ABCZ.resize(27);
            for(int i = 0; i < 26; ++i) {
                ABCZ[i] = char('A' + i);
            }
            ABCZ.back() = '?';
        }
    } ex;
    // <Cipher> ::= <String> [<String>]*
    // <String> ::= <Letter> | '['<Cipher>']'
    // <Letter> ::= ['+' | '-']* [A-Z | ?]
    Parser(const string &s) {
        now = s.begin();
        ans = Cipher(now);
    }
    // <Cipher> ::= <String> [<String>]*
    string Cipher(itr &now) {
        string ret = String(now);
        while(*now != ']' and *now != '\0') {
            ret += String(now);
        }
        return ret;
    }
    // <String> ::= <Letter> | '['<Cipher>']'
    string String(itr &now) {
        if(*now == '[') {
            next(now, '[');
            string ret = Cipher(now);
            next(now, ']');
            reverse(ret.begin(), ret.end());
            return ret;
        } else {
            string ret(1, Letter(now));
            return ret;
        }
    }
    // <Letter> ::= ['+' | '-']* [A-Z | ?]
    char Letter(itr &now) {
        int cnt = 0;
        while(*now == '+' or *now == '-') {
            if(*now == '+') {
                cnt++;
                next(now, '+');
            }
            if(*now == '-') {
                cnt--;
                next(now, '-');
            }
        }
        cnt %= ABC_SIZE;
        char ret = *now;
        if(ret != '?') ret = 'A' + (((ret - 'A') + cnt + ABC_SIZE) % ABC_SIZE);
        next(now, ex.ABCZ);
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

int main(){
    string s;
    while(cin >> s and s != ".") {
        Parser parse(s);
        for(char &c : parse.ans) {
            if(c == '?') c = 'A';
        }
        cout << parse.ans << endl;
    }
    return 0;
}
