
// configDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "configDlg.h"
#include "PythonFileInfo.h"
#include <vector>


// CconfigDlg 对话框
class CconfigDlg : public CDialogEx
{
// 构造
public:
	CconfigDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CString m_path;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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