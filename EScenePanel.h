#ifndef ESCENEPANEL_H
#define ESCENEPANEL_H

#include <QFrame>
#include "ui_EScenePanel.h"
#include "qwidget.h"

class EScenePanel : public QWidget
{
	Q_OBJECT

public:
	EScenePanel(QWidget *parent = 0);
	~EScenePanel();
	virtual void resizeEvent(QResizeEvent *);

private:
	Ui::EScenePanel ui;
};

#endif // ESCENEPANEL_H
