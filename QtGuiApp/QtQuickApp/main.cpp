#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_DisableShaderDiskCache);

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	engine.load(QUrl(QStringLiteral("qrc:/red_rect.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}