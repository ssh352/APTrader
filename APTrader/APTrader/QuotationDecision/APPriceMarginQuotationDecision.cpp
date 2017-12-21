#include "APPriceMarginQuotationDecision.h"
#include "../APInstrumentQuotation.h"
#include "../APMarketDataManager.h"

APPriceMarginQuotationDecision::APPriceMarginQuotationDecision(APASSETID srcInstrumentID, APASSETID targetInstrumentID, double priceDiff)
{
	m_srcQuotation = APMarketDataMgr->subscribeInstrument(srcInstrumentID);
	m_targetQuotation = APMarketDataMgr->subscribeInstrument(targetInstrumentID);
	m_priceDiff = priceDiff;
}


APPriceMarginQuotationDecision::~APPriceMarginQuotationDecision()
{
	if (m_srcQuotation != NULL) {
		APMarketDataMgr->unSubscribeInstrument(m_srcQuotation->getInstrumentID());
	}

	if (m_targetQuotation != NULL) {
		APMarketDataMgr->unSubscribeInstrument(m_targetQuotation->getInstrumentID());
	}
}

double APPriceMarginQuotationDecision::getValueReference()
{
	if (m_srcQuotation != NULL && m_targetQuotation != NULL) {
		double srcPrice = m_srcQuotation->getCurPrice();
		double targetPrice = m_targetQuotation->getCurPrice();
		return targetPrice - srcPrice;
	}

	return -DBL_MAX;
}
