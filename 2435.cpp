#include <bits/stdc++.h>
using namespace std;

bool solve() {
	int m; cin >> m;
	map<string, pair<int, int>> range;
	while(m--) {
		string name; cin >> name;
		int lb, ub; cin >> lb >> ub;
		range[name] = {lb, ub};
	}
	int n; cin >> n;
	stack<set<int>> num;
	while(n--) {
		string e; cin >> e;
		set<int> st;
		if(range.count(e)) {
			for(int i = range[e].first; i <= range[e].second; ++i) {
				st.insert(i);
			}
		} else if(e == "+" or e == "-" or e == "*" or e == "/") {
			auto st2 = num.top();
			num.pop();
			auto st1 = num.top();
			num.pop();
			for(auto lhs : st1) {
				for(auto rhs : st2) {
					if(e == "+") st.insert((lhs + rhs) % 256);
					if(e == "-") st.insert((lhs - rhs + 256) % 256);
					if(e == "*") st.insert((lhs * rhs) % 256);
					if(e == "/") {
						if(rhs == 0) return false;
						st.insert((lhs / rhs) % 256);
					}
				}
			}
		} else {
			int tmp = 0;
			for(char c : e) {
				tmp *= 10;
				tmp += c - '0';
			}
			st.insert(tmp);
		}
		num.push(st);
	}
	return true;
}

int main() {
	cout << (solve() ? "correct" : "error") << "\n";
	return 0;
}