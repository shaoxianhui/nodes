
// NodeManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNodeManagerApp: 
// �йش����ʵ�֣������ NodeManager.cpp
//

class CNodeManagerApp : public CWinApp
{
public:
	CNodeManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNodeManagerApp theApp;