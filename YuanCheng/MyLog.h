#ifndef _MYLOG_H_
#define _MYLOG_H_

#pragma once
#include "stdafx.h"
class MyLog
{
public:
	MyLog(void);
	~MyLog(void);
	/**
	 *��¼��־�ļ�
	 **/
	static void WriteLog(CString str);
};

#endif