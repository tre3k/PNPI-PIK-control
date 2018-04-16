#ifndef RUN_THREAD_H
#define RUN_THREAD_H

#include <QThread>
#include <QApplication>
#include <QDebug>
#include <PythonQt/PythonQt.h>

struct threadParams{
    QString InitFileName;
    QString scriptText;
    PythonQtObjectPtr mainModule;
};

class run_thread : public QThread
{
    Q_OBJECT
public:
    run_thread();
private:
    threadParams params;
    PythonQtObjectPtr mainModule;
protected:
    void run();
signals:
    void signal_outText(QString);
    void signal_errText(QString);
public slots:
    void slot_reciveParams(threadParams);
    void slot_outText(QString);
    void slot_errText(QString);
};

#endif // RUN_THREAD_H
