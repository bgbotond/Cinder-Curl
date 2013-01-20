#include "cinder/app/App.h"
#include "Curl.h"
#include "Ftp.h"

namespace mndl {

Ftp::Ftp( const std::string &address, const std::string &user, const std::string &password, const ci::fs::path &fileName )
: mAddress( address )
, mUser( user )
, mPassword( password )
, mFileName( fileName )
, mDone( false )
, mResult( false )
{
}

Ftp::~Ftp()
{
	ci::app::App::get()->console() << "Ftp destroyed (" << mFileName << ")" << std::endl;
}

bool Ftp::getDone()
{
	std::lock_guard< std::mutex > lock( mMutex );
	return mDone;
}

bool Ftp::getResult()
{
	std::lock_guard< std::mutex > lock( mMutex );
	return mResult;
}

void Ftp::send()
{
	ci::app::App::get()->console() << "Ftp send started (" << mFileName << ")" << std::endl;
	{
		mMutex.lock();
		mDone   = false;
		mResult = false;
		mMutex.unlock();
	}

	bool ret = mndl::curl::Curl::ftpUpload( mAddress, mUser, mPassword, mFileName );

	if( ret )
		ci::app::App::get()->console() << "Ftp send successfully finished (" << mFileName << ")" << std::endl;
	else
		ci::app::App::get()->console() << "Ftp send unsuccessfully finished (" << mFileName << ")" << std::endl;

	{
		mMutex.lock();
		mDone   = true;
		mResult = ret;
		mMutex.unlock();
	}
}

} // namespace mndl
