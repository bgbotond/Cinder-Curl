#ifndef _FTPMANAGER_HEADER_INCLUDED_
#define _FTPMANAGER_HEADER_INCLUDED_

#include <vector>
#include "cinder/Thread.h"
#include "Ftp.h"

namespace mndl {

class FtpManager;
typedef std::shared_ptr< FtpManager  > FtpManagerPtr;

class FtpManager
{
	typedef std::shared_ptr< std::thread > ThreadPtr;
	typedef std::pair< FtpPtr, ThreadPtr > FtpThread;
	typedef std::vector< std::pair< FtpThread, int > > FtpThreads;

public:
	FtpManager( const std::string &address, const std::string &user, const std::string &password, int tryCount = 5 );
	virtual ~FtpManager();

	void send( const ci::fs::path &fileName );
	void update();

private:
	std::string mAddress;
	std::string mUser;
	std::string mPassword;

	int         mTryCount;

	FtpThreads  mFtpThreads;
};

} // namespace mndl

#endif // _FTPMANAGER_HEADER_INCLUDED_