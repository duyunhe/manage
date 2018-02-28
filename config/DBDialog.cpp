// DBDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "config.h"
#include "DBDialog.h"
#include "afxdialogex.h"


// CDBDialog �Ի���

IMPLEMENT_DYNAMIC(CDBDialog, CDialogEx)

CDBDialog::CDBDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBDialog::IDD, pParent)
	, m_strAddr(_T(""))
	, m_strPort(_T(""))
	, m_strDb(_T(""))
	, m_strUser(_T(""))
	, m_strPswd(_T(""))
{

}

CDBDialog::~CDBDialog()
{
}

void CDBDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strAddr);
	DDX_Text(pDX, IDC_EDIT2, m_strPort);
	DDX_Text(pDX, IDC_EDIT4, m_strDb);
	DDX_Text(pDX, IDC_EDIT3, m_strUser);
	DDX_Text(pDX, IDC_EDIT5, m_strPswd);
}


BEGIN_MESSAGE_MAP(CDBDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDBDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CDBDialog ��Ϣ�������


BOOL CDBDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString filename = m_path + "\\dbconn\\config.ini";

	GetPrivateProfileString("db", "host", "default", m_strAddr.GetBuffer(MAX_PATH), MAX_PATH, filename);
	GetPrivateProfileString("db", "port", "default", m_strPort.GetBuffer(MAX_PATH), MAX_PATH, filename);
	GetPrivateProfileString("db", "db", "default", m_strDb.GetBuffer(MAX_PATH), MAX_PATH, filename);
	GetPrivateProfileString("db", "pswd", "default", m_strPswd.GetBuffer(MAX_PATH), MAX_PATH, filename);
	GetPrivateProfileString("db", "user", "default", m_strUser.GetBuffer(MAX_PATH), MAX_PATH, filename);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDBDialog::SetPath(CString path)
{
	m_path = path;
}


void CDBDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveData();
	CDialogEx::OnOK();
}

void CDBDialog::SaveData()
{
	UpdateData(TRUE);

	CString filename = m_path + "\\dbconn\\config.ini";
	CFileFind finder;   //�����Ƿ����ini�ļ����������ڣ�������һ���µ�Ĭ�����õ�ini�ļ��������ͱ�֤�����Ǹ��ĺ������ÿ�ζ�����
	BOOL ifFind = finder.FindFile(filename);
	if( ifFind )
	{
		WritePrivateProfileString("db", "host", m_strAddr.GetBuffer(), filename.GetBuffer());
		WritePrivateProfileString("db", "port", m_strPort.GetBuffer(), filename.GetBuffer());
		WritePrivateProfileString("db", "db", m_strDb.GetBuffer(), filename.GetBuffer());
		WritePrivateProfileString("db", "pswd", m_strPswd.GetBuffer(), filename.GetBuffer());
		WritePrivateProfileString("db", "user", m_strUser.GetBuffer(), filename.GetBuffer());
	}
}
