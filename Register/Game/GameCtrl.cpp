#include "stdafx.h"
#include "GameCtrl.h"
#include "Tool.h"
#include "GameDlg.h"
CGameCtrl * CGameCtrl::self=nullptr;
CGameCtrl & CGameCtrl::GetInstance(CGameDlg * parent)  //����ʽ
{
	if (self==nullptr)
	{
		self = new CGameCtrl(parent);
	}
	return *self;
}

enum  ImgGroupType
{
	����,����,��ʾ,����,����,�е���,������,׼��
};

CGameCtrl::CGameCtrl(CGameDlg * parent):data(CTool::GetInstance()),
	main_dlg(parent),
	button_center(GAME_DLG_WIDTH/2,GAME_DLG_HEIGHT/2+50),
	button_size(100,39)
{
	
}


CGameCtrl::~CGameCtrl(void)
{
	self=nullptr;
}

void CGameCtrl::Show(Gdiplus::Graphics * g)
{
	for (const auto & i:ls_base_ctrl)
	{
		i->Show(g);
	}
	ShowCtrl(g);
}

void CGameCtrl::InitCtrl()
{
	const int IDG_MIN   = 10000;
	const int IDG_CLOSE = 10001;
	const int bt_width  = res.vec_min[0]->GetWidth();
	const int bt_height = res.vec_min[0]->GetHeight();

	const CRect rectDlg(0,0,GAME_DLG_WIDTH,GAME_DLG_HEIGHT);

	Rect rect=Rect(rectDlg.Width()-bt_width*1.6,5,bt_width,bt_height);

	bt_close.Create(rect,main_dlg,IDG_CLOSE,res.vec_close);
	bt_close.SetCmd([this]()
	{
		main_dlg->PostMessageW(WM_CLOSE);
	});
	ls_base_ctrl.push_back(&bt_close);
	rect.X-=bt_width*1.5;
	bt_min.Create(rect,main_dlg,IDG_MIN,res.vec_min);
	bt_min.SetCmd([this]()
	{
		main_dlg->PostMessageW(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	ls_base_ctrl.push_back(&bt_min);

	CreatCtrl_Ready(ls_game_ctrl);
}

void CGameCtrl::OnGameTimer()
{
	game_timer++;
}

void CGameCtrl::OnGameWin(const int serial_num)
{
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GAME_WIN;
	pack.buf=serial_num;
	data.DealData(pack);
}

void CGameCtrl::CreatCtrl_Ready(IN CtrlList & ctrl_ls)
{
	/************************************************************************/
	/*			�е���	���� 	������		����                            */
	/************************************************************************/
	Rect rect;
	CPNGButton * button;

	//�е���
	button=new CPNGButton();
	rect = Rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
	button->Create(rect,main_dlg,ctrl_ls.size(),res.vec_button_img[�е���]);
	button->SetCmd([=]()
	{
		DATA_PACKAGE pack;
		pack.ms_type=MS_TYPE::WANT_LANDLORD;
		data.DealData(pack);
	});
	ls_game_ctrl.emplace_back(button);

	//����
	button=new CPNGButton();
	rect.X+=button_size.Width*1.5+20;
	button->Create(rect,main_dlg,ctrl_ls.size(),res.vec_button_img[����]);
	button->SetCmd([=]()
	{
		DATA_PACKAGE pack;
		pack.ms_type=MS_TYPE::NOT_WANT_LANDLORD;
		data.DealData(pack);
	});
	ls_game_ctrl.emplace_back(button);
}

void CGameCtrl::ShowCtrl(Gdiplus::Graphics * g)
{
	for (const auto & i:ls_game_ctrl)
	{
		i->Show(g);
	}
}

void CGameCtrl::CreatCtlr_Wait(CtrlList & ctrl_ls)
{
	/************************************************************************/
	/*						      ��ʼ                                      */
	/************************************************************************/

	Rect rect;
	CPNGButton * button;
	button=new CPNGButton();
	rect = Rect(Point(button_center.X-button_size.Width*1.5-10,button_center.Y),button_size);
	button->Create(rect,main_dlg,ctrl_ls.size(),res.vec_button_img[׼��]);
	button->SetCmd([=]()
	{
		DATA_PACKAGE pack;
		pack.ms_type=MS_TYPE::WANT_LANDLORD;
		data.DealData(pack);
	});
	ls_game_ctrl.emplace_back(button);
}

CGameCtrl::GameRes::GameRes()
{
	auto vec_temp=::GetImageGroup(IDB_GAME_CTRL,2,3);
	for (auto & i:vec_temp)
	{
		i=ResizeImg(i,0.4);
	}
	for (int i=0;i<3;i++)
	{
		vec_min.push_back(vec_temp[i]);
	}
	for (int i=3;i<6;i++)
	{
		vec_close.push_back(vec_temp[i]);
	}

	vec_temp=::GetImageGroup(IDB_GAME_BUTTON,7,3);
	for (int i=0;i<7;i++)
	{
		vec_button_img[i].resize(3);
		for (int j=0;j<3;j++)
		{
			vec_button_img[i][j]=vec_temp[3*i+j];
		}
	}
}