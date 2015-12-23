#include "MyString.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
CMyString::CMyString(string subject){
	this->subject=subject;
}

CMyString::CMyString(void)
{
}


CMyString::~CMyString(void)
{
}
string CMyString::replace(string search,string replace,string subject){
	if(subject=="")subject=this->subject;
	int start_pos=0,length=0;
	if (subject.find(search) != -1)
	{
		start_pos=subject.find(search);
		length=search.length();
		subject.replace(start_pos,length,replace);
		return subject;
	}else{
		return subject;
	}
}

string CMyString::enString(const char* src,const char* key)
{
	int KeyPos=-1;
	int SrcPos=0;
	int SrcAsc=0;
	time_t t;

	int KeyLen=strlen(key);
	if(KeyLen==0)return "";

	srand((unsigned)time(&t));
	int offset=rand()%255;

	char buff[3];
	sprintf(buff,"%1.2x",offset);
	string dest=buff;
	int a=strlen(src);
	for(int i=0;i<a;i++)
	{
		SrcAsc=(src[i]+offset)%255;
		if(KeyPos<KeyLen-1)
			KeyPos++;
		else
			KeyPos=0;

		SrcAsc=SrcAsc^key[KeyPos];

		memset(buff,0,sizeof(buff));
		sprintf(buff,"%1.2x",SrcAsc);
		dest=dest+(string)buff;
		offset=SrcAsc;
	}
	return dest;
}
string CMyString::deString(const char* src,const char* key)
{
	int KeyLen=strlen(key);
	if(KeyLen==0)
		return "";

	int KeyPos=-1;
	int offset=0;
	string dest="";
	int SrcPos=0;
	int SrcAsc=0;
	int TmpSrcAsc=0;

	char buff[5];
	sprintf(buff,"0x%s",substr(src,1,2));
	sscanf(buff,"%x",&offset);
	SrcPos=3;
	while (SrcPos<=strlen(src))
	{
		sprintf(buff,"0x%s",substr(src,SrcPos,2));
		sscanf(buff,"%x",&SrcAsc);
		if(KeyPos<KeyLen-1)
			KeyPos++;
		else
			KeyPos=0;

		TmpSrcAsc=SrcAsc^key[KeyPos];
		if(TmpSrcAsc<=offset)
			TmpSrcAsc=255+TmpSrcAsc-offset;
		else
			TmpSrcAsc=TmpSrcAsc-offset;
		dest+=char(TmpSrcAsc);
		offset=SrcAsc;
		SrcPos=SrcPos+2;
	}
	return dest;
}
char* CMyString::substr(const char* _str,int pos,int len){
	static char ptr[10];
	memcpy(ptr,_str+pos-1,len);
	ptr[len]='\0';
	return ptr;
}

//CString CMyString::Encryptt(CString S, WORD Key){
//	CString Result,str;
//	int i,j;
//
//	Result=S; // ��ʼ������ַ���
//	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
//	{
//		Result.SetAt(i, S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
//		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2; // ������һ����Կ
//	}
//	S=Result; // ������
//	Result.Empty(); // ������
//	for(i=0; i<S.GetLength(); i++) // �Լ��ܽ������ת��
//	{
//		j=(BYTE)S.GetAt(i); // ��ȡ�ַ�
//		// ���ַ�ת��Ϊ������ĸ����
//		str="12"; // ����str����Ϊ2
//		str.SetAt(0, 65+j/26);//���ｫ65�Ĵ���������256�����ľͻ�����룬Ч�����ã���Ӧ�ģ����ܴ�Ҫ��Ϊ��ͬ����
//		str.SetAt(1, 65+j%26);
//		Result += str;
//	}
//	return Result;
//}

//CString CMyString::Decryptt(CString S, WORD Key){
//	CString Result,str;
//	int i,j;
//
//	Result.Empty(); // ������
//	for(i=0; i < S.GetLength()/2; i++) // ���ַ���������ĸһ����д���
//	{
//		 j = ((BYTE)S.GetAt(2*i)-65)*26;);//��Ӧ�ģ����ܴ�Ҫ��Ϊ��ͬ����
//
//		j += (BYTE)S.GetAt(2*i+1)-65;
//		str="1"; // ����str����Ϊ1
//		str.SetAt(0, j);
//		Result+=str; // ׷���ַ�����ԭ�ַ���
//	}
//	S=Result; // �����м���
//	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
//	{
//		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
//		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2; // ������һ����Կ
//	}
//	return Result;
//}