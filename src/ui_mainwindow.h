/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEditNome;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QSpinBox *spinQuantita;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QComboBox *comboCategoria;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnAggiungi;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *comboFiltroCategoria;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QListWidget *listOggetti;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *labelTotale;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(570, 583);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEditNome = new QLineEdit(centralwidget);
        lineEditNome->setObjectName("lineEditNome");

        verticalLayout->addWidget(lineEditNome);


        verticalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        spinQuantita = new QSpinBox(centralwidget);
        spinQuantita->setObjectName("spinQuantita");

        verticalLayout_2->addWidget(spinQuantita);


        verticalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        comboCategoria = new QComboBox(centralwidget);
        comboCategoria->setObjectName("comboCategoria");

        verticalLayout_3->addWidget(comboCategoria);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        btnAggiungi = new QPushButton(centralwidget);
        btnAggiungi->setObjectName("btnAggiungi");

        verticalLayout_4->addWidget(btnAggiungi);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_6, 0, 0, 1, 1);


        verticalLayout_7->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        comboFiltroCategoria = new QComboBox(centralwidget);
        comboFiltroCategoria->setObjectName("comboFiltroCategoria");

        horizontalLayout_2->addWidget(comboFiltroCategoria);


        verticalLayout_7->addLayout(horizontalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        verticalLayout_5->addWidget(label_5);

        listOggetti = new QListWidget(centralwidget);
        listOggetti->setObjectName("listOggetti");

        verticalLayout_5->addWidget(listOggetti);


        verticalLayout_7->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        labelTotale = new QLabel(centralwidget);
        labelTotale->setObjectName("labelTotale");

        horizontalLayout_3->addWidget(labelTotale);


        verticalLayout_7->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 570, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nome", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Quantit\303\240", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Categoria", nullptr));
        btnAggiungi->setText(QCoreApplication::translate("MainWindow", "Aggiungi", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Filtro per categoria: ", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Lista:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Totale oggetti da acquistare:", nullptr));
        labelTotale->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
