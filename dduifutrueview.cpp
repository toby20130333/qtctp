#include "dduifutrueview.h"
#include "ui_dduifutrueview.h"
#include <QDebug>

DDuiFutrueView::DDuiFutrueView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DDuiFutrueView)
{
    ui->setupUi(this);
}

DDuiFutrueView::~DDuiFutrueView()
{
    delete ui;
}

void DDuiFutrueView::updateMarketData(const QString &json)
{
//    qDebug()<<Q_FUNC_INFO<<json;
    ui->plainTextEdit->appendHtml(json);
}

void DDuiFutrueView::on_pushButton_clicked()
{
    emit signalDataSub(ui->lineEdit->text().trimmed());
}
