/********************************************************************************
** Form generated from reading UI file 'TexturePacking.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREPACKING_H
#define UI_TEXTUREPACKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TexturePackingClass
{
public:
    QWidget *centralWidget;
    QLineEdit *WidthEdit;
    QLineEdit *OptimalHeightEdit;
    QLineEdit *NumEdit;
    QLineEdit *IterEdit;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *calculateButton;
    QLineEdit *TimeEdit;
    QLineEdit *HeightEdit;
    QLineEdit *RatioEdit;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_6;
    QRadioButton *Algorithm_1;
    QRadioButton *Algorithm_2;
    QRadioButton *Algorithm_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *UltilizationEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TexturePackingClass)
    {
        if (TexturePackingClass->objectName().isEmpty())
            TexturePackingClass->setObjectName(QStringLiteral("TexturePackingClass"));
        TexturePackingClass->resize(1159, 1037);
        centralWidget = new QWidget(TexturePackingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WidthEdit = new QLineEdit(centralWidget);
        WidthEdit->setObjectName(QStringLiteral("WidthEdit"));
        WidthEdit->setGeometry(QRect(120, 60, 113, 31));
        OptimalHeightEdit = new QLineEdit(centralWidget);
        OptimalHeightEdit->setObjectName(QStringLiteral("OptimalHeightEdit"));
        OptimalHeightEdit->setGeometry(QRect(360, 60, 113, 31));
        NumEdit = new QLineEdit(centralWidget);
        NumEdit->setObjectName(QStringLiteral("NumEdit"));
        NumEdit->setGeometry(QRect(690, 60, 113, 31));
        IterEdit = new QLineEdit(centralWidget);
        IterEdit->setObjectName(QStringLiteral("IterEdit"));
        IterEdit->setGeometry(QRect(970, 60, 113, 31));
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(70, 60, 41, 24));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        label_1->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 60, 81, 24));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(9);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 70, 131, 24));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(870, 70, 81, 24));
        label_4->setFont(font);
        calculateButton = new QPushButton(centralWidget);
        calculateButton->setObjectName(QStringLiteral("calculateButton"));
        calculateButton->setGeometry(QRect(510, 510, 121, 31));
        calculateButton->setFont(font);
        TimeEdit = new QLineEdit(centralWidget);
        TimeEdit->setObjectName(QStringLiteral("TimeEdit"));
        TimeEdit->setGeometry(QRect(120, 110, 113, 31));
        HeightEdit = new QLineEdit(centralWidget);
        HeightEdit->setObjectName(QStringLiteral("HeightEdit"));
        HeightEdit->setGeometry(QRect(360, 110, 113, 31));
        RatioEdit = new QLineEdit(centralWidget);
        RatioEdit->setObjectName(QStringLiteral("RatioEdit"));
        RatioEdit->setGeometry(QRect(690, 110, 113, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 110, 91, 24));
        label->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(270, 110, 71, 24));
        label_5->setFont(font);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(530, 110, 121, 24));
        label_6->setFont(font);
        Algorithm_1 = new QRadioButton(centralWidget);
        Algorithm_1->setObjectName(QStringLiteral("Algorithm_1"));
        Algorithm_1->setGeometry(QRect(520, 330, 101, 28));
        Algorithm_1->setFont(font);
        Algorithm_2 = new QRadioButton(centralWidget);
        Algorithm_2->setObjectName(QStringLiteral("Algorithm_2"));
        Algorithm_2->setGeometry(QRect(520, 390, 71, 28));
        Algorithm_2->setFont(font);
        Algorithm_3 = new QRadioButton(centralWidget);
        Algorithm_3->setObjectName(QStringLiteral("Algorithm_3"));
        Algorithm_3->setGeometry(QRect(520, 450, 61, 28));
        Algorithm_3->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(80, 970, 161, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(14);
        label_7->setFont(font2);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(720, 960, 141, 31));
        label_8->setFont(font2);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(890, 120, 61, 24));
        label_9->setFont(font);
        UltilizationEdit = new QLineEdit(centralWidget);
        UltilizationEdit->setObjectName(QStringLiteral("UltilizationEdit"));
        UltilizationEdit->setGeometry(QRect(970, 110, 113, 31));
        TexturePackingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TexturePackingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1159, 23));
        TexturePackingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TexturePackingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TexturePackingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TexturePackingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TexturePackingClass->setStatusBar(statusBar);

        retranslateUi(TexturePackingClass);

        QMetaObject::connectSlotsByName(TexturePackingClass);
    } // setupUi

    void retranslateUi(QMainWindow *TexturePackingClass)
    {
        TexturePackingClass->setWindowTitle(QApplication::translate("TexturePackingClass", "TexturePacking", nullptr));
        label_1->setText(QApplication::translate("TexturePackingClass", "Width", nullptr));
        label_2->setText(QApplication::translate("TexturePackingClass", "Optimal height", nullptr));
        label_3->setText(QApplication::translate("TexturePackingClass", "Number of rectangles", nullptr));
        label_4->setText(QApplication::translate("TexturePackingClass", "iteration times", nullptr));
        calculateButton->setText(QApplication::translate("TexturePackingClass", "Calculate", nullptr));
        label->setText(QApplication::translate("TexturePackingClass", "Running Time", nullptr));
        label_5->setText(QApplication::translate("TexturePackingClass", "Height Now", nullptr));
        label_6->setText(QApplication::translate("TexturePackingClass", "Approximation Ratio", nullptr));
        Algorithm_1->setText(QApplication::translate("TexturePackingClass", "GRASP/VNS", nullptr));
        Algorithm_2->setText(QApplication::translate("TexturePackingClass", "FFDH", nullptr));
        Algorithm_3->setText(QApplication::translate("TexturePackingClass", "SAS", nullptr));
        label_7->setText(QApplication::translate("TexturePackingClass", "Algorithm Solution", nullptr));
        label_8->setText(QApplication::translate("TexturePackingClass", "Optimal Solution", nullptr));
        label_9->setText(QApplication::translate("TexturePackingClass", "ultilization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TexturePackingClass: public Ui_TexturePackingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREPACKING_H
