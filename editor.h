#ifndef EDITOR_H
#define EDITOR_H

#include "EEditorManager.h"
#include "qmainwindow.h"
namespace Ui {
	class MainWindow;
}
class Editor : public QMainWindow
{
    Q_OBJECT

public:
	Editor ( QWidget *parent = 0, Qt::WindowType flags = Qt::WindowOverridesSystemGestures );
	//Editor ( QWidget *parent = 0, Qt::WindowType flags = Qt::Window );
    ~Editor();

protected:
    virtual void timerEvent ( QTimerEvent * );
    virtual bool winEvent ( MSG *message, long *result );

    void setFocus ( Qt::FocusReason reason );
	virtual void mouseMoveEvent(QMouseEvent *);
	bool event(QEvent *);

public slots:
    void openFile();
	void changeToNextCamera();
	void saveFile();
private:
    Ui::MainWindow* ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
	QMenu* mAssistMenu;
    QDockWidget* mObjectPropertyPanel;
    QDockWidget* mObjectListPanel;
	QDockWidget* mOptionPanel;
    QWidget* mScenePanel;
    QString curSceneFile;

    int  mIdleTimeID;
public:
    QDockWidget* getObjectEditPanel() const
    {
        return mObjectPropertyPanel;
    }
    QDockWidget* getObjectListPanel() const
    {
        return mObjectListPanel;
    }
	QDockWidget* getOptionPanel() const
	{
		return mOptionPanel;
	}
    QWidget* getScenePanel() const
    {
        return  mScenePanel;
    }
};

#endif // EDITOR_H
