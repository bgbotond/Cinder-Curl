#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "FtpManager.h"

#define FTP_ADDRESS  "ftp.address.com"
#define FTP_USERNAME "username"
#define FTP_PASSWORD "password"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative
{
public:
	void setup();
	void update();
	void draw();
private:
	mndl::FtpManagerPtr mFtpManager;
};

void CinderProjectApp::setup()
{
	mFtpManager = mndl::FtpManagerPtr( new mndl::FtpManager( FTP_ADDRESS, FTP_USERNAME, FTP_PASSWORD ));

	mFtpManager->send( getAssetPath( "testfile.txt" ));
}

void CinderProjectApp::update()
{
	mFtpManager->update();
}

void CinderProjectApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
