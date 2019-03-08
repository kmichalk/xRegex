/********************************************************************************
** Form generated from reading UI file 'RegexEngineTester.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGEXENGINETESTER_H
#define UI_REGEXENGINETESTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegexEngineTesterClass
{
public:
    QWidget *centralWidget;
    QFrame *frame_main;
    QGroupBox *groupBox_regexEngineChoice;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_groupBox_regexEngineChoice;
    QRadioButton *radioButton_xRegex;
    QRadioButton *radioButton_stdRegex;
    QRadioButton *radioButton_QRegularExpression;
    QRadioButton *radioButton_BoostRegex;
    QLabel *label_regex;
    QTextEdit *textEdit_input;
    QLabel *label_input;
    QTextEdit *textEdit_results;
    QPushButton *pushButton_search;
    QCheckBox *checkBox_saveState;
    QPushButton *pushButton_save;
    QLabel *label_iterations;
    QPushButton *pushButton_load;
    QPushButton *pushButton_match;
    QLineEdit *lineEdit_iterations;
    QCheckBox *checkBox_highlight;
    QPushButton *pushButton_random;
    QLineEdit *lineEdit_symbols;
    QLineEdit *lineEdit_lengthRange;
    QPushButton *pushButton_test;
    QGroupBox *groupBox_modeChoice;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_groupBox_modeChoice;
    QRadioButton *radioButton_standardTest;
    QRadioButton *radioButton_automatedTest;
    QTextEdit *textEdit_regex;
    QCheckBox *checkBox_regexLineWrap;
    QCheckBox *checkBox_inputLineWrap;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RegexEngineTesterClass)
    {
        if (RegexEngineTesterClass->objectName().isEmpty())
            RegexEngineTesterClass->setObjectName(QStringLiteral("RegexEngineTesterClass"));
        RegexEngineTesterClass->resize(675, 832);
        RegexEngineTesterClass->setStyleSheet(QLatin1String("QWidget {\n"
"	background-color: #3A3A3A;\n"
"	color: #BBBBBB;\n"
"}\n"
"QGroupBox {	\n"
"	border: 1px solid #505050;\n"
"}\n"
"QLabel {\n"
"	color: #BBBBBB;\n"
"}\n"
"QLineEdit { \n"
"	color: #BEBEBE;\n"
"	background-color: #323232;\n"
"	selection-color: #101010;\n"
"	selection-background-color: #8398ba;\n"
"	border: 1px solid #505050;\n"
"}\n"
"QTextEdit { \n"
"	color: #BEBEBE;\n"
"	background-color: #323232;\n"
"	selection-color: #101010;\n"
"	selection-background-color: #8398ba;\n"
"	border: 1px solid #505050;\n"
"}\n"
"QPushButton {\n"
"	background-color: #424242;\n"
"}"));
        centralWidget = new QWidget(RegexEngineTesterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        frame_main = new QFrame(centralWidget);
        frame_main->setObjectName(QStringLiteral("frame_main"));
        frame_main->setGeometry(QRect(5, 5, 662, 766));
        frame_main->setFrameShape(QFrame::StyledPanel);
        frame_main->setFrameShadow(QFrame::Raised);
        groupBox_regexEngineChoice = new QGroupBox(frame_main);
        groupBox_regexEngineChoice->setObjectName(QStringLiteral("groupBox_regexEngineChoice"));
        groupBox_regexEngineChoice->setGeometry(QRect(5, 0, 651, 41));
        layoutWidget = new QWidget(groupBox_regexEngineChoice);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(5, 15, 641, 19));
        horizontalLayout_groupBox_regexEngineChoice = new QHBoxLayout(layoutWidget);
        horizontalLayout_groupBox_regexEngineChoice->setSpacing(6);
        horizontalLayout_groupBox_regexEngineChoice->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_groupBox_regexEngineChoice->setObjectName(QStringLiteral("horizontalLayout_groupBox_regexEngineChoice"));
        horizontalLayout_groupBox_regexEngineChoice->setContentsMargins(0, 0, 0, 0);
        radioButton_xRegex = new QRadioButton(layoutWidget);
        radioButton_xRegex->setObjectName(QStringLiteral("radioButton_xRegex"));
        radioButton_xRegex->setChecked(true);

        horizontalLayout_groupBox_regexEngineChoice->addWidget(radioButton_xRegex);

        radioButton_stdRegex = new QRadioButton(layoutWidget);
        radioButton_stdRegex->setObjectName(QStringLiteral("radioButton_stdRegex"));
        radioButton_stdRegex->setCheckable(true);
        radioButton_stdRegex->setChecked(false);

        horizontalLayout_groupBox_regexEngineChoice->addWidget(radioButton_stdRegex);

        radioButton_QRegularExpression = new QRadioButton(layoutWidget);
        radioButton_QRegularExpression->setObjectName(QStringLiteral("radioButton_QRegularExpression"));

        horizontalLayout_groupBox_regexEngineChoice->addWidget(radioButton_QRegularExpression);

        radioButton_BoostRegex = new QRadioButton(layoutWidget);
        radioButton_BoostRegex->setObjectName(QStringLiteral("radioButton_BoostRegex"));

        horizontalLayout_groupBox_regexEngineChoice->addWidget(radioButton_BoostRegex);

        label_regex = new QLabel(frame_main);
        label_regex->setObjectName(QStringLiteral("label_regex"));
        label_regex->setGeometry(QRect(10, 90, 47, 13));
        textEdit_input = new QTextEdit(frame_main);
        textEdit_input->setObjectName(QStringLiteral("textEdit_input"));
        textEdit_input->setGeometry(QRect(10, 190, 641, 291));
        textEdit_input->setStyleSheet(QStringLiteral(""));
        textEdit_input->setLineWrapMode(QTextEdit::NoWrap);
        label_input = new QLabel(frame_main);
        label_input->setObjectName(QStringLiteral("label_input"));
        label_input->setGeometry(QRect(10, 170, 47, 13));
        textEdit_results = new QTextEdit(frame_main);
        textEdit_results->setObjectName(QStringLiteral("textEdit_results"));
        textEdit_results->setGeometry(QRect(10, 484, 641, 161));
        textEdit_results->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        pushButton_search = new QPushButton(frame_main);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(575, 680, 75, 23));
        checkBox_saveState = new QCheckBox(frame_main);
        checkBox_saveState->setObjectName(QStringLiteral("checkBox_saveState"));
        checkBox_saveState->setGeometry(QRect(10, 650, 70, 17));
        pushButton_save = new QPushButton(frame_main);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(10, 675, 75, 23));
        label_iterations = new QLabel(frame_main);
        label_iterations->setObjectName(QStringLiteral("label_iterations"));
        label_iterations->setGeometry(QRect(415, 690, 75, 13));
        pushButton_load = new QPushButton(frame_main);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(10, 705, 75, 23));
        pushButton_match = new QPushButton(frame_main);
        pushButton_match->setObjectName(QStringLiteral("pushButton_match"));
        pushButton_match->setGeometry(QRect(575, 650, 75, 23));
        lineEdit_iterations = new QLineEdit(frame_main);
        lineEdit_iterations->setObjectName(QStringLiteral("lineEdit_iterations"));
        lineEdit_iterations->setGeometry(QRect(495, 680, 75, 20));
        lineEdit_iterations->setStyleSheet(QStringLiteral(""));
        checkBox_highlight = new QCheckBox(frame_main);
        checkBox_highlight->setObjectName(QStringLiteral("checkBox_highlight"));
        checkBox_highlight->setGeometry(QRect(100, 650, 70, 17));
        checkBox_highlight->setChecked(true);
        pushButton_random = new QPushButton(frame_main);
        pushButton_random->setObjectName(QStringLiteral("pushButton_random"));
        pushButton_random->setGeometry(QRect(575, 710, 75, 23));
        lineEdit_symbols = new QLineEdit(frame_main);
        lineEdit_symbols->setObjectName(QStringLiteral("lineEdit_symbols"));
        lineEdit_symbols->setGeometry(QRect(415, 710, 75, 20));
        lineEdit_symbols->setStyleSheet(QStringLiteral(""));
        lineEdit_lengthRange = new QLineEdit(frame_main);
        lineEdit_lengthRange->setObjectName(QStringLiteral("lineEdit_lengthRange"));
        lineEdit_lengthRange->setGeometry(QRect(495, 710, 75, 20));
        lineEdit_lengthRange->setStyleSheet(QStringLiteral(""));
        pushButton_test = new QPushButton(frame_main);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));
        pushButton_test->setGeometry(QRect(575, 740, 75, 23));
        groupBox_modeChoice = new QGroupBox(frame_main);
        groupBox_modeChoice->setObjectName(QStringLiteral("groupBox_modeChoice"));
        groupBox_modeChoice->setGeometry(QRect(5, 45, 651, 41));
        layoutWidget_2 = new QWidget(groupBox_modeChoice);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(5, 15, 641, 19));
        horizontalLayout_groupBox_modeChoice = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_groupBox_modeChoice->setSpacing(6);
        horizontalLayout_groupBox_modeChoice->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_groupBox_modeChoice->setObjectName(QStringLiteral("horizontalLayout_groupBox_modeChoice"));
        horizontalLayout_groupBox_modeChoice->setContentsMargins(0, 0, 0, 0);
        radioButton_standardTest = new QRadioButton(layoutWidget_2);
        radioButton_standardTest->setObjectName(QStringLiteral("radioButton_standardTest"));
        radioButton_standardTest->setChecked(true);

        horizontalLayout_groupBox_modeChoice->addWidget(radioButton_standardTest);

        radioButton_automatedTest = new QRadioButton(layoutWidget_2);
        radioButton_automatedTest->setObjectName(QStringLiteral("radioButton_automatedTest"));
        radioButton_automatedTest->setCheckable(true);
        radioButton_automatedTest->setChecked(false);

        horizontalLayout_groupBox_modeChoice->addWidget(radioButton_automatedTest);

        textEdit_regex = new QTextEdit(frame_main);
        textEdit_regex->setObjectName(QStringLiteral("textEdit_regex"));
        textEdit_regex->setGeometry(QRect(10, 110, 640, 55));
        textEdit_regex->setLineWrapMode(QTextEdit::NoWrap);
        checkBox_regexLineWrap = new QCheckBox(frame_main);
        checkBox_regexLineWrap->setObjectName(QStringLiteral("checkBox_regexLineWrap"));
        checkBox_regexLineWrap->setGeometry(QRect(55, 90, 70, 17));
        checkBox_inputLineWrap = new QCheckBox(frame_main);
        checkBox_inputLineWrap->setObjectName(QStringLiteral("checkBox_inputLineWrap"));
        checkBox_inputLineWrap->setGeometry(QRect(55, 170, 70, 17));
        RegexEngineTesterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RegexEngineTesterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 675, 21));
        RegexEngineTesterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RegexEngineTesterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RegexEngineTesterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RegexEngineTesterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RegexEngineTesterClass->setStatusBar(statusBar);

        retranslateUi(RegexEngineTesterClass);

        QMetaObject::connectSlotsByName(RegexEngineTesterClass);
    } // setupUi

    void retranslateUi(QMainWindow *RegexEngineTesterClass)
    {
        RegexEngineTesterClass->setWindowTitle(QApplication::translate("RegexEngineTesterClass", "RegexEngineTester", Q_NULLPTR));
        groupBox_regexEngineChoice->setTitle(QApplication::translate("RegexEngineTesterClass", "regex engine:", Q_NULLPTR));
        radioButton_xRegex->setText(QApplication::translate("RegexEngineTesterClass", "x::regex", Q_NULLPTR));
        radioButton_stdRegex->setText(QApplication::translate("RegexEngineTesterClass", "std::regex", Q_NULLPTR));
        radioButton_QRegularExpression->setText(QApplication::translate("RegexEngineTesterClass", "QRegularExpression", Q_NULLPTR));
        radioButton_BoostRegex->setText(QApplication::translate("RegexEngineTesterClass", "Boost.Regex", Q_NULLPTR));
        label_regex->setText(QApplication::translate("RegexEngineTesterClass", "regex:", Q_NULLPTR));
        textEdit_input->setHtml(QApplication::translate("RegexEngineTesterClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">aab</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">abbbb</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">bbabaabba</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">acbbcbabbccba</p></body></html>", Q_NULLPTR));
        label_input->setText(QApplication::translate("RegexEngineTesterClass", "input:", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("RegexEngineTesterClass", "Search", Q_NULLPTR));
        checkBox_saveState->setText(QApplication::translate("RegexEngineTesterClass", "save state", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("RegexEngineTesterClass", "Save", Q_NULLPTR));
        label_iterations->setText(QApplication::translate("RegexEngineTesterClass", "iterations:", Q_NULLPTR));
        pushButton_load->setText(QApplication::translate("RegexEngineTesterClass", "Load", Q_NULLPTR));
        pushButton_match->setText(QApplication::translate("RegexEngineTesterClass", "Match", Q_NULLPTR));
        lineEdit_iterations->setText(QApplication::translate("RegexEngineTesterClass", "1", Q_NULLPTR));
        checkBox_highlight->setText(QApplication::translate("RegexEngineTesterClass", "highlight", Q_NULLPTR));
        pushButton_random->setText(QApplication::translate("RegexEngineTesterClass", "Random", Q_NULLPTR));
        lineEdit_symbols->setText(QApplication::translate("RegexEngineTesterClass", "abc", Q_NULLPTR));
        lineEdit_lengthRange->setText(QApplication::translate("RegexEngineTesterClass", "1000 1-5", Q_NULLPTR));
        pushButton_test->setText(QApplication::translate("RegexEngineTesterClass", "Test", Q_NULLPTR));
        groupBox_modeChoice->setTitle(QApplication::translate("RegexEngineTesterClass", "mode:", Q_NULLPTR));
        radioButton_standardTest->setText(QApplication::translate("RegexEngineTesterClass", "standard test", Q_NULLPTR));
        radioButton_automatedTest->setText(QApplication::translate("RegexEngineTesterClass", "automated validity test", Q_NULLPTR));
        checkBox_regexLineWrap->setText(QApplication::translate("RegexEngineTesterClass", "line wrap", Q_NULLPTR));
        checkBox_inputLineWrap->setText(QApplication::translate("RegexEngineTesterClass", "line wrap", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegexEngineTesterClass: public Ui_RegexEngineTesterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGEXENGINETESTER_H
