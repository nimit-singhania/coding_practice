#include "connexus.hpp"

#include <iostream>

Picture* Connexus::uploadPicture(std::vector<int> data, int owner, int time, location loc, bool isPublic) {
	auto* pic = new Picture{.data = data, .isPublic = isPublic, .owner = owner, .time = time, .geoLocation = loc};
	pic->readers.push_back(owner);
	picturesByUser[owner].insert(pic);
	if (isPublic) publicPictures.insert(pic);
	return pic;
}

bool Connexus::addReader(Picture* p, int reader) {
	p->readers.push_back(reader);
	picturesByUser[reader].insert(p);
	return true;
}

std::set<Picture*> Connexus::getByTime(int user, int startTime, int endTime) {
	std::set<Picture*> pics;

	for (auto* p : publicPictures) {
		if (p->time < startTime || p->time >= endTime) {
			continue;
		}
		pics.insert(p);
	}
	
	for (auto* p : picturesByUser[user]) {
		if (p->time < startTime || p->time >= endTime) {
			continue;
		}
		pics.insert(p);
	}
	return pics;
}

std::set<Picture*> Connexus::getByLocation(int user, location startLocation, location endLocation) {
	std::set<Picture*> pics;

	for (auto* pic : publicPictures) {
		// Filter by location.
		auto loc = pic->geoLocation;
		if (loc.first >= startLocation.first && loc.first < endLocation.first &&
		    loc.second >= startLocation.second && loc.second < endLocation.second) {
			pics.insert(pic);
		}
	}
	for (auto* pic : picturesByUser[user]) {
		// Filter by location.
		auto loc = pic->geoLocation;
		if (loc.first >= startLocation.first && loc.first < endLocation.first &&
		    loc.second >= startLocation.second && loc.second < endLocation.second) {
			pics.insert(pic);
		}
	}

	return pics;
}


void Connexus::addComment(int user, Picture* p, std::string comment) {
	if (std::find(p->readers.begin(), p->readers.end(), user) == p->readers.end()) {
		return;
	}

	p->comments.push_back(comment);
}

std::vector<std::string> Connexus::readComments(int user, Picture* p) {
	if (std::find(p->readers.begin(), p->readers.end(), user) == p->readers.end()) {
		return {};
	}
	return p->comments;
}

int main(int argc, char** argv) {

	Connexus connexus;

	auto *p1 = connexus.uploadPicture({1, 0, 0, 1}, 1, 1, location(1, 1), true);
	connexus.uploadPicture({0, 1, 0, 1}, 1, 2, location(1, 2), true);
	connexus.uploadPicture({0, 0, 1, 1}, 2, 3, location(2, 1), true);
	connexus.uploadPicture({1, 0, 1, 0}, 2, 4, location(2, 2), true);

	auto pics = connexus.getByTime(1, 1, 2);

	for (auto* p: pics) {
		std::cout << "Pics found by time: " << p->time << " location: " << p->geoLocation.first << ", " << p->geoLocation.second << std::endl;
	}
	pics = connexus.getByLocation(2, location(0, 0), location(3, 2));

	for (auto* p: pics) {
		std::cout << "Pics found by location: " << p->time << " location: " << p->geoLocation.first << ", " << p->geoLocation.second << std::endl;
	}

	connexus.addComment(1, p1, "Great Picture!");
	connexus.addComment(2, p1, "Love the picture!");
	connexus.addComment(1, p1, "Nice capture.");

	std::cout << "Comments on picture: ";

	auto comments = connexus.readComments(1, p1);

	for (auto c : comments) {
		std::cout << c << std::endl;
	}


	return 0;
}
