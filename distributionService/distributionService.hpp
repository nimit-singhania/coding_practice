// Distribution Service
//
// Elements of Programming Interviews, Chapter 20, Exercise 17
//
// To design a distribution service for distributing 100 kb files to edge servers from a central server.
//
// We build a tree of distribution nodes, thereby each server needs to distribute its data to a small set of other servers.
//

// Server node.
struct largeFile {
	char* data;
};

class node {
public:
	// Send file to another node n.
	virtual void sendService(node* n, largeFile* f) = 0;
};

// Wrapper around nodes to ease distribution.
struct tree {
	node* n;
	int size; // For balancing the tree service.
	tree* left;
	tree* right;
};

// Service to efficiently distribute files.
class distributionService {
	tree* root;

	void distributeFile(tree* t, largeFile* f);
public:
	void addNode(node* n);

	void distributeFile(largeFile* f);
};
