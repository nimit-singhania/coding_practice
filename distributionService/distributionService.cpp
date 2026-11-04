#include "distributionService.hpp"

#include <iostream>

void distributionService::addNode(node* n) {
	// Add node to the tree of nodes.
	tree* t = new tree{.n = n, .size = 1};

	if (root ==  nullptr) {
		root = t;
		return;
	}

	// Check sizes on both trees and insert in respective sub-trees.
	auto tmp = root;
	while (true) {

		tmp->size++; // Increment size.
		if (!tmp->left) {
			tmp->left = t;
			return;
		}
	
		if (!tmp->right) {
			tmp->right = t;
			return;
		}
	
		if (tmp->left->size > tmp->right->size) {
			// Insert in the right.
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}
}


void distributionService::distributeFile(largeFile* f) {
	distributeFile(root, f);
}

void distributionService::distributeFile(tree* t, largeFile* f) {
	if (!t) return;

	auto* n = t->n;

	if (t->left) {
		n->sendService(t->left->n, f);
	}
	if (t->right) {
		n->sendService(t->right->n, f);
	}

	// Repeat for child nodes.
	if (t->left) {
		distributeFile(t->left, f);
	}
	if (t->right) {
		distributeFile(t->right, f);
	}
}

class TempNode : public node {
	public:
		TempNode(std::string name) : name(name) {}

		void sendService(node* n, largeFile* f) override {
			auto tmpNode = dynamic_cast<TempNode*>(n);
			std::cout << this->name << ": sending file to node " << tmpNode->name << std::endl;
		}
	private:
		std::string name;
};

int main(int argc, char** argv) {
	distributionService ds;

	TempNode root("root"), n1("n1"), n2("n2"), n3("n3"), n4("n4"), n5("n5");

	ds.addNode(&root);
	ds.addNode(&n1);
	ds.addNode(&n2);
	ds.addNode(&n3);
	ds.addNode(&n4);
	ds.addNode(&n5);

	largeFile f;

	ds.distributeFile(&f);

	return 0;
}

	

