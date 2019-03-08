#include "stdafx.h"
#include "RegexEngineTester.h"
#include <QtWidgets/QApplication>
#include "Regex.h"


int main(int argc, char *argv[])
{
	boost::regex r("a");
	boost::regex_match(std::string("a"), r);

	QApplication a(argc, argv);
	RegexEngineTester w;
	w.show();
	return a.exec();
}
