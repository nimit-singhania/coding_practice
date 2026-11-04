// This file defines the congurence closure algorithm that is an extension of the
// union-find algorithm for sets. The congurence closure operates on a DAG that
// represents an uninterpreted function application over expressions.
// In particular, it models the following rleation:
//   x1 = y1, x2 = y2, ..., xn = yn => f(x1, x2, ..., xn) = f(y1, y2, ..., yn)
// where f is a side-effect value only funciton.
//
// The congurence closure algorithm enables checking if two expressions are congurent.

#include <vector>
#include <string>

struct node {
	std::string symbol;
	std::vector<node*> children;
	node* find;
	std::vector<node*> ccpar;
};

// Operations supported by a congurence closure algorithm.

// Return the representative of the node (via transitive closure over the find edge).
node* find(node* n);

// Are the two nodes congurent. Do they belong to the same congurence class?
bool isCongurent(node* n1, node* n2);

// Merge the congurence classes of nodes n1 and n2.
void merge(node* n1, node* n2);
