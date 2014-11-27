#ifndef EFILMSHEETDELEGATE_H
#define EFILMSHEETDELEGATE_H

#include <QItemDelegate>

class EFilmSheetDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	EFilmSheetDelegate(QObject *parent = 0);
	~EFilmSheetDelegate();
protected:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
private:
	
};

#endif // EFILMSHEETDELEGATE_H
