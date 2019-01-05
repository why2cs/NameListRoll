
// NameListRollDlg.h : ͷ�ļ�
//

#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using std::ifstream;
using std::string;
using std::vector;

// CNameListRollDlg �Ի���
class CNameListRollDlg : public CDialogEx
{
// ����
public:
	CNameListRollDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAMELISTROLL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL PreTranslateMessage(MSG* pMsg);

private:
	bool isRolling = false;
	bool randomOrder = false;
	bool isFullScreen = false;

	vector<string> nameList;
	size_t index = 0;
	CBrush brush;
	CFont font;
	enum TIMER { ROLL };

	void readFile();
};


//	stringת����wstring
std::wstring StoWs(const std::string& s);
