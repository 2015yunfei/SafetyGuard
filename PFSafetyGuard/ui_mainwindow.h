/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *filePathTextEdit;
    QPushButton *openFileButton;
    QPushButton *tempButton;
    QPushButton *clsButton;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *infoTree;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *processName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *processID;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *processPriority;
    QLabel *label_3;
    QTextEdit *processModules;
    QPushButton *infoButton;
    QTextEdit *info;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 494);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 681, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        filePathTextEdit = new QTextEdit(horizontalLayoutWidget);
        filePathTextEdit->setObjectName(QString::fromUtf8("filePathTextEdit"));
        filePathTextEdit->setMaximumSize(QSize(16777215, 26));
        QFont font;
        font.setPointSize(10);
        filePathTextEdit->setFont(font);

        horizontalLayout->addWidget(filePathTextEdit);

        openFileButton = new QPushButton(horizontalLayoutWidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        openFileButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        openFileButton->setIcon(icon);

        horizontalLayout->addWidget(openFileButton);

        tempButton = new QPushButton(horizontalLayoutWidget);
        tempButton->setObjectName(QString::fromUtf8("tempButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/start.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tempButton->setIcon(icon1);

        horizontalLayout->addWidget(tempButton);

        clsButton = new QPushButton(horizontalLayoutWidget);
        clsButton->setObjectName(QString::fromUtf8("clsButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/cls.ico"), QSize(), QIcon::Normal, QIcon::Off);
        clsButton->setIcon(icon2);

        horizontalLayout->addWidget(clsButton);

        horizontalLayoutWidget_5 = new QWidget(centralwidget);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 50, 681, 431));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        infoTree = new QTreeWidget(horizontalLayoutWidget_5);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(1, font);
        __qtreewidgetitem->setFont(0, font);
        infoTree->setHeaderItem(__qtreewidgetitem);
        infoTree->setObjectName(QString::fromUtf8("infoTree"));

        horizontalLayout_6->addWidget(infoTree);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(horizontalLayoutWidget_5);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        processName = new QLabel(horizontalLayoutWidget_5);
        processName->setObjectName(QString::fromUtf8("processName"));

        horizontalLayout_3->addWidget(processName);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(horizontalLayoutWidget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        processID = new QLabel(horizontalLayoutWidget_5);
        processID->setObjectName(QString::fromUtf8("processID"));

        horizontalLayout_4->addWidget(processID);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(horizontalLayoutWidget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        processPriority = new QLabel(horizontalLayoutWidget_5);
        processPriority->setObjectName(QString::fromUtf8("processPriority"));

        horizontalLayout_5->addWidget(processPriority);


        verticalLayout_2->addLayout(horizontalLayout_5);

        label_3 = new QLabel(horizontalLayoutWidget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        processModules = new QTextEdit(horizontalLayoutWidget_5);
        processModules->setObjectName(QString::fromUtf8("processModules"));

        verticalLayout_2->addWidget(processModules);

        infoButton = new QPushButton(horizontalLayoutWidget_5);
        infoButton->setObjectName(QString::fromUtf8("infoButton"));
        infoButton->setIconSize(QSize(24, 24));

        verticalLayout_2->addWidget(infoButton);

        info = new QTextEdit(horizontalLayoutWidget_5);
        info->setObjectName(QString::fromUtf8("info"));

        verticalLayout_2->addWidget(info);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);
        verticalLayout_2->setStretch(4, 4);
        verticalLayout_2->setStretch(6, 2);

        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        openFileButton->setText(QApplication::translate("MainWindow", "open file", nullptr));
        tempButton->setText(QApplication::translate("MainWindow", "start", nullptr));
        clsButton->setText(QApplication::translate("MainWindow", "cls", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = infoTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "time/property", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Name", nullptr));
        label->setText(QApplication::translate("MainWindow", "processName\357\274\232", nullptr));
        processName->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "processID", nullptr));
        processID->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Process priority", nullptr));
        processPriority->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Process Modules", nullptr));
        infoButton->setText(QApplication::translate("MainWindow", "info", nullptr));
#ifndef QT_NO_SHORTCUT
        infoButton->setShortcut(QString());
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
