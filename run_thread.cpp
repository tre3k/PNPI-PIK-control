#include "run_thread.h"

run_thread::run_thread(){
    PythonQt::init();
    mainModule = PythonQt::self()->getMainModule();
}

void run_thread::run()
{
    connect(PythonQt::self(),SIGNAL(pythonStdErr(QString)),
            this,SLOT(slot_errText(QString)));
    connect(PythonQt::self(),SIGNAL(pythonStdOut(QString)),
            this,SLOT(slot_outText(QString)));

    if(mainModule.isNull()){
        qDebug () << "ERROR! run PythonQt mainModule";
        return;
    }
    mainModule.evalFile(params.InitFileName);
    mainModule.evalScript(params.scriptText);

    disconnect(PythonQt::self(),SIGNAL(pythonStdErr(QString)),
            this,SLOT(slot_errText(QString)));
    disconnect(PythonQt::self(),SIGNAL(pythonStdOut(QString)),
            this,SLOT(slot_outText(QString)));
    return;
}

void run_thread::slot_reciveParams(threadParams p){
    params = p;
    return;
}

void run_thread::slot_errText(QString str){
    emit signal_errText(str);
}

void run_thread::slot_outText(QString str){
    emit signal_outText(str);
}
