#pragma once
#include "EPropertySheet.h"
#include "qobject.h"
#include "Game.h"
class EPropertySheet;
class EObjectListSheet;
class EOptionPanel;
class QTreeView;
class QWidget;
class QMenu;
class QMainWindow;
class QAction;
class Editor;
class  EEditorManager: public QObject, public CXCallBack
{
    Q_OBJECT
public:
    EEditorManager ( void );
    ~EEditorManager ( void );

    bool init ( Editor* parent );

    QTreeView* getPropertyView() const;
    QTreeView* getObjectListView() const;
    EObjectListSheet* getObjectListSheet() const;

    void initObjectMenu ( const CharStringArr& gameobjTypeArr );
    void setComponentMenuState ( const char* componentType, bool checked, bool enabled );

    void notifyPropertyChange ( void* pre, void* changed );
    void notifyPropertyChangeEnd ( void* cur );

    void updateObjectList();
    void updatePopMenu();
    void updatePropertySheet();

    void updateOptionSheet();

	Editor* getMainWindow();
public slots:
    void onAddObjectAction ( QAction* );
protected:
    EPropertySheet* mObjectPropertySheet;
    EPropertySheet* mOptionSheet;
    EObjectListSheet* mObjectListSheet;

    void* mWindowProc;
    QMainWindow* mParent;
    QMenu* mObjectMenu;
    QString mSelectedObj;

public:

    inline EPropertySheet* getPropertySheet() const
    {
        return mObjectPropertySheet;
    }
    inline 	const QString& getSelectObj() const
    {
        return mSelectedObj;
    }
    void SetSelectObj ( const char* obj );
	void clearSelect();
    virtual void onCallBack ( const CXDelegate& );

};

#define EditorMgr CXSingleton<EEditorManager>::GetSingletonPtr()
