#include <sstream>
#include <iostream>
#include "Curl.h"

using namespace std;

namespace mndl { namespace curl {

string Curl::post( const string &url, vector<string> &m )
{
	bool   usePost    = true;
	string postString = "";
	stringstream st;
	int    count = 0;

	vector<string>::iterator act, end;
	for( act = m.begin(), end = m.end(); act != end; ++act )
	{
		st.clear();
		st.str( string());
		st << count++;

		postString += st.str() + "=" + Curl::urlEncode( *act ) + "&";
	}

	return easyCurl( url, usePost, postString );
}

string Curl::post( const string &url, map<string, string> &m )
{
	bool   usePost    = true;
	string postString = "";

	map<string, string>::iterator act, end;
	for( act = m.begin(), end = m.end(); act != end; ++act )
	{
		postString += act->first + "=" + Curl::urlEncode( act->second ) + "&";
	}

	return easyCurl( url, usePost, postString );
}

string Curl::get( const string &url )
{
	bool   usePost = false;
	string params  = "";

	return easyCurl( url, usePost, params );
}

int Curl::writer( char *data, size_t size, size_t nmemb, string *buffer )
{
	int result = 0;
	if( buffer != NULL )
	{
		buffer->append( data, size * nmemb );
		result = size * nmemb;
	}
	return result;
}

string Curl::easyCurl( const string &url, bool post, const string &postParamString )
{
	string buffer = "";
	char errorBuffer[CURL_ERROR_SIZE];

	errorBuffer[0] = 0;

	CURL *curl = curl_easy_init();
	CURLcode result;

	if( ! curl )
		return "";

	curl_easy_setopt( curl, CURLOPT_ERRORBUFFER   , errorBuffer );
	curl_easy_setopt( curl, CURLOPT_URL           , url.c_str() );
	curl_easy_setopt( curl, CURLOPT_HEADER        , 0           );
	curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1           );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION , writer      );
	curl_easy_setopt( curl, CURLOPT_WRITEDATA     , &buffer     );
	if( post )
	{
		curl_easy_setopt( curl, CURLOPT_POST      , 1                      );
		curl_easy_setopt( curl, CURLOPT_POSTFIELDS, postParamString.c_str());
	}
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYHOST, 2                                                     );
	curl_easy_setopt( curl, CURLOPT_USERAGENT     , "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)" );
	curl_easy_setopt( curl, CURLOPT_SSL_VERIFYPEER, 0                                                 ); // this line makes it work under https
	curl_easy_setopt( curl, CURLOPT_COOKIEFILE    , "cookies.txt"                                         ); // read from
	curl_easy_setopt( curl, CURLOPT_COOKIEJAR     , "cookies.txt"                                         ); // write to

	result = curl_easy_perform( curl );

	curl_easy_cleanup( curl );

	if( result == CURLE_OK )
	{
		return buffer;
	}
	else
	{
		cerr << "error:" << errorBuffer << endl;
		return "";
	}
}

string Curl::urlEncode( const string &c )
{
	string escaped = "";
	int max = c.length();
	for( int i = 0; i < max; ++i )
	{
		if( ( '0' <= c[i] && c[i] <= '9' )
		 || ( 'a' <= c[i] && c[i] <= 'z' )
		 || ( 'A' <= c[i] && c[i] <= 'Z' )
		 || ( c[i] == '~' || c[i] == '!' || c[i] == '*' || c[i] == '(' || c[i] == ')' || c[i] == '\''))
		{
			escaped.append( &c[i], 1 );
		}
		else
		{
			escaped.append( "%" );
			escaped.append( char2Hex( c[i] )); // converts char 255 to string "ff"
		}
	}
	return escaped;
}

string Curl::char2Hex( char dec )
{
	char dig1 = ( dec & 0xF0 ) >> 4;
	char dig2 = ( dec & 0x0F );

	if(  0 <= dig1 && dig1 <=  9 ) dig1 += '0';
	if( 10 <= dig1 && dig1 <= 15 ) dig1 += 'a' - 10;
	if(  0 <= dig2 && dig2 <=  9 ) dig2 += '0';
	if( 10 <= dig2 && dig2 <= 15 ) dig2 += 'a' - 10;

	string r;
	r.append( &dig1, 1);
	r.append( &dig2, 1);
	return r;
}

} } // namespace mndl::curl
