#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <PythonQt/PythonQt.h>

#include <QTextStream>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QFileDialog>
#include <QDebug>
#include <QThread>
#include <QMessageBox>

#include <Qsci/qscilexerpython.h>
#include <Qsci/qsciscintilla.h>

#include "run_thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString labelButtonRun = "Run";
    QString labelButtonStop = "STOP!";
    QString labelButtonTest = "Test";

    QString filename;
    QString initfile="/home/kirill/coding/Qt5/PNPI/control/client_init.py";

    QWidget *mainWidget;
    QsciScintilla *textEdit;
    QListWidget *listWidgetCommands;
    QPlainTextEdit *outText;
    QLineEdit *lineEditSearch;

    QPushButton *buttonRun;
    QPushButton *buttonTest;

    threadParams tP;
    run_thread *thread;

private slots:
    void slot_pushButtonRun();
    void slot_doubleClicOnList();
    void slot_consoleOut(QString);
    void slot_thread_end();
    void on_actionOpen_python_script_triggered();
    void on_actionSave_python_script_triggered();
    void on_actionSave_as_triggered();
    void on_actionNew_triggered();
    void on_actionE_xit_triggered();


    void on_actionAbout_triggered();

signals:
    void signal_sendParams(threadParams);
};

#endif // MAINWINDOW_H
