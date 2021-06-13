#include <bits/stdc++.h>
using namespace std;

// <Program> := [<Sentence>]*
// <Sentence> := [<Condition><Program>] | {<Condition><Program>} | <Move>
// <Move> :=  ^ | v | < | >
// <Condition> := [~] N | E | S | W | C | T

bool visited[55][55][4][1010];

struct Parser {
	using itr = string::const_iterator;
	itr now, begin;
	const vector<vector<char>> G;
	const int h, w;
	int nowy, nowx, nowd;
	const int gy, gx;
	enum dir {N, E, S, W};
	const int dy[4] = {-1, 0, 1, 0};
	const int dx[4] = {0, 1, 0, -1};
	int ans = 0;
	Parser(const string &s, const vector<vector<char>> &G, const int sy, const int sx, const int gy, const int gx) :
		now(s.begin()),
		begin(s.begin()),
		G(G),
		h(G.size()),
		w(G[0].size()),
		nowy(sy),
		nowx(sx),
		nowd(0),
		gy(gy),
		gx(gx)
		{
			// visited[nowy][nowx][nowd][0] = true;
			try {
				Program(now);
			}
			catch(const char *e) {
				if(e == "SUCCESS") return;
				throw "FAILED";
			}
		}
	void Program(itr &now) {
		// cerr << "Program : "  << *now << '\n';
		while(*now != '}' and *now != ']' and *now != '\0') {
			Sentence(now);
		}
		if(*now == '\0') throw "IMPOSSIBLE";
	}
	void Sentence(itr &now) {
		// cerr << "Sentence : " << *now << '\n';
		if(*now == '[') {
			next(now, '[');
			if(Condition(now)) {
				if(*now != ']') {
					Program(now);
				}
			}
			int depth = 1;
			while(depth > 0) {
				if(*now == '[') depth++;
				if(*now == ']') depth--;
				now++;
			}
		} else if(*now == '{') {
			itr loop = now;
			next(now, '{');
			if(Condition(now)) {
				if(*now == '}') throw "IMPOSSIBLE";
				Program(now);
				now = loop;
				Program(now);
				return;
			}
			// cerr << "Loop End" << '\n';
			int depth = 1;
			while(depth > 0) {
				if(*now == '{') depth++;
				if(*now == '}') depth--;
				now++;
			}
		} else {
			Move(now);
			if(nowy == gy and nowx == gx) {
				throw "SUCCESS";
			}
		}
	}
	void Move(itr &now) {
		// cerr << "Move : " << *now << '\n';
		ans++;
		// cerr << nowy << " " << nowx << " " << nowd << '\n';
		if(*now == '^') {
			next(now, '^');
			int nxty = nowy + dy[nowd];
			int nxtx = nowx + dx[nowd];
			if(able(nxty, nxtx)) {
				nowy = nxty;
				nowx = nxtx;
			}
		} else if(*now == '>') {
			next(now, '>');
			nowd = (nowd + 1) % 4;
		} else if(*now == 'v') {
			next(now, 'v');
			int nxty = nowy + dy[(nowd + 2) % 4];
			int nxtx = nowx + dx[(nowd + 2) % 4];
			if(able(nxty, nxtx)) {
				nowy = nxty;
				nowx = nxtx;
			}
		} else if(*now == '<') {
			next(now, '<');
			nowd = (nowd + 3) % 4;
		}
		// cerr << nowy << " " << nowx << " " << nowd << '\n';
	}
	bool Condition(itr &now) {
		// cerr << "Condition : " << *now << '\n';
		bool NOT = false;
		if(*now == '~') {
			next(now, '~');
			NOT = true;
		}
		bool ret = false;
		if(*now == 'N' and nowd == N) ret = true;
		if(*now == 'E' and nowd == E) ret = true;
		if(*now == 'S' and nowd == S) ret = true;
		if(*now == 'W' and nowd == W) ret = true;
		if(*now == 'C') {
			int nxty = nowy + dy[nowd];
			int nxtx = nowx + dx[nowd];
			if(not able(nxty, nxtx)) ret = true;
		}
		if(*now == 'T') ret = true;
		next(now, *now);
		return NOT ^ ret;
	}
	bool able(const int y, const int x) {
		if(G[y][x] == '#') return false;
		return true;
	}
	int dist(itr &now) {
		return (int)(now - begin);
	}
	void next(itr &now, const char expected) {
		vector<char> req = {expected};
		next(now, req);
	}
	void next(itr &now, const vector<char> &expected) {
		for(char c: expected) {
			if(*now == c) {
				if(visited[nowy][nowx][nowd][dist(now)]) throw "IMPOSSIBLE";
				visited[nowy][nowx][nowd][dist(now)] = true;
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
	int h, w; cin >> h >> w;
	vector<vector<char>> G(h, vector<char>(w));
	int sy, sx;
	int gy, gx;
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			cin >> G[i][j];
			if(G[i][j] == 's') {
				sy = i, sx = j;
				G[i][j] = '.';
			}
			if(G[i][j] == 'g') {
				gy = i, gx = j;
				G[i][j] = '.';
			}
		}
	}
	string s; cin >> s;
	try {
		Parser parse(s, G, sy, sx, gy, gx);
		cout << parse.ans << '\n';
	}
	catch(...) {
		cout << -1 << '\n';
	}
	return 0;
}
