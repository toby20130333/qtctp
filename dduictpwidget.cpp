#include "dduictpwidget.h"

#include <QEventLoop>
#include <QDebug>
#include <QTextCursor>

///
///  深度行情 中金的合约可以 其他的可以走交易段的行情查询接口
///
char *DDuiCTPWidget::Instrumnet[]={"IF1709","IF1706"};

DDuiCTPWidget::DDuiCTPWidget(QWidget *parent) : QWidget(parent)
  ,pMarketApi(NULL),pTraderApi(NULL)
  ,mTraderCallBack(NULL),mMarketCallBack(NULL)
  ,mFutrueView(NULL)
{
    qRegisterMetaType<QTextCursor>("QTextCursor");
    setWindowTitle(QStringLiteral("Qt For 期货CTP例子"));

    createWidgets();
    connectQuoteServer();
    connectTraderServer();
    createConnect();
}

DDuiCTPWidget::~DDuiCTPWidget()
{
    if(pMarketApi){
        pMarketApi->RegisterSpi(NULL);
        pMarketApi->Release();
        pMarketApi = NULL;
        delete mMarketCallBack;
        mMarketCallBack = NULL;
    }
    if(pTraderApi){
        pTraderApi->RegisterSpi(NULL);
        pTraderApi->Release();
        pTraderApi = NULL;
        delete mTraderCallBack;
        mTraderCallBack = NULL;
    }
}

void DDuiCTPWidget::connectServer()
{
    connectQuoteServer();
}
///
/// \brief DDuiCTPWidget::connectTraderServer
/// 初始化交易服务器对象
///     // 订阅私(公)有流
///TERT_RESTART:从本交易日开始重传
///TERT_RESUME:从上次收到的续传
///TERT_QUICK:只传送登录后私(公)有流的内容
///
void DDuiCTPWidget::connectTraderServer()
{
    // 产生一个CThostFtdcTraderApi实例
    pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
    // 产生一个事件处理的实例
    mTraderCallBack = new DDuiTraderApi;
    // 注册一事件处理的实例
    pTraderApi->RegisterSpi(mTraderCallBack);
    //订阅私流
    pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
    // 订阅公共流
    pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);
    // 设置交易托管系统服务的地址，可以注册多个地址备用
    pTraderApi->RegisterFront(TRADE_SERVER);
    // 使客户端开始与后台服务建立连接
    pTraderApi->Init();
    WaitForSingleObject(g_hEvent,INFINITE);
}
///
/// \brief DDuiCTPWidget::connectQuoteServer
/// 初始化行情服务器对象
///
void DDuiCTPWidget::connectQuoteServer()
{
    // 产生一个CThostFtdcMdApi实例
    pMarketApi = CThostFtdcMdApi::CreateFtdcMdApi("",true);
    // 产生一个事件处理的实例
    mMarketCallBack = new DDuiMarketDataApi;
    // 注册一事件处理的实例
    pMarketApi->RegisterSpi(mMarketCallBack);
    // 设置交易托管系统服务的地址，可以注册多个地址备用
    pMarketApi->RegisterFront(MARKET_SERVER);
    // 使客户端开始与后台服务建立连接
    pMarketApi->Init();
//    pUserApi->Join();
    WaitForSingleObject(g_hEvent2,INFINITE);
    // 释放API实例
    // pUserApi->Release();
}

void DDuiCTPWidget::createConnect()
{
    connect(mMarketCallBack,&DDuiMarketDataApi::signalFrontConnected,[&](){
        CThostFtdcReqUserLoginField reqUserLogin;
        // get BrokerID
        strcpy(reqUserLogin. BrokerID, BROKER_ID);
        // get userid
        strcpy(reqUserLogin.UserID, USER_ID);
        // get password
        strcpy(reqUserLogin.Password,PASSWD_ID);
        // 发出登陆请求
        qDebug()<<Q_FUNC_INFO<<pMarketApi->ReqUserLogin(&reqUserLogin, 0);
    });
    connect(mMarketCallBack,&DDuiMarketDataApi::signalRspUserLogin,[&](bool success){
        // 订阅行情
        qDebug()<<Q_FUNC_INFO<<success;
       if(success){
           qDebug()<<"sub ok? "<<pMarketApi->SubscribeMarketData (Instrumnet,2);
       }
    });
    connect(mTraderCallBack,&DDuiTraderApi::signalFrontConnected,[&](){
        CThostFtdcReqUserLoginField reqUserLogin;
        // get BrokerID
        strcpy(reqUserLogin. BrokerID, BROKER_ID);
        // get userid
        strcpy(reqUserLogin.UserID, USER_ID);
        // get password
        strcpy(reqUserLogin.Password,PASSWD_ID);
        // 发出登陆请求
        pTraderApi->ReqUserLogin(&reqUserLogin, 0);
    });
    connect(mTraderCallBack,&DDuiTraderApi::signalRspUserLogin,[&](bool success){
        // 订阅行情
        qDebug()<<Q_FUNC_INFO<<success;
        // 端登成功,发出报单录入请求
        CThostFtdcInputOrderField ord;
        memset(&ord, 0, sizeof(ord));
        //经纪公司代码
        strcpy(ord.BrokerID, BROKER_ID);
        //投资者代码
        strcpy(ord.InvestorID, "12345");
        // 合约代码
        strcpy(ord.InstrumentID, "cn0601");
        ///报单引用
        strcpy(ord.OrderRef, "000000000001");
        // 用户代码
        strcpy(ord.UserID, USER_ID);
        // 报单价格条件
        ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        // 买卖方向
        ord.Direction = THOST_FTDC_D_Buy;
        // 组合开平标志
        strcpy(ord.CombOffsetFlag, "0");
        // 组合投机套保标志
        strcpy(ord.CombHedgeFlag, "1");
        // 价格
        ord.LimitPrice = 50000;
        // 数量
        ord.VolumeTotalOriginal = 10;
        // 有效期类型
        ord.TimeCondition = THOST_FTDC_TC_GFD;
        // GTD日期
        strcpy(ord.GTDDate, "");
        // 成交量类型
        ord.VolumeCondition = THOST_FTDC_VC_AV;
        // 最小成交量
        ord.MinVolume = 0;
        // 触发条件
        ord.ContingentCondition = THOST_FTDC_CC_Immediately;
        // 止损价
        ord.StopPrice = 0;
        // 强平原因
        ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
        // 自动挂起标志
        ord.IsAutoSuspend = 0;
        pTraderApi->ReqOrderInsert(&ord, 1);
    });
    connect(mMarketCallBack,&DDuiMarketDataApi::signalRspMarketData,[&](QString json){
        mFutrueView->updateMarketData(json);
    });
    connect(mFutrueView,&DDuiFutrueView::signalDataSub,[&](QString code,bool sub){
        if(code.isEmpty())return;
        subMarketData(QStringList()<<code,sub);
    });
}

void DDuiCTPWidget::createWidgets()
{
    mFutrueView = new DDuiFutrueView;
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(mFutrueView);
    lay->setSpacing(0);
    lay->setContentsMargins(0,0,0,0);
    setLayout(lay);
}
///
/// \brief DDuiCTPWidget::subMarketData
/// \param codeList
/// \param sub
/// 订阅行情和反订阅
///
void DDuiCTPWidget::subMarketData(const QStringList &codeList, bool sub)
{
    if(codeList.isEmpty() || codeList.size() >10)return;
    int index = 0;
    char* tmpIns = new char[codeList.size()];
    memset(tmpIns,0,sizeof(char*));
    for(QString code:codeList){
        strcpy(&tmpIns[index],code.toUtf8().data());
        index++;
    }
    if(sub){
        qDebug()<<"sub ok? "<<pMarketApi->SubscribeMarketData (&tmpIns,2);
    }else{
        qDebug()<<"unsub ok? "<<pMarketApi->UnSubscribeMarketData(&tmpIns,2);
    }
}
