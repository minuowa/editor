#include "stdafx.h"
#include "EScenePanel.h"
#include "Game.h"
EScenePanel::EScenePanel(QWidget *parent)
	//: QFrame(parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

EScenePanel::~EScenePanel()
{

}

void EScenePanel::resizeEvent( QResizeEvent * szEvent)
{
	__super::resizeEvent ( szEvent );
	QRect rc = this->rect();
	TheGame->resize ( rc.width(), rc.height() );
}
