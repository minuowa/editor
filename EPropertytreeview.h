#ifndef EPROPERTYTREEVIEW_H
#define EPROPERTYTREEVIEW_H

#include <QTreeView>

class EPropertyTreeView : public QTreeView
{
	Q_OBJECT

public:
	EPropertyTreeView(QWidget *parent = 0);
	~EPropertyTreeView();
signals:
	void changed(const QMimeData *mimeData = 0);
protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);
};

#endif // EPROPERTYTREEVIEW_H
