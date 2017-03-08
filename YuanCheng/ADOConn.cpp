
// ADOConn.cpp: implementation of the CADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CADOConn::CADOConn()
{
	//���ݿ����ͣ�Access
	m_iDatabaseType = 1;
	m_strDatabaseName = _bstr_t("./data/data.mdb");
}

CADOConn::~CADOConn()
{

}

/************************************************************************
������:  CADOConn
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-5
��  ��:  �����ݿ����ƴ��ݸ�m_strDatabaseName,���ж����ݿ�����
�β���:  strDatabaseName ���ݿ�����
����ֵ:
�޸ļ�¼:
************************************************************************/
CADOConn::CADOConn(CString strDatabaseName)
{
	CString strFormat;
	strDatabaseName.TrimLeft();
	strDatabaseName.TrimRight();
	m_strDatabaseName = _bstr_t(strDatabaseName);
	strFormat = strDatabaseName.Right(strDatabaseName.GetLength() - strDatabaseName.ReverseFind('.') - 1);

	if (strFormat == "mdb")
	{
		m_iDatabaseType = 1;
	}
	if (strFormat == "xls" || strFormat == "xlsx")
	{
		m_iDatabaseType = 2;
	}
}

/************************************************************************
������:  GetAppPath
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-18
��  ��:  ��ȡ��ǰ����Ŀ�ִ���ļ����ڵ�Ŀ¼
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
CString CADOConn::GetAppPath()
{
	char lpFilePath[MAX_PATH];
	CString strPath;

	GetModuleFileName(::GetModuleHandle(NULL), lpFilePath, MAX_PATH);
	strPath = lpFilePath;
	strPath = strPath.Left(strPath.ReverseFind('\\'));

	return strPath;
}

/************************************************************************
������:  InitCADOConn
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-5
��  ��:  ��ʼ�����ݿ�����
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
void CADOConn::InitCADOConn()
{
	CString toolPath = GetAppPath();

	//��ʼ��OLE/COM�⻷��
	::CoInitialize(NULL);
	try
	{
		m_pConnection = NULL;
		m_pRecordset = NULL;
		//����Connection����
		m_pConnection.CreateInstance("ADODB.Connection");
		//���������ַ�����������BSTR�ͻ���_bstr_t����
		_bstr_t strConnect;

		switch (m_iDatabaseType)
		{
		case 1://ACCESS
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\data\\") + m_strDatabaseName;
			break;
		case 2://EXCEL
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\") + m_strDatabaseName;
			strConnect = strConnect + ";Extended Properties=Excel 8.0";
			break;
		case 3://SQL SERVER
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\") + m_strDatabaseName;
			strConnect = strConnect + ";Extended Properties=Excel 8.0";
			break;
		}

		m_pConnection->Open(strConnect, _bstr_t(""), _bstr_t(""), adModeUnknown);
		//ShellExecute(NULL, _T("open"), toolPath + "\\" + m_strDatabaseName, NULL, NULL, SW_SHOWMAXIMIZED);
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "����", MB_ICONEXCLAMATION);
	}
}

/************************************************************************
������:  GetRecordSet
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-5
��  ��:  ִ�в�ѯ
�β���:  strSQL SQL���
����ֵ:  m_pRecordset �ֶμ���ָ��
�޸ļ�¼:
************************************************************************/
_RecordsetPtr& CADOConn::GetRecordSet(CString strSQL)
{
	try
	{
		//�������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		//������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//ȡ�ñ��еļ�¼
		m_pRecordset->Open(_bstr_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		return m_pRecordset;
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "����", MB_ICONEXCLAMATION);
	}

	return m_pRecordset;
}

/************************************************************************
������:  Open
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-5
��  ��:  ���ַ���
�β���:  strSQL SQL���
����ֵ:  TRUE:�ɹ� FALSE:ʧ��
�޸ļ�¼:
************************************************************************/
BOOL CADOConn::Open(CString strSQL)
{
	try
	{
		//�������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		//������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//ȡ�ñ��еļ�¼
		m_pRecordset->Open(_bstr_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "����", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

/************************************************************************
������:  ExecuteSQL
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-5
��  ��:  ִ��SQL���(Insert Update delete)
�β���:  strSQL SQL���
����ֵ:  TRUE:�ɹ� FALSE:ʧ��
�޸ļ�¼:
************************************************************************/
BOOL CADOConn::ExecuteSQL(CString strSQL)
{
	try
	{
		//�������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		m_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
		return TRUE;
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "����", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

/************************************************************************
������:  MoveFirst
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  ��¼������ͷ
�β���:
����ֵ:  TRUE:�ɹ� FALSE:ʧ��
�޸ļ�¼:
************************************************************************/
BOOL CADOConn::MoveFirst()
{
	if (m_pRecordset == NULL)
	{
		return FALSE;
	}
	else
	{
		m_pRecordset->MoveFirst();
		return TRUE;
	}
}

/************************************************************************
������:  MoveNext
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  ��¼�������ƶ�
�β���:
����ֵ:  TRUE:�ɹ� FALSE:ʧ��
�޸ļ�¼:
************************************************************************/
BOOL CADOConn::MoveNext()
{
	if (m_pRecordset == NULL)
	{
		return FALSE;
	}
	else
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveNext();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/************************************************************************
������:  GetItemString
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  ȡ���ֶ��е��ַ���
�β���:  index:�ֶμ��е�����
����ֵ:
�޸ļ�¼:
************************************************************************/
CString CADOConn::GetItemString(int index)
{
	_variant_t vValue;
	_variant_t vIndex;
	CString strValue, str;

	if (m_pRecordset == NULL || m_pRecordset->adoEOF)
	{
		return "";
	}

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->GetCollect(vIndex);
	//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		str = "";
		break;
	case VT_ERROR:
		str = "";
		break;
	case VT_EMPTY:
		str = "";
		break;
	default:
		str = (LPCTSTR)_bstr_t(vValue);
	}

	strValue.Format(_T("%s"), str);
	strValue.TrimRight();
	strValue.TrimLeft();

	return strValue;
}

/************************************************************************
������:  GetItemInt
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-18
��  ��:  ȡ���ֶ��е�����
�β���:  index:�ֶμ��е�����
����ֵ:
�޸ļ�¼:
************************************************************************/
int CADOConn::GetItemInt(int index)
{
	_variant_t vValue;
	_variant_t vIndex;
	int iValue;

	if (m_pRecordset == NULL || m_pRecordset->adoEOF)
	{
		exit(1);
	}

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->GetCollect(vIndex);
	//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		iValue = 0;
		break;
	case VT_ERROR:
		iValue = 0;
		break;
	case VT_EMPTY:
		iValue = 0;
		break;
	default:
		iValue = vValue.iVal;
	}

	return iValue;
}

/************************************************************************
������:  GetItemLong
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-18
��  ��:  ȡ���ֶ��е�����
�β���:  index:�ֶμ��е�����
����ֵ:
�޸ļ�¼:
************************************************************************/
long CADOConn::GetItemLong(int index)
{
	long lValue;
	_variant_t vIndex;
	_variant_t vValue;

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		lValue = 0;
		break;
	case VT_ERROR:
		lValue = 0;
		break;
	case VT_EMPTY:
		lValue = 0;
		break;
	default:
		lValue = vValue.lVal;
	}

	return lValue;
}

/************************************************************************
������:  GetFieldName
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  ȡ���б���
�β���:  index:�ֶμ��е�����,��СֵΪ0
����ֵ:
�޸ļ�¼:
************************************************************************/
CString CADOConn::GetFieldName(int index)
{
	_variant_t vIndex;
	CString strFieldName;

	if (index < m_pRecordset->Fields->Count)
	{
		vIndex.vt = VT_I2;
		vIndex.iVal = index;
		strFieldName = (LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();
	}
	else
	{
		::MessageBox(NULL,"Invalid index!" , "����", MB_ICONEXCLAMATION);
	}

	return strFieldName;
}

/************************************************************************
������:  GetFieldsCount
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  ȡ������
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
int CADOConn::GetFieldsCount()
{
	int colNum = m_pRecordset->Fields->Count;
	return colNum;
}

/************************************************************************
������:  adoEOF
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  �ж��ֶμ��Ƿ����
�β���:
����ֵ:  TRUE:���� FALSE:δ����
�޸ļ�¼:
************************************************************************/
BOOL CADOConn::adoEOF()
{
	if (m_pRecordset->adoEOF)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/************************************************************************
������:  ExitConnect
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-6
��  ��:  �˳�����
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
void CADOConn::ExitConnect()
{
	try
	{
		if (m_pRecordset != NULL)
		{
			m_pRecordset->Close();
		}
		if (m_pConnection != NULL)
		{
			m_pConnection->Close();
		}

		m_pRecordset = NULL;
		m_pConnection = NULL;

		//�ͷ�OLE/COM�⻷��
		::CoUninitialize();
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "����", MB_ICONEXCLAMATION);

	}
}

/************************************************************************
������:  InitList
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-19
��  ��:  ��ʼ���б�
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
//BOOL CADOConn::InitList(CListCtrl *listMain)
//{
//	int iMaxCol = 0, i;
//	_variant_t vIndex;
//
//	vIndex.vt = VT_I2;
//	iMaxCol = m_pRecordset->Fields->Count;
//	listMain->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
//
//	for (i = 0; i < iMaxCol; i++)
//	{
//		CString strTitle;
//		vIndex.iVal = i;
//		strTitle = (LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();
//		listMain->InsertColumn(i, strTitle, LVCFMT_CENTER, 100, 0);
//	}
//
//	int iWidth = 0;
//	for (i = 0; i < iMaxCol; i++)
//	{
//		listMain->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
//		iWidth = iWidth + listMain->GetColumnWidth(i);
//	}
//
//	RECT rectList;
//	listMain->GetWindowRect(&rectList);
//	if (iWidth < (rectList.right - rectList.left))
//	{
//		iWidth = (rectList.right - rectList.left - iWidth) / iMaxCol;
//	}
//	else
//	{
//		return TRUE;
//	}
//
//	for (i = 0; i < iMaxCol; i++)
//	{
//		listMain->SetColumnWidth(i, listMain->GetColumnWidth(i) + iWidth);
//	}
//
//	return TRUE;
//}

/************************************************************************
������:  FillList
��  ��:	 ̷����(Charles Tan)
��  ��:	 2013-3-19
��  ��:  ����б�
�β���:
����ֵ:
�޸ļ�¼:
************************************************************************/
//BOOL CADOConn::FillList(CListCtrl *listMain)
//{
//
//	int i, iType, iRow = 0, listWidth = 0;//iType:�ֶμ����������� listWidth:�б����еĿ��
//	_variant_t vIndex;
//	long lMax = 0;
//	lMax = m_pRecordset->Fields->Count;
//	vIndex.vt = VT_I2;
//	if (!m_pRecordset->adoEOF)
//	{
//		MoveFirst();
//		while (!m_pRecordset->adoEOF)
//		{
//			for (i = 0; i<lMax; i++)
//			{
//				CString strValue = "";
//				vIndex.iVal = i;
//				iType = m_pRecordset->Fields->GetItem(vIndex)->GetType();
//				switch (iType)
//				{
//				case ado_Field_Str:
//				case ado_Field_Text:
//					strValue = GetItemString(i);
//					break;
//				case ado_Field_Long:
//					strValue.Format(_T("%d"), GetItemLong(i));
//					break;
//				case ado_Field_Int:
//					strValue.Format(_T("%d"), GetItemInt(i));
//					break;
//					//				case ado_Field_Float:
//					//					strValue=GetValueFloatStr(i,0,2);
//					//					break;
//					//				case ado_Field_Double:
//					//					strValue=GetValueDoubleStr(i,0,2);
//					//					break;
//					//				case ado_Field_Byte:
//					//					strValue=GetValueByteStr(i,0);
//					//					break;
//				case ado_Field_Date:
//					strValue = GetItemString(i);
//					break;
//				default:
//					strValue = "";
//					break;
//				}
//
//				if (i == 0)
//					listMain->InsertItem(iRow, strValue, 0);
//				else
//					listMain->SetItemText(iRow, i, strValue);
//			}
//			m_pRecordset->MoveNext();
//		}
//		//����ͷ
//		MoveFirst();
//	}
//
//	return TRUE;
//}