#include "APFuturesCTPMDResponser.h"
#include "APFuturesCTPMDAgent.h"
#include "../Utils/APLog.h"

//test
#include "../Quotation/APFuturesMarketQuotations.h"


APFuturesCTPMDResponser::APFuturesCTPMDResponser()
{
}


APFuturesCTPMDResponser::~APFuturesCTPMDResponser()
{
}

void APFuturesCTPMDResponser::OnFrontConnected()
{
	APFuturesCTPMDAgent::getInstance()->login();
}

void APFuturesCTPMDResponser::OnFrontDisconnected(int nReason)
{
	APLogger->log("CTP MD Front Disconnected, error: %d. ", nReason);
}

void APFuturesCTPMDResponser::OnHeartBeatWarning(int nTimeLapse)
{
}

void APFuturesCTPMDResponser::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	APFuturesCTPMDAgent::getInstance()->onLogin();

	//test
	//std::string instrumentID0 = "hc1805";
	//std::string instrumentID1 = "i1805";
	//APFuturesMarketQuotations::getInstance()->init();
	//APFuturesMarketQuotations::getInstance()->subscribeInstrument(instrumentID0);
	//APFuturesMarketQuotations::getInstance()->subscribeInstrument(instrumentID1);
	//CThostFtdcMdApi* mdApi = APFuturesCTPMDAgent::getInstance()->getMDApi();
	//char* ppInstrumentsID[] = {"hc1805"};
	//bool ret = mdApi->SubscribeMarketData(ppInstrumentsID, 1);
	//APLogger->log("Ret: %d", ret);
	
	//while (true) {
		std::string instrumentID0 = "hc1805";
		APFuturesCTPMDAgent::getInstance()->subscribeInstrument(instrumentID0);
	//}
}

void APFuturesCTPMDResponser::OnRspUserLogout(CThostFtdcUserLogoutField * pUserLogout, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void APFuturesCTPMDResponser::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	APLogger->log(pRspInfo->ErrorMsg);
}

void APFuturesCTPMDResponser::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	APLogger->log("On Subscribe Market Data, Instrument ID: %s, ErrorID: %d, ErrorMsg: %s", 
				pSpecificInstrument->InstrumentID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

void APFuturesCTPMDResponser::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	APLogger->log("On UnSubscribe Market Data, Instrument ID: %s, ErrorID: %d, ErrorMsg: %s",
		pSpecificInstrument->InstrumentID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

void APFuturesCTPMDResponser::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void APFuturesCTPMDResponser::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void APFuturesCTPMDResponser::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{
	APLogger->log("On Get Market Data, Instrument ID: %s, Price: %f. ",
					pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);
}

void APFuturesCTPMDResponser::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField * pForQuoteRsp)
{
}