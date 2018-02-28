#include "stdafx.h"
#pragma once
class CPythonFileInfo
{
	CString filename;
	CString author;
	CString desc;
	bool	used;
public:
	CPythonFileInfo(void);
	~CPythonFileInfo(void);
};

