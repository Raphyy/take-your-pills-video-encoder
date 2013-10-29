//============================================================================
// Name        : Take Your Pills Video Encoder
// Author      : Raphy
// Website     : www.takeyourpills.fr
// Copyright   : Please contact contact@takeyourpills.fr
//============================================================================


#ifndef _NEWFORM_H
#define	_NEWFORM_H


#include "ui_previewForm.h"


class previewForm : public QDialog
{
    Q_OBJECT
    public:
        previewForm();
        virtual ~previewForm();
        QString pathUserFileInput;
    
    signals:
        void sendTime(double);
    
    public slots:
        void receivePath(QString);
        void play();
        void pause();
        void stop();
        void jumptoPreviousFrame();
        void jumptoNextFrame();
        void jumptoPreviousStep();
        void jumptoNextStep();
        void choose();
        
    private:
        Ui::previewForm widget;
        Phonon::MediaObject *mdobjVideo;
};


#endif	/* _NEWFORM_H */
