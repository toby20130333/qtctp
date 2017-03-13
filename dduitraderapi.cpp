#include "dduitraderapi.h"
#include <iostream>
#include <QDebug>

using namespace std;
DDuiTraderApi::DDuiTraderApi(QObject *parent) : QObject(parent)
{

}
void DDuiTraderApi::OnFrontConnected(){
    std::cerr << "--->>> " << __FUNCTION__ << std::endl;
    emit signalFrontConnected();
}

void DDuiTraderApi::OnFrontDisconnected(int nReason){
    std::cerr << "--->>> " << "reason: " << nReason << std::endl;
}

void DDuiTraderApi::OnHeartBeatWarning(int nTimeLapse){
    std::cerr << "--->>> " << nTimeLapse << std::endl;
}

void DDuiTraderApi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    std::cerr << "--->>> " << __FUNCTION__ << std::endl;
    std::cerr << "brokerID: " << pRspAuthenticateField->BrokerID << " UserID: " << pRspAuthenticateField->UserID << " ProductInfo: " << pRspAuthenticateField->UserProductInfo << std::endl;
    std::cerr << "RspInfo: " << pRspInfo->ErrorMsg << std::endl;

}

void DDuiTraderApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    std::cerr << "--->>> " << __FUNCTION__ << std::endl;
    std::cerr << "brokerID: " << pRspUserLogin->BrokerID << " UserID: " << pRspUserLogin->UserID << " ProductInfo: " << std::endl;
    std::cerr << "RspInfo: " << pRspInfo->ErrorMsg << std::endl;
    qDebug("OnRspUserLogin:\n");
    qDebug("ErrorCode=[%d], ErrorMsg=[%s]\n",
           pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    qDebug("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
    if (pRspInfo->ErrorID != 0) {
        // 端登失败，客户端需进行错误处理
        qDebug("Failed to login, errorcode=%d errormsg=%s\
               requestid=%d chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg,
                nRequestID, bIsLast);
        emit signalRspUserLogin(false);
        return;
    }
    emit signalRspUserLogin(true);

}

void DDuiTraderApi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    // 输出报单录入结果
    qDebug("ErrorCode=[%d], ErrorMsg=[%s]\n",
           pRspInfo->ErrorID, pRspInfo->ErrorMsg);
}

void DDuiTraderApi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData
                                            , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if(!pDepthMarketData)return;
    qDebug()<<Q_FUNC_INFO<<pDepthMarketData->AskPrice1
           <<"day: "<<pDepthMarketData->ActionDay;
}

void DDuiTraderApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if(!pRspInfo)return;
    qDebug("OnRspError:\n");
    qDebug("ErrorCode=[%d], ErrorMsg=[%s]\n",
           pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    qDebug("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
    // 客户端需进行错误处理
}

void DDuiTraderApi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
    if(!pOrder)return;
    qDebug("OnRtnOrder:\n");
    qDebug("OrderSysID=[%s]\n", pOrder->OrderSysID);
}
