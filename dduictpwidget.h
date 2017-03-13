#ifndef DDUICTPWIDGET_H
#define DDUICTPWIDGET_H

#include <QWidget>
#include <windows.h>
#include "dduimarketdataapi.h"
#include "dduitraderapi.h"
#include <dduifutrueview.h>


#include <QHBoxLayout>
class DDuiCTPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DDuiCTPWidget(QWidget *parent = 0);
    ~DDuiCTPWidget();
    void connectServer();
signals:

public slots:
private:
    void connectTraderServer();
    void connectQuoteServer();
    void createConnect();
    void createWidgets();
    void subMarketData(const QStringList& code,bool sub = true);

    HANDLE  g_hEvent;
    HANDLE  g_hEvent2;
    CThostFtdcMdApi *pMarketApi;
    CThostFtdcTraderApi *pTraderApi;
    DDuiMarketDataApi *mMarketCallBack;
    DDuiTraderApi *mTraderCallBack;

    static  char* Instrumnet[];
    DDuiFutrueView *mFutrueView;
};

#endif // DDUICTPWIDGET_H
