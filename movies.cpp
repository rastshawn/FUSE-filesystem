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

void addComment(std::string filename, std::string input) {
	mysqlpp::Connection myDB("cse381", "localhost", "cse381", "m1am1");
	mysqlpp::Query q = myDB.query();

	q << "SELECT comment FROM movies WHERE title = '" << filename << "'";
	q.parse();
	mysqlpp::StoreQueryResult result = q.store();
	std::string comment(result[0][0].c_str());

	mysqlpp::Query q2 = myDB.query();
	q2 << "UPDATE movies SET comment = '" << comment;
	q2 << "\n" << input << "'";
	q2 << "WHERE title = '" << filename << "'";
	q2.parse();

	q2.store();
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
	std::string original_language(result[0][4].c_str());
	if (original_language.length() > 0) 
		buf += "Original Language: " + original_language + "\n";
	std::string original_title(result[0][5].c_str());
	if (original_title.length() > 0)
		buf += "Original Title: " + original_title + "\n";
	std::string overview(result[0][6].c_str());
	if (overview.length() > 0)
		buf += "Overview: " + overview + "\n";
	std::string popularity(result[0][7]);
	if (popularity.length() > 0) 
		buf += "Popularity: " + popularity + "\n";
	std::string production_companies(result[0][8].c_str());
	if (production_companies.length() > 0) 
		buf += "Production Companies: " + production_companies + "\n";
	std::string production_countries(result[0][9].c_str());
	if (production_countries.length() > 0)
		buf += "Production Countries: " + production_countries + "\n";
	std::string release_date(result[0][10].c_str());
	if (release_date.length() > 0) 
		buf += "Release date: " + release_date + "\n";
	std::string revenue(result[0][11]);
	if (revenue.length() > 0)
		buf += "Revenue: $" + revenue + "\n";
	std::string runtime(result[0][12]);
	if (runtime.length() > 0) 
		buf += "Runtime: " + runtime + " min\n";
	std::string comment(result[0][13].c_str());
	if (comment.length() > 0)
		buf += "Comment: " + comment + "\n";


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


