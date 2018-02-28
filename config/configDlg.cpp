
// configDlg.cpp : ʵ���ļ�
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

const int UNICODE_TXT_FLG = 0xFEFF;  //UNICODE�ı���ʾ


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CconfigDlg �Ի���




CconfigDlg::CconfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CconfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lc);
	DDX_Control(pDX, IDC_BUTTON_CONFIG, m_btnCfg);
}

BEGIN_MESSAGE_MAP(CconfigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CconfigDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_DIR, &CconfigDlg::OnBnClickedButtonDir)
END_MESSAGE_MAP()


// CconfigDlg ��Ϣ�������

BOOL CconfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitListCtrl();
	m_btnCfg.EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CconfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CconfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CconfigDlg::OnBnClickedButtonConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDBDialog dlg;
	dlg.SetPath(m_path);
	dlg.DoModal();
}


void CconfigDlg::OnBnClickedButtonDir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString root = ReadConfig();
	TCHAR targetPath[MAX_PATH]; 
	_tcscpy_s(targetPath, root);//�Լ����õ��ļ���·��  
	CString str;
	
	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = targetPath;   
	bi.lpszTitle = "��ѡ���ļ���Ŀ¼��";   
	bi.ulFlags = 0;   
	bi.lpfn = BrowseCallbackProc;   
	bi.lParam = LPARAM(targetPath);   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	ZeroMemory(targetPath, sizeof(targetPath));   

	if(lp && SHGetPathFromIDList(lp, targetPath))
	{
		str.Format("��ǰĿ¼�� %s", targetPath);
		SetDlgItemText(IDC_STATIC1, str);
		SaveConfig(targetPath);
		ShowAllFiles(targetPath);
		m_path = targetPath;
		m_btnCfg.EnableWindow(TRUE);
	}
	//m_btnCfg.set
}

void CconfigDlg::InitListCtrl()
{
	m_lc.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lc.InsertColumn(0, "����", 0, 80);
	m_lc.InsertColumn(1, "����", 0, 200);
	m_lc.InsertColumn(2, "����", 0, 500);
	m_lc.InsertColumn(3, "ʹ�����", 0, 100);
}

void CconfigDlg::ShowAllFiles(CString Curdir)
{
	HANDLE hfile;				//�����ļ����
	WIN32_FIND_DATA wfdata;		//�ļ���Ϣ�ṹ
	BOOL IsOver = false;		//���ҹ��̽�����־
	CString strname;			//�ļ���
	CString strfull;			//ȫ·��
	strfull = Curdir + "\\*.py";       
	hfile = FindFirstFile(strfull, &wfdata);	//���ҵ�һ���ļ�
	if(hfile == INVALID_HANDLE_VALUE)
		IsOver = true;							//���ҹ��̽���

	m_fileList.clear();
	while(!IsOver)
	{
		strname.Format("%s", wfdata.cFileName);	//��ȡ�ҵ����ļ���
		strfull = Curdir + "\\" + strname;			//ȫ·��
		//if(wfdata.cFileName[0]!=_TEXT('.'))
		m_fileList.push_back(strfull);
		IsOver = !FindNextFile(hfile, &wfdata);		//������һ���ļ�
	}
	FindClose(hfile);		//�رվ��

	m_lc.DeleteAllItems();
	for(unsigned int i = 0; i < m_fileList.size(); ++ i)
	{
		InsertIntoList(i, m_fileList[i]);
	}
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
	m_lc.InsertItem(idx, "���");
	CString name, desc;
	GetFileInfo(filename, name, desc);
	m_lc.SetItemText(idx, 0, name);
	m_lc.SetItemText(idx, 1, desc);
	m_lc.SetItemText(idx, 2, "ʹ����");
}

void CconfigDlg::GetFileInfo(CString filename, CString &name, CString &desc)
{
	fstream fin(filename);
	string readline;
	while (getline(fin, readline)) //���ж�ȡ��ֱ������
	{
		int pos = readline.find_first_of('@');
		if(pos != -1)
		{
			pos = readline.find_first_of('F', pos + 1);
			if(pos != -1)
			{
				pos = readline.find_first_of(':');
				int pos2 = readline.find_first_of('.', pos);
				string sub = readline.substr(pos + 2, pos2 - pos - 2);
				name = sub.c_str();
			}

			char *sz = new char[256];
			UTF82GBK((char*)readline.c_str(), sz, 100);
			string new_line(sz);
			pos = new_line.find_first_of('��', pos + 1);
			delete sz;

			if(pos != -1)
			{
				TRACE("%d\n", pos);
				pos = new_line.find_first_of(':');
				int pos2 = new_line.find_first_of('.', pos);
				string sub = new_line.substr(pos + 2, pos2 - pos - 2);
				desc = sub.c_str();
			}
		}
	}
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
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);   //����Ĭ�ϴ�·�� break;
	case BFFM_SELCHANGED:    //ѡ��·���仯��BFFM_SELCHANGED
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