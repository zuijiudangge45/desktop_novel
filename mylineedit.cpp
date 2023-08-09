#include "mylineedit.h"

#include <QTextStream>
#include <QDebug>
#include <QScrollBar>
#include <QApplication>

MyLineEdit::MyLineEdit(QString fileName, QWidget *parent) : fileName(fileName), QPlainTextEdit(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);        //背景透明
    setGeometry(400, 400, 600, 150);
    setBackgroundVisible(false);
    setFrameStyle(QFrame::NoFrame);
    this->setObjectName("myLineEdit");
    this->setStyleSheet("#myLineEdit {"
                        "    background-color: rgba(110, 0, 0, 0);"
                        "    border: none;"
                        "    font-size: 12px;"
                        "    color: rgb(107, 154, 97); "
                        "    "
                        "}");
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 0px; }");
    this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    //
    //
    //
    //
    //
    //
    //
    QFile file(fileName); // 修改为你的文件名
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if(line.isEmpty())
            {
                continue;
            }
            fileContent.append(line);
            fileContent.append("\n");
        }
        file.close();
    }
    else
    {
        qDebug() << "error read!";
    }

    QFile file1("index.txt");
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file1);
        while (!in.atEnd())
        {
            currentLine = in.readLine().toInt();
            qDebug() << currentLine;
        }
        file1.close();
    }
    else
    {
        currentLine = 0;
    }


    updateTextEdit();

//    connect(this, &MyLineEdit::wheelEvent, this, &MyLineEdit::handleWheelEvent);

}

MyLineEdit::~MyLineEdit()
{
    qDebug() << __func__;

    QFile file("index.txt"); // 修改为你的文件名
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream out(&file);
        out << QString::number(currentLine) << "\n";
        file.close();
        qDebug() << "File written successfully!";
    }
    else
    {
        qDebug() << "Error opening file!";
    }

}


void MyLineEdit::handleWheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0 && currentLine > 0)
    {
        currentLine--;
        updateTextEdit();
    }
    else if (event->delta() < 0 && currentLine < fileContent.count() - 1)
    {
        currentLine++;
        updateTextEdit();
    }
}

void MyLineEdit::wheelEvent(QWheelEvent *e)
{
    handleWheelEvent(e);
}

void MyLineEdit::mousePressEvent(QMouseEvent *e)
{
    isPress = true;
    startPoint = e->pos();
}

void MyLineEdit::mouseReleaseEvent(QMouseEvent *e)
{
    if(isPress)
    {
        this->move(e->globalPos() - startPoint);
        isPress = false;
    }
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    static bool isHidden = false;
    if(!isHidden)
    {
//        this->hide();
        this->setStyleSheet("#myLineEdit { "
                            "background-color: rgba(110, 0, 0, 0);"
                            "border: none;"
                            "font-size: 12px;"
                            "color: rgba(107, 154, 97, 0)"
                            "}" );
        isHidden = true;
    }
    else
    {
//        this->show();
        this->setStyleSheet("#myLineEdit { "
                            "background-color: rgba(110, 0, 0, 0);"
                            "border: none;"
                            "font-size: 12px;"
                            "color: rgba(107, 154, 97, 1)"
                            "}" );
        isHidden = false;
    }
}

void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
    {
        currentLine--;
        updateTextEdit();
    }
    else if(event->key() == Qt::Key_Down)
    {
        currentLine++;
        updateTextEdit();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        qApp->quit();
    }
    else if(event->key() == Qt::Key_Space)
    {
        mouseDoubleClickEvent(nullptr);
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void MyLineEdit::updateTextEdit()
{
    QString visibleText = fileContent.mid(currentLine, 5).join(".");
    setPlainText(visibleText);
}
