// When nodes in a directed acyclic graph or DAG can represent equivalent nodes,
// we would like to compute a closure of the equivalence relation so that all
// equivalent nodes are merged. In particular, if the DAG encodes relations
// on individual nodes, then we would like to merge parent nodes when they
// consist of equivalent children nodes. The congurence closure algorithm allows
// computing this equivalence between nodes and checking if two nodes are
// equivalent with respect to the congurence relation.

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

// Utility method to read nodes from a file.
std::vector<node*> readNodesFromFile(std::string path);

// Utility to read constraints and check if the contraints are satisfiable.
// The constraints are equality and inequality constraints.
// If unsatisfiable, return a possible conflict of constraints.
void checkSatisfiability(std::string path);
