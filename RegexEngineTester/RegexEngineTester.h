#pragma once

#include <QtWidgets/QMainWindow>
#include "./GeneratedFiles/ui_RegexEngineTester.h"
#include "RegexSearchData.h"
#include "SearchResultHighlighter.h"

class RegexEngine;

//main class of the Qt application, inheriting QMainWindow; the gui of application
class RegexEngineTester : public QMainWindow
{
	Q_OBJECT

	//the Qt-generated ui object
	Ui::RegexEngineTesterClass _ui;
	//the results highlighter instance
	SearchResultHighlighter _resultHighlihter;
	//the 4 compared regex engines
	RegexEngine* _stdRegexEngine;
	RegexEngine* _qRegularExpressionEngine;
	RegexEngine* _boostRegexEngine;
	RegexEngine* _xRegexEngine;
	//the pointer to currently selected regex engine
	RegexEngine* _currentEngine;
	//buffer object for regex search resuts, stored for optimization
	RegexSearchData _searchData;
	//detailed benchmark statistics
	ResultStat _stats;
	//flag specifying if input is currently plain text
	bool _inputIsPlainText;

	void initializeRegexEngines();
	void connectSignals();
	void setStatus(char const* message);
	void setStatus(std::string const& message);
	void setStatus(QString const& message);
	void updateStatusAfterSearch(RegexSearchData const& searchData);
	bool processInputWithCurrentEngine();
	void benchmarkSearchWithCurrentEngine();
	void saveApplicationState();
	void restoreApplicationState();
	void convertInputToPlainText();
	void runStandardMatchTest();
	void runAutomatedValidityTest();
	void runAutomatedValidityTestsForAllEngines();
	static void makePlainText(QTextEdit* textEdit);
	static void setText(QTextEdit* textEdit, QString const& text);

	//slots fired in cases of user interaction with gui
private slots:
	void radioButton_xRegex_toggled(bool checked);
	void radioButton_stdRegex_toggled(bool checked);
	void radioButton_QRegularExpression_toggled(bool checked);
	void radioButton_BoostRegex_toggled(bool checked);
	void radioButton_standardTest_toggled(bool checked);
	void radioButton_automatedTest_toggled(bool checked);
	void pushButton_search_click(bool checked);
	void pushButton_load_click(bool checked);
	void pushButton_save_click(bool checked);
	void pushButton_random_click(bool checked);
	void pushButton_test_click(bool checked);
	void pushButton_match_click(bool checked);
	void textEdit_input_textChanged();
public:
	//standard ctor for classes inheriting any QWidget
	RegexEngineTester(QWidget *parent = Q_NULLPTR);
	~RegexEngineTester();
};
