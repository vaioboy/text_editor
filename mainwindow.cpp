#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->textEdit);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time_function()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_function()
{
    QTime time = QTime::currentTime();
    QString time_string = time.toString("hh:mm:ss");
    ui->statusBar->showMessage(time_string);
}

void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Open", "/home", "All files(*.*);;Text files(*.txt)");
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
//        QMessageBox::warning(this, "Warning", "Cannot open file");
        return;
    }
    QString text = file.readAll();
    ui->textEdit->setPlainText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if(file_path == ""){
        file_path = QFileDialog::getSaveFileName(this, "Save", "/home", "All file(*.*);;Text file(*.txt)");
    }
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
//        QMessageBox::warning(this, "Warning", "Cannot save file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    file_path = QFileDialog::getSaveFileName(this, "Save", "/home", "All file(*.*);;Text file(*.txt)");
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
//        QMessageBox::warning(this, "Warning", "Cannot save file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow::on_actionAbout_Text_Editor_triggered()
{
    QMessageBox::information(this, "About", "This is Bob's Qt Text Edit Demo");
}
