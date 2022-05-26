#include "stdafx.h"
#include "DIDemoProgramDlg.h"

class CDIDemoProgram : public CWinApp {
public:
	CDIDemoProgram() {
		m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_AUTOSAVE_AT_RESTART;
	}

	BOOL InitInstance() {
		CWinApp::InitInstance();

		CDIDemoProgramDlg* dlg = new CDIDemoProgramDlg();

		m_pMainWnd = dlg;
		dlg->DoModal();

		return FALSE;
	}

	//DECLARE_MESSAGE_MAP()
	virtual int ExitInstance() {
		return CWinApp::ExitInstance();
	}

} DIApp;
