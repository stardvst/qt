#pragma once

#include <QStyledItemDelegate>
#include <QSpinBox>

class SpinBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit SpinBoxDelegate(QObject *parent = nullptr)
		: QStyledItemDelegate(parent)
	{
	}

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		const auto editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setRange(0, 100);
		return editor;
	}

	void setEditorData(QWidget *editor, const QModelIndex &index) const override
	{
		const auto value = index.model()->data(index, Qt::EditRole).toInt();
		static_cast<QSpinBox *>(editor)->setValue(value);
	}

	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
	{
		const auto spinBox = static_cast<QSpinBox *>(editor);
		spinBox->interpretText();
		model->setData(index, spinBox->value(), Qt::EditRole);
	}

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		editor->setGeometry(option.rect);
	}

	// delegates are often stateless
};
