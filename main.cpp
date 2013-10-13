//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphy
// Website     : www.takeyourpills.fr
// Copyright   : Please contact contact@takeyourpills.fr
//============================================================================


#include <QApplication>
#include "mainForm.h"


int main(int argc,char *argv[])
{
	QApplication mainApplication(argc,argv);
	mainForm form;
	form.show();
	form.setWindowIcon(QIcon("icon.png"));
	return mainApplication.exec();
}
