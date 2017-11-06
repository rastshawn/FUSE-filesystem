#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include "moviesdb.h"


mysqlpp::Query connect() {
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection myDB("cse381", "localhost", "cse381", "m1am1");
    // Create a query 
	
    return myDB.query();
}


void getMovieListing(std::vector<std::string> &movies) {
	mysqlpp::Connection myDB("cse381", "localhost", "cse381", "m1am1");
	mysqlpp::Query q = myDB.query();

	q << "SELECT title FROM movies";
	q.parse();

	mysqlpp::StoreQueryResult result = q.store();
	
	for (size_t row=0; row<result.size(); row++) {
		movies.push_back(result[row][0].c_str());
	}
}

void getMovieInfo(const char * path, std::string &buf) {
	buf += "title = " + std::string(path) + "\n";
}

int main() {

	std::vector<std::string> movies;
	getMovieListing(movies);

	for (size_t i=0; i<movies.size(); i++) {
		std::cout << movies[i] << std::endl;
	}

/*
	query.parse();
	
	mysqlpp::StoreQueryResult result = query.store();

	for (int i = 0; i<result.size(); i++) {
		std::string s = result[i][1].c_str();
		std::cout << s << std::endl;
	}
*/
}



