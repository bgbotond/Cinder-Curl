#ifndef _FTP_HEADER_INCLUDED_
#define _FTP_HEADER_INCLUDED_

#include "cinder/Thread.h"
#include <string>
#include <memory>

namespace mndl {

class Ftp;
typedef std::shared_ptr< Ftp > FtpPtr;

class Ftp
{
public:
	Ftp( const std::string &address, const std::string &user, const std::string &password, const ci::fs::path &fileName );
	virtual ~Ftp();

	void send();

	bool getDone();
	bool getResult();

	const ci::fs::path &getFileName() { return mFileName; }

private:
	std::string  mAddress;
	std::string  mUser;
	std::string  mPassword;
	ci::fs::path mFileName;

	bool         mDone;
	bool         mResult;

	std::mutex   mMutex;
};

} // namespace mndl

#endif // _FTP_HEADER_INCLUDED_