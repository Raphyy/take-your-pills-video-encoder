//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphy
// Website     : www.takeyourpills.fr
// Copyright   : Please contact contact@takeyourpills.fr
//============================================================================


#include "os.h"

#ifdef LINUX
	#include <Phonon>
#endif
#ifdef WINDOWS
	#include <Phonon/MediaObject>
#endif

#include <QUrl>
#include <QLabel>
#include "previewForm.h"


// Define constants to skip images and steps
const int intFrameOffset = 50;
const int intStepOffset = 300;
const int intPreviewOffset = 35;


previewForm::previewForm()
{
    widget.setupUi(this);
    
    QObject::connect(widget.pushbuttonPlay,SIGNAL(clicked()),this,SLOT(play()));
    QObject::connect(widget.pushbuttonPause,SIGNAL(clicked()),this,SLOT(pause()));
    QObject::connect(widget.pushbuttonStop,SIGNAL(clicked()),this,SLOT(stop()));
    QObject::connect(widget.phononVideoPlayer, SIGNAL(finished()),this, SLOT(stop()));
    QObject::connect(widget.pushbuttonPreviousFrame,SIGNAL(clicked()),this,SLOT(jumptoPreviousFrame()));
    QObject::connect(widget.pushbuttonNextFrame,SIGNAL(clicked()),this,SLOT(jumptoNextFrame()));
    QObject::connect(widget.pushbuttonPreviousStep,SIGNAL(clicked()),this,SLOT(jumptoPreviousStep()));
    QObject::connect(widget.pushbuttonNextStep,SIGNAL(clicked()),this,SLOT(jumptoNextStep()));
    QObject::connect(widget.pushbuttonChoose,SIGNAL(clicked()),this,SLOT(choose()));
    QObject::connect(widget.pushbuttonChoose,SIGNAL(clicked()),widget.phononVideoPlayer, SLOT(stop()));
}


previewForm::~previewForm()
{
    
}


void previewForm::receivePath(QString pathVideo)
{
    mdobjVideo = new Phonon::MediaObject;
    mdobjVideo->setCurrentSource(QUrl(pathVideo));
    widget.phononSeekSlider->setMediaObject(widget.phononVideoPlayer->mediaObject());
}


void previewForm::play()
{
    widget.labelTakeYourPillsLogo->setVisible(false);
    widget.phononVideoPlayer->play(mdobjVideo->currentSource());
}


void previewForm::pause()
{
   widget.phononVideoPlayer->pause();
}


void previewForm::stop()
{
   widget.phononVideoPlayer->stop();
   widget.labelTakeYourPillsLogo->setVisible(true);
}


void previewForm::jumptoPreviousFrame()
{
    widget.phononVideoPlayer->seek(widget.phononVideoPlayer->currentTime() - intFrameOffset);
}


void previewForm::jumptoNextFrame()
{
    widget.phononVideoPlayer->seek(widget.phononVideoPlayer->currentTime() + intFrameOffset);
}


void previewForm::jumptoPreviousStep()
{
    widget.phononVideoPlayer->seek(widget.phononVideoPlayer->currentTime() - intStepOffset);
}


void previewForm::jumptoNextStep()
{
    widget.phononVideoPlayer->seek(widget.phononVideoPlayer->currentTime() + intStepOffset);
}


void previewForm::choose()
{
    emit sendTime((double(widget.phononVideoPlayer->currentTime() + intPreviewOffset) / 1000.0));
    close();
}