
// configDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "config.h"
#include "configDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "DBDialog.h"
#include <iostream>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int UNICODE_TXT_FLG = 0xFEFF;  //UNICODE文本标示


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CconfigDlg 对话框




CconfigDlg::CconfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CconfigDlg::IDD, pParent)
	, m_batName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lc);
	DDX_Control(pDX, IDC_BUTTON_CONFIG, m_btnCfg);
	DDX_Text(pDX, IDC_EDIT1, m_batName);
	DDX_Control(pDX, IDC_BUTTON1, m_btnBat);
}

BEGIN_MESSAGE_MAP(CconfigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CconfigDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_DIR, &CconfigDlg::OnBnClickedButtonDir)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CconfigDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CconfigDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CconfigDlg 消息处理程序

BOOL CconfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitListCtrl();
	m_batName = "start.bat";
	m_btnCfg.EnableWindow(FALSE);
	m_btnBat.EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CconfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CconfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CconfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CconfigDlg::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CDBDialog dlg;
	dlg.SetPath(m_path);
	dlg.DoModal();
}


void CconfigDlg::OnBnClickedButtonDir()
{
	// TODO: 在此添加控件通知处理程序代码
	CString root = ReadConfig();
	TCHAR targetPath[MAX_PATH]; 
	_tcscpy_s(targetPath, root);		//自己设置的文件夹路径  
	CString str;
	
	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = targetPath;   
	bi.lpszTitle = "请选择文件的目录：";   
	bi.ulFlags = 0;   
	bi.lpfn = BrowseCallbackProc;   
	bi.lParam = LPARAM(targetPath);   
	bi.iImage = 0;   
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	ZeroMemory(targetPath, sizeof(targetPath));   

	if(lp && SHGetPathFromIDList(lp, targetPath))
	{
		str.Format("程序目录： %s", targetPath);
		SetDlgItemText(IDC_STATIC1, str);
		SaveConfig(targetPath);
		ShowAllFiles(targetPath);
		m_path = targetPath;
		m_btnCfg.EnableWindow(TRUE);
		m_btnBat.EnableWindow(TRUE);
	}
	//m_btnCfg.set
}

void CconfigDlg::InitListCtrl()
{
	m_lc.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lc.InsertColumn(0, "作者", 0, 80);
	m_lc.InsertColumn(1, "名称", 0, 200);
	m_lc.InsertColumn(2, "描述", 0, 500);
	m_lc.InsertColumn(3, "使用情况", 0, 100);
}

void CconfigDlg::ShowAllFiles(CString Curdir)
{
	HANDLE hfile;				//查找文件句柄
	WIN32_FIND_DATA wfdata;		//文件信息结构
	BOOL IsOver = false;		//查找过程结束标志
	CString strname;			//文件名
	CString strfull;			//全路径
	strfull = Curdir + "\\*.py";       
	hfile = FindFirstFile(strfull, &wfdata);	//查找第一个文件
	if(hfile == INVALID_HANDLE_VALUE)
		IsOver = true;							//查找过程结束

	m_fileList.clear();
	ClearFileInfo();
	while(!IsOver)
	{
		strname.Format("%s", wfdata.cFileName);		//获取找到的文件名
		strfull = Curdir + "\\" + strname;			//全路径
		//if(wfdata.cFileName[0]!=_TEXT('.'))
		m_fileList.push_back(strfull);
		IsOver = !FindNextFile(hfile, &wfdata);		//查找下一个文件
	}
	FindClose(hfile);		//关闭句柄

	m_lc.DeleteAllItems();
	for(unsigned int i = 0; i < m_fileList.size(); ++ i)
	{
		InsertIntoList(i, m_fileList[i]);
	}
	Invalidate(TRUE);
}

CString CconfigDlg::ReadConfig()
{
	CFile file;
	
	if(!file.Open("config.txt", CFile::modeRead, NULL))
	{
		return "C:\\";
	}
	
	TCHAR* temp = new TCHAR[(unsigned int)file.GetLength() + 1];  
	file.Read(temp, file.GetLength());  
	temp[file.GetLength()] = 0;  
	
	file.Close();
	CString ret(temp);
	delete temp;
	return ret;
}

void CconfigDlg::SaveConfig(CString str)
{
	CFile file("config.txt", CFile::modeWrite | CFile::modeCreate);
	int len = lstrlen(str);
	file.Write(str.GetBuffer(), str.GetLength());
	file.Flush();
	file.Close();
}

void CconfigDlg::InsertIntoList(int idx, CString filename)
{
	m_lc.InsertItem(idx, "编号");
	CPythonFileInfo *fileinfo = new CPythonFileInfo();
	GetFileInfo(filename, *fileinfo);
	m_fileinfoList.push_back(fileinfo);

	m_lc.SetItemText(idx, 0, fileinfo->author);
	m_lc.SetItemText(idx, 1, fileinfo->filename);
	m_lc.SetItemText(idx, 2, fileinfo->desc);
	m_lc.SetItemText(idx, 3, "使用");
}

void CconfigDlg::GetFileInfo(CString filename, CPythonFileInfo &fileinfo)
{
	fstream fin(filename);
	string readline;
	CString name, desc, author;

	while (getline(fin, readline)) //逐行读取，直到结束
	{
		char *sz = new char[256];
		UTF82GBK((char*)readline.c_str(), sz, 100);
		string new_line(sz);
		delete sz;
		// utf8转gb2312
		int pos = new_line.find_first_of('@');
		
		if(pos != -1)
		{
			int pos1 = pos + 1;
			if(new_line[pos1] == 'F')
			{
				pos = new_line.find_first_of(':', pos1);
				int pos2 = new_line.find_first_of('.', pos);
				string sub = new_line.substr(pos + 2, pos2 - pos - 2);
				name = sub.c_str();
			}
			else if(new_line[pos1] == 'A')
			{
				pos = new_line.find_first_of(':', pos1);
				int pos2 = new_line.find_first_of('.', pos);
				string sub = new_line.substr(pos + 2, pos2 - pos - 2);
				author = sub.c_str();
			}
			else
			{
				int pos1 = new_line.find_first_of('简');
				if(pos1 != pos + 2)
					continue;
				pos = new_line.find_first_of(':', pos1);
				int pos2 = new_line.find_first_of('.', pos);
				string sub = new_line.substr(pos + 2, pos2 - pos - 2);
				desc = sub.c_str();
			}
			
		}
	}

	fileinfo.author = author;
	fileinfo.desc = desc;
	fileinfo.filename = name;
	fileinfo.used = 1;
}

void CconfigDlg::ClearFileInfo()
{
	for(unsigned i = 0; i < m_fileinfoList.size(); ++ i)
	{
		delete m_fileinfoList[i];
	}
	m_fileinfoList.clear();
}

static int CALLBACK BrowseCallbackProc (
	HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:    
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);   //传递默认打开路径 break;
	case BFFM_SELCHANGED:    //选择路径变化，BFFM_SELCHANGED
		/*{
		char curr[MAX_PATH];   
		SHGetPathFromIDList((LPCITEMIDLIST)lParam,(LPWSTR)(LPCTSTR)curr);   
		::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)&curr[0]);  
		}*/
		break;
	default:
		break;
	} 
	return 0;

}


//UTF-8 GBK
int UTF82GBK(char *szUtf8,char *&szGbk,int Len)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR) * n];
	memset(wszGBK, 0, sizeof(WCHAR) * n);
	MultiByteToWideChar(CP_UTF8, 0,szUtf8,-1, wszGBK, n);

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	if (n > Len)
	{
		delete[]wszGBK;
		return -1;
	}

	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGbk, n, NULL, NULL);

	delete[]wszGBK;
	wszGBK = NULL;

	return 0;
}

void CconfigDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NMLISTVIEW *pp = (NMLISTVIEW*)pNMHDR;
	int i = pp->iItem;
	int j = pp->iSubItem;
	m_fileinfoList[i]->used = !m_fileinfoList[i]->used;
	if(m_fileinfoList[i]->used)
	{
		m_lc.SetItemText(i, 3, "使用");
	}
	else
	{
		m_lc.SetItemText(i, 3, "未使用");
	}
	Invalidate(TRUE);
}


void CconfigDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFile file;
	CString filename = m_path + "\\" + m_batName;
	file.Open(filename, CFile::modeCreate | CFile::modeWrite|CFile::typeBinary);
	file.SeekToBegin();
	 
	file.Write("@echo off\n", 10);
	int idx = 1;
	for(int i = 0; i < m_fileinfoList.size(); ++ i)
	{
		if(!m_fileinfoList[i]->used) continue;
		CString filename = " python " + m_fileinfoList[i]->filename + ".py\n";

		CString str_idx;
		str_idx.Format("start \"%d.", idx);
		CString desc = str_idx + m_fileinfoList[i]->filename + "\" /min cmd /c";
		char sz[256];
		strcpy(sz, desc.GetBuffer());
		file.Write(sz, strlen(sz));

		strcpy(sz, filename.GetBuffer());
		filename.ReleaseBuffer();
		file.Write(sz, strlen(sz));
		//file.Write(sz, strlen(sz));
		idx ++;
	}
	char sz[256];
	strcpy(sz, "pause\n");
	file.Write(sz, strlen(sz));
	file.Write("exit\n", 5);
	file.Close();

	MessageBox("在程序目录下已经生成脚本！");
}
