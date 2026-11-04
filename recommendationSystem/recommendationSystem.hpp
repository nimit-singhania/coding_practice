// Recommendation System
//
// Elements of Programming Interviews, Chapter 20, Exercise 16.
// The goal is to find related articles and show related articles at the end of a given article.
//
// We use keyword matching to find related article. Each article is assoicated with keywords and two articles are said to be related if they share a pair of keywords.
//

#include <string>
#include <vector>
#include <map>

struct article {
	std::string title;
	std::string body;
	std::vector<std::string> keywords;
};

class recommendationSystem {
	// Map keyword to articles.
	std::map<std::string, std::vector<article*>> keywordToArticlesMap;
	std::vector<article*> articles;

public:
	std::vector<article*> findRelatedArticles(article* a);

	article* getArticle(std::string title);

	void addArticle(std::string title, std::vector<std::string> keywords);
};
