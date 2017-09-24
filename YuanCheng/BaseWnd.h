#pragma once
#include "stdafx.h"



#ifndef  _BASEWND_H_ 
#define  _BASEWND_H_

struct SetCText{
	HWND m_hwnd;
	CControlUI* m_pcontrol;
	CString m_settext;
};
struct Prama
{
	HWND m_hwnd;
	CString postdata;
	CString m_settext;
	int requesttype;
	CLabelUI* plab;
	CRichEditUI* prdt;
	CString url;
	CRichEditUI* pPostdata;

};
class BaseWnd: public WindowImplBase
{
public:
	BaseWnd(void);
	~BaseWnd(void);
	UILIB_RESOURCETYPE GetResourceType() const;
	LPCTSTR GetResourceID() const;
	UINT GetClassStyle() const;
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage(HWND /*hWnd*/);

	// ͨ�� WindowImplBase �̳�
	virtual CDuiString GetSkinFolder() override;
	//���汣�����麯��Ҫ������һ��Ҫʵ�ַ���xml�ļ�
	//virtual CDuiString GetSkinFile() override;
};

#endif