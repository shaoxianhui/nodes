
// NodeSimulator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNodeSimulatorApp: 
// �йش����ʵ�֣������ NodeSimulator.cpp
//

class CNodeSimulatorApp : public CWinApp
{
public:
	CNodeSimulatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNodeSimulatorApp theApp;