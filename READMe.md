---
layout:     post
title:      "基于Qt封装期货CTP接口"
subtitle:   " \"基于Qt框架的期货CTP\""
date:       2017-03-13
author:     "Tobyyi"
header-img: "http://www.chinabigdata.com/cn/img/banner1.jpg"
tags:
    - Qt
    - C++
    - CTP
---

> “Yeah It's on. ”

## CTP开发需要C++基础

 * 掌握必要的C++基础是学习和使用CTP框架的重要基石

## CTP能做什么

 * 最近几年，国内程序化交易技术爆发式发展，这得益于上期技术公司基于CTP柜台推出的交易API，使得用户可以随意开发自己的交易软件直接连接到交易柜台上进行交易，同时CTP API的设计模式也成为了许多其他柜台上交易API的设计标准。

 * 交易Api建立在Tcp协议上，实现了客户端和综合交易平台之间的双向异步通讯。行情Api可以运行在Tcp或者在Udp协议上，目前大部分还是用TCP连接。

 * CTP_API 是一个基于 C++的类库, 通过使用和扩展类库提供的接口来实现相关交易功能，包括报单与报价的录入、报单与报价的撤销、报单与报价的挂起、报单与报价的激活、报单与报价的修改、报单与报价的查询、成交单查询、投资者查询、投资者持仓查询、合约查询、交易日获取等。

## CTP系统架构

* 行情API

   * 行情订阅合约代码

* 交易API

   * 交易接口(Trader API)

   * 风控接口(Risk API)

   * 结算接口(CSV)

## 基于Qt的C++类行情接口实现


  * 继承CThostFtdcMdSpi的行情接口类 实现行情接口回调处理

  * 继承QObject 实现信号槽的连接


```
#ifndef DDUIMARKETDATAAPI_H
#define DDUIMARKETDATAAPI_H

#include <QObject>
#include <tradeapidll/32/ThostFtdcMdApi.h>
#include <tradeapidll/32/ThostFtdcUserApiStruct.h>
#include <dduictpconfig.h>

class DDuiMarketDataApi : public QObject
        ,public CThostFtdcMdSpi
{
    Q_OBJECT
public:
    explicit DDuiMarketDataApi(QObject *parent = 0);

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

    ///登录请求响应
     void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin
                                , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登出请求响应
     void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout
                                 , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
         void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅行情应答
     void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                    , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
     void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                      , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///订阅询价应答
     void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                     , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅询价应答
     void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument
                                       , CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
     void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

    ///询价通知
     void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

signals:
     //通知到其他模块
     void signalFrontConnected();
     void signalRspUserLogin(bool success);
};

#endif // DDUIMARKETDATAAPI_H

```

## 基于Qt的C++类交易接口实现

  * 继承CThostFtdcTraderSpi的交易接口类 实现交易接口回调处理

  * 继承QObject 实现信号槽的连接

```
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
     ///..............诸多接口回调

signals:
     void signalFrontConnected();
     void signalRspUserLogin(bool success);

};

#endif // DDUITRADERAPI_H

```

## Qt-CTP类的使用

    * 一个基于QApplication的app

    * QtWidgets类中使用

```

/// \brief DDuiCTPWidget::connectTraderServer
/// 初始化交易工作线程
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
/// 初始化行情接口的工作线程
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
    WaitForSingleObject(g_hEvent2,INFINITE);
}

```

## 注意事项

    * 开发者需要在[simnow官网](http://www.simnow.com.cn/)进行注册

    * BrokerID统一为：9999

    *  标准CTP：
        第一组：Trade Front：180.168.146.187:10000，Market Front：180.168.146.187:10010；【电信】

        第二组：Trade Front：180.168.146.187:10001，Market Front：180.168.146.187:10011；【电信】

        第三组：Trade Front：218.202.237.33 :10002，Market Front：218.202.237.33 :10012；【移动】

        交易阶段(服务时间)：与实际生产环境保持一致

    * 新注册用户，需要等到第二个交易日才能使用第二套环境


## 应用场景

* 方便Qt开发者关注业务逻辑实现
* 实现期货CTP客户端开发

## 有问题反馈

在使用中有任何问题，欢迎反馈给我，可以用以下联系方式跟我交流

* 邮件(373955953#qq.com, 把#换成@)
* QQ: 39559539234
* QQ群:312125701
* github: [@寒山-居士](https://github.com/toby20130333)

## 关于作者

```javascript

  var duoduozhijiao = {
    nickName  : "寒山-居士",
    site : "http://www.heilqt.com",
    blog : "http://blog.heilqt.com"
  }

```