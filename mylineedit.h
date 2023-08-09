#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>

class MyLineEdit : public QPlainTextEdit
{
public:
    MyLineEdit(QString fileName, QWidget *parent = nullptr);
    ~MyLineEdit();

    void handleWheelEvent(QWheelEvent *event);

protected:
//    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    QString fileName;
    QStringList fileContent;
    int currentLine;
    bool isPress = false;
    QPoint startPoint;

    void updateTextEdit();
};

#endif // MYLINEEDIT_H
