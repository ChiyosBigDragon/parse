#include <bits/stdc++.h>
using namespace std;

// <expr> ::= <term1>[op0<term1>]*
// <term1> ::= <term2>[op1<term2>]*
// <term2> ::= <fact>[op2<fact>]*
// <fact> ::= <numb> | (<expr>)
// <numb> ::= [0-9]+

template<typename T>
struct Parser {
	using itr = string::const_iterator;
	itr now;
	T ans;
	map<char, int> op;
	const struct ex {
		vector<char> _012;
		ex() {
			_012.resize(10);
			for(int i = 0; i < 10; ++i) {
				_012[i] = (char)('0' + i);
			}
		}
	} ex;
	Parser(const string &s, const map<char, int> &op) : op(op) {
		now = s.begin();
		ans = expr(now);
	}
	T calc(T lhs, T rhs, char op) {
		if(op == '+') return lhs + rhs;
		if(op == '-') return lhs - rhs;
		if(op == '*') return lhs * rhs;
	}
	T expr(itr &now) {
		T ret = term1(now);
		while(true) {
			char c = *now;
			if(op[c] == 1) {
				next(now, c);
				ret = calc(ret, term1(now), c);
			} else {
				return ret;
			}
		}
	}
	T term1(itr &now) {
		T ret = term2(now);
		while(true) {
			char c = *now;
			if(op[c] == 2) {
				next(now, c);
				ret = calc(ret, term2(now), c);
			} else {
				return ret;
			}
		}
	}
	T term2(itr &now) {
		T ret = fact(now);
		while(true) {
			char c = *now;
			if(op[c] == 3) {
				next(now, c);
				ret = calc(ret, fact(now), c);
			} else {
				return ret;
			}
		}
	}
	T fact(itr &now) {
		if(*now == '(') {
			next(now, '(');
			T ret = expr(now);
			next(now, ')');
			return ret;
		} else {
			return numb(now);
		}
	}
	T numb(itr &now) {
		T ret = 0;
		while('0' <= *now and *now <= '9') {
			ret *= 10;
			ret += (T)(*now - '0');
			next(now, ex._012);
		}
		return ret;
	}
	void next(itr &now, const char expected) {
		vector<char> req = {expected};
		next(now, req);
	}
	void next(itr &now, const vector<char> &expected) {
		for(char c : expected) {
			if(*now == c) {
				now++;
				return;
			}
		}
		cerr << "now " << *now << "\n";
		for(char c : expected) cerr << c << "\n";
	}
};

int main() {
	string s; cin >> s;
	map<char, int> op;
	int64_t ans = INT64_MIN;
	for(int i = 0; i < pow(3, 3); ++i) {
		int tmp = i;
		op['+'] = tmp % 3 + 1;
		tmp /= 3;
		op['-'] = tmp % 3 + 1;
		tmp /= 3;
		op['*'] = tmp % 3 + 1;
		Parser<int64_t> parse(s, op);
		// fprintf(stderr, "%d %d %d\n", op['+'], op['-'], op['*']);
		// cerr << parse.ans << "\n";
		ans = max(ans, parse.ans);
	}
	cout << ans << "\n";
	return 0;
}