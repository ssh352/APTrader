#include "APObjectFactory.h"
#include "./Quotation/APFuturesQuotation.h"
#include "./Quotation/APSharesQuotation.h"
#include "./PositionCtrl/APFuturesPositionCtrl.h"
#include "./PositionCtrl/APSharesPositionCtrl.h"
#include "./QuotationDecision/APSingleQuotationDecision.h"
#include "./QuotationDecision/APPriceMarginQuotationDecision.h"
#include "./QuotationDecision/APPriceRatioQuotationDecision.h"
#include "./Trade/APFuturesTrade.h"
#include "./Trade/APSharesTrade.h"
//#include "APTypes.h"
//Sim
#include "./Simulation/APSimSingleQuotationDecision.h"

APObjectFactory::APObjectFactory()
{
}

APObjectFactory::~APObjectFactory()
{
}

APInstrumentQuotation * APObjectFactory::newInstrumentQuotation(APFinancialInstrumentType marketType, APASSETID instrumentID)
{
	APInstrumentQuotation* cq = NULL;
	switch (marketType) {
	case FCT_Shares:
		cq = new APSharesQuotation(instrumentID);
		break;
	case FCT_Futrues:
		cq = new APFuturesQuotation(instrumentID);
		break;
	case FCT_Options:
		break;
	default:
		break;
	}
	return cq;
}

APPositionCtrl * APObjectFactory::newPositionCtrl(APFinancialInstrumentType marketType)
{
	APPositionCtrl* pc = NULL;
	switch (marketType) {
	case FCT_Shares:
		pc = new APSharesPositionCtrl();
		break;
	case FCT_Futrues:
		pc = new APFuturesPositionCtrl(); // todo: add type
		break;
	case FCT_Options:
		break;
	default:
		break;
	}
	return pc;
}

APTrade * APObjectFactory::newTrade(APFinancialInstrumentType marketType)
{
	APTrade* trader = NULL;
	switch (marketType) {
	case FCT_Shares:
		trader = new APSharesTrade();
		break;
	case FCT_Futrues:
		trader = new APFuturesTrade();
		break;
	case FCT_Options:
		break;
	default:
		break;
	}
	return trader;
}

APQuotationDecision * APObjectFactory::newQuotationDecision(APQuotationDecisionType type, APASSETID srcID, APASSETID targetID, double param)
{
	APQuotationDecision* decision = NULL;
	switch (type) {
	case QDT_Single:
		decision = new APSingleQuotationDecision(srcID);
		break;
	case QDT_PriceMargin:
		decision = new APPriceMarginQuotationDecision(srcID, targetID, param);
		break;
	case QDT_PriceRatio:
		decision = new APPriceRatioQuotationDecision(srcID, targetID, param);
		break;
	case QDT_SimSingle:
		decision = new APSimSingleQuotationDecision(srcID);
		break;
	default:
		break;
	}

	return decision;
}
