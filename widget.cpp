#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include "parser.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("load file"), "", tr("Gcode (*.gcode);;All Files (*)"));
    ui->file_name_label->setText(filename);
}

void Widget::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Address Book"), "", tr("Gcode (*.gcode);;All Files (*)"));
    std::string stdOutFile = fileName.toUtf8().constData();
    std::string stdInFile = ui->file_name_label->text().toUtf8().constData();
    parseG(stdInFile, stdOutFile, this->commands);
}

void Widget::updataCommands() {
    QString qs;
    for (auto i : this->commands) {
        qs += QString::fromStdString(i);
        qs += " ";
    }
    ui->commands->setText(qs);
}
void Widget::on_AddButton_clicked()
{
    std::string add = ui->add_line->text().toUtf8().constData();
    this->commands.push_back(add);
    updataCommands();
    ui->add_line->clear();
}

void Widget::on_DeleteButton_clicked()
{
    std::string stdStr = ui->delete_line->text().toUtf8().constData();
    for (auto i = commands.begin(); i != commands.end(); i++) {
        if (*i == stdStr) {
            i = commands.erase(i);
        }
        if (i == commands.end()) break;
    }
    updataCommands();
    ui->delete_line->clear();
}

void Widget::on_ClearButton_clicked()
{
    this->commands.clear();
    updataCommands();
}
