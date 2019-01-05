
// NameListRollDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NameListRoll.h"
#include "NameListRollDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNameListRollDlg �Ի���


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


// CNameListRollDlg ��Ϣ�������

BOOL CNameListRollDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	readFile();

	brush.CreateSolidBrush(RGB(255, 0, 0));
	font.CreatePointFont(1200, _T("����"));

	SetDlgItemText(IDC_NameLabel, StoWs("* * *").c_str());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNameListRollDlg::OnPaint()
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
HCURSOR CNameListRollDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNameListRollDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_NameLabel)
	{
		
		pDC->SetBkColor(RGB(255, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		return brush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
					auto status = MessageBox(StoWs("�Ƿ�Ҫ��������ɾ��:  ��" + nameList[index - 1] + "��  ?").c_str(), StoWs("��ʾ").c_str(), MB_OKCANCEL);
					if (status == IDOK) {
						--index;
						nameList.erase(nameList.begin() + index);
						currentDisplayHasDeleted = true;
					}
				} else {
					MessageBox(StoWs("��ǰ��Ա�Ѿ���ɾ�����ˣ�").c_str(), StoWs("��ʾ").c_str(), MB_OK);
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

