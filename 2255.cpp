#include <bits/stdc++.h>
using namespace std;

string s;
vector<vector<bool>> visited;
vector<vector<set<int>>> dp;

void init() {
	visited = vector<vector<bool>>(210, vector<bool>(210, false));
	dp = vector<vector<set<int>>>(210, vector<set<int>>(210));
}

bool number(int l, int r) {
	if(r <= l) return false;
	int ret = 0;
	for(int i = l; i < r; ++i) {
		ret *= 10;
		if(s[i] < '0' or '9' < s[i]) return false;
		ret += (s[i] - '0');
	}
	// fprintf(stderr, "[%d, %d) : %d\n", l, r, ret);
	throw ret;
}

set<int> dfs(int l, int r) {
	if(r <= l) return {};
	if(visited[l][r]) return dp[l][r];
	if(s[l] == '(') {
		int depth = 0;
		bool flg = 1;
		for(int i = l; i < r; ++i) {
			if(s[i] == '(') {
				depth++;
				continue;
			}
			if(s[i] == ')') {
				depth--;
				continue;
			}
			if(depth == 0) {
				flg = 0;
			}
		}
		if(flg and s[r - 1] == ')') return dfs(l + 1, r - 1);
	}
	// fprintf(stderr, "[%d, %d)\n", l, r);
	try {
		number(l, r);
	}
	catch(int num) {
		dp[l][r].insert(num);
		visited[l][r] = true;
		return dp[l][r];
	}
	set<int> ret;
	int depth = 0;
	for(int i = l; i < r; ++i) {
		if(s[i] == '(') {
			depth++;
			continue;
		}
		if(s[i] == ')') {
			depth--;
			continue;
		}
		if(depth > 0) continue;
		if('0' <= s[i] and s[i] <= '9') continue;
		int lid = l, ldepth = 0;
		for(int j = i - 1; j >= l; --j) {
			if(s[j] == ')') {
				ldepth++;
			}
			if(s[j] == '(') {
				lid = j;
				ldepth--;
			}
			if(ldepth < 0) break;
			lid = l;
		}
		set<int> left = dfs(lid, i);
		int rid = r, rdepth = 0;
		for(int j = i + 1; j < r; ++j) {
			if(s[j] == '(') {
				rdepth++;
			}
			if(s[j] == ')') {
				rid = j + 1;
				rdepth--;
			}
			if(rdepth < 0) break;
			rid = r;
		}
		set<int> right = dfs(i + 1, rid);
		if(s[i] == '+') {
			for(int ll : left) {
				for(int rr : right) {
					ret.insert(ll + rr);
				}
			}
		}
		if(s[i] == '-') {
			for(int ll : left) {
				for(int rr : right) {
					ret.insert(ll - rr);
				}
			}
		}
		if(s[i] == '*') {
			for(int ll : left) {
				for(int rr : right) {
					ret.insert(ll * rr);
				}
			}
		}
		if(s[i] == '/') {
			for(int ll : left) {
				for(int rr : right) {
					if(rr == 0) continue;
					ret.insert(ll / rr);
				}
			}
		}
	}
	dp[l][r] = ret;
	visited[l][r] = true;
	// fprintf(stderr, "[%d, %d)\n", l, r);
	// for(int i : dp[l][r]) {
	// 	cerr << i <<endl;
	// }
	return dp[l][r];
}

int main() {
	while(cin >> s and s != "#") {
		init();
		int n = s.size();
		set<int> ans = dfs(0, n);
		// for(int i : ans) {
		// 	cerr << i <<endl;
		// }
		cout << ans.size() << endl;
	}
	return 0;
}