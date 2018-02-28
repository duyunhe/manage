#pragma once


// CDBDialog �Ի���

class CDBDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDBDialog) 

public:
	CDBDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_DB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString m_path;
	DECLARE_MESSAGE_MAP()
public:
	CString m_strAddr;
	CString m_strPort;
	CString m_strDb;
	CString m_strUser;
	CString m_strPswd;
	void SetPath(CString path);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void SaveData();
};
