#include <bits/stdc++.h>
using namespace std;

// CAT ::= m[CAT]eCat
// eCat ::= e[CAT]w

template<typename T>
struct Parser {
	using itr = string::const_iterator;
	itr now;
	T ans;
	Parser(const string &s) {
		now = s.begin();
		ans = true;
		try {
			CAT(now);
			if(*now != '\0') throw "Rabbit";
		}
		catch(...) {
			ans = false;
		}
	}
	T CAT(itr &now) {
		next(now, 'm');
		if(*now == 'm') {
			CAT(now);
		}
		eCat(now);
	}
	T eCat(itr &now) {
		next(now, 'e');
		if(*now == 'm') {
			CAT(now);
		}
		next(now, 'w');
	}
	void next(itr &now, const char expected) {
		vector<char> req = {expected};
		next(now, req);
	}
	void next(itr &now, const vector<char> &expected) {
		// cerr << "now " << *now << "\n";
		for(char c : expected) {
			if(*now == c) {
				now++;
				return;
			}
		}
		throw "Rabbit";
		for(char c : expected) cerr << c << "\n";
	}
};

int main() {
	string s; cin >> s;
	Parser<bool> parse(s);
	cout << (parse.ans ? "Cat" : "Rabbit") << "\n";
	return 0;
}
