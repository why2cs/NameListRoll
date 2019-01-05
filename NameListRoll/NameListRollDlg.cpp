
// NameListRollDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NameListRoll.h"
#include "NameListRollDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNameListRollDlg 对话框


CNameListRollDlg::CNameListRollDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NAMELISTROLL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNameListRollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNameListRollDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CNameListRollDlg 消息处理程序

BOOL CNameListRollDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	readFile();

	brush.CreateSolidBrush(RGB(255, 0, 0));
	font.CreatePointFont(1200, _T("黑体"));

	SetDlgItemText(IDC_NameLabel, StoWs("* * *").c_str());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNameListRollDlg::OnPaint()
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
HCURSOR CNameListRollDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNameListRollDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case ROLL:
		if (index < nameList.size()) {
			SetDlgItemText(IDC_NameLabel, StoWs(nameList[index++]).c_str());
		}else if (index == nameList.size()) {
			index = 0;
		}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CNameListRollDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_NameLabel)
	{
		
		pDC->SetBkColor(RGB(255, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		return brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CNameListRollDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_SPACE:
			if (!isRolling) {
				SetTimer(ROLL, 50, NULL);
				isRolling = true;
				currentDisplayHasDeleted = false;
			} else {
				KillTimer(ROLL);
				isRolling = false;
			}
			break;
		case VK_F11:
			if (!isFullScreen) {
				ShowWindow(SW_SHOWMAXIMIZED);
				isFullScreen = true;
			} else {
				ShowWindow(SW_RESTORE);
				isFullScreen = false;
			}
			break;
		case VK_DELETE:
			if (!isRolling) {
				if (!currentDisplayHasDeleted) {
					auto status = MessageBox(StoWs("是否要从名单中删除:  【" + nameList[index - 1] + "】  ?").c_str(), StoWs("提示").c_str(), MB_OKCANCEL);
					if (status == IDOK) {
						--index;
						nameList.erase(nameList.begin() + index);
						currentDisplayHasDeleted = true;
					}
				} else {
					MessageBox(StoWs("当前人员已经被删除过了！").c_str(), StoWs("提示").c_str(), MB_OK);
				}
				MessageBox(StoWs(nameList[index - 1] + "  " + nameList[index] + "  " + nameList[index + 1]).c_str());
			}
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CNameListRollDlg::readFile()
{
	ifstream nameStream("config.txt", ifstream::in);
	string name;

	while (getline(nameStream, name)) {
		if (name.size() > 0 && (name != "\t" || name != " " || name != "\r")) {
			nameList.push_back(name);
		}
	}

	if (randomOrder) {
		srand((unsigned)time(NULL));
		random_shuffle(nameList.begin(), nameList.end());
	}
}


std::wstring StoWs(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

