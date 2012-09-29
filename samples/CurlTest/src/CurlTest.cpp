#include "Curl.h"

#include <iostream>

using namespace std;
using namespace mndl::curl;

static void testPostVector();
static void testPostMap();
static void testGet();

int main(int argc, char *argv[])
{
	testPostVector();
	testPostMap();
	testGet();
}

static void testPostVector()
{
	std::vector<string> strings;

	strings.push_back( "vector value1");
	strings.push_back( "vector value2");

	cout << "test post vector: " << Curl::post( "localhost/curlTest.php", strings );
}

static void testPostMap()
{
	std::map<string,string> strings;

	strings.insert(pair<string, string>( "first" , "map value1" ));
	strings.insert(pair<string, string>( "second", "map value2" ));

	cout << "test post map: " << Curl::post( "localhost/curlTest.php", strings ) << endl;
}

static void testGet()
{
	cout << "test get: " << Curl::get( "localhost/curlTest.php" ) << endl;
}
