#include <bits/stdc++.h>
using namespace std;

struct Parser {
    using itr = string::const_iterator;
    itr now;
    int ans;
    vector<int> pqr;
    const struct ex {
        const vector<char> _012 = {'0', '1', '2'};
        const vector<char> PQR = {'P', 'Q', 'R'};
    } ex;
    // <formula> ::= 0 | 1 | 2 | P | Q | R |
    //               -<formula> |
    //               (<formula>*<formula>) | (<formula>+<formula>)
    Parser(const string &s, vector<int> &pqr)
        : pqr(pqr)
        {
            now = s.begin();
            ans = formula(now);
        }
    int formula(itr &now) {
        // <formula> ::= -<formula>
        if(*now == '-') {
            next(now, '-');
            int x = formula(now);
            return NOT(x);
        } else if(*now == '(') {
            next(now, '(');
            int x = formula(now);
            // <formula> ::= (<formula>*<formula>)
            if(*now == '*') {
                next(now, '*');
                int y = formula(now);
                next(now, ')');
                return AND(x, y);
            // <formula> ::= (<formula>+<formula>)
            } else if(*now == '+') {
                next(now, '+');
                int y = formula(now);
                next(now, ')');
                return OR(x, y);
            }
        // <formula> ::= 0 | 1 | 2
        } else if('0' <= *now and *now <= '2') {
            int ret = *now - '0';
            next(now, ex._012);
            return ret;
        // <formula> ::= P | Q | R
        } else if('P' <= *now and *now <= 'R') {
            int ret = pqr[*now - 'P'];
            next(now, ex.PQR);
            return ret;
        }
        return 0;
    }
    int NOT(int x) {
        if(x != 1) x = (x + 2) % 4;
        return x;
    }
    int AND(int x, int y) {
        if(x == 2 and y == 2) return 2;
        if(x > 0 and y > 0) return 1;
        return 0;
    }
    int OR(int x, int y) {
        if(x == 0 and y == 0) return 0;
        if(x < 2 and y < 2) return 1;
        return 2;
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
    string s;
    while(cin >> s and s != ".") {
        int cnt = 0;
        for(int i = 0; i < pow(3,3); ++i) {
            vector<int> pqr(3);
            int tmp = i;
            for(int j = 0; j < 3; ++j) {
                pqr[j] = tmp % 3;
                tmp /= 3;
            }
            Parser parse(s,pqr);
            if(parse.ans == 2) {
                cnt++;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
