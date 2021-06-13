#include <bits/stdc++.h>
using namespace std;

// <tree> ::= ( <term> ) [ <number> ] ( <term> )
// <term> ::= "" | <tree>
// <number> ::= [0-9]+

struct Node {
	int num;
	Node* lhs;
	Node* rhs;
};

int cnt = 0;
Node a[100010];

struct Parser {
	// var
	using itr = string::const_iterator;
	itr now;
	Node* root;
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
		root = tree(now);
	}
	// <tree> ::= ( <term> ) [ <number> ] ( <term> )
	Node* tree(itr& now) {
		next(now, '(');
		Node* lhs = term(now);
		next(now, ')');
		next(now, '[');
		int num = number(now);
		next(now, ']');
		next(now, '(');
		Node* rhs = term(now);
		next(now, ')');
		a[cnt].lhs = lhs;
		a[cnt].rhs = rhs;
		a[cnt].num = num;
		return &a[cnt++];
	}
	// <term> ::= "" | <tree>
	Node* term(itr& now) {
		if(*now == '(') {
			return tree(now);
		} else {
			return NULL;
		}
	}
	// <number> ::= [0-9]+
	int number(itr& now) {
		int ret = 0;
		while(true) {
			if('0' <= *now and *now <= '9') {
				ret *= 10;
				ret += (*now) - '0';
				++now;
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

Node* dfs(Node* A, Node* B) {
	Node* lhs = NULL;
	Node* rhs = NULL;
	if(A->lhs != NULL and B->lhs != NULL) {
		lhs = dfs(A->lhs, B->lhs);
	}
	if(A->rhs != NULL and B->rhs != NULL) {
		rhs = dfs(A->rhs, B->rhs);
	}
	a[cnt].num = A->num + B->num;
	a[cnt].lhs = lhs;
	a[cnt].rhs = rhs;
	return &a[cnt++];
}

void _dfs(Node* A) {
	cout << A << " " << A->num << " " << A->lhs << " " << A->rhs << '\n';
	if(A->lhs != NULL) _dfs(A->lhs);
	if(A->rhs != NULL) _dfs(A->rhs);
}

string restore(Node* C) {
	string ret = ")[" + to_string(C->num) + "](";
	if(C->lhs != NULL) {
		ret = restore(C->lhs) + ret;
	}
	if(C->rhs != NULL) {
		ret = ret + restore(C->rhs);
	}
	ret = "(" + ret + ")";
	return ret;
}

int main() {
	string A, B; cin >> A >> B;
	Parser pa(A);
	Parser pb(B);
	Node* C = dfs(pa.root, pb.root);
	// cout << "A" << '\n';
	// _dfs(pa.root);
	// cout << "B" << '\n';
	// _dfs(pb.root);
	// cout << "C" << '\n';
	// _dfs(C);
	cout << restore(C) << '\n';
}
