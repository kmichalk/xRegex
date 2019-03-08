#include "stdafx.h"
#include "RegexEngineTester.h"
#include "StdRegex.h"
#include "QtRegex.h"
#include "XRegex.h"
#include "BoostRegex.h"
#include "RandomString.h"
#include "RegexValidityTest.h"


void RegexEngineTester::initializeRegexEngines() {
	_stdRegexEngine = new StdRegex;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::connectSignals() {
	connect(_ui.radioButton_xRegex, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_xRegex_toggled);
	connect(_ui.radioButton_stdRegex, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_stdRegex_toggled);
	connect(_ui.radioButton_QRegularExpression, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_QRegularExpression_toggled);
	connect(_ui.radioButton_BoostRegex, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_BoostRegex_toggled);
	connect(_ui.radioButton_standardTest, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_standardTest_toggled);
	connect(_ui.radioButton_automatedTest, &QRadioButton::toggled, this, &RegexEngineTester::radioButton_automatedTest_toggled);
	connect(_ui.pushButton_search, &QPushButton::clicked, this, &RegexEngineTester::pushButton_search_click);
	connect(_ui.pushButton_load, &QPushButton::clicked, this, &RegexEngineTester::pushButton_load_click);
	connect(_ui.pushButton_save, &QPushButton::clicked, this, &RegexEngineTester::pushButton_save_click);
	connect(_ui.pushButton_random, &QPushButton::clicked, this, &RegexEngineTester::pushButton_random_click);
	connect(_ui.pushButton_test, &QPushButton::clicked, this, &RegexEngineTester::pushButton_test_click);
	connect(_ui.pushButton_match, &QPushButton::clicked, this, &RegexEngineTester::pushButton_match_click);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::setStatus(char const * message) {
	_ui.statusBar->showMessage(message);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::setStatus(std::string const & message) {
	_ui.statusBar->showMessage(QString::fromStdString(message));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::setStatus(QString const & message) {
	_ui.statusBar->showMessage(message);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::updateStatusAfterSearch(RegexSearchData const & searchData) {
	if (!searchData.compilationSucceeded)
		setStatus("Regex compilation failed");
	else
		setStatus("Search succeeded");
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool RegexEngineTester::processInputWithCurrentEngine() {
	std::string regex = _ui.textEdit_regex->toPlainText().toStdString();
	std::string input = _ui.textEdit_input->toPlainText().toStdString();
	/*if (regex.empty()) {
		setStatus("Regex is empty");
		return false;
	}*/
	_searchData = _currentEngine->search(regex, input);	
	if (_ui.checkBox_highlight->isChecked()) {
		setText(_ui.textEdit_input, _resultHighlihter.highlight(_ui.textEdit_input->toPlainText(), _searchData));
		_inputIsPlainText = false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::benchmarkSearchWithCurrentEngine() {
	bool ok;
	int reps = _ui.lineEdit_iterations->text().toInt(&ok);
	if (ok) {
		std::string regex = _ui.textEdit_regex->toPlainText().toStdString();
		std::string input = _ui.textEdit_input->toPlainText().toStdString();
		_stats = _currentEngine->benchmark(regex, input, reps);
		_ui.textEdit_results->setText(_stats.info(1000.0f, 5));
		_ui.statusBar->showMessage("Benchmark completed");
	} else {
		_ui.statusBar->showMessage("Iterations: invalid value");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::saveApplicationState() {
	QSettings settings(SETTINGS_FILENAME, QSettings::Format::IniFormat);
	if (_ui.checkBox_saveState->isChecked()) {
		settings.setValue("selectedEngine", 0);
		settings.setValue("regex", _ui.textEdit_regex->toPlainText());
		settings.setValue("input", _ui.textEdit_input->toPlainText());
		settings.setValue("results", _ui.textEdit_results->toPlainText());
		settings.setValue("saveState", _ui.checkBox_saveState->isChecked());
		settings.setValue("iterations", _ui.lineEdit_iterations->text());
	} else
		settings.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::restoreApplicationState() {
	QSettings settings(SETTINGS_FILENAME, QSettings::Format::IniFormat);
	if (settings.allKeys().isEmpty()) {
		setStatus("Application state could not be restored");
		return;
	}
	int selectedEngine = settings.value("selectedEngine").toInt();
	_ui.textEdit_regex->setText(settings.value("regex").toString());
	_ui.textEdit_input->setText(settings.value("input").toString());
	_ui.textEdit_results->setText(settings.value("results").toString());
	_ui.checkBox_saveState->setChecked(settings.value("saveState").toBool());
	_ui.lineEdit_iterations->setText(settings.value("iterations").toString());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::convertInputToPlainText() {
	if (_inputIsPlainText)
		return;
	else {
		makePlainText(_ui.textEdit_input);
		_inputIsPlainText = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::runStandardMatchTest() {
	QString regex = _ui.textEdit_regex->toPlainText();
	QString input = _ui.textEdit_input->toPlainText();
	x::MatchTestResult result;
	_currentEngine->safeMatch(regex.toStdString(), input.toStdString(), result);
	_ui.textEdit_results->setPlainText(QString::fromStdString(result.format(true)));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::runAutomatedValidityTest() {
	QString input = _ui.textEdit_input->toPlainText();
	x::RegexTestSet testSet;
	testSet.read(input);
	testSet.execute(_currentEngine);
	_ui.textEdit_results->setPlainText(testSet.toQString());
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::runAutomatedValidityTestsForAllEngines() {
	QString input = _ui.textEdit_input->toPlainText();
	QString results;
	x::RegexTestSet testSet;
	testSet.read(input);
	testSet.execute(_xRegexEngine);
	results += "==== x::Regex ====\n";
	results += testSet.toQString();
	testSet.execute(_stdRegexEngine);
	results += "\n\n==== std::regex ====\n";
	results += testSet.toQString();
	testSet.execute(_boostRegexEngine);
	results += "\n\n==== Boost.Regex ====\n";
	results += testSet.toQString();
	testSet.execute(_qRegularExpressionEngine);
	results += "\n\n==== QRegularExpression ====\n";
	results += testSet.toQString();
	_ui.textEdit_results->setPlainText(results);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::makePlainText(QTextEdit* textEdit) {
	textEdit->blockSignals(true);
	auto prevCursor = textEdit->textCursor();
	int pos = prevCursor.position();
	textEdit->setPlainText(textEdit->toPlainText());
	prevCursor.setPosition(pos);
	textEdit->setTextCursor(prevCursor);
	textEdit->blockSignals(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::setText(QTextEdit * textEdit, QString const & text) {
	textEdit->blockSignals(true);
	//auto prevCursorPos = textEdit->cursor().pos();
	textEdit->setText(text);
	//textEdit->cursor().setPos(prevCursorPos);
	textEdit->blockSignals(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_xRegex_toggled(bool checked) {
	if (checked)
		_currentEngine = _xRegexEngine;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_stdRegex_toggled(bool checked) {
	if (checked)
		_currentEngine = _stdRegexEngine;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_QRegularExpression_toggled(bool checked) {
	if (checked)
		_currentEngine = _qRegularExpressionEngine;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_BoostRegex_toggled(bool checked) {
	if (checked)
		_currentEngine = _boostRegexEngine;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_standardTest_toggled(bool checked) {
	_ui.textEdit_regex->setEnabled(checked);
	_ui.lineEdit_iterations->setEnabled(checked);
	_ui.lineEdit_lengthRange->setEnabled(checked);
	_ui.lineEdit_symbols->setEnabled(checked);
	_ui.pushButton_search->setEnabled(checked);
	_ui.pushButton_random->setEnabled(checked);
	_ui.label_iterations->setEnabled(checked);
	_ui.label_regex->setEnabled(checked);
	_ui.textEdit_regex->setVisible(checked);
	_ui.lineEdit_iterations->setVisible(checked);
	_ui.lineEdit_lengthRange->setVisible(checked);
	_ui.lineEdit_symbols->setVisible(checked);
	_ui.pushButton_search->setVisible(checked);
	_ui.pushButton_random->setVisible(checked);
	_ui.label_iterations->setVisible(checked);
	_ui.label_regex->setVisible(checked);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::radioButton_automatedTest_toggled(bool checked) {
	
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_search_click(bool checked) {
	try {
		if (_currentEngine == nullptr) {
			setStatus("Regex engine not selected");
		}
		processInputWithCurrentEngine();
		benchmarkSearchWithCurrentEngine();
		updateStatusAfterSearch(_searchData);
	} 
	catch (...) {
		_ui.statusBar->showMessage("Unexpected exception");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_load_click(bool checked) {
	QString filename = QFileDialog::getOpenFileName(nullptr, "Open file", "Resources", "Text files (*.txt);;All files (*.*)*");
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly)) {
		QString content(file.readAll());
		_ui.textEdit_input->setPlainText(content);
		_ui.statusBar->showMessage("File loaded successfully");
	} else {
		_ui.statusBar->showMessage("Error: file not loaded");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_save_click(bool checked) {
	QString filename = QFileDialog::getSaveFileName(nullptr, "Open file", "Resources", "Text files (*.txt);;All files (*.*)*");
	QFile file(filename);
	if (file.open(QIODevice::WriteOnly)) {
		file.write(_ui.textEdit_input->toPlainText().toLatin1());
		_ui.statusBar->showMessage("File saved successfully");
	} else {
		_ui.statusBar->showMessage("Error: file not saved");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_random_click(bool checked) {
	std::string symbols = _ui.lineEdit_symbols->text().toStdString();
	QString range = _ui.lineEdit_lengthRange->text();
	auto parts = range.split(QRegularExpression("[; ,-]"), QString::SplitBehavior::SkipEmptyParts);
	int n = parts[0].toInt();
	int minLength = parts[1].toInt();
	int maxLength = parts[2].toInt();
	_ui.textEdit_input->setPlainText(QString(RandomString::get(symbols, n, minLength, maxLength).c_str()));
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_test_click(bool checked) {
	if (_ui.radioButton_automatedTest->isChecked())
		return runAutomatedValidityTestsForAllEngines();
	try {
		bool ok;
		int reps = _ui.lineEdit_iterations->text().toInt(&ok);
		if (ok) {
			std::string regex = _ui.textEdit_regex->toPlainText().toStdString();
			std::string input = _ui.textEdit_input->toPlainText().toStdString();
			QString statsInfo;
			QString csv;
			csv += ResultStat::timeCsvHeader(false);
			for (auto button : {_ui.radioButton_xRegex, _ui.radioButton_BoostRegex, _ui.radioButton_stdRegex, _ui.radioButton_QRegularExpression}) {
				button->setChecked(true);
				_stats = _currentEngine->benchmark(regex, input, reps);
				statsInfo += "Engine: ";
				statsInfo += button->text();
				statsInfo += "\n";
				statsInfo += _stats.timeInfo(1000.0f, 5);
				statsInfo += "\n\n";
				csv += _stats.timeCsvLine(button->text(), false);
			}
			statsInfo = "Regex: " + QString(regex.c_str()) + "\n\n" + _stats.matchInfo() + "\n\n" + statsInfo;
			_ui.textEdit_results->setText(statsInfo);

			{QString filename = "Resources\\test " + QDate::currentDate().toString() + ".csv";
			QFile file(filename);
			if (file.open(QIODevice::WriteOnly)) {
				file.write(csv.toLatin1());
				file.close();
			}}
			{QString filename = "Resources\\test " + QDate::currentDate().toString() + ".txt";
			QFile file(filename);
			if (file.open(QIODevice::WriteOnly)) {
				file.write(statsInfo.toLatin1());
				file.close();
			}}
			_ui.statusBar->showMessage("Benchmark completed");
		} else {
			_ui.statusBar->showMessage("Iterations: invalid value");
		}
	}
	catch (...) {
		_ui.statusBar->showMessage("Unexpected exception");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::pushButton_match_click(bool checked) {
	if (_ui.radioButton_automatedTest->isChecked())
		runAutomatedValidityTest();
	else
		runStandardMatchTest();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void RegexEngineTester::textEdit_input_textChanged() {
	if (_ui.textEdit_input->hasFocus())
		convertInputToPlainText();
	//processInputWithCurrentEngine();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexEngineTester::RegexEngineTester(QWidget *parent)
	: QMainWindow(parent),
	_stdRegexEngine(new StdRegex),
	_qRegularExpressionEngine(new QtRegex),
	_boostRegexEngine(new BoostRegex),
	_xRegexEngine(new XRegex),
	_currentEngine(_xRegexEngine),
	_inputIsPlainText(true) {
	_ui.setupUi(this);
	connectSignals();
	restoreApplicationState();
}

///////////////////////////////////////////////////////////////////////////////////////////////

RegexEngineTester::~RegexEngineTester() {
	saveApplicationState();
}
