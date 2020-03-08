#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QUrl>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QAction>
#include <QTabWidget>

class QWEVNode
{
public:
   QWebEngineView *QWEVTab;
   int TabIndex;
   QWEVNode *next;
   QWEVNode *prev;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    //QTabWidget *tabWidget;
    QWEVNode *qwevnode;
    QWebEngineView *currentWebView;
    QUrl Url;
    QUrl Url1;
private:
    //QWEVNode *qwevnode;
//    QWebEngineView *m_webEngineView;
    QLineEdit *urlLineEdit;
    QPushButton *backButton;
    QPushButton *faivButton;
    QPushButton *faivShow;
    QPushButton *tab;
    QTabWidget *tabWidget;
public slots:
    void faivWrite();
    void updateFaiv();
    void newtab();
    void tabSelected();
    void mySlot(QAction *action);
    void closeTab_(int index);


};

#endif // WIDGET_H
