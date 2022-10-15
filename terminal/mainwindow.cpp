#include "mainwindow.h"

//Dazhuang Teng 251052285
//10/5/2021
//this class will bulid a ui window and do the request job like compile the linux command and display the result and history
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(900,500);
    setWindowTitle("CommandGUI");
    commandQ = new QLabel ( "Please enter a command:");
    exit = new QLabel ( "Exit code: ");
    code = new QLabel(" ");//code number for exit code
    output = new QLabel("Result Output Area:");
    history = new QLabel("User Command History:");
    nothing = new QLabel("         ");//really doing nothing, just use it to fill some part of layout

    command_input = new QLineEdit();

    command_output = new QTextEdit();
    command_output -> setReadOnly(true);//set the ouput are to read only
    //show scroll bar
    command_output->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    command_output->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    command_output->setLineWrapMode(QTextEdit::NoWrap);

    command_history = new QListWidget();
    //show scroll bar
    command_history->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    command_history->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //set the signal when clicked one of the history item, the history result will display
    connect(command_history, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT (displayHistory()));

    runButton = new QPushButton("Run!", this);
    //set the signal, once click the buttion, the porgam will complie the input text
    connect(runButton, SIGNAL (clicked()),this, SLOT (handleButton()));
    connect(command_input, SIGNAL(returnPressed()), runButton, SIGNAL(clicked()), Qt::UniqueConnection);
    //runButton->setFocus();
    //runButton->setDefault(true);

    //the following are the layout setting, nothing special
    layoutpart1 = new QGridLayout();
    layoutpart2 = new QVBoxLayout();
    layoutpart3 = new QVBoxLayout();
    layoutpart4 = new QHBoxLayout();
    finallayout = new QHBoxLayout();
    this-> setCentralWidget(new QWidget());
    this-> centralWidget()->setLayout(finallayout);

    layoutpart1-> addWidget (commandQ,0, 0);
    layoutpart1-> addWidget(command_input,1,0);
    layoutpart1-> addWidget(runButton,1,1) ;

    layoutpart4-> addWidget(exit);
    layoutpart4-> addWidget(code);
    layoutpart4-> addWidget(nothing);
    layoutpart4-> addWidget(nothing);

    layoutpart2-> addLayout(layoutpart1);
    layoutpart2-> addWidget(history);
    layoutpart2-> addWidget(command_history);
    layoutpart2-> addLayout(layoutpart4);

    layoutpart3-> addWidget(output);
    layoutpart3-> addWidget(command_output);
    layoutpart3-> addWidget(nothing);

    finallayout-> addLayout(layoutpart2);
    finallayout-> addLayout(layoutpart3);

}

//Function:handleButton
//description: this method doing all the work with button, like compile the linux command, showing desplay result also show the hisoty command
//parameter: all comment by the side of the code
//return: this is a void, no reutrn
void MainWindow::handleButton()
{
    command* compiler = new command(command_input->text().toStdString());//make a object that connect to command class to do all the work
    compiler->execute();

    command_output->setText(QString::fromStdString(compiler->getResult()));//display the output from input linux command

    int itemNumber,lineNumber;
    itemNumber = command_history->count();//get all item total number, start with 0, will add 1 anytime when there is more item, this make sure the line number will be the same with the add order
    lineNumber = itemNumber + 1;//since the item have 0 at the beginning, and line numebr start with 1 just simply add 1

    historyText[itemNumber]= compiler->getResult();//add the history result same number as the line number, this way it can output the right history.
    historyText[1000-lineNumber]= compiler->getCodestring();//add history exit code, backward from this array

    std::string listItem = std::to_string(lineNumber)+ ". " + command_input->text().toStdString() + " ("+ compiler->getCodestring()+")";
    command_history->addItem(QString::fromStdString(listItem));

    code->setText(QString::fromStdString(compiler->getCodestring()));//change the exit code
}

//Function:displayHistory
//description:this method doing all history display work like, select one item and display its histry result
//parameter:itemnumber is the linenumber of select item
//return:void no return
void MainWindow::displayHistory(){
    int itemNumber;
    itemNumber = command_history->currentRow();//get the linenumber where the user selected
    command_output->setText(QString::fromStdString(historyText[itemNumber]));//becuase it all saved at the play where the save spot and line number are the same. output whatever in the linenumber.
    code->setText(QString::fromStdString(historyText[1000-itemNumber-1]));//change the exit code to the history code
}

//Funcation:displayHistory
//this is a destructor
MainWindow::~MainWindow()
{
}

