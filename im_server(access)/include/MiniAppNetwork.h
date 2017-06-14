/************************************************************************ 
 �ļ�������Ӧ�������
     ��ҵ��������ļ�Ⱥʵ���������͸��·�ɣ�����ά���������ĸ�ͨѶ��·
 
 �����ˣ� zouyf, 2006-6-9 
 
 �޸ļ�¼�� 
************************************************************************/

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� MINIAPPNETWORK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// MINIAPPNETWORK_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once

#ifdef MINIAPPNETWORK_EXPORTS
	#define MINIAPPNETWORK_API 
#else
	#define MINIAPPNETWORK_API 
#endif

#include "PublicType.h"
#include "MiniNetTrans.h"
#include <vector>

typedef struct tagONLINE_USER_INFO
{
	uint32 uid;
#ifdef IM_USE_MULTIDEVICE
	vector<multiDevice_t> device;
#else
	uint32 uip;
	uint16 uport;
	char sessionKey[16];
	char p2pSessionKey[16];
	uint32 srvip;
	uint8  isDirect;
	uint32 joinedTime;  //�Ѽ���ʱ��
	uint32 lanip;
	uint16 lanport;
	uint8 flag;//�ж�����PC�ˡ�WEB�˻��ƶ���
	uint32 newlylivetime;	// ��½ʱ��
	uint32 merchantID;		// merchantID
#endif
	tagONLINE_USER_INFO()
	{
		memset(this,0,sizeof(tagONLINE_USER_INFO));
	}
}ONLINE_USER_INFO, * LPONLINE_USER_INFO;

typedef struct tagONLINE_FAMILY_INFO
{
	uint32 fid;
	uint8  ftype; //PERM_FAMILY TEMP_FAMILY
	uint32 srvip;
	uint8  isDirect;
	uint32 joinedTime;
	tagONLINE_FAMILY_INFO()
	{
		memset(this,0,sizeof(tagONLINE_FAMILY_INFO));
	}
}ONLINE_FAMILY_INFO, * LPONLINE_FAMILY_INFO;

//Ӧ�ò�ص�����
typedef void (*pfnAppNetCallback)(void * pUserKey,int nEvent,const RecvDataStruct * pRecvData);

// �����Ǵ� MiniAppNetwork.dll ������
class MINIAPPNETWORK_API CMiniAppNetwork
{
public:
	CMiniAppNetwork(void);
	~CMiniAppNetwork(void);

	/*
	��������: �����û��ص������ͻص�����
	��Ҫ����˵����pUserKey���û��ص�����
				  pfnCallback���û��ص�����
	�� �� ֵ��
	*/ 
	void SetUserCallback(void * pUserKey,pfnAppNetCallback pfnCallback);

	void SetUserCallback(FunRecvNetData funRecvNetData);

	void SetCallback_SendNetData(FunSendNetData pFunSendNetData);

	/*
	��������: ����Ӧ����������
	��Ҫ����˵����addr��IP ��ַ
				  prot��udp�����˿�
	�� �� ֵ��0 �ɹ���< 0 ʧ��
	*/ 
	int StartWork(const char * addr,uint16 port = 0);

	/*
	��������: �����û�������Ϣ
	��Ҫ����˵����uid���û�ID
	�� �� ֵ�� �û�������Ϣ
	*/ 	
#ifdef ACCESS_SERVER	
	LPONLINE_USER_INFO FindOnlineUser(uint32 uid);
	// ��ȡ�����û�hash�б���hash��֧��
	int GetUserHash_Elems();
	// ��ȡ�����û�hash�б���hash��֧�����������(�������û�idΪ����)
	void GetUserHash_ElemIDs(int nElemIdex, std::vector<uint32> &vecID);
#else
	BOOL FindOnlineUser(CGlobalBusi *pGlobalBusi, uint32 uid);
#endif
#ifdef ACCESS_SERVER	
	/*
	��������: �û���½
	��Ҫ����˵����uid���û�ID
	�� �� ֵ�� 0 ������½�� 1 �����ص�½ ��2 ����ص�¼
	*/
	int UserLogin(CGlobalBusi *pGlobalBusi,uint32 uid,uint32 uip,uint16 uport,const char * pSessionKey = NULL,const char * pP2PSessionKey = NULL,uint32 lanip = 0,uint16 lanport = 0,uint8 flag = XT_HEAD::FLAG_CNTREQUEST);
	void UserLogout(uint32 uid);
#endif
	/*
	��������: �����½
	��Ҫ����˵����fid������ID
	�� �� ֵ��
	*/ 
	void FamilyLogin(uint32 fid,uint8 ftype = PERM_FAMILY);
	void FamilyLogout(uint32 fid,uint8 ftype = PERM_FAMILY);

	/*
	��������: ͨ��Ӧ������㷢�����ݣ��Զ�����
	��Ҫ����˵����uid ��Ŀ���û�
				  data�����͵�����
				  size�����ݳ���
				  retrys���ط�����
				  interval���ط����
	�� �� ֵ��0 �ɹ���< 0 ʧ��
	*/ 
	int SendDataTo(CGlobalBusi *pGlobalBusi, const char * data,int size,int retrys = 0,uint16 interval = 0,uint32 ip = 0,uint16 port = 0,uint32 vlink = 0);

	//ֱ��ͨ������㷢������
	int SendDataTo(CGlobalBusi *pGlobalBusi, SendDataStruct & sendData);

	void StopWork();

	uint16 GetPort();
	uint32 GetLocalIP();

	CUdpNetTrans*  GetSrvNetTrans();
/*	
	CUdpNetTrans*  GetCntNetTrans();
*/
	void AddImServer(uint32 srvid,uint32 srvip);
	void DelImServer(uint32 srvid);

	//����û�����
	int UserType(CGlobalBusi *pGlobalBusi, uint32 id);

	// �����ݰ�ѹ�����
	void ImSvrP2PRecvData(int nEvent,const RecvDataStruct * pRecvData);

private:
	void * m_pAppNetwork;
};