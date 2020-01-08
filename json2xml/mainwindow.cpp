#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include"jsonfile.h"
#include "filefactory.h"
#include "ifile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    _isJsonToXml = true;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_translateButton_clicked() {
    QString value = ui->inputTextEdit->toPlainText();

    FileFactory fileFactory;
    IFile *file = fileFactory.createFileByFlag(_isJsonToXml);

    QString xml = _translateText(value, file);

    ui->outputTextEdit->setText(xml);
}

void MainWindow::on_changeDirectionButton_clicked() {
    _isJsonToXml = !_isJsonToXml;
    _swapLabels();
}

QString MainWindow::_translateText(QString text, IFile *file) {
    QByteArray byteArray(text.toStdString().c_str(), text.length());
    file->parse(byteArray);
    return file->translate().toStdString().c_str();
}

void MainWindow::_swapLabels() {
    QString temp = ui->inputLabel->text();
    ui->inputLabel->setText(ui->outputLabel->text());
    ui->outputLabel->setText(temp);
}
