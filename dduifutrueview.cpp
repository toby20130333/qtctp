#include "dduifutrueview.h"
#include "ui_dduifutrueview.h"

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
    ui->textBrowser->append(json);
}

void DDuiFutrueView::on_pushButton_clicked()
{
    emit signalDataSub(ui->lineEdit->text().trimmed());
}
