#ifndef DDUITRADERAPI_H
#define DDUITRADERAPI_H

#include <QObject>
#include <tradeapidll/32/ThostFtdcTraderApi.h>
#include <tradeapidll/32/ThostFtdcUserApiStruct.h>
#include <tradeapidll/32/ThostFtdcUserApiDataType.h>
#include <dduictpconfig.h>

///
/// \brief The DDuiTraderApi class
/// 实现CTP的交易接口的虚函数
///
class DDuiTraderApi : public QObject
        ,public CThostFtdcTraderSpi
{
    Q_OBJECT
public:
    explicit DDuiTraderApi(QObject *parent = 0);
    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
     void OnFrontConnected();
    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
     void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
     void OnHeartBeatWarning(int nTimeLapse);

    ///客户端认证响应
     void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登录请求响应
     void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登出请求响应
     void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///用户口令更新请求响应
     void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///资金账户口令更新请求响应
     void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///报单录入请求响应
     void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///预埋单录入请求响应
     void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///预埋撤单录入请求响应
     void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///报单操作请求响应
     void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///查询最大报单数量响应
     void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///投资者结算结果确认响应
     void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///删除预埋单响应
     void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///删除预埋撤单响应
     void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///执行宣告录入请求响应
     void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///执行宣告操作请求响应
     void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///询价录入请求响应
     void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///报价录入请求响应
     void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///报价操作请求响应
     void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///批量报单操作请求响应
     void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///申请组合录入请求响应
     void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询报单响应
     void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询成交响应
     void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询投资者持仓响应
     void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询资金账户响应
     void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询投资者响应
     void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询交易编码响应
     void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询合约保证金率响应
     void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询合约手续费率响应
     void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询交易所响应
     void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询产品响应
     void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询合约响应
     void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询行情响应
     void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者结算结果响应
     void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询转帐银行响应
     void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询投资者持仓明细响应
     void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询客户通知响应
     void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询结算信息确认响应
     void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询投资者持仓明细响应
     void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///查询保证金监管系统经纪公司资金账户密钥响应
     void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询仓单折抵信息响应
     void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询投资者品种/跨品种保证金响应
     void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询交易所保证金率响应
     void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询交易所调整保证金率响应
     void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询汇率响应
     void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询二级代理操作员银期权限响应
     void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询产品报价汇率
     void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询产品组
     void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询期权交易成本响应
     void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询期权合约手续费响应
     void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询执行宣告响应
     void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询询价响应
     void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询报价响应
     void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询组合合约安全系数响应
     void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询申请组合响应
     void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询转帐流水响应
     void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询银期签约关系响应
     void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///错误应答
     void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
     void OnRtnOrder(CThostFtdcOrderField *pOrder);

    ///成交通知
     void OnRtnTrade(CThostFtdcTradeField *pTrade) {}

    ///报单录入错误回报
     void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {}

    ///报单操作错误回报
     void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {}

    ///合约交易状态通知
     void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {}

    ///交易通知
     void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {}

    ///提示条件单校验错误
     void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {}

    ///执行宣告通知
     void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {}

    ///执行宣告录入错误回报
     void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {}

    ///执行宣告操作错误回报
     void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {}

    ///询价录入错误回报
     void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {}

    ///报价通知
     void OnRtnQuote(CThostFtdcQuoteField *pQuote) {}

    ///报价录入错误回报
     void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {}

    ///报价操作错误回报
     void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {}

    ///询价通知
     void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {}

    ///保证金监控中心用户令牌
     void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {}

    ///批量报单操作错误回报
     void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) {}

    ///申请组合通知
     void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {}

    ///申请组合录入错误回报
     void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo) {}

    ///请求查询签约银行响应
     void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询预埋单响应
     void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询预埋撤单响应
     void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询交易通知响应
     void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询经纪公司交易参数响应
     void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询经纪公司交易算法响应
     void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///请求查询监控中心用户令牌
     void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///银行发起银行资金转期货通知
     void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {}

    ///银行发起期货资金转银行通知
     void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {}

    ///银行发起冲正银行转期货通知
     void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {}

    ///银行发起冲正期货转银行通知
     void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {}

    ///期货发起银行资金转期货通知
     void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {}

    ///期货发起期货资金转银行通知
     void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {}

    ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
     void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {}

    ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
     void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {}

    ///期货发起查询银行余额通知
     void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {}

    ///期货发起银行资金转期货错误回报
     void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {}

    ///期货发起期货资金转银行错误回报
     void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {}

    ///系统运行时期货端手工发起冲正银行转期货错误回报
     void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {}

    ///系统运行时期货端手工发起冲正期货转银行错误回报
     void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {}

    ///期货发起查询银行余额错误回报
     void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {}

    ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
     void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {}

    ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
     void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {}

    ///期货发起银行资金转期货应答
     void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///期货发起期货资金转银行应答
     void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///期货发起查询银行余额应答
     void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

    ///银行发起银期开户通知
     void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {}

    ///银行发起银期销户通知
     void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {}

    ///银行发起变更银行账号通知
     void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {}
signals:
     void signalFrontConnected();
     void signalRspUserLogin(bool success);
public slots:
private:
//     CThostFtdcTraderApi *mPTraderApi;
};

#endif // DDUITRADERAPI_H
