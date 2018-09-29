#include "stdAfx.h"
#include "afxwin.h"
#include "PNGButton.h"
#include "Resource.h"
#include "Sys.h"
const UINT TIMER_CONTROL =1; 



CPNGButton::CPNGButton(void) { 
	
} 
CPNGButton::~CPNGButton(void) { }

IMPLEMENT_DYNCREATE(CPNGButton, CWnd)  

BEGIN_MESSAGE_MAP(CPNGButton, CWnd)  
		ON_WM_MOUSELEAVE()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
	END_MESSAGE_MAP()  



BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, Gdiplus::Image* BG,Gdiplus::Image* _hoverBg,Gdiplus::Image* _click_bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg.resize(3);
	vec_bg[normal_bg]=BG;
	vec_bg[hover_bg]=_hoverBg;
	vec_bg[click_bg]=_click_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT);
	return OK;
}

BOOL CPNGButton::Create(Rect rect,CWnd * pParentWnd,UINT nID, std::vector<Image*>& _bg)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	SetRect(rect);
	vec_bg=_bg;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,RectTransform(rect),pParentWnd, nID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 
	return OK;
}




void CPNGButton::ClickDown(bool flag)
{
	click_move=flag;
}

void CPNGButton::Show(Graphics* & g)
{
	if (button_down_flag)
	{
		auto t_rec=mRect;
		if (click_move)
		{
			t_rec.Offset(1,1);
		}
		g->DrawImage(vec_bg[click_bg],t_rec);
	}
	else if(is_tracked)
	{
		g->DrawImage(vec_bg[hover_bg],mRect); 
	}
	else
	{
		g->DrawImage(vec_bg[normal_bg],mRect); 
	}
}




void CPNGButton::Check(bool check)
{
	if(this->is_checked!=check)
	{
		this->is_checked=check;
		Invalidate();
		UpdateWindow();
		//TRACE(L"DrawSelected\r\n");
	} /*else{  TRACE(L"Check(%d,%d)\r\n",GetDlgCtrlID(),check); }*/
}

 


