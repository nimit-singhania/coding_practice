// Implementation (based on Calculus of Computation Chapter 9)
#include "congurenceClosure.hpp"

#include <iostream>
#include <fstream>

std::string print(node* n) {
	std::string out;

	if (n->children.size() == 0) return n->symbol;

	out = n->symbol + "(";
	for (int i = 0; i < n->children.size(); i++) {
		out += print(n->children[i]);
		if (i < n->children.size() - 1)
			out += ",";
	}
	out += ")";

	return out;
}


// Return the representative of the node (via transitive closure over the find edge).
node* find(node* n) {
	node* t = n;
	while (t) {
		if (t == t->find) {
			// self-representative
			// std::cout << "[DEBUG] Representative for " << print(n) << " = " << print(t) << std::endl;
			return t;
		}
		t = t->find;
	}
	return nullptr;
}

// Are the two nodes congurent. Do they belong to the same congurence class?
bool isCongurent(node* n1, node* n2) {
	if (n1->symbol != n2->symbol) return false;

	if (n1->children.size() != n2->children.size()) return false;

	for (int i = 0; i < n1->children.size(); i++) {
		if (find(n1->children[i]) != find(n2->children[i])) {
			// TWo children not equivalent by the congurence relation.
			return false;
		}
	}

	return true;
}

// Merge the congurence classes of nodes n1 and n2.
void merge(node* n1, node* n2) {
	if (find(n1) == find(n2)) {
		// Already congurent, merging not required.
		return;
	}

	std::cout << "[DEBUG] Merging " << print(n1) << " and " << print(n2) << std::endl;
	// merge n1 and n2.
	auto rep1 = find(n1);
	auto rep2 = find(n2);
	rep1->find = rep2;

	// Rep2 is the representative of the merged congurence class.
	// Also, we now need to merge any operations / functions that are applied on n1 and n2.
	for (auto c1 : rep1->ccpar) {
		for (auto c2 : rep2->ccpar) {
			if (isCongurent(c1, c2)) {
				merge(c1, c2);
			}
		}
	}

	// Finally, the parent set of rep1 can be reset, and all parents merged in rep2
	for (auto p : rep1->ccpar) {
		rep2->ccpar.push_back(p);
	}
	rep1->ccpar.clear();

	// If not congurent, no merging is required.
}

node* singletonNode(std::string symbol) {
	node* n = new node;
	n->symbol = symbol;
	n->find = n;
	return n;
}

node* functionNode(std::string symbol, std::vector<node*> nodes) {
	node* n = new node;
	n->symbol = symbol;
	n->find = n;
	n->children = nodes;
	for (auto c: nodes) {
		// Add parent ndoe.
		c->ccpar.push_back(n);
	}
	return n;
}

node* findNode(node* n, const std::vector<node*>& all_nodes) {
	for (auto a : all_nodes) {
		if (isCongurent(n, a)) return a;
	}
	return nullptr;
}

std::vector<node*> all_nodes;

node* parseNode(char* s, int& pos) {
	// Merge nodes to form a DAG of nodes.
	std::string symbol;
	node* n = nullptr;
	while (s[pos] != '\0') {
		// read character
		char a = s[pos];

		if (a == '(') {
			// begining of a new function application.
			n = functionNode(symbol, {});
			while (s[pos] != ')') {
				auto child = parseNode(s, ++pos);
				n->children.push_back(child);
				child->ccpar.push_back(n);

				if (s[pos] == ',') pos++;
			}
			break;

		}
		if (a == ',') {
			break;
		}
		if (a == ')') {
			break;
		}
		if (a == ' ') {
			break;
		}
		symbol.push_back(a);
		pos++;
	}
	if (!n && symbol.size() > 0) {
		// singleton node.
		n =  singletonNode(symbol);
	}
	node* existing = findNode(n, all_nodes);
	if (existing == nullptr) {
		all_nodes.push_back(n);
	}
	else {
		n = existing;
	}
	return n;
}



std::vector<node*> readNodesFromFile(std::string path) {
	std::ifstream f(path);
	if (!f.is_open()) return {};

	std::vector<node*> nodes;
	char s[1024];
	while (!f.eof()) {
		f.getline(s, 1024);

		int pos = 0;
		node* n = parseNode(s, pos);

		if (n) {
			nodes.push_back(n);
		}
	}

	return nodes;
}

void checkSatisfiability(std::string path) {
	std::ifstream f(path);

	if (!f.is_open()) return;

	std::vector<node*> nodes;
	char s[1024];
	while(!f.eof()) {
		f.getline(s, 1024);

		// each line is of the form x = y or x != y;
		int pos = 0;

		node* n1 = parseNode(s, pos);
		pos++;

		// skip spaces.
		while (s[pos] != '\0' && s[pos] == ' ') pos++;

		if (s[pos] == '=') {
		
			// equality found.
			pos++;
			while (s[pos] != '\0' && s[pos] == ' ') pos++;
			node* n2 = parseNode(s, pos);
			merge(n1, n2);
		}
		else if (s[pos] == '!' && s[pos+1] == '=') {
			// inequality found.
			pos++; pos++;
			while (s[pos] != '\0' && s[pos] == ' ') pos++;
			node* n2 = parseNode(s, pos);
			if (find(n1) == find(n2) ) {
				std::cout << "Conflict found: " << print(n1) << " is equivalent to " << print(n2) << std::endl;
			}
			return;
		}
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage: congurenceClosure <satisfiability file>" << std::endl;
		return 0;
	}

	auto path  = argv[1];
//	// construct a = f(f(f(a))) && f(f(f(f(f(a))))) = a.
//	node* a = singletonNode("a");
//	node* fa = functionNode("f", {a});
//	node* ffa = functionNode("f", {fa});
//	node* fffa = functionNode("f", {ffa});
//	node* ffffa = functionNode("f", {fffa});
//	node* fffffa = functionNode("f", {ffffa});
//	std::cout << "Merge " << print(a) << " and " << print(fffa) << std::endl;
//	merge(a, fffa);
//
//	std::cout << "Merge " << print(a) << " and " << print(fffffa) << std::endl;
//	merge(a, fffffa);
//
//	bool output = find(a) == find(fa);
//	std::cout << "Is f(a) == a? " << ((output)?"Yes":"No") << std::endl;
//
//	readNodesFromFile("sample.txt");
	checkSatisfiability(argv[1]);

	return 0;
}

