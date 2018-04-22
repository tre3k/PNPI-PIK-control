#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainWidget = new QWidget;
    textEdit = new QsciScintilla;
    outText = new QPlainTextEdit;
    listWidgetCommands = new QListWidget;
    lineEditSearch = new QLineEdit;

    /* read config */
    commandList.append("for i in range(start,end):");
    commandList.append("sleep(sec)");
    commandList.append("print(asctime())");
    commandList.append("print(\"var = \"+str(var))");
    commandList.append("motion_detector_z(pos)");
    commandList.append("while");

    helpAboutCommandList.append("simple loop, where \"i\" range from start to end");
    helpAboutCommandList.append("delay of sec");
    helpAboutCommandList.append("print current date");
    helpAboutCommandList.append("print variable");
    helpAboutCommandList.append("move detector ");
    helpAboutCommandList.append("loop while condition is true");

    /* ====== */

    textEdit->setUtf8(true);
    QsciLexerPython *lexerPy = new QsciLexerPython(this);
    lexerPy->setFont(QFont("monofur",12));
    QsciAPIs *apis = new QsciAPIs(lexerPy);
    for(int i=0;i<commandList.count();i++) apis->add(commandList.at(i));
    apis->prepare();
    lexerPy->setAPIs(apis);
    textEdit->setLexer(lexerPy);

    textEdit->setAutoIndent(true);
    textEdit->setIndentationGuides(true);
    textEdit->setIndentationsUseTabs(false);
    textEdit->setIndentationWidth(4);

    textEdit->setMarginsBackgroundColor(QColor("gainsboro"));
    textEdit->setMarginLineNumbers(1, true);
    textEdit->setMarginWidth(1, 50);

    textEdit->setAutoCompletionSource(QsciScintilla::AcsAll);
    textEdit->setAutoCompletionCaseSensitivity(true);
    textEdit->setAutoCompletionReplaceWord(true);
    textEdit->setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
    textEdit->setAutoCompletionThreshold(1);

    textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    textEdit->setMatchedBraceBackgroundColor(Qt::yellow);
    textEdit->setUnmatchedBraceForegroundColor(Qt::blue);

    textEdit->setCaretLineBackgroundColor(QColor("#eeeeee"));
    textEdit->setCaretLineVisible(true);

    textEdit->setToolTip("Write here your experement code");


    buttonRun = new QPushButton(labelButtonRun);
    buttonTest = new QPushButton(labelButtonTest);
    buttonRun->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    buttonTest->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));


    outText->setReadOnly(true);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonRun);
    buttonLayout->addWidget(buttonTest);
    buttonLayout->addStretch();

    QSplitter *splitter1 = new QSplitter;
    QSplitter *splitter2 = new QSplitter;

    QWidget *commandListWidget = new QWidget;
    QVBoxLayout *commandListLayout = new QVBoxLayout;

    commandListLayout->addWidget(lineEditSearch);
    commandListLayout->addWidget(listWidgetCommands);
    commandListWidget->setLayout(commandListLayout);

    splitter1->setOrientation(Qt::Vertical);
    splitter1->addWidget(textEdit);
    splitter1->addWidget(outText);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(commandListWidget);

    mainLayout->addWidget(splitter2);
    mainLayout->addLayout(buttonLayout);

    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);


    connect(buttonRun,SIGNAL(clicked(bool)),
            this,SLOT(slot_pushButtonRun()));
    connect(listWidgetCommands,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(slot_doubleClicOnList()));
    connect(listWidgetCommands,SIGNAL(clicked(QModelIndex)),
            this,SLOT(slot_setToolTipList()));


    for(int i=0;i<commandList.count();i++){
        listWidgetCommands->addItem(commandList.at(i));
    }

    thread = new run_thread();

    connect(this,SIGNAL(signal_sendParams(threadParams)),
            thread,SLOT(slot_reciveParams(threadParams)));
    connect(thread,SIGNAL(signal_errText(QString)),
            this,SLOT(slot_consoleErr(QString)));
    connect(thread,SIGNAL(signal_outText(QString)),
            this,SLOT(slot_consoleOut(QString)));
    connect(thread,SIGNAL(finished()),
            this,SLOT(slot_thread_end()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_pushButtonRun(){
    tP.InitFileName = initfile;
    tP.scriptText = textEdit->text();
    emit signal_sendParams(tP);

    if(thread==NULL) thread = new run_thread();

    if(!thread->isRunning()){
        thread->start();
        buttonRun->setText(labelButtonStop);
    }else{
        thread->terminate();
        buttonRun->setText(labelButtonRun);
    }

}

void MainWindow::slot_doubleClicOnList(){
    int i;
    for(i=0;i<listWidgetCommands->count();i++){
        if(listWidgetCommands->item(i)->isSelected()) break;
    }
    textEdit->insert(listWidgetCommands->item(i)->text());

}

void MainWindow::on_actionOpen_python_script_triggered()
{
    filename = QFileDialog::getOpenFileName(this,"Open python script","","(*.py)");
    if(filename=="") return;
    QFile f(filename);
    f.open(QIODevice::ReadOnly);

    QString text = "";
    char buff[1024];

    while(!f.atEnd()){
        f.readLine(buff,1024);
        text += QString(buff);
    }
    f.close();

    textEdit->setText(text);
}

void MainWindow::on_actionSave_python_script_triggered()
{
    if(filename==""){
        filename = QFileDialog::getSaveFileName(this,"Open python script","","(*.py)");
    }
    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly)){
        QMessageBox::critical(0,"Error open file","File did't open for save =(");
        return;
    }
    QTextStream stream(&f);
    stream << textEdit->text();
    f.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    filename = "";
    on_actionSave_python_script_triggered();
}

void MainWindow::on_actionNew_triggered()
{
    filename = QFileDialog::getSaveFileName(this,"Open python script","","(*.py)");
}

void MainWindow::on_actionE_xit_triggered()
{
    exit(0);
}

void MainWindow::slot_consoleOut(QString str){
    str.replace('\n',' ');
    if(str == ' ') return;
    outText->appendHtml("<font color=\"black\">"+str+"</font>");
}

void MainWindow::slot_consoleErr(QString str){
    str.replace('\n',' ');
    if(str == ' ') return;
    outText->appendHtml("<font color=\"red\">"+str+"</font>");
}

void MainWindow::slot_thread_end(){
    buttonRun->setText(labelButtonRun);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(0,"About","PNPI (c) 2018");
}

void MainWindow::slot_setToolTipList(){
    int index;
    for(index=0;index<listWidgetCommands->count();index++){
        if(listWidgetCommands->item(index)->isSelected()) break;
    }
    if(index>=helpAboutCommandList.count()) return;
    QString toolTipText = commandList.at(index)+" - "+
            helpAboutCommandList.at(index);
    listWidgetCommands->setToolTip(toolTipText);
    QToolTip::showText(QCursor::pos(),toolTipText);
}
