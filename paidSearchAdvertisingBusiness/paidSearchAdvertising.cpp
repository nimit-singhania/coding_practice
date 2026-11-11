#include "paidSearchAdvertising.hpp"	

#include <iostream>
std::map<adListing*, int> paidSearchAdvertising::findListings(std::vector<std::string> keywords) {
	std::map<adListing*, int> matchWithCount;

	for (auto l : listings) {
		for (auto k : keywords) {
			if (l->title.find(k) != std::string::npos) {
				// Mmatch found.
				if (matchWithCount.find(l) == matchWithCount.end()) {
					matchWithCount.emplace(l, 1);
				}
				else {
					matchWithCount[l]++;
				}
			}
		}
	}
	return matchWithCount;
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
std::vector<AdListingWithMatchCount> paidSearchAdvertising::sortListings(std::map<adListing*, int>& vec) {
    // Sort listings by number of keywords matched.
	std::vector<AdListingWithMatchCount> sortedList;
	for (auto p : vec) {
		// std::cout << "DEBUG: " << p.first->title << ": " << p.second << std::endl;
		sortedList.push_back(p);
	}

   	std::sort(sortedList.begin(), sortedList.end(), [](const AdListingWithMatchCount& a, const AdListingWithMatchCount& b) {
			return a.second > b.second;
			});

	return sortedList;
}


int main(int argc, char** argv) {
	paidSearchAdvertising adService;

	adService.addListing(1, "coffee table");
	adService.addListing(1, "computer table standing");
	adService.addListing(2, "computer table electric");

	auto listings = adService.findListings({"computer", "table"});
	for (auto l: listings) {
		std::cout << "Listing title: " << l.first->title << std::endl;
	}

	adService.removeListing(2, "computer table electric");
	std::cout << "Removed listing: computer table electric " << std::endl;
	listings = adService.findListings({"computer", "table"});
	for (auto l: listings) {
		std::cout << "Listing title: " << l.first->title << std::endl;
	}

	std::cout << "Sorted Listings: " << std::endl;
	auto sortedList = adService.sortListings(listings);
	for (auto l: sortedList) {
		std::cout << "Listing title: " << l.first->title << std::endl;
	}

	return 0;
}
