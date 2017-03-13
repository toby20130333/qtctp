#ifndef DDUIFUTRUEVIEW_H
#define DDUIFUTRUEVIEW_H

#include <QFrame>

namespace Ui {
class DDuiFutrueView;
}

class DDuiFutrueView : public QFrame
{
    Q_OBJECT
public:
    explicit DDuiFutrueView(QWidget *parent = 0);
    ~DDuiFutrueView();
signals:
    void signalDataSub(const QString& id=QString(""),bool sub=true);
public slots:
    void updateMarketData(const QString& json);
private slots:
    void on_pushButton_clicked();

private:
    Ui::DDuiFutrueView *ui;
};

#endif // DDUIFUTRUEVIEW_H
