#ifndef __COMMUNICATOR_H_INCLUDED__
#define __COMMUNICATOR_H_INCLUDED__

#include <map>
#include <string>
#include <vector>

#include <curl/curl.h>

namespace mndl { namespace curl {

class Communicator
{
public:
	Communicator(){};
	~Communicator(){};
	static std::string post( const std::string &url, std::vector<std::string>           &params );
	static std::string post( const std::string &url, std::map<std::string, std::string> &params );
	static std::string get ( const std::string &url );

protected:
	static int writer( char *data, size_t size, size_t nmemb, std::string *buffer );
	static std::string easyCurl( const std::string &url, bool post, const std::string &postParamString );
	static std::string urlEncode( const std::string &c );
	static std::string char2Hex( char dec );
};

} } // namespace mndl::curl

#endif // __COMMUNICATOR_H_INCLUDED__
