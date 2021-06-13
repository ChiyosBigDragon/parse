#include <bits/stdc++.h>
using namespace std;

// <expr> ::= <term> [ >> <term> ]*
// <term> ::= <number> | S< <expr> >
// <number> ::= 0 | [1-9][0-9]*
constexpr int64_t MOD = 1e9 + 7;

struct Parser {
	// var
	using itr = string::const_iterator;
	itr now;
	int64_t ans;
	// expect
	const struct ex {
		vector<char> _012;
		vector<char> azAZ;
		ex() {
			for(char c = '0'; c <= '9'; ++c) {
				_012.push_back(c);
			}
			for(char c = 'a'; c <= 'z'; ++c) {
				azAZ.push_back(c);
			}
			for(char c = 'A'; c <= 'Z'; ++c) {
				azAZ.push_back(c);
			}
		}
	} ex;
	
	Parser(const string& s) {
		now = s.begin();
		ans = expr(now);
	}
	// <expr> ::= <term> [ >> <term> ]*
	int64_t expr(itr& now) {
		int64_t ret = term(now);
		while(true) {
			if(*now == '>') {
				next(now, '>');
				if(*now != '>') {
					now -= 1;
					return ret;
				}
				next(now, '>');
				if(*now == 'S' or ('0' <= *now and *now <= '9')) {
					int64_t x = term(now);
					ret >>= min<int64_t>(60, x);
				} else {
					now -= 2;
					return ret;
				}
			} else {
				return ret;
			}
		}
	}
	// <term> ::= <number> | S< <expr> >
	int64_t term(itr& now) {
		if(*now == 'S') {
			next(now, 'S');
			next(now, '<');
			int64_t ret = expr(now);
			next(now, '>');
			ret %= MOD;
			return (ret * ret % MOD);
		} else {
			return number(now);
		}
	}
	// <number> ::= 0 | [1-9][0-9]*
	int64_t number(itr& now) {
		int64_t ret = 0;
		if(*now == '0') {
			next(now, '0');
			return ret;
		} else {
			while(true) {
				if('0' <= *now and *now <= '9') {
					ret *= 10;
					ret += (*now) - '0';
					next(now, ex._012);
				} else {
					return ret;
				}
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
				++now;
				return;
			}
		}
		// Debug
		fprintf(stderr, "Expected: ");
		for(char c: expected) {
			fprintf(stderr, "%c, ", c);
		}
		fprintf(stderr, "\nGot: %c\n", *now);
		fprintf(stderr, "Rest: ");
		while(*now) {
			fprintf(stderr, "%c", *now++);
		}
		fprintf(stderr, "\n");
		exit(1);
	}
};

void solve(string& s) {
	Parser p(s);
	cout << p.ans << '\n';
}

int main() {
	string s;
	while(true) {
		getline(cin, s);
		if(s == "#") break;
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
		solve(s);
	}
	return 0;
}
