//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphaël GUILLORY
// Version     : Beta
// Copyright   : Please contact raphael.guillory@gmail.com
// Description : Video encoder for Take Your Pills
//============================================================================


#ifndef _FORM_H
#define	_FORM_H


#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QProgressBar>
#include <QPushButton>
#include "commands.h"


class form : public QWidget
{
	// Use own slots
	Q_OBJECT

public:
	form();

public slots:
	void openFile();
	void displayHelp();
	void encodeVideo();
	
private:
	// Standard Definition section
	QGroupBox *groupboxStandardDefinition;
	QLabel *labelStandardDefinition;
	QLineEdit *lineeditStandardDefinition;
	QToolButton *toolbuttonStandardDefinition;
	QLabel *labelBasename;
	QLineEdit *lineeditBasename;
	QToolButton *toolbuttonBasename;
	// High Definition section
	QGroupBox *groupboxHighDefinition;
	QCheckBox *checkboxHighDefinition;
	// Preview section
	QGroupBox *groupboxPreview;
	QCheckBox *checkboxPreview;
	QLabel *labelPreviewAt;
	QDoubleSpinBox *doublespinboxSeconds;
	QLabel *labelSeconds;
	// Encode section
	QProgressBar *progressbarEncode;
	QPushButton *pushbuttonEncode;
	// Version section
	QLabel *labelVersion;
	// Important stuff
	std::string pathApp;
	std::string pathInfile;
	std::string basename;
	bool needHd;
	bool needPv;
	double timePreview;
};


std::string getPath(std::string);


void generateCommand(std::string *,
							std::string,
							std::string,
							std::string,
							double,
							std::string);


std::string checkPath (std::string);


int getPercentage(int,int);


std::string DoubleToString(double);

#endif


