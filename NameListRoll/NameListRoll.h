
// NameListRoll.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNameListRollApp: 
// �йش����ʵ�֣������ NameListRoll.cpp
//

class CNameListRollApp : public CWinApp
{
public:
	CNameListRollApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNameListRollApp theApp;