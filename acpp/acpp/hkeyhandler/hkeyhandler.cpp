
#include "hkeyhandler.h"

using namespace std;

HkeyHandler::HkeyHandler(HKEY _hive, string _path)	// throws BadConfig
{
	wstring wpath = wstring(_path.begin(), _path.end());

	LONG ret = RegOpenKeyEx( _hive,
	wpath.c_str(),	//   "SOFTWARE\\Experis"
	0,
	KEY_ALL_ACCESS | KEY_WOW64_64KEY,
	&m_key);

	CHECK_AND_THROW_DIF(ret, ERROR_SUCCESS, "RegOpenKeyEx", BadHkeyHandler);
}