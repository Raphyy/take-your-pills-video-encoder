//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphy
// Website     : www.takeyourpills.fr
// Copyright   : Please contact contact@takeyourpills.fr
//============================================================================


//#define LINUX
#define WINDOWS


#include <fstream>
#include <iostream>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTime>
#include <QDesktopServices>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "mainForm.h"
#include "tinyxml.h"


// Define all possible tags
const std::string filenameCommands = "config.xml";
const std::string tagInternalFFmpeg = "{internal.ffmpeg}";
const std::string tagInternalFFmpegPresetFastFirstPass = "{internal.ffmpeg.preset.fastfirstpass}";
const std::string tagInternalFFmpegPresetHq = "{internal.ffmpeg.preset.hq}";
const std::string tagInternalMP4box = "{internal.mp4box}";
const std::string tagUserFileInput = "{user.file.input}";
const std::string tagUserFileOutput = "{user.file.output.";
const std::string tagUserPreviewTime = "{user.preview.time}";
const std::string tagUserResizeResolution = "{user.resize.resolution}";
const std::string tagUserResizeBitrate = "{user.resize.bitrate}";
const std::string tagUserResizeBitrateTolerance = "{user.resize.bitratetolerance}";
const std::string tagUserCutTimeStart = "{user.cut.time.start}";
const std::string tagUserCutTimeStop = "{user.cut.time.stop}";
const std::string idPreview = "Preview";
const std::string id360 = "360";
const std::string id720 = "720";
const std::string id1080 = "1080";
const std::string idUser = "User";


// Define CSS styles
const QString cssLineEditOk = "QLineEdit{background: #FFFFFF;foreground-color: #000000;font-weight: regular;}";
const QString cssLineEditError = "QLineEdit{background: #FF9090;foreground-color: #FFFFFF;font-weight: bold;}";
const QString cssDoubleSpinBoxOk = "QDoubleSpinBox{background: #FFFFFF;foreground-color: #000000;font-weight: regular;}";
const QString cssDoubleSpinBoxError = "QDoubleSpinBox{background: #FF9090;foreground-color: #FFFFFF;font-weight: bold;}";
const QString cssSpinBoxOk = "QSpinBox{background: #FFFFFF;foreground-color: #000000;font-weight: regular;}";
const QString cssSpinBoxError = "QSpinBox{background: #FF9090;foreground-color: #FFFFFF;font-weight: bold;}";


// Define constants used to compute bitrates and bitrates tolerances
const float intBirateA = 1.712962963;
const float intBirateB = 613333.3333;
const float intBirateToleranceA = 1.101792944;
const float intBirateToleranceB = 1560587.623;


mainForm::mainForm()
{
    widget.setupUi(this);
    
    // Link actions
    QObject::connect(widget.toolbuttonUserFileInput,SIGNAL(clicked()),this,SLOT(openFile()));
    QObject::connect(widget.toolbuttonBasename,SIGNAL(clicked()),this,SLOT(displayHelp()));
    QObject::connect(widget.pushbuttonEncode,SIGNAL(clicked()),this,SLOT(encodeVideo()));
    QObject::connect(widget.checkboxPreview,SIGNAL(stateChanged(int)),this,SLOT(updateGUIPreview(int)));
    QObject::connect(widget.checkboxUserDefined,SIGNAL(stateChanged(int)),this,SLOT(updateGUIUserDefinedVideo(int)));
}
    

mainForm::~mainForm()
{
}


void mainForm::openFile()
{
	// Select video file to encode
	QString fileName = QFileDialog::getOpenFileName(this,tr("Select a video file"),"/",tr("Video (*.*)"));
	widget.lineeditUserFileInput->setText(fileName);
}


void mainForm::displayHelp()
{
	// Display information message
	QMessageBox::information(this,"About Basename","Basename is used to generate filenames.\nFor example, if you enter \"typ\", output files should be named:\n\"typSD.flv\" \"typHD.flv\" and \"typPV.jpg\".");
}


// TODO: Implement video display to select the preview


void mainForm::encodeVideo()
{
    // Initialize log file
    std::ofstream LogFile;
    LogFile.open ("previousrun.log");
    
    
    // Initialize GUI
    widget.lineeditUserFileInput->setStyleSheet(cssLineEditOk);
    widget.lineeditBasename->setStyleSheet(cssLineEditOk);
    widget.doublespinboxUserPreviewTime->setStyleSheet(cssDoubleSpinBoxOk);
    widget.spinboxUserResizeResolutionX->setStyleSheet(cssSpinBoxOk);
    widget.spinboxUserResizeResolutionY->setStyleSheet(cssSpinBoxOk);

    
	// Initialize variables from GUI
	pathApp = QDir::currentPath();
	pathUserFileInput = widget.lineeditUserFileInput->text();
	basename = widget.lineeditBasename->text();
	needPreview = widget.checkboxPreview->isChecked();
    need360 = widget.checkbox360->isChecked();
    need720 = widget.checkbox720->isChecked();
    need1080 = widget.checkbox1080->isChecked();
    needUserDefined = widget.checkboxUserDefined->isChecked();
	timeUserPreviewTime = widget.doublespinboxUserPreviewTime->value();
    intUserResizeResolutionX = widget.spinboxUserResizeResolutionX->value();
    intUserResizeResolutionY = widget.spinboxUserResizeResolutionY->value();
    intUserResizeBitrate = getBitrate(intUserResizeResolutionX,intUserResizeResolutionY);
    intUserResizeBitrateTolerance = getBitrateTolerance(intUserResizeResolutionX,intUserResizeResolutionY);
    timeUserCutTimeStart = widget.doublespinboxUserCutTimeStart->value();
    timeUserCutTimeStop = widget.doublespinboxUserCutTimeStop->value();
    

#ifdef LINUX
	std::string pathCommands = pathApp.toStdString() + "/" + filenameCommands;
#endif
#ifdef WINDOWS
	std::string pathCommands = pathApp.toStdString() + "\\" + filenameCommands;
#endif
	
	TiXmlDocument xmlFile(pathCommands.c_str());
	commands EncodingCommands;
	command tempCommand;
    QString tempArgument;
    std::string tempId;
    bool boolFormIsOk = true;
    
    
    // TODO: Ask Devon for accurate translations
    
    
	// Check if a file has been selected
	if ((pathUserFileInput.size() == 0) && boolFormIsOk)
    {
        boolFormIsOk = false;
        widget.lineeditUserFileInput->setStyleSheet(cssLineEditError);
		QMessageBox::information(this,"Information","You must select a video file.");
    }
    
    // Check if a basename has been entered
	if ((basename.size() == 0) && boolFormIsOk)
    {
        boolFormIsOk = false;
        widget.lineeditBasename->setStyleSheet(cssLineEditError);
		QMessageBox::information(this,"Information","You must enter a basename.");
    }
    
    // Check a new resolution X has been entered, if needed
    if ((needUserDefined == 1) && (intUserResizeResolutionX == 0)  && boolFormIsOk)
    {
        boolFormIsOk = false;
        widget.spinboxUserResizeResolutionX->setStyleSheet(cssSpinBoxError);
        QMessageBox::information(this,"Information","As you want a user-defined video, you should enter a valid resolution.");
    }

    // Check a new resolution Y has been entered, if needed
    if ((needUserDefined == 1) && (intUserResizeResolutionY == 0) && boolFormIsOk)
    {
        boolFormIsOk = false;
        widget.spinboxUserResizeResolutionY->setStyleSheet(cssSpinBoxError);
        QMessageBox::information(this,"Information","As you want a user-defined video, you should enter a valid resolution.");
    }

    // Check a preview time has been entered, if needed
    if ((needPreview == 1) && (timeUserPreviewTime == 0) && boolFormIsOk)
    {
        widget.doublespinboxUserPreviewTime->setStyleSheet(cssDoubleSpinBoxError);
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Question","You want a preview but you let the default preview time. Is it what you want ?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
            boolFormIsOk = false;
        else
        {
            boolFormIsOk = boolFormIsOk && true;
            widget.doublespinboxUserPreviewTime->setStyleSheet(cssLineEditOk);
        }
    }
    
    // Form is correct
    if (boolFormIsOk)
    {
        // Form is correct disable GUI components
        widget.lineeditUserFileInput->setEnabled(false);
        widget.toolbuttonUserFileInput->setEnabled(false);
        widget.lineeditBasename->setEnabled(false);
        widget.toolbuttonBasename->setEnabled(false);
        widget.checkboxPreview->setEnabled(false);
        widget.checkbox360->setEnabled(false);
        widget.checkbox720->setEnabled(false);
        widget.checkbox1080->setEnabled(false);
        widget.checkboxUserDefined->setEnabled(false);
        widget.doublespinboxUserPreviewTime->setEnabled(false);
        widget.toolbuttonUserPreviewTime->setEnabled(false);
        widget.spinboxUserResizeResolutionX->setEnabled(false);
        widget.spinboxUserResizeResolutionY->setEnabled(false);
        widget.doublespinboxUserCutTimeStart->setEnabled(false);
        widget.doublespinboxUserCutTimeStop->setEnabled(false);
        widget.pushbuttonEncode->setEnabled(false);

        // Start to load commands
        addNewLineInLog(LogFile);
        LogFile << "Starting to load \"config.xml\" file ...\n";

        if (!xmlFile.LoadFile())
        {
            QMessageBox::critical(this,"Error","Unable to load the file \"config.xml\".\nIt should be in application's root folder.");
            addNewLineInLog(LogFile);
            LogFile << "   > Unable to load \"config.xml\" or not valid.\n";
            LogFile.close();
        }

        else
        {
            TiXmlElement *xmlRoot, *xmlCommand, *xmlSoftware, *xmlArgument;

            xmlRoot = xmlFile.FirstChildElement("uploadurl");
            urlUpload = QUrl(QString(xmlRoot->GetText()), QUrl::TolerantMode);
            addNewLineInLog(LogFile);
            LogFile << "   Upload URL loaded : " << urlUpload.toString().toStdString() << "\n";
            
            xmlRoot = xmlRoot->NextSiblingElement("commands");

            // Detect error in finding first element in XML file
            if (!xmlRoot)
            {
                QMessageBox::critical(this,"Error","Unable to read XML data from the file \"config.xml\".");
                addNewLineInLog(LogFile);
                LogFile << "   > Unable to find the \"<commands>\" root tag in the \"config.xml\" file.\n";
                LogFile.close();
            }

            else
            {
                xmlCommand = xmlRoot -> FirstChildElement("command");

                if (!xmlCommand)
                {
                    // TODO: Test log files writting in case of bad tags
                    QMessageBox::critical(this,"Error","Unable to read XML data from the file \"config.xml\".");
                    addNewLineInLog(LogFile);
                    LogFile << "   > Unable to find the \"<command>\" tag in the \"config.xml\" file.\n";
                    LogFile.close();
                }

                else
                {
                    do
                    {
                        // Fill id and exitStatus attributes
                        tempId = xmlCommand->Attribute("id");
                        tempCommand.id = tempId;
                        tempCommand.exitStatus = 0;
                        addNewLineInLog(LogFile);
                        LogFile << "   " << xmlCommand -> Attribute("id") << " loaded : ";

                        // Fill software attribute
                        xmlSoftware = xmlCommand -> FirstChildElement("software");
                        tempCommand.software = xmlSoftware->GetText();
                        LogFile << xmlSoftware->GetText() << " ";

                        xmlArgument = xmlSoftware -> NextSiblingElement("argument");

                        if (!xmlSoftware or !xmlArgument)
                        {
                            QMessageBox::critical(this,"Error","Unable to read XML data from the file \"config.xml\".");
                            addNewLineInLog(LogFile);
                            LogFile << "   > Unable to find the \"<software>\" or \"<argument>\" tags in the \"config.xml\" file.";
                            LogFile.close();
                        }

                        // Fill arguments attribute
                        else
                        {
                            do
                            {
                                tempArgument = xmlArgument->Attribute("option");
                                if (!tempArgument.isEmpty())
                                {
                                    tempCommand.arguments << tempArgument;
                                    LogFile << tempArgument.toStdString() << " ";
                                }

                                tempArgument = xmlArgument->GetText();
                                if (!tempArgument.isEmpty())
                                {
                                    tempCommand.arguments << tempArgument;
                                    LogFile << tempArgument.toStdString() << " ";
                                }

                                xmlArgument = xmlArgument -> NextSiblingElement("argument");
                            } while (xmlArgument);
                        }

                        // Add the current command to the joblist only if needed
                        if ((idPreview.compare(tempId) == 0) && (needPreview == 1))
                            EncodingCommands.joblist.push_back(tempCommand);
                        else if ((id360.compare(tempId) == 0) && (need360 == 1))
                            EncodingCommands.joblist.push_back(tempCommand);
                        else if ((id720.compare(tempId) == 0) && (need720 == 1))
                            EncodingCommands.joblist.push_back(tempCommand);
                        else if ((id1080.compare(tempId) == 0) && (need1080 == 1))
                            EncodingCommands.joblist.push_back(tempCommand);
                        else if ((idUser.compare(tempId) == 0) && (needUserDefined == 1))
                            EncodingCommands.joblist.push_back(tempCommand);

                        // Initialize data for the next command
                        LogFile << "\n";
                        tempCommand.software.clear();
                        tempCommand.arguments.clear();
                        xmlCommand = xmlCommand -> NextSiblingElement("command");

                    } while (xmlCommand);
                }

                // Update and show progress bar
                widget.progressbarEncode->setValue(0);
                widget.progressbarEncode->setVisible(true);

                // Initialize variables
                QProcess process;
                bool joblistExitStatus = true;

                // Determine commands number to execute to fill the Progress Bar
                int nbrCommands = EncodingCommands.joblist.size();

                addNewLineInLog(LogFile);
                LogFile << "Executing command(s) ...\n";

                // Execute commands
                for(int i=0;i<nbrCommands;i++)
                {
                    // Prepare and execute process
                    generateCommand(&EncodingCommands.joblist[i], pathApp, pathUserFileInput, basename, EncodingCommands.joblist[i].id, timeUserPreviewTime, intUserResizeResolutionX, intUserResizeResolutionY, timeUserCutTimeStart, timeUserCutTimeStop, intUserResizeBitrate, intUserResizeBitrateTolerance);
                    process.start(EncodingCommands.joblist[i].software, EncodingCommands.joblist[i].arguments);

                    // Avoid freezing the GUI
                    while (process.state() != QProcess::NotRunning)
                        QCoreApplication::processEvents();

                    // Manage process exit status
                    EncodingCommands.joblist[i].exitStatus = process.exitStatus();
                    joblistExitStatus = joblistExitStatus && (process.exitStatus()==0);
                    widget.progressbarEncode->setValue(getPercentage(i+1, nbrCommands));

                    // Update logfile
                    addNewLineInLog(LogFile);
                    if (EncodingCommands.joblist[i].exitStatus == 0)
                        LogFile << "   Done   : ";
                    else
                        LogFile << "   Failed : ";
                    LogFile << EncodingCommands.joblist[i].software.toStdString() << " ";
                    for (int j=0; j<EncodingCommands.joblist[i].arguments.size(); j++)
                    {
                        LogFile << EncodingCommands.joblist[i].arguments.at(j).toStdString() << " ";
                    }
                    LogFile << "\n";
                }

                // Log executed commands
                addNewLineInLog(LogFile);
                if (joblistExitStatus == 0)
                    LogFile << "Job failed.";
                else
                    LogFile << "Job done.";

                // Display messages if error occurs when encoding
                if (!joblistExitStatus)
                    QMessageBox::critical(this, "Error", "Something went wrong while encoding.\nCheck the log file to know which command failed.");
                else
                {
                    if (urlUpload.isEmpty())
                        QMessageBox::information(this, "Information", "Job done ! You can upload generated video files.");
                    else
                    {
                        QMessageBox::StandardButton reply = QMessageBox::question(this, "Question", "Job done ! Do you want to upload generated file(s) ?", QMessageBox::Yes|QMessageBox::No);
                        if (reply == QMessageBox::Yes)
                            QDesktopServices::openUrl(urlUpload);
                    }
                }

                // Reinitialize form
                widget.progressbarEncode->setVisible(false);
                widget.lineeditUserFileInput->setText(QString(""));
                widget.lineeditBasename->setText(QString(""));
                widget.checkboxPreview->setChecked(false);
                widget.checkbox360->setChecked(false);
                widget.checkbox720->setChecked(false);
                widget.checkbox1080->setChecked(false);
                widget.checkboxUserDefined->setChecked(false);
                widget.doublespinboxUserPreviewTime->setValue(0);
                widget.spinboxUserResizeResolutionX->setValue(0);
                widget.spinboxUserResizeResolutionY->setValue(0);
                widget.doublespinboxUserCutTimeStart->setValue(0);
                widget.doublespinboxUserCutTimeStop->setValue(99999);

                // Process finished enable GUI components
                widget.lineeditUserFileInput->setEnabled(true);
                widget.toolbuttonUserFileInput->setEnabled(true);
                widget.lineeditBasename->setEnabled(true);
                widget.toolbuttonBasename->setEnabled(true);
                widget.checkboxPreview->setEnabled(true);
                widget.checkbox360->setEnabled(true);
                widget.checkbox720->setEnabled(true);
                widget.checkbox1080->setEnabled(true);
                widget.checkboxUserDefined->setEnabled(true);
                widget.doublespinboxUserPreviewTime->setEnabled(false);
                widget.toolbuttonUserPreviewTime->setEnabled(false);
                widget.spinboxUserResizeResolutionX->setEnabled(false);
                widget.spinboxUserResizeResolutionY->setEnabled(false);
                widget.doublespinboxUserCutTimeStart->setEnabled(false);
                widget.doublespinboxUserCutTimeStop->setEnabled(false);
                widget.pushbuttonEncode->setEnabled(true);

                // Easy ...
                LogFile.close();
            }
        }
	}
}


void mainForm::updateGUIPreview(int checkboxState)
{
    if (checkboxState == Qt::Checked)
    {
        widget.doublespinboxUserPreviewTime->setEnabled(true);
        widget.toolbuttonUserPreviewTime->setEnabled(true);
    }
    else
    {
        widget.doublespinboxUserPreviewTime->setEnabled(false);
        widget.toolbuttonUserPreviewTime->setEnabled(false);
    }
}


void mainForm::updateGUIUserDefinedVideo(int checkboxState)
{
    if (checkboxState == Qt::Checked)
    {
        widget.spinboxUserResizeResolutionX->setEnabled(true);
        widget.spinboxUserResizeResolutionY->setEnabled(true);
        widget.doublespinboxUserCutTimeStart->setEnabled(true);
        widget.doublespinboxUserCutTimeStop->setEnabled(true);
    }
    else
    {
        widget.spinboxUserResizeResolutionX->setEnabled(false);
        widget.spinboxUserResizeResolutionY->setEnabled(false);
        widget.doublespinboxUserCutTimeStart->setEnabled(false);
        widget.doublespinboxUserCutTimeStop->setEnabled(false);
    }
}


std::string getPath(std::string filepath)
{
	int index = filepath.find_last_of("/\\");
	return filepath.substr(0,index+1);
}


void generateCommand(command *commandCurrent,
					 QString pathApp,
					 QString pathUserFileInput,
					 QString basename,
                     std::string type,
					 double timeUserPreviewTime,
                     double intUserResizeResolutionX,
                     double intUserResizeResolutionY,
                     double timeUserCutTimeStart,
                     double timeUserCutTimeStop,
                     int intUserResizeBitrate,
                     int intUserResizeBitrateTolerance)
{
    QString temp;
    
    // Manage tag {internal.ffmpeg}
    temp = pathApp + "/ffmpeg/";
    #ifdef LINUX
		temp = temp + "ffmpeg";
    #endif
    #ifdef WINDOWS
		temp = temp + "ffmpeg.exe";
    #endif
    commandCurrent->software.replace(QString::fromStdString(tagInternalFFmpeg), temp);
    temp = "";
    
    // Manage tag {internal.ffmpeg.preset.fastfirstpass}
    temp = pathApp + "/ffmpeg/fastfirstpass.ffpreset";
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagInternalFFmpegPresetFastFirstPass), temp);
    temp = "";
    
    // Manage tag {internal.ffmpeg.preset.hq}
    temp = pathApp + "/ffmpeg/hq.ffpreset";
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagInternalFFmpegPresetHq), temp);
    temp = "";

    // Manage tag {internal.mp4box}
    temp = pathApp + "/mp4box/";
    #ifdef LINUX
		temp = temp + "mp4box";
    #endif
    #ifdef WINDOWS
		temp = temp + "mp4box.exe";
    #endif
    commandCurrent->software.replace(QString::fromStdString(tagInternalMP4box), temp);
    temp = "";
    
    // Manage tag {user.file.input}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserFileInput), pathUserFileInput);
        
    // Manage tag {user.preview.time}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserPreviewTime), QString::number(timeUserPreviewTime));
    
    // Manage tag {user.cut.time.start}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserCutTimeStart), QString::number(timeUserCutTimeStart));
    
    // Manage tag {user.cut.time.stop}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserCutTimeStop), QString::number(timeUserCutTimeStop-timeUserCutTimeStart));
    
    // Manage tag {user.resize.resolution}
    temp = QString::number(intUserResizeResolutionX,'g',6) + "x" + QString::number(intUserResizeResolutionY,'g',6);
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserResizeResolution), temp);
    temp = "";
    
    // Manage tag {user.resize.bitrate}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserResizeBitrate), QString::number(intUserResizeBitrate));
    
    // Manage tag {user.resize.bitratetolerance}
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserResizeBitrateTolerance), QString::number(intUserResizeBitrateTolerance));
    
    // Manage tag {user.file.output.*} (MUST be the LAST operation)
    #ifdef LINUX
		temp = pathUserFileInput.section("/",0,-2) + "/" + basename + QString::fromStdString(type).toUpper() + ".";
    #endif
    #ifdef WINDOWS
		temp = pathUserFileInput.section("/",0,-2) + "/" + basename + QString::fromStdString(type).toUpper() + ".";
    #endif
    commandCurrent->arguments.replaceInStrings(QString::fromStdString(tagUserFileOutput), temp);
    commandCurrent->arguments.replaceInStrings(QRegExp("[}]$"),"");  // Removes all "}" at the end of QStringLists
    temp = "";
}


void addNewLineInLog (std::ofstream& LogFile)
{
    LogFile << QDate::currentDate().toString("dd/MM/yyyy").toStdString() << " "
            << QTime::currentTime().toString().toStdString() << "  ";
}


int getBitrate(int resolutionX,int resolutionY)
{
	return ((resolutionX * resolutionY * intBirateA) + intBirateB);
}


int getBitrateTolerance(int resolutionX,int resolutionY)
{
	return ((resolutionX * resolutionY * intBirateToleranceA) + intBirateToleranceB);
}


int getPercentage(int value,int maximum)
{
	return (value * 100 / maximum);
}
