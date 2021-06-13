#include <bits/stdc++.h>
using namespace std;

// <E> ::= <T> [ + <T> | − <T>]*
// <T> ::= <F> [ ∗ <F> ]*
// <F> ::= <N> | − <F> | ( <E> )
// <N> ::= 0 | 1 [01]*

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
		ans = E(now);
		if(now != s.end()) {
			throw "INVALID";
		}
	}
	// <E> ::= <T> [ + <T> | − <T>]*
	int64_t E(itr& now) {
		int64_t ret = T(now);
		while(true) {
			if(*now == '+') {
				next(now, '+');
				ret += T(now);
			} else if(*now == '-') {
				next(now, '-');
				ret -= T(now);
			} else {
				return ret;
			}
		}
	}
	// <T> ::= <F> [ ∗ <F> ]*
	int64_t T(itr& now) {
		int64_t ret = F(now);
		while(true) {
			if(*now == '*') {
				next(now, '*');
				ret *= F(now);
			} else {
				return ret;
			}
		}
	}
	// <F> ::= <N> | − <F> | ( <E> )
	int64_t F(itr& now) {
		if(*now == '-') {
			next(now, '-');
			return -F(now);
		} else if(*now == '(') {
			next(now, '(');
			int64_t ret = E(now);
			next(now, ')');
			return ret;
		} else if(*now == '0' or *now == '1') {
			return N(now);
		} else {
			throw "INVALID";
		}
	}
	// <N> ::= 0 | 1 [01]*
	int64_t N(itr& now) {
		int64_t ret = 0;
		if(*now == '0') {
			next(now, '0');
			return ret;
		} else {
			next(now, '1');
			ret += 1;
			while(true) {
				if('0' <= *now and *now <= '1') {
					ret *= 2;
					ret += (*now) - '0';
					next(now, {'0', '1'});
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
		// fprintf(stderr, "Expected: ");
		// for(char c: expected) {
		// 	fprintf(stderr, "%c, ", c);
		// }
		// fprintf(stderr, "\nGot: %c\n", *now);
		// fprintf(stderr, "Rest: ");
		// while(*now) {
		// 	fprintf(stderr, "%c", *now++);
		// }
		// fprintf(stderr, "\n");
		// exit(1);
		throw "INVALID";
	}
};

void solve() {
	string s; cin >> s;
	vector<char> op = {'0', '1', '+', '-', '*', '(', ')', '='};
	sort(op.begin(), op.end());
	map<char, int> mp;
	for(char c : s) {
		if('a' <= c and c <= 'z') {
			mp[c] = 0;
		}
		if('A' <= c and c <= 'Z') {
			mp[c] = 0;
		}
	}
	if(mp.size() > op.size()) {
		cout << 0 << '\n';
		return;
	}
	{
		int i = 0;
		for(auto& e : mp) {
			e.second = i;
			++i;
		}
	}
	int ans = 0;
	int n = op.size();
	for(int mask = 0; mask < (1 << n); ++mask) {
		if(__builtin_popcount(mask) != mp.size()) continue;
		vector<char> ops;
		for(int i = 0; i < n; ++i) {
			if(mask >> i & 1) {
				ops.push_back(op[i]);
			}
		}	
		do {
			string ss = s;
			for(char& c : ss) {
				if('a' <= c and c <= 'z') {
					c = ops[mp[c]];
				}
				if('A' <= c and c <= 'Z') {
					c = ops[mp[c]];
				}
			}
			int idx = -1;
			bool valid = true;
			for(int i = 0; i < ss.size(); ++i) {
				if(ss[i] == '=') {
					if(idx != -1) {
						valid = false;
					}
					idx = i;
				}
			}
			if(not valid or idx == -1 or idx == 0 or idx + 1 == ss.size()) continue;
			string s1 = ss.substr(0, idx), s2 = ss.substr(idx + 1);
			try {
				Parser p1(s1);
				Parser p2(s2);
				if(p1.ans == p2.ans) {
					// cerr << s1 << " " << s2 << '\n';
					++ans;
				}
			} catch(...) {
				continue;
			}
		} while(next_permutation(ops.begin(), ops.end()));
	}
	cout << ans << '\n';
}

int main() {
	solve();
	return 0;
}

