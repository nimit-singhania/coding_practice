// System for sharing pictures online.
//
// Elements of Programming Interviews, Chapter 20, Exercise 14.

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef std::pair<int, int> location;

// Picture class that stores all necessary data.
struct Picture {
	std::vector<int> data;
	bool isPublic;
	std::vector<int> readers;
	int owner;
	int time;
	location geoLocation;
	std::vector<std::string> comments;
};

bool less(const Picture* a, const Picture* b) {
	return a->data < b->data ||
		a->data == b->data && a->time < b->time ||
		a->data == b->data && a->time == b->time && a->geoLocation < b->geoLocation ||
		a->data == b->data && a->time == b->time && a->geoLocation == b->geoLocation && a->owner < b->owner;
}

class Connexus {
	// Keep pictures by time and by user, so they are easy to locate.
	std::set<Picture*> publicPictures;
	// Pictures accessible by user.
	std::map<int, std::set<Picture*>> picturesByUser;
public:

	Picture* uploadPicture(std::vector<int> data, int owner, int time, location loc, bool isPublic = false);

	bool addReader(Picture* p, int reader);

	// Get pictures that can be accessed by the user.
	// Start time inclusive, end time non-inclusive.
	std::set<Picture*> getByTime(int user, int startTime, int endTime);

	// Get pictures that can be accessed by the user.
	// Start location inclusive, end location non-inclusive.
	std::set<Picture*> getByLocation(int user, location startLocation, location endLocation);

	// Add comment to a picture.
	void addComment(int user, Picture* p, std::string comment);

	// Read comments on a picture.
	std::vector<std::string> readComments(int user, Picture* p);
};
