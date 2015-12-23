#include "Db.h"
CDb::CDb(void)
{
	//��ʼ��COM
	::CoInitialize(NULL);
	try
	{
		try {
			m_conn.CreateInstance("ADODB.Connection");
			CString conn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=.//data//data.mdb";
			//SQL SERVER�����ַ���
			//CString conn="Driver={SQL Server};server=(local);uid=sa;database=pubs";//local���Ը�Ϊ127.0.0.1
			if (FAILED(m_conn->Open((_bstr_t)conn, "", "", -1)))
			{
				::MessageBox(NULL, "���ݿ�����ʧ��", "����", MB_ICONEXCLAMATION);
				return;
			}
		}catch(_com_error &e){
			::MessageBox(NULL, "���ݿ����ӳ����쳣", "����", MB_ICONEXCLAMATION);
		}
	}
	catch(...)
	{
		::MessageBox(NULL,"���ݿ����ӳ����쳣","����",MB_ICONEXCLAMATION);
	}

}

CDb::~CDb(void)
{
	//if(m_rs!=NULL)
	m_rs->Close();
	m_rs.Release();
	m_conn->Close();
	m_conn.Release();
	::CoUninitialize();
}
_RecordsetPtr CDb::GetRs(CString strSql)
{
	try
	{
		m_rs.CreateInstance("ADODB.Recordset");
		m_rs=m_conn->Execute((_bstr_t)strSql,NULL,adCmdText);
	}
	catch(...)
	{
		return NULL;
	}
	return m_rs;
}
string CDb::getByfield(string table,string id,string field){
	string sql="select top 1 "+field+" from "+table+" where id="+id;
	GetRs(CString(sql.c_str()));
	if(m_rs){
		string str=(LPCTSTR)(_bstr_t)(m_rs->Fields->GetItem(field.c_str())->Value);
		return str;
	}else{
		return NULL;
	}
}
bool CDb::ExecuteSql(CString& strSql)
{
	try
	{
		m_conn->Execute((_bstr_t)strSql,NULL,adCmdText);
		return true;
	}
	catch(...)
	{
		return false;
	}
}