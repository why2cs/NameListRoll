
// NameListRollDlg.h : 头文件
//

#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using std::ifstream;
using std::string;
using std::vector;

// CNameListRollDlg 对话框
class CNameListRollDlg : public CDialogEx
{
// 构造
public:
	CNameListRollDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAMELISTROLL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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


//	string转换成wstring
std::wstring StoWs(const std::string& s);
