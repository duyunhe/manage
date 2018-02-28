#include "stdAfx.h"
#include "ColorListCtrl.h"


BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
END_MESSAGE_MAP()

CColorListCtrl::CColorListCtrl(void)
{
}


CColorListCtrl::~CColorListCtrl(void)
{
}

void CColorListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch(lplvdr->nmcd.dwDrawStage)		//判断状态
	{
	case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
	case (CDDS_ITEMPREPAINT | CDDS_SUBITEM) :					//如果为画ITEM之前就要进行颜色的改变
		{
			CString strText;
			strText = GetItemText((int)nmcd.dwItemSpec, 3);
			int iRow = lplvdr->nmcd.dwItemSpec;
			if(strText.Find(_T("使用")) != -1)
			{
				if ( 3 == lplvdr->iSubItem )
				{
					lplvdr->clrTextBk = RGB(0xc1, 0xff, 0xc1);
					//lplvdr->clrText = m_TextColor;

					//SetFont(m_Font, false);
				}
				else
				{
					lplvdr->clrTextBk = 16777215;	//如果不是选择的“行”和“列”就设置成系统默认的那种颜色。
					lplvdr->clrText = 0;
				}

			}
		}
		break;
	}
}

void CColorListCtrl::SetColor(int iRow, int iCol, COLORREF color)
{

}
