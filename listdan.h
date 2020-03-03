#ifndef LISTDAN_H
#define LISTDAN_H

#include <QMainWindow>
#include <QMessageBox>
#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ListDan; }
QT_END_NAMESPACE

class ListDan : public QMainWindow
{
    Q_OBJECT

public:
    ListDan(QWidget *parent = nullptr);
    ~ListDan();
    void updateValues();

private slots:
    void on_pushbackBut_clicked();

    void on_pushfrontBut_clicked();

    void on_insertBut_clicked();

    void on_popback_clicked();

    void on_popfrontBut_clicked();

    void on_eraseBut_clicked();

    void on_clearBut_clicked();

    void on_insertionsortBut_clicked();

    void on_bubblesortBut_clicked();

    void on_averageBut_clicked();

private:
    Ui::ListDan *ui;
    List<int> mainList;
};
#endif // LISTDAN_H
