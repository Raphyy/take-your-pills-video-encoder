//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphy
// Website     : www.takeyourpills.fr
// Copyright   : Please contact contact@takeyourpills.fr
//============================================================================


#ifndef _MAINFORM_H
#define	_MAINFORM_H


#include <QUrl>
#include <vector>
#include "ui_mainForm.h"
#include "previewForm.h"


class command
{
    public:
        std::string id;
        QString software;
        QStringList arguments;
        int exitStatus;
};


class commands
{
    public:
        std::vector<command> joblist;
};


class mainForm : public QDialog
{
    Q_OBJECT
    
    public:
        mainForm();
        virtual ~mainForm();
        
    public slots:
        void openFile();
        void displayHelp();
        void openPreviewForm();
        void receiveTime(double);
        void enablePreviewGroupbox(int);
        void enableUserDefinedVideoGroupbox(int);
        void enableEncodeButton(int);
        void encodeVideo();
        
    signals:
        void sendPath(QString);
    
    private:
        void reinitializeForm();
        Ui::mainForm widget;
        previewForm* preview;
        QString pathApp;
        QString pathUserFileInput;
    	QString basename;
    	bool needPreview;
        bool need360;
        bool need720;
    	bool need1080;
        bool needUserDefined;
    	double timeUserPreviewTime;
        int intUserResizeResolutionX;
        int intUserResizeResolutionY;
        int intUserResizeBitrate;
        int intUserResizeBitrateTolerance;
        double timeUserCutTimeStart;
        double timeUserCutTimeStop;
        QUrl urlUpload;
};


void generateCommand(command *,
                    QString,
					QString,
					QString,
                    std::string,
					double,
                    double,
                    double,
                    double,
                    double,
                    int,
                    int);


void addNewLineInLog (std::ofstream&);


int getBitrate(int,int);


int getBitrateTolerance(int,int);


int getPercentage(int,int);


#endif	/* _MAINFORM_H */
