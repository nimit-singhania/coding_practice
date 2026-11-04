
#include "recommendationSystem.hpp"

#include <iostream>
#include <set>

std::vector<article*> recommendationSystem::findRelatedArticles(article* a)
{
	std::vector<article*> related;
	std::set<article*> found;
	auto keywords = a->keywords;
	for (auto k : keywords) {
		for (auto a : keywordToArticlesMap[k]) {
			if (found.find(a) == found.end()) {
				related.push_back(a);
				found.insert(a);
			}
		}
	}
	return related;
}

void recommendationSystem::addArticle(std::string title, std::vector<std::string> keywords) {
	auto a = new article{.title = title, .keywords = keywords};
	for (auto k : keywords) {
		keywordToArticlesMap[k].push_back(a);
	}
	articles.push_back(a);
}

article* recommendationSystem::getArticle(std::string title) {
	for (auto l : articles) {
		if (l->title == title) return l;
	}

	return nullptr;
}

int main(int argc, char** argv) {
	recommendationSystem rs;

	rs.addArticle("Space exploration", {"space", "celestial", "exploration"});
	rs.addArticle("Mars Voyage", {"space", "exploration"});
	rs.addArticle("Big bang theory", {"space", "celestial"});
	rs.addArticle("Escape Velocity", {"space", "celestial"});
	rs.addArticle("Light and Sound", {"light", "sound", "concepts", "physics"});
	rs.addArticle("Beethoven", {"sound", "music", "classical"});

	auto a = rs.getArticle("Space exploration");
	auto related = rs.findRelatedArticles(a);
	for (auto r : related ) {
		std::cout << "Found related article: " << r->title << std::endl;
	}

	return 0;
}
