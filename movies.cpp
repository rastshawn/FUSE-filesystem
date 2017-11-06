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

	q << "SELECT title FROM movies WHERE title IS NOT NULL";
	q.parse();

	mysqlpp::StoreQueryResult result = q.store();
	
	for (size_t row=0; row<result.size(); row++) {
		movies.push_back(result[row][0].c_str());
	}
}

void getMovieInfo(const char * path, std::string &buf) {
	std::string title = std::string(path).substr(1);
	
	buf += "Title: " + title + "\n";
	

	mysqlpp::Connection myDB("cse381", "localhost", "cse381", "m1am1");
	mysqlpp::Query q = myDB.query();

	
	q << "SELECT budget,genre,homepage,keywords,";
	q << "original_language,original_title,overview,";
	q << "popularity,production_companies,production_countries,";
	q << "release_date,revenue,runtime,comment FROM movies";
	q << " WHERE title = '" << title << "'";
	q.parse();
	
	mysqlpp::StoreQueryResult result(q.store());


	std::string budget(result[0][0]);
	if (budget.length() >0)
		buf += "Budget: $" + budget + "\n";
	std::string genre(result[0][1].c_str());
	if (genre.length() > 0)
		buf += "Genres: " + genre + "\n";
	std::string homepage(result[0][2].c_str());
	if (homepage.length() > 0)
		buf += "Homepage: " + homepage + "\n";
	std::string keywords(result[0][3].c_str());
	if (keywords.length() > 0)
		buf += "Keywords: " + keywords + "\n";


}

/*
int main() {

	std::vector<std::string> movies;
	getMovieListing(movies);

	for (size_t i=0; i<movies.size(); i++) {
		std::cout << movies[i] << std::endl;
	}
*/
/*
	query.parse();
	
	mysqlpp::StoreQueryResult result = query.store();

	for (int i = 0; i<result.size(); i++) {
		std::string s = result[i][1].c_str();
		std::cout << s << std::endl;
	}
}
*/


