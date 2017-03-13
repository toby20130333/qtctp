#include "dduimarketdataapi.h"
#include <QDebug>

DDuiMarketDataApi::DDuiMarketDataApi(QObject *parent) : QObject(parent)
{
}
void DDuiMarketDataApi::OnFrontConnected(){
    qDebug()<<Q_FUNC_INFO<<" OnFrontConnected";
    emit signalFrontConnected();
}

void DDuiMarketDataApi::OnFrontDisconnected(int nReason){
    qDebug()<<Q_FUNC_INFO<<" OnFrontDisconnected";
}

void DDuiMarketDataApi::OnHeartBeatWarning(int nTimeLapse){
    qDebug()<<Q_FUNC_INFO<<" OnHeartBeatWarning"<<nTimeLapse;
}

void DDuiMarketDataApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin
                                       , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug("OnRspUserLogin:\n");
    qDebug("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    qDebug("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
    if (pRspInfo->ErrorID != 0) {
        // 端登失败，客户端需进行错误处理
        qDebug("Failed to login, errorcode=%d errormsg=%s requestid=%d chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
        emit signalRspUserLogin(false);
        return;
    }
    emit signalRspUserLogin(true);
}

void DDuiMarketDataApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout
                                        , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorMsg;
}

void DDuiMarketDataApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorID;
}

void DDuiMarketDataApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                           , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorMsg;
}

void DDuiMarketDataApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                             , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorMsg;
}

void DDuiMarketDataApi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                            , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorMsg;
}

void DDuiMarketDataApi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                              , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    qDebug()<<Q_FUNC_INFO<<pRspInfo->ErrorMsg;
}

void DDuiMarketDataApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData ) {
    //    qDebug()<<Q_FUNC_INFO<<pDepthMarketData->AskPrice1;
    // 输出报单录入结果
    if(!pDepthMarketData)return;
    qDebug()<<Q_FUNC_INFO<<pDepthMarketData->AskPrice1
           <<" "<<pDepthMarketData->ActionDay<<" code "<<pDepthMarketData->InstrumentID;

    QString json = QString("<font color='green'> LastPrice:%1, time: %2,code:%3,price1:%4</font>")
            .arg(pDepthMarketData->LastPrice)
            .arg(pDepthMarketData->ActionDay).arg(pDepthMarketData->InstrumentID)
            .arg(pDepthMarketData->AskPrice1);
    emit signalRspMarketData(json);
}

void DDuiMarketDataApi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
    qDebug()<<Q_FUNC_INFO<<pForQuoteRsp->TradingDay;
}

