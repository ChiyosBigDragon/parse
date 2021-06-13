#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int ans;
    map<string, int> mp;
    const struct ex {
        vector<char> ABC, abc, _012;
        ex() {
            ABC.resize(26);
            abc.resize(26);
            _012.resize(10);
            for(int i = 0; i < 26; ++i) {
                ABC[i] = char('A' + i);
                abc[i] = char('a' + i);
                if(i < 10) _012[i] = char('0' + i);
            }
        }
    } ex;
    // <Molecule> ::= <fact> [<fact>]*
    // <fact> ::= <Atom> [<Number>]? | (<Molecule>) <Number>
    // <Atom> ::= [A-Z] [a-z]?
    // <Number> ::= [1-9] [0-9]?
    Parser(const string &s, const map<string, int> &mp)
        : mp(mp)
        {
            now = s.begin();
            ans = Molecule(now);
        }
    // <Molecule> ::= <fact> [<fact>]*
    int Molecule(itr &now) {
        int ret = fact(now);
        while(*now != ')' and *now != '\0') {
            ret += fact(now);
        }
        return ret;
    }
    // <fact> ::= <Atom> [<Number>]? | (<Molecule>) <Number>
    int fact(itr &now) {
        // <fact> ::= <Atom> [<Number>]?
        if('A' <= *now and *now <= 'Z') {
            int ret = Atom(now);
            if('1' <= *now and *now <= '9') {
                ret *= Number(now);
            }
            return ret;
        }
        // <fact> ::= (<Molecule>) <Number>
        if(*now == '(') {
            next(now, '(');
            int ret = Molecule(now);
            next(now, ')');
            ret *= Number(now);
            return ret;
        }
        return 0;
    }
    // <Atom> ::= [A-Z] [a-z]?
    int Atom(itr &now) {
        string atom;
        atom += *now;
        next(now, ex.ABC);
        if('a' <= *now and *now <= 'z') {
            atom += *now;
            next(now, ex.abc);
        }
        if(mp.at(atom)) {
            return mp[atom];
        }
        throw;
    }
    // <Number> ::= [1-9] [0-9]?
    int Number(itr &now) {
        int ret = *now - '0';
        next(now, ex._012);
        if('0' <= *now and *now <= '9') {
            ret *= 10;
            ret += *now - '0';
            next(now, ex._012);
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

void solve(const map<string, int> &mp) {
    string s;
    while(cin >> s and s != "0") {
        try {
            Parser parse(s, mp);
            cout << parse.ans << endl;
        }
        catch(...) {
            cout << "UNKNOWN" << endl;
            solve(mp);
        }
    }
}

int main(){
    map<string, int> mp;
    string s;
    while(cin >> s and s != "END_OF_FIRST_PART") {
        cin >> mp[s];
    }
    solve(mp);
    return 0;
}
