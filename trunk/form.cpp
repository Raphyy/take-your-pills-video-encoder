//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphaël GUILLORY
// Version     : alpha
// Copyright   : Please contact raphael.guillory@gmail.com
// Description : Video encoder for Take Your Pills
//============================================================================


//#define LINUX
#define WINDOWS


#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "tinyxml.h"
#include "form.h"


const std::string filenameCommands = ("commands.xml");
const std::string tagInternalFFmpegRun = ("{internal.ffmpeg.run}");
const std::string tagInternalFFmpegPresetFastFirstPass = "{internal.ffmpeg.preset.fastfirstpass}";
const std::string tagInternalFFmpegPresetHq = "{internal.ffmpeg.preset.hq}";
const std::string tagUserFileIn = ("{user.file.in}");
const std::string tagUserFileOut = ("{user.file.out.");
const std::string tagUserTime = ("{user.time}");
const std::string idSd = ("sd");
const std::string idHd = ("hd");
const std::string idPv = ("pv");


form::form():QWidget()
{
	// Window properties
	setFixedSize(370,300);
	setWindowTitle("Take Your Pills Video Encoder");

	// Standard Definition section
	groupboxStandardDefinition = new QGroupBox(this);
	groupboxStandardDefinition->setTitle("Standard Definition");
	groupboxStandardDefinition->resize(350,80);
	groupboxStandardDefinition->move(10,10);

	labelStandardDefinition = new QLabel(groupboxStandardDefinition);
	labelStandardDefinition->setText("Select file");
	labelStandardDefinition->move(10,25);

	lineeditStandardDefinition = new QLineEdit(groupboxStandardDefinition);
	lineeditStandardDefinition->setReadOnly(true);
	lineeditStandardDefinition->resize(240,20);
	lineeditStandardDefinition->move(70,20);

	toolbuttonStandardDefinition = new QToolButton(groupboxStandardDefinition);
	toolbuttonStandardDefinition->setText("...");
	toolbuttonStandardDefinition->resize(20,20);
	toolbuttonStandardDefinition->move(320,20);
	QObject::connect(toolbuttonStandardDefinition,SIGNAL(clicked()),this,SLOT(openFile()));
	
	labelBasename = new QLabel(groupboxStandardDefinition);
	labelBasename->setText("Basename");
	labelBasename->move(10,55);

	lineeditBasename = new QLineEdit(groupboxStandardDefinition);
	lineeditBasename->resize(240,20);
	lineeditBasename->move(70,50);
	
	toolbuttonBasename = new QToolButton(groupboxStandardDefinition);
	toolbuttonBasename->setText(" ? ");
	toolbuttonBasename->resize(20,20);
	toolbuttonBasename->move(320,50);
	QObject::connect(toolbuttonBasename,SIGNAL(clicked()),this,SLOT(displayHelp()));

	// High Definition section
	groupboxHighDefinition = new QGroupBox(this);
	groupboxHighDefinition->setTitle("High Definition");
	groupboxHighDefinition->resize(350,50);
	groupboxHighDefinition->move(10,100);

	checkboxHighDefinition = new QCheckBox(groupboxHighDefinition);
	checkboxHighDefinition->setText("I wanna HD too !");
	checkboxHighDefinition->move(20,20);
	
	// Preview section
	groupboxPreview = new QGroupBox(this);
	groupboxPreview->setTitle("Preview");
	groupboxPreview->resize(350,70);
	groupboxPreview->move(10,160);

	checkboxPreview = new QCheckBox(groupboxPreview);
	checkboxPreview->setText("I wanna preview too !");
	checkboxPreview->move(20,20);

	labelPreviewAt = new QLabel(groupboxPreview);
	labelPreviewAt->setText("Preview at");
	labelPreviewAt->move(20,50);

	doublespinboxSeconds = new QDoubleSpinBox(groupboxPreview);
	doublespinboxSeconds->setMaximum(9999);
	doublespinboxSeconds->resize(60,20);
	doublespinboxSeconds->move(80,45);

	labelSeconds = new QLabel(groupboxPreview);
	labelSeconds->setText("seconds");
	labelSeconds->move(150,50);

	// Encode section
	progressbarEncode = new QProgressBar(this);
	progressbarEncode->setTextVisible(false);
	progressbarEncode->resize(220,15);
	progressbarEncode->move(20,255);
	progressbarEncode->setMinimum(0);
	progressbarEncode->setMaximum(100);
	progressbarEncode->setVisible(false);

	pushbuttonEncode = new QPushButton(this);
	pushbuttonEncode->setText("Encode !");
	pushbuttonEncode->resize(90,30);
	pushbuttonEncode->move(270,245);
	QObject::connect(pushbuttonEncode,SIGNAL(clicked()),this,SLOT(encodeVideo()));

	// Version section
	labelVersion = new QLabel(this);
	labelVersion->setText("Raphy | vBeta");
	labelVersion->move(5,285);

	// Important stuff
	pathApp.clear();
	pathInfile.clear();
	basename.clear();
	needHd = false;
	needPv = false;
	timePreview = 0;
}


void form::openFile()
{
	// Select video file to encode
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"/",tr("Video File(*.*)"));
	lineeditStandardDefinition->setText(fileName);
}


void form::displayHelp()
{
	// Display information message
	QMessageBox::information(this,"About Basename","Basename is used to generate filenames.\nFor example, if you enter \"typ\", output files should be named:\n\"typSD.flv\" \"typHD.flv\" and \"typPV.jpg\".");
}


void form::encodeVideo()
{
	// Initialize variables
	pathApp = QDir::currentPath().toStdString();
	pathInfile = lineeditStandardDefinition->text().toStdString();
	basename = lineeditBasename->text().toStdString();
	needHd = checkboxHighDefinition->isChecked();
	needPv = checkboxPreview->isChecked();
	timePreview = doublespinboxSeconds->value();

#ifdef LINUX
	std::string pathCommands = pathApp + "/" + filenameCommands;
#endif
#ifdef WINDOWS
	std::string pathCommands = pathApp + "\\" + filenameCommands;
#endif
	
	TiXmlDocument fileXml(pathCommands.c_str());
	commands commandsEncode;
	command tempCommand;

	// Check if a file has been selected
	if (pathInfile.size() == 0)
		QMessageBox::critical(this,"Error","You must select a video file.");
	else
	{

		// Check if a basename has been entered
		if (basename.size() == 0)
			QMessageBox::critical(this,"Error","You must enter a basename.");
		
		else // Form is correct
		{
			if (!fileXml.LoadFile())
			{
				QMessageBox::critical(this,"Error","Unable to find the file \"commands.xml\".\nIt should be in the same folder as this application.");
			}

			else
			{
				TiXmlHandle commandHandle(&fileXml);
				TiXmlElement *commandElement = commandHandle.FirstChildElement().FirstChildElement().Element();

				// Detect error in finding first element in XML file
				if (!commandElement)
				{
					QMessageBox::critical(this,"Error","Unable to read XML data from the file \"commands.xml\".");
				}

				else
				{
					// Extract all fields from XML file
					while (commandElement)
					{
						tempCommand.name = commandElement->Attribute("name");
						tempCommand.id = commandElement->Attribute("id");
						tempCommand.pass = atoi(commandElement->Attribute("pass"));
						tempCommand.commandline = commandElement->GetText();
						// Save command in the appropriate list
						if (idSd.compare(tempCommand.id) == 0)
							commandsEncode.commandsSd.push_back(tempCommand);
						else if (idHd.compare(tempCommand.id) == 0)
							commandsEncode.commandsHd.push_back(tempCommand);
						else if (idPv.compare(tempCommand.id) == 0)
							commandsEncode.commandsPv.push_back(tempCommand);
						commandElement = commandElement->NextSiblingElement();
					}

					// Update and show progress bar
					progressbarEncode->setValue(0);
					progressbarEncode->setVisible(true);

					int nbrCommandsSd = commandsEncode.commandsSd.size();
					int nbrCommandsHd = commandsEncode.commandsHd.size();
					int nbrCommandsPv = commandsEncode.commandsPv.size();
					int currentCommand = 0;
					std::string tempCommand;

					// Determine commands number to execute
					int nbrCommands = nbrCommandsSd;
					if (needHd)
						nbrCommands += nbrCommandsHd;
					if (needPv)
						nbrCommands += nbrCommandsPv;

					// Get result from commands execution
					int commandResultCurrent;
					bool commandResultSdOk = true;
					bool commandResultHdOk = true;
					bool commandResultPvOk = true;

					// Encode SD
					for(int i=0;i<nbrCommandsSd;i++)
					{
						currentCommand ++;
						tempCommand = commandsEncode.commandsSd[i].commandline;
						generateCommand(&tempCommand,pathApp,pathInfile,basename,timePreview,idSd);
						//std::cout << tempCommand.c_str() << std::endl;
						commandResultCurrent = system(tempCommand.c_str());
						commandResultSdOk = commandResultSdOk && (commandResultCurrent==0);
						progressbarEncode->setValue(getPercentage(i+1,nbrCommands));
					}

					// Encode HD
					if (needHd)
					{
						for(int i=0;i<nbrCommandsHd;i++)
						{
							currentCommand ++;
							tempCommand = commandsEncode.commandsHd[i].commandline;
							generateCommand(&tempCommand, pathApp, pathInfile, basename, timePreview, idHd);
							//std::cout << tempCommand << std::endl;
							commandResultCurrent = system(tempCommand.c_str());
							commandResultHdOk = commandResultHdOk && (commandResultCurrent==0);
							progressbarEncode->setValue(getPercentage(i + 1, nbrCommands));
						}
					}

					// Get preview
					if (needPv)
					{
						for(int i=0;i<nbrCommandsPv;i++)
						{
							currentCommand ++;
							tempCommand = commandsEncode.commandsPv[i].commandline;
							generateCommand(&tempCommand, pathApp, pathInfile, basename, timePreview, idPv);
							//std::cout << tempCommand << std::endl;
							commandResultCurrent = system(tempCommand.c_str());
							commandResultPvOk = commandResultPvOk && (commandResultCurrent==0);
							progressbarEncode->setValue(getPercentage(i + 1, nbrCommands));
						}
					}

					// Display messages if error occurs when encoding
					if (!commandResultSdOk)
						QMessageBox::critical(this, "Error", "Oups ! Something went wrong while encoding Standard Definition.\nTry to use folders without accents.");
					if (!commandResultHdOk)
						QMessageBox::critical(this, "Error", "Oups ! Something went wrong while encoding High Definition.\nTry to use folders without accents.");
					if (!commandResultPvOk)
						QMessageBox::critical(this, "Error", "Oups ! Something went wrong while creating preview.\nTry to use folders without accents.");
					if (commandResultSdOk && commandResultHdOk && commandResultPvOk)
						QMessageBox::information(this, "Information", "Job done ! You can upload generated video files.");
					
					// Reinitialize form
					progressbarEncode->setVisible(false);
					lineeditStandardDefinition->setText(QString(""));
					lineeditBasename->setText(QString(""));
					checkboxHighDefinition->setChecked(false);
					checkboxPreview->setChecked(false);
					doublespinboxSeconds->setValue(0);
				}
			}
		}
	}
}


std::string getPath(std::string filepath)
{
	int index = filepath.find_last_of("/\\");
	return filepath.substr(0,index+1);
}


void generateCommand(std::string *command,
							std::string pathApp,
							std::string pathInfile,
							std::string basename,
							double timePreview,
							std::string type)
{
	// Initialize variables
	size_t found;
	std::string temp;

	// Manage tag "{internal.ffmpeg.run}"
	found = command->find(tagInternalFFmpegRun);
	while (found != std::string::npos)
	{
#ifdef LINUX
		temp = pathApp + "/ffmpeg/ffmpeg";
#endif
#ifdef WINDOWS
		temp = pathApp + "\\ffmpeg\\ffmpeg.exe";
#endif
		command->replace(found, tagInternalFFmpegRun.size(), checkPath(temp));
		found = command->find(tagInternalFFmpegRun, found + temp.size());
	}

	// Manage tag "{internal.ffmpeg.preset.fastfirstpass}"
	found = command->find(tagInternalFFmpegPresetFastFirstPass);
	while (found != std::string::npos)
	{
#ifdef LINUX
		temp = pathApp + "/ffmpeg/fastfirstpass.ffpreset";
#endif
#ifdef WINDOWS
		temp = pathApp + "\\ffmpeg\\fastfirstpass.ffpreset";
#endif
		command->replace(found, tagInternalFFmpegPresetFastFirstPass.size(), checkPath(temp));
		found = command->find(tagInternalFFmpegPresetFastFirstPass, found + temp.size());
	}

	// Manage tag "{internal.ffmpeg.preset.hq}"
	found = command->find(tagInternalFFmpegPresetHq);
	while (found != std::string::npos)
	{
#ifdef LINUX
		temp = pathApp + "/ffmpeg/hq.ffpreset";
#endif
#ifdef WINDOWS
		temp = pathApp + "\\ffmpeg\\hq.ffpreset";
#endif
		command->replace(found, tagInternalFFmpegPresetHq.size(), checkPath(temp));
		found = command->find(tagInternalFFmpegPresetHq, found + temp.size());
	}

	// Manage tag "{user.file.in}"
	found = command->find(tagUserFileIn);
	while (found != std::string::npos)
	{
#ifdef LINUX
		temp = pathInfile;
#endif
#ifdef WINDOWS
		temp = pathInfile;
#endif
		command->replace(found, tagUserFileIn.size(), checkPath(temp));
		found = command->find(tagUserFileIn, found + temp.size());
	}

	// Manage tag "{user.file.out.*}"
	found = command->find(tagUserFileOut);
	while (found != std::string::npos)
	{
#ifdef LINUX
		size_t foundBraket = command->find("}", found + tagUserFileOut.size());
		std::string extension (*command,found + tagUserFileOut.size(),foundBraket-(found+tagUserFileOut.size()));
		std::string tag = tagUserFileOut + extension + "}";
		std::transform(type.begin(),type.end(),type.begin(),::toupper);
		temp = getPath(pathInfile) + basename + type + "." + extension;
#endif
#ifdef WINDOWS
		size_t foundBraket = command->find("}", found + tagUserFileOut.size());
		std::string extension (*command,found + tagUserFileOut.size(),foundBraket-(found+tagUserFileOut.size()));
		std::string tag = tagUserFileOut + extension + "}";
		std::transform(type.begin(),type.end(),type.begin(),::toupper);
		temp = getPath(pathInfile) + basename + type + "." + extension;
#endif
		command->replace(found,tag.size(),checkPath(temp));
		found = command->find(tagUserFileOut, found + temp.size());
	}

	// Manage tag "{user.time}"
	found = command->find(tagUserTime);
	while (found != std::string::npos)
	{
		temp = DoubleToString(timePreview);
		command->replace(found, tagUserTime.size(), temp);
		found = command->find(tagUserTime, found + temp.size());
	}

	#ifdef WINDOWS
		*command = "\" " + *command + " \"";
	#endif
}


std::string checkPath (std::string path)
{
#ifdef LINUX
	size_t found;
	std::string charToFind = " ";
	std::string charReplace = "\\ ";
	found = path.find(charToFind);
	while (found != std::string::npos)
	{
		path.replace(found, charToFind.size(), charReplace);
		found = path.find(charToFind, found + charReplace.size());
	}
#endif
#ifdef WINDOWS
	size_t found;
	std::string charToFind = "/";
	std::string charReplace = "\\";
	found = path.find(charToFind);
	while (found != std::string::npos)
	{
		path.replace(found, charToFind.size(), charReplace);
		found = path.find(charToFind, found + charReplace.size());
	}
	path = "\"" + path + "\"";
#endif
	return path;
}


int getPercentage(int value,int maximum)
{
	return (value * 100 / maximum);
}


std::string DoubleToString(double number)
{
	std::ostringstream temp;
	temp << number;                                                        // Double to String
	return temp.str();
}