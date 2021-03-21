#include <QApplication>
#include <QLineEdit>
#include <QIntValidator>
#include <QDebug>

class MyValidator : public QIntValidator
{
public:
	using QIntValidator::QIntValidator;

	QValidator::State validate(QString &input, int &pos) const override
	{
		auto state = QIntValidator::validate(input, pos);
		if (state == QValidator::State::Intermediate && input.length() == std::to_string(top()).length())
			return  QValidator::State::Invalid;
		return state;
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QLineEdit lineEdit;
	lineEdit.setValidator(new MyValidator(0, std::numeric_limits<int>::max(), &lineEdit));
	lineEdit.show();

	return app.exec();
}
