#include "paidSearchAdvertising.hpp"	

#include <iostream>

std::vector<adListing*> paidSearchAdvertising::findListings(std::vector<std::string> keywords) {
	std::vector<adListing*> match;

	for (auto l : listings) {
		bool found = false;
		for (auto k : keywords) {
			if (l->title.find(k) != std::string::npos) {
				// Mmatch found.
				match.push_back(l);
				found = true;
				break;
			}
		}
	}
	return match;
}

// Listing services.
void paidSearchAdvertising::addListing(int seller, std::string title) {
	auto * l = new adListing;
	l->seller = seller;
	l->title = title;
	l->numberOfClicks = 0;
	listings.push_back(l);
}

void paidSearchAdvertising::removeListing(int seller, std::string title) {
	std::vector<std::vector<adListing*>::iterator> marked;
	for (auto it = listings.begin(); it != listings.end(); it++) {
		if ((*it)->title == title && (*it)->seller == seller) {
			marked.push_back(it);
		}
	}
	for (auto it : marked) {
		listings.erase(it);
	}
}

void paidSearchAdvertising::resetClicks(int seller) {
	for (auto l :listings) {
		if (l->seller == seller) l->numberOfClicks = 0;
	}
}

int paidSearchAdvertising::computeFee(int seller, float adRate) {
	float fee = 0;
	for (auto l : listings) {
		if (l->seller == seller) {
			fee += adRate*l->numberOfClicks;
		}
	}
	return (int) fee;
}
// Ranking
void paidSearchAdvertising::sortListings(std::vector<adListing*>& vec) {
    // Sort listings by number of keywords matched.
    // TODO
}


int main(int argc, char** argv) {
	paidSearchAdvertising adService;

	adService.addListing(1, "computer table standing");
	adService.addListing(1, "coffee table");
	adService.addListing(2, "computer table electric");

	auto listings = adService.findListings({"computer"});
	for (auto l: listings) {
		std::cout << "Listing title: " << l->title << std::endl;
	}

	adService.removeListing(2, "computer table electric");
	std::cout << "Removed listing: computer table electric " << std::endl;
	listings = adService.findListings({"computer"});
	for (auto l: listings) {
		std::cout << "Listing title: " << l->title << std::endl;
	}

	return 0;
}
