/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *controlFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *statsButton;
    QPushButton *resetButton;
    QComboBox *algorithmComboBox;
    QLineEdit *findEdit;
    QComboBox *sizeComboBox;
    QLabel *statsLabel;
    QLabel *timeLabel;
    QLabel *speedLabel;
    QSlider *speedSlider;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(904, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        controlFrame = new QFrame(centralwidget);
        controlFrame->setObjectName(QString::fromUtf8("controlFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlFrame->sizePolicy().hasHeightForWidth());
        controlFrame->setSizePolicy(sizePolicy);
        controlFrame->setFrameShape(QFrame::StyledPanel);
        controlFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(controlFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        startButton = new QPushButton(controlFrame);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout->addWidget(startButton);

        statsButton = new QPushButton(controlFrame);
        statsButton->setObjectName(QString::fromUtf8("statsButton"));

        horizontalLayout->addWidget(statsButton);

        resetButton = new QPushButton(controlFrame);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        horizontalLayout->addWidget(resetButton);

        algorithmComboBox = new QComboBox(controlFrame);
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->setObjectName(QString::fromUtf8("algorithmComboBox"));

        horizontalLayout->addWidget(algorithmComboBox);

        findEdit = new QLineEdit(controlFrame);
        findEdit->setObjectName(QString::fromUtf8("findEdit"));
        findEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(findEdit);

        sizeComboBox = new QComboBox(controlFrame);
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->setObjectName(QString::fromUtf8("sizeComboBox"));

        horizontalLayout->addWidget(sizeComboBox);

        statsLabel = new QLabel(controlFrame);
        statsLabel->setObjectName(QString::fromUtf8("statsLabel"));

        horizontalLayout->addWidget(statsLabel);

        timeLabel = new QLabel(controlFrame);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        horizontalLayout->addWidget(timeLabel);

        speedLabel = new QLabel(controlFrame);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));

        horizontalLayout->addWidget(speedLabel);

        speedSlider = new QSlider(controlFrame);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setMinimum(1);
        speedSlider->setMaximum(100);
        speedSlider->setValue(100);
        speedSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(speedSlider);


        verticalLayout->addWidget(controlFrame);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sorting Visualizer", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        statsButton->setText(QCoreApplication::translate("MainWindow", "Show Stats", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        algorithmComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Bubble Sort", nullptr));
        algorithmComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Selection Sort", nullptr));
        algorithmComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Insertion Sort", nullptr));
        algorithmComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Quick Sort", nullptr));
        algorithmComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Merge Sort", nullptr));
        algorithmComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Shell Sort", nullptr));
        algorithmComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Linear Search", nullptr));
        algorithmComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Binary Search", nullptr));

        sizeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "10 Elements", nullptr));
        sizeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "100 Elements", nullptr));
        sizeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "1000 Elements", nullptr));

        statsLabel->setText(QCoreApplication::translate("MainWindow", "Swaps: 0 Comparisons: 0", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "delay ms: 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
