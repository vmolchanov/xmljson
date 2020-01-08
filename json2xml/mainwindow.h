#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_translateButton_clicked();

    void on_changeDirectionButton_clicked();

private:
    Ui::MainWindow *ui;

    bool _isJsonToXml;

    QString _translateText(QString text, File *file);

    void _swapLabels();
};
#endif // MAINWINDOW_H
