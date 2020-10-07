#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FFT.hpp"

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
    void makePlot(Complex *C, ul N);

    void on_calcButton_clicked();

    void on_rangeButton_clicked();

    void on_randomButton_clicked();

    void displayOutput(Complex C[], ul Size);

    void on_actionAbout_triggered();

    void initGraph();

    void on_graphTypeComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
