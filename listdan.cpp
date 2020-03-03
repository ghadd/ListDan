#include "listdan.h"
#include "ui_listdan.h"

ListDan::ListDan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListDan)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

ListDan::~ListDan()
{
    delete ui;
}

void ListDan::updateValues()
{
    ui->listWidget->clear();
    for (auto it = mainList.begin(); it != nullptr; it = it->next()){
        ui->listWidget->addItem(QString::number(it->value()));
    }
}


void ListDan::on_pushbackBut_clicked()
{
    this->mainList+=ui->pushbackLineEdit->text().toInt();
    updateValues();
}

void ListDan::on_pushfrontBut_clicked()
{
    this->mainList+ui->pushfrontLineEdit->text().toInt();
    updateValues();
}

void ListDan::on_insertBut_clicked()
{
    try{
        this->mainList.insert(ui->insertLineEdit->text().toInt(),
                              ui->insertLineEdit_2->text().toInt());
    } catch(std::out_of_range& exc){
        QMessageBox::information(this, "Info", exc.what());
    }

    updateValues();
}

void ListDan::on_popback_clicked()
{
    try {
        this->mainList--;
    } catch (std::out_of_range& exc) {
        QMessageBox::information(this, "Info", exc.what());
    }
    updateValues();
}

void ListDan::on_popfrontBut_clicked()
{
    try {
        --this->mainList;
    } catch (std::out_of_range& exc) {
        QMessageBox::information(this, "Info", exc.what());
    }
    updateValues();
}

void ListDan::on_eraseBut_clicked()
{
    try {
        this->mainList.erase(ui->eraseLineEdit->text().toInt());
    } catch (std::out_of_range& exc) {
        QMessageBox::information(this, "Info", exc.what());
    }
    updateValues();
}

void ListDan::on_clearBut_clicked()
{
    this->mainList.clear();
    updateValues();
}

void ListDan::on_insertionsortBut_clicked()
{
    this->mainList.insertionSort();
    updateValues();
}

void ListDan::on_bubblesortBut_clicked()
{
    this->mainList.bubbleSort();
    updateValues();
}

void ListDan::on_averageBut_clicked()
{
    try{
        ui->avgLabel->setText(" = " + QString::number(mainList.avg()));
    }
    catch (const std::exception&){
        ui->avgLabel->setText(" = undef");
    }
}
