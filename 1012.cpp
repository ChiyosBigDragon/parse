#include <bits/stdc++.h>
using namespace std;

// <expr> ::= <term> [ [uids] <term> ]*
// <term> ::= c <name> | ( <expr> )
// <name> ::= [A-E]
set<int> st[5];
set<int> u;

struct Parser {
	// var
	using itr = string::const_iterator;
	itr now;
	set<int> ans;
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
	set<int> calc(set<int>& lhs, set<int>& rhs, char op) {
		set<int> ret;
		if(op == 'u') {
			for(int i : lhs) {
				ret.insert(i);
			}
			for(int i : rhs) {
				ret.insert(i);
			}
		}
		if(op == 'i') {
			for(int i : lhs) {
				if(rhs.find(i) != rhs.end()) {
					ret.insert(i);
				}
			}
		}
		if(op == 'd') {
			for(int i : lhs) {
				if(rhs.find(i) == rhs.end()) {
					ret.insert(i);
				}
			}
		}
		if(op == 's') {
			for(int i : lhs) {
				if(rhs.find(i) == rhs.end()) {
					ret.insert(i);
				}
			}
			for(int i : rhs) {
				if(lhs.find(i) == lhs.end()) {
					ret.insert(i);
				}
			}
		}
		return ret;
	}
	// <expr> ::= <term> [ [uids] <term> ]*
	set<int> expr(itr& now) {
		set<int> ret = term(now);
		while(true) {
			if(*now == 'u' or *now == 'i' or *now == 'd' or *now == 's') {
				char op = *now;
				next(now, op);
				set<int> rhs = term(now);
				ret = calc(ret, rhs, op);
			} else {
				return ret;
			}
		}
	}
	// <term> ::= <name> | c <term> | ( <expr> )
	set<int> term(itr& now) {
		set<int> ret;
		if(*now == 'c') {
			next(now, 'c');
			set<int> rhs = term(now);
			ret = calc(u, rhs, 'd');
			return ret;
		} else if(*now == '(') {
			next(now, '(');
			set<int> ret = expr(now);
			next(now, ')');
			return ret;
		} else {
			ret = name(now);
			return ret;
		}
	}
	// <name> ::= [A-E]
	set<int> name(itr& now) {
		char c = *now;
		next(now, c);
		set<int> ret = st[c - 'A'];
		return ret;
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

void solve() {
	string s; cin >> s;
	Parser p(s);
	int n = p.ans.size();
	if(n == 0) {
		cout << "NULL" << '\n';
	} else {
		int cnt = 1;
		for(int i : p.ans) {
			cout << i << (cnt == n ? '\n' : ' ');
			++cnt;
		}
	}
}

int main() {
	char c;
	int n;
	while(cin >> c >> n) {
		if(c == 'R') {
			solve();
			for(int i = 0; i < 5; ++i) {
				st[i].clear();
			}
			u.clear();
		} else {
			for(int i = 0; i < n; ++i) {
				int x; cin >> x;
				st[c - 'A'].insert(x);
				u.insert(x);
			}
		}
	}
}
