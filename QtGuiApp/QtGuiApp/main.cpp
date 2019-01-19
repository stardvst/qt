#include <QApplication>
#include <QTreeWidget>
#include <QHeaderView>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTreeWidget treeWidget;
	treeWidget.setColumnCount(2);

	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < 5; ++i)
		items.append(new QTreeWidgetItem(&treeWidget,
			QStringList{ "item", QString("%1").arg(i) }));
	treeWidget.insertTopLevelItems(0, items);
	
	auto header = treeWidget.header();
	header->setSectionResizeMode(0, QHeaderView::Stretch);
	header->setSectionResizeMode(1, QHeaderView::Fixed);
	header->setStretchLastSection(false);
	header->setDefaultSectionSize(50);

	treeWidget.show();

	return QApplication::exec();
}
