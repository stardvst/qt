#include <QApplication>
#include <QStandardItemModel>
#include <QTableView>
#include "spinBoxDelegate.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QStandardItemModel model(4, 2);
	QTableView tableView;
	tableView.setModel(&model);

	SpinBoxDelegate delegate;
	tableView.setItemDelegate(&delegate);

	for (auto row = 0; row < 4; ++row)
	{
		for (auto column = 0; column < 2; ++column)
		{
			const auto index = model.index(row, column, {});
			model.setData(index, QVariant{ (row + 1)*(column + 1) });
		}
	}

	tableView.setWindowTitle(QObject::tr("Spin Box Delegate"));
	tableView.show();

	return QApplication::exec();
}
