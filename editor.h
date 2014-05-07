#ifndef EDITOR_H
#define EDITOR_H

#include <QtGui/QMainWindow>
#include "ui_editor.h"
#include "EEditorSheetManager.h"

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor ( QWidget *parent = 0, Qt::WFlags flags = Qt::WindowMinMaxButtonsHint );
    ~Editor();

    void InitObjectMenu ( const QVector<QString>& list );
protected:
    virtual void timerEvent ( QTimerEvent * );
    virtual bool winEvent ( MSG *message, long *result );

    void setFocus ( Qt::FocusReason reason );

public slots:
    void openFile();
    void createObj ( const char* string );

private:
    Ui::EditorClass ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QDockWidget* mObjectPropertyPanel;
    QDockWidget* mObjectListPanel;
    QWidget* mScenePanel;
    QString curSceneFile;

    int  mIdleTimeID;
public:
    QDockWidget* GetObjectEditPanel() const
    {
        return mObjectPropertyPanel;
    }
    QDockWidget* GetObjectListPanel() const
    {
        return mObjectListPanel;
    }
    QWidget* GetScenePanel() const
    {
        return reinterpret_cast<QWidget*> ( mScenePanel );
    }
};

#endif // EDITOR_H
