#include <QApplication>
#include<QWidget>
#include"dduictpwidget.h"

void test(){
    char a[5]={'a','b','c','d'};
    char (*p1)[5]= &a;
    char (*p2)[5]=(char (*)[5])a;

    qDebug("a=%d\n",a);
    qDebug("a=%c\n",a[0]);
    qDebug("p1=%c\n",**p1);
    qDebug("p2=%c\n",**p2);
    qDebug("p1+1=%c\n",**(p1+1));
    qDebug("p2+1=%c\n",**(p2+1));
}

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    DDuiCTPWidget frameview;
    frameview.resize(600,400);
    frameview.show();
//    frameview.connectServer();
    return app.exec();
}
