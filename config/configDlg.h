
// configDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "configDlg.h"
#include "PythonFileInfo.h"
#include <vector>


// CconfigDlg �Ի���
class CconfigDlg : public CDialogEx
{
// ����
public:
	CconfigDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CString m_path;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	std::vector<CString> m_fileList;
	std::vector<CPythonFileInfo*> m_fileinfoList;
	void InitListCtrl();
	void ShowAllFiles(CString tp);
	CString ReadConfig();
	void SaveConfig(CString);
	void ClearFileInfo();
	void InsertIntoList(int idx, CString filename);
	CString m_lpszInitialPath;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonDir();
	CListCtrl m_lc;
	void GetFileInfo(CString filename, CString &name, CString &desc);
	CButton m_btnCfg;
};
static int CALLBACK BrowseCallbackProc ( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
int UTF82GBK(char *szUtf8,char *&szGbk,int Len);