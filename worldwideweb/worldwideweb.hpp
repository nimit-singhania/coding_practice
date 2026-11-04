// World Wide Web Service
//
// Elements of Programming Interviews, Chapter 20, Exercise 18.
//
// The goal is to design a world-wide-web, where given a URL, we would like to retrieve the contents from the URL (if valid).
// The web consists of a set of hosts, each hosting a set of files via a URL. A node on the web can retrieve content from one
// of the hosts, by specifying the URL and host that hosts the URL can be contacted to return the file from the URL.
//
// The URL can consist of two parts: the domain name (that is hosted by the host ex. www.abc.com) and a path to the file that
// is requested (example: /main/content/file1.html). We must split the URL to find the domain name, reach out to the node
// hosting the domain and then request the path to the file to obtain the data.

#include <string>
#include <map>

class node {
	protected:
	std::string domain;

	public:
	node(std::string d) : domain(d) {}
	
	virtual std::string retrieveContent(std::string path) = 0;

	std::string getDomain() { return domain; }
};


class worldWideWebService {
	std::map<std::string, node*> DomainToHostMapping;

public:
	std::string retrieveContent(std::string url);

	void addNode(std::string domain, node* n) {
		DomainToHostMapping[domain] = n;
	}
};
