#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FFT.hpp"
#include <algorithm>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::initGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraph()
{

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    ui->customPlot->graph(0)->setName("Real");
    ui->customPlot->graph(1)->setName("Imaginary");


    ui->customPlot->graph(0)->setPen(QPen(Qt::red, 3.0));
    ui->customPlot->graph(1)->setPen(QPen(Qt::blue, 3.0));

    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Magnitude");

    ui->customPlot->xAxis->setTickLabelFont(QFont("Helvetica", 8));
    ui->customPlot->yAxis->setTickLabelFont(QFont("Helvetica", 8));

    ui->customPlot->xAxis->setLabelFont(QFont("Helvetica", 12));
    ui->customPlot->yAxis->setLabelFont(QFont("Helvetica", 12));

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 14));
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems);


}


void MainWindow::makePlot(Complex *C, ul N)
{

    QVector<double> x, y_real, y_imag;
    x.reserve(N);
    y_real.reserve(N);
    y_imag.reserve(N);

    for(ul i =0; i < N; i++)
    {
        y_real.push_back(C[i].real());
        y_imag.push_back(C[i].imag());
        x.push_back(i);
    }

    double min = findMin(y_real, y_imag);
    double max = findMax(y_real, y_imag);

    min -= (10 - (int(min) % 10));
    max += (10 - (int(max) % 10));


    // set axes ranges, so we see all data:
    ui->customPlot->graph(0)->setData(x, y_real);
    ui->customPlot->graph(1)->setData(x, y_imag);

    ui->customPlot->xAxis->setRange(0, N);
    ui->customPlot->yAxis->setRange(min, max);

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);

    //ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->replot();


}


void MainWindow::on_calcButton_clicked()
{
    QString input_real_string = ui->input_real->toPlainText().trimmed();
    QString input_imag_string = ui->input_imag->toPlainText().trimmed();

    ul inputSize = findLength(input_real_string);
    std::vector<Complex> C;
    Complex A[inputSize];

    C.reserve(inputSize);
    C = parseInput(input_real_string, input_imag_string);

    std::copy(C.begin(), C.end(), A);
    Calculate(A, inputSize);

    displayOutput(A, inputSize);

    makePlot(A, inputSize);

}


// For expansion
void MainWindow::on_rangeButton_clicked()
{
    QString input_real_string = ui->input_real->toPlainText().trimmed();
    QString input_imag_string = ui->input_imag->toPlainText().trimmed();

    double real_start = input_real_string.toDouble();
    double imag_start = input_imag_string.toDouble();


}


void MainWindow::displayOutput(Complex C[], ul Size)
{
    QString output_real;
    QString output_imag;

    for(ul i =0; i < Size; i++)
    {
        output_real += QString::number(C[i].real(), 'f', 4) + "\n";
        output_imag += QString::number(C[i].imag(), 'f', 4) + "\n";
    }

    ui->output_real->setText(output_real);
    ui->output_imag->setText(output_imag);
}


// Generate Random data of size N and output the value
void MainWindow::on_randomButton_clicked()
{
    try
    {
    // Need to take input from input_real because for some reason qt won't add new widget
    ul Size = ui->sizeInput->toPlainText().toUInt();
    //unsigned long Steps = ui->stepsInput->toPlainText().toUInt();
    if(!Size)
        throw RandomInputEmpty();

    // Generate Complex of Size
    Complex C[Size];
    //Random number generator with seed
    QRandomGenerator rd(QDateTime::currentMSecsSinceEpoch());

    // Generate N random Numbers
    for(ul i =0; i< Size; i++)
    {
        C[i] = Complex(rd.generate(), rd.generate());
    }


    // Because qt won't allow you to pass a ui element to another function
    // I need to read the docs
    QString output_real;
    QString output_imag;

    //  Generate string
    for(ul i =0; i < Size; i++)
    {
        output_real += QString::number(C[i].real(), 'f', 4) + "\n";
        output_imag += QString::number(C[i].imag(), 'f', 4) + "\n";
    }

    // Output to input
    ui->input_real->setText(output_real);
    ui->input_imag->setText(output_imag);

    // Calculate
    Calculate(C, Size);

    // Display output
    displayOutput(C, Size);

    // Generate plot
    makePlot(C, Size);
    }
    catch (RandomInputEmpty e)
    {
        showMessage("Invalid input", "Invalid input");
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox MsgBox;
    MsgBox.setWindowTitle("About");
    MsgBox.setText("Developed by: Ajaykumar Nair\nCopyright: 2020\nLicense: MIT");
    MsgBox.button(MsgBox.Ok);
    MsgBox.exec();
}

void MainWindow::on_graphTypeComboBox_currentIndexChanged(int index)
{
    QCPGraph::LineStyle GraphStyle = QCPGraph::lsLine;

    switch(index)
    {
        case 0:
            GraphStyle = QCPGraph::lsLine;
        break;

        case 1:
            GraphStyle = QCPGraph::lsImpulse;
        break;

        case 2:
            GraphStyle = QCPGraph::lsStepCenter;
        break;

        case 3:
            GraphStyle = QCPGraph::lsStepLeft;
        break;

        case 4:
            GraphStyle = QCPGraph::lsStepRight;
        break;
    }
    ui->customPlot->graph(0)->setLineStyle(GraphStyle);
    ui->customPlot->graph(1)->setLineStyle(GraphStyle);
    ui->customPlot->replot();
}
