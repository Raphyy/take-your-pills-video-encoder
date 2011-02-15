//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphaël GUILLORY
// Version     : alpha
// Copyright   : Please contact raphael.guillory@gmail.com
// Description : Video encoder for Take Your Pills
//============================================================================


#include <QApplication>
#include "form.h"


int main(int argc,char *argv[])
{
	// Launch widget
	QApplication mainApplication(argc,argv);
	form mainForm;
	mainForm.show();
	mainForm.setWindowIcon(QIcon("icon.png"));
	return mainApplication.exec();
}
