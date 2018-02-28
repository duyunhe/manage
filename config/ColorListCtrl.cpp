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
	switch(lplvdr->nmcd.dwDrawStage)		//�ж�״̬
	{
	case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
	case (CDDS_ITEMPREPAINT | CDDS_SUBITEM) :					//���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
		{
			CString strText;
			strText = GetItemText((int)nmcd.dwItemSpec, 3);
			int iRow = lplvdr->nmcd.dwItemSpec;
			if(strText.Find(_T("ʹ��")) != -1)
			{
				if ( 3 == lplvdr->iSubItem )
				{
					lplvdr->clrTextBk = RGB(0xc1, 0xff, 0xc1);
					//lplvdr->clrText = m_TextColor;

					//SetFont(m_Font, false);
				}
				else
				{
					lplvdr->clrTextBk = 16777215;	//�������ѡ��ġ��С��͡��С������ó�ϵͳĬ�ϵ�������ɫ��
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
