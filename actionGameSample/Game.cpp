#include "Game.h"

void callQuit( char *nextappPath, char* nextexename )
{
	SHELLEXECUTEINFO *m_appInfo;
	m_appInfo = new SHELLEXECUTEINFO;
	memset( m_appInfo, 0, sizeof(SHELLEXECUTEINFO) );
	m_appInfo->cbSize       = sizeof(SHELLEXECUTEINFO);
	m_appInfo->fMask        = SEE_MASK_NO_CONSOLE     ;
	m_appInfo->hwnd         = GetMainWindowHandle()   ; 
	m_appInfo->lpParameters = NULL                    ;
	m_appInfo->lpDirectory  = _T(nextappPath)           ; //ƒpƒX
	m_appInfo->nShow        = SW_SHOWNORMAL           ;
	m_appInfo->lpFile       = _T(nextexename);
}