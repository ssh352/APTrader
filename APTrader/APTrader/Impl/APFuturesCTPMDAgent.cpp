#include "APFuturesCTPMDAgent.h"
#include "../Utils/APJsonReader.h"

std::string mdflowpath = "Data/CTP/mdflow/";

APFuturesCTPMDAgent::APFuturesCTPMDAgent()
{
}


APFuturesCTPMDAgent::~APFuturesCTPMDAgent()
{
}

void APFuturesCTPMDAgent::initCTP() 
{
	m_mdApi = CThostFtdcMdApi::CreateFtdcMdApi(mdflowpath.c_str(), true);
	m_mdResponser = new APFuturesCTPMDResponser();	
	m_mdApi->RegisterSpi(m_mdResponser);
	m_mdApi->RegisterFront((char*)m_marketFront.c_str());
	m_mdApi->Init();
	m_mdApi->Join();
}

void APFuturesCTPMDAgent::login() 
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, m_brokerID.c_str());
	strcpy(req.UserID, m_userID.c_str());
	strcpy(req.Password, m_password.c_str());

	int ret = m_mdApi->ReqUserLogin(&req, genReqID());
}

CThostFtdcMdApi* APFuturesCTPMDAgent::getMDApi() {
	return m_mdApi;
}

bool APFuturesCTPMDAgent::subscribeInstrument(APASSETID instrumentID)
{
	if (m_mdApi == NULL) {
		return false;
	}

	char** ppSubscribeArr = (char**)malloc(sizeof(char**));
	std::set<APASSETID>::iterator it;

	//for (it = m_subscribedInstruments.begin(); it != m_subscribedInstruments.end(); it++) {
	//	APASSETID id = *it;
	//	*ppSubscribeArr++ = (char*)id.c_str();
	//}
	*ppSubscribeArr = (char*)instrumentID.c_str();

	bool ret = m_mdApi->SubscribeMarketData(ppSubscribeArr, 1);// m_subscribedInstruments.size() + 1);
	//if (ret) {
	//	m_subscribedInstruments.insert(instrumentID);
	//}

	delete ppSubscribeArr;
	return ret;
}