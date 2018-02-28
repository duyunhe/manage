#include "stdafx.h"
#pragma once
class CPythonFileInfo
{
public:
	CString filename;
	CString author;
	CString desc;
	bool	used;
	CPythonFileInfo(void);
	~CPythonFileInfo(void);
};

