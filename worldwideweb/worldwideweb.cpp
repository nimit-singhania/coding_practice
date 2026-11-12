#include "worldwideweb.hpp"

#include <iostream>

// URL service.
std::string getDomain(std::string url) {
	int pos = 0;
	std::string HTTP_PREFIX = "http://";
	if (url.find(HTTP_PREFIX) != std::string::npos) {
		pos = url.find_first_of(HTTP_PREFIX) + HTTP_PREFIX.size();
	}

	int end_pos = url.find_first_of("/", pos);
	if (end_pos == std::string::npos) {
		return url.substr(pos);
	}
	else 
		return url.substr(pos, end_pos - pos);

	return "";
}

std::string getPath(std::string url) {
	int pos = 0;
	std::string HTTP_PREFIX = "http://";
	if (url.find(HTTP_PREFIX) != std::string::npos) {
		pos = url.find_first_of(HTTP_PREFIX) + HTTP_PREFIX.size();
	}

	pos = url.find_first_of("/", pos);

	if (pos == std::string::npos) {
		return "";
	}
	else {
		return url.substr(pos);
	}

	return "";
}

class TmpNode: public node {
public:
	TmpNode(std::string domain, bool isHttp = true) : node(domain, !isHttp) {}
	std::string retrieveContent(std::string path) override {
		return  domain + ": Retrieving contents for path: " + path + ".";
	}
};


std::string worldWideWebService::retrieveContent(std::string url) {
	// split url
	std::string domain = getDomain(url);

	std::string path = getPath(url);

	if (DomainToHostMapping.find(domain) != DomainToHostMapping.end()) {

		if (domain.find_first_of("https") != 0 && DomainToHostMapping[domain]->isHttps()) {
			// Incompliant protocol.
			return "";
		}

		return DomainToHostMapping[domain]->retrieveContent(path);
	}

	return "";
}

int main(int argc, char** argv) {
	worldWideWebService www;

	TmpNode n1("abc.com", false), n2("xyz.com"), n3("pqr.com"), n4("def.com"), n5("jkl.com");

	www.addNode(n1.getDomain(), &n1);
	www.addNode(n2.getDomain(), &n2);
	www.addNode(n3.getDomain(), &n3);
	www.addNode(n4.getDomain(), &n4);
	www.addNode(n5.getDomain(), &n5);

	std::cout << www.retrieveContent("http://abc.com/main/content/file1.html") << std::endl;
	std::cout << www.retrieveContent("http://pqr.com/main/content/file2.html") << std::endl;
	std::cout << www.retrieveContent("http://z.com/main/content/file.html") << std::endl;

	return 0;
}
