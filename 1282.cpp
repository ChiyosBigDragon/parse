#include <bits/stdc++.h>
using namespace std;

// <expression> ::= <number> | <array_name> [ <expression> ]
// <number> ::= 0 | [1-9] [0-9]*
// <array_name> ::= [a-zA-Z]

struct Parser {
	// var
	using itr = string::const_iterator;
	itr now;
	int64_t ans;
	map<char, map<int64_t, int64_t>> arr;
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
	
	Parser(const string& s, map<char, map<int64_t, int64_t>>& arr) : arr(arr) {
		now = s.begin();
		ans = expression(now);
	}
	// <expression> ::= <number> | <array_name> [ <expression> ]
	// <array_name> ::= [a-zA-Z]
	int64_t expression(itr& now) {
		for(char c : ex.azAZ) {
			if(*now == c) {
				next(now, c);
				next(now, '[');
				int64_t ret = expression(now);
				next(now, ']');
				if(arr.count(c) and arr[c].count(ret)) {
					return arr[c][ret];
				} else {
					throw "INVALID";
				}
			}
		}
		return number(now);
	}
	// <number> ::= 0 | [1-9] [0-9]*
	int64_t number(itr& now) {
		int64_t ret = 0;
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
	map<char, int64_t> sz;
	map<char, map<int64_t, int64_t>> arr;
	bool bug = false;
	for(int q = 1; ; ++q) {
		if(not bug) {
			bool dec = true;
			string s1, s2;
			for(int i = 0; i < s.size(); ++i) {
				if(s[i] == '=') {
					s1 = s.substr(0, i);
					s2 = s.substr(i + 1);
					dec = false;
					break;
				}
			}
			if(dec) {
				int64_t num = 0;
				for(int i = 2; i + 1 < s.size(); ++i) {
					num *= 10;
					num += s[i] - '0';
				}
				sz[s[0]] = num;
			} else {
				try {
					Parser p1(s1.substr(2, s1.size() - 3), arr);
					if('0' <= s2[0] and s2[0] <= '9') {
						int64_t num = 0;
						for(int i = 0; i < s2.size(); ++i) {
							num *= 10;
							num += s2[i] - '0';
						}
						if(not sz.count(s1[0])) {
							cout << q << '\n';
							bug = true;
							continue;
						}
						if(sz[s1[0]] <= p1.ans) {
							cout << q << '\n';
							bug = true;
							continue;
						}
						arr[s1[0]][p1.ans] = num;
						// cerr << s1[0] << p1.ans << " " << num << '\n';
					} else {
						Parser p2(s2, arr);
						if(not sz.count(s1[0])) {
							cout << q << '\n';
							bug = true;
							continue;
						}
						if(sz[s1[0]] <= p1.ans) {
							cout << q << '\n';
							bug = true;
							continue;
						}
						arr[s1[0]][p1.ans] = p2.ans;
						// cerr << s1[0] << p1.ans << " " << p2.ans << '\n';
					}
				} catch(...) {
					cout << q << '\n';
					bug = true;
				}
			}
		}
		cin >> s;
		if(s == ".") {
			if(not bug) {
				cout << 0 << '\n';
			}
			return;
		}
	}
}

int main() {
	string s;
	while(cin >> s and s != ".") {
		solve(s);
	}
	return 0;
}

