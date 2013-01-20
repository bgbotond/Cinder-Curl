#include "cinder/app/App.h"
#include "FtpManager.h"

namespace mndl {

FtpManager::FtpManager( const std::string &address, const std::string &user, const std::string &password, int tryCount /* = 5 */ )
: mAddress( address )
, mUser( user )
, mPassword( password )
, mTryCount( tryCount )
{
	if( mTryCount <= 0 )
		mTryCount = 5;
}

FtpManager::~FtpManager()
{
	for( FtpThreads::iterator it = mFtpThreads.begin(); it != mFtpThreads.end(); ++it )
	{
		it->first.second->join();	// wait for the end of the threads
		++it;
	}
}

void FtpManager::send( const ci::fs::path &fileName )
{
	FtpPtr ftp = FtpPtr( new Ftp( mAddress, mUser, mPassword, fileName ));
	ThreadPtr tr = ThreadPtr( new std::thread( &Ftp::send, ftp.get()));
	mFtpThreads.push_back( std::make_pair( std::make_pair( ftp, tr ), 0 ));
}

void FtpManager::update()
{
	FtpThreads::iterator it = mFtpThreads.begin();
	while( it != mFtpThreads.end())
	{
		FtpPtr ftp = it->first.first;

		if( ftp->getDone())
		{
			if( ftp->getResult())              // success
			{
				it = mFtpThreads.erase( it );
				continue;
			}
			else if( it->second >= mTryCount ) // try cout exceeded
			{
				ci::app::App::get()->console() << "Ftp try count exceeded (" << ftp->getFileName() << ")" << std::endl;
				it = mFtpThreads.erase( it );
				continue;
			}
			else                               // failed
			{
				ci::app::App::get()->console() << "Ftp try to send again (" << ftp->getFileName() << ")" << std::endl;
				ThreadPtr tr = ThreadPtr( new std::thread( &Ftp::send, ftp.get()));
				it->first.second = tr;
				++( it->second );
			}
		}

		++it;
	}
}

} // namespace mndl