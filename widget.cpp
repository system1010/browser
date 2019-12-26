#include "widget.h"
#include <QTimer>
#include <QToolButton>
#include <QLabel>
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    qwevnode = new QWEVNode();
    qwevnode->QWEVTab = new QWebEngineView;
    qwevnode->QWEVTab->load(QUrl(QStringLiteral("https://google.ru")));
    qwevnode->QWEVTab->show();
    qwevnode->TabIndex = 0;
    currentWebView = qwevnode->QWEVTab;
    tabWidget = new QTabWidget;
    tabWidget->addTab(qwevnode->QWEVTab, tr("https://google.ru"));
    tabWidget->setTabsClosable(true);
    urlLineEdit = new QLineEdit;
    backButton = new QPushButton;
    backButton->setText("<<");
    faivButton = new QPushButton;
    faivButton->setText("add2faiv");
    faivShow = new QPushButton;
    faivShow->setText("faiv");
    QMenu *menu= new QMenu;
    faivShow->setMenu(menu);
    menu->show();
    tab = new QPushButton;
    tab->setText("newtab");
    tab->show();
    updateFaiv();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(backButton, 0, 0);
    layout->addWidget(faivButton, 0, 1);
    layout->addWidget(faivShow, 0 , 2);
    layout->addWidget(tab, 0, 3);
    layout->addWidget(urlLineEdit, 0, 4, 1, 55);
    layout->addWidget(tabWidget, 1, 0, 1, 59);
    setLayout(layout);
    connect(urlLineEdit, &QLineEdit::returnPressed, [this]{currentWebView->load(QUrl(urlLineEdit->text()));    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());
});
    connect(currentWebView, &QWebEngineView::urlChanged, [this]{urlLineEdit->setText(currentWebView->url().toString());    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());
});
    connect(backButton, &QPushButton::clicked, [this]{currentWebView->page()->triggerAction(QWebEnginePage::Back);    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());
});
    connect(faivButton, SIGNAL(clicked()), this, SLOT(faivWrite()));
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(mySlot(QAction*)));
    connect(tab, SIGNAL(clicked()), this, SLOT(newtab()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab_(int)));
    //connect(currentWebView, &QWebEngineView::urlChanged, [this](const QUrl &url)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this,timer]{if (Url1==Url)currentWebView->load(Url);timer->stop();Url=NULL;Url1=NULL;});
    connect(currentWebView->page(), &QWebEnginePage::linkHovered, [this, timer](const QString &url) {
        if(!url.isEmpty()){
        Url1=url;
        timer->start(2000);
        Url = url;
        }else timer->stop();
    });
}


void Widget::closeTab_(int index)
{
// Remove the tab using removeTab(). Be aware that the
// page widget itself is not deleted!
    tabWidget->removeTab(index);

    // OR (do NOT do both)

    // Delete the page widget, which automatically removes
    // the tab as well.
    //delete tabWidget_->widget(index);
}


void Widget::mySlot(QAction *action) {
    currentWebView->load(action->text());
    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());
    urlLineEdit->setText(currentWebView->url().toString());
    updateFaiv();
}

void Widget::updateFaiv()
{
    QFile file("/root/.faiv");
    file.open(QIODevice::ReadOnly);
    QTextStream writeStream(&file);
    faivShow->menu()->clear();
    while (!writeStream.atEnd()){
        QAction *action=new QAction;
        action->setText(writeStream.readLine());
        faivShow->menu()->addAction(action);
    }
    file.close();
}

void Widget::newtab()
{
    QWEVNode *head = new QWEVNode();
    QWEVNode *prev = new QWEVNode();
    for (head=qwevnode;head;head = head->next)
        if (head) prev = head;//qDebug()<< head->TabIndex;}
    head=new QWEVNode();
    head->QWEVTab = new QWebEngineView;
    head->TabIndex = tabWidget->count();
    prev->next=head;
    head->next=NULL;
    head->prev=prev;
    tabWidget->addTab(head->QWEVTab, tr("TabWidget"));
    currentWebView = head->QWEVTab;
    currentWebView->load(QUrl(QStringLiteral("https://google.ru")));
    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());


 }

void Widget::tabSelected()
{
    QWEVNode *head = new QWEVNode();
    for (head=qwevnode;!(tabWidget->currentIndex()==head->TabIndex);head = head->next){}
    currentWebView = head->QWEVTab;
    urlLineEdit->setText(currentWebView->url().toString());
    tabWidget->setTabText(tabWidget->currentIndex(),urlLineEdit->text());
    //currentWebView->load(QUrl(QStringLiteral("https://google.ru")));
    //qDebug() << tabWidget->currentIndex();
}
void Widget::faivWrite()
{
    QFile file("/root/.faiv");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream writeStream(&file);
    writeStream << urlLineEdit->text() <<endl;
    file.close();
    updateFaiv();

}

