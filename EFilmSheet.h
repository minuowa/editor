#ifndef EFilmSheet_H
#define EFilmSheet_H

#include <QWidget>
#include "..\..\..\Qt\Qt5.3.2\5.3\msvc2012_opengl\include\QtCore\qitemselectionmodel.h"
namespace Ui
{
class EFilmSheet;
}
class QMenuBar;
class QPushButton;
class QStyleOptionToolBar;
class QRadioButton;
class QMenu;
class QListView;
class EFilmSheet : public QWidget,public CXCallBack
{
    Q_OBJECT

public:
    EFilmSheet ( QWidget *parent = 0 );
    ~EFilmSheet();
public slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();

    void onPlay();
    void onPause();
    void onStop();

	void addFrame();
	void deleteFrame();
	void playFrame();

	void onClicked(const QModelIndex &index);
public:
	virtual void onCallBack ( const CXDelegate& , CXEventArgs*  )override;
protected:
	virtual bool event(QEvent* event);
protected:
    Ui::EFilmSheet* ui;
	QListView* mFrameList;
	QMenu* mPopMenu;
	QModelIndex mSelectedIndex;
};

#endif // EFilmSheet_H
