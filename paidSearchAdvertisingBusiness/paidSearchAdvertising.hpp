// Search Advertising
//
// Elements of Programming Interviews, Chapter 20, Exercise 15.
//

// The goal is to build a search advertising framework that supports an internet search service.
// A basic advertising framework consists of ad listings which can be shown to the user in the
// search river.
// These listings can be fetched for a given user query.
// The listings are paid for by the seller to show on the site.
// The ad format can be two fold:
//     cost per action: the fee is paid when the seller obtains revenue from the ad (for selling a product).
//     cost per click: the fee is paid when a buyer clicks on the product.
// We support cost per click model here. To support the model, we must maintain clicks on the products and compute fee based on the number of clicks (given by adrate).

#include <string>
#include <vector>

struct adListing {
	std::string title;
	int seller;
	int numberOfClicks;
};

class paidSearchAdvertising {
	std::vector<adListing*> listings;

public:
	std::vector<adListing*> findListings(std::vector<std::string> keywords);

	// Listing services.
	void addListing(int seller, std::string title);

	void removeListing(int seller, std::string title);

	void resetClicks(int seller);

	int computeFee(int seller, float adRate);

	// Ranking
	void sortListings(std::vector<adListing*>& vec);
};
