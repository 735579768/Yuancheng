#ifndef _DB_H
#define _DB_H
#pragma once

#include "stdafx.h"
//#import "C://Program Files//Common Files//System//ado//msado15.dll" 
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","rsEOF")
class CDb
{
public:
	CDb(void);
	//�õ����ݼ�
	_RecordsetPtr GetRs(CString strSql);
	//ִ��SQL���
	bool ExecuteSql(CString& strSql);
	//ͨ��idȡ������¼��һ���ֶ�
	string getByfield(string table,string id,string field);
public:
	~CDb(void);
private:
	_ConnectionPtr m_conn;
	_RecordsetPtr m_rs;

};
#endif