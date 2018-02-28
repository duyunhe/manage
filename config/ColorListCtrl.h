#pragma once
class CColorListCtrl: public CListCtrl
{
public:
	CColorListCtrl(void);
	~CColorListCtrl(void);
	void SetColor(int iRow, int iCol, COLORREF color);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};

