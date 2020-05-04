

#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

void loadFont(const QString & fontPath)
{
	int id = QFontDatabase::addApplicationFont(fontPath);
	QFontDatabase database;
	QStringList families = database.applicationFontFamilies(id);
	if (families.count()) {
		QString family = families.at(0);
		QFont _font(family);
		qApp->setFont(_font);
	} else {
		qDebug() << "ERROR to load font:" << fontPath;
	}
}

int main(int argc, char *argv[])
{
	if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
		qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
		qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	}

	QGuiApplication app(argc, argv);

	QString defAppFont = QGuiApplication::font().toString();

	qDebug() << "Original default font:" << defAppFont;

	loadFont(":/ihm/font/Android.ttf");
	loadFont(":/ihm/font/Exo-Medium.ttf");
	loadFont(":/ihm/font/Generica.otf");
	loadFont(":/ihm/font/Monoglyceride.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-Black.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-Bold.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-BoldItalic.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-ExtraLight.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-ExtraLightItalic.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-Italic.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-Light.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-LightItalic.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-Regular.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-SemiBold.ttf");
	loadFont(":/ihm/font/titillium-web/TitilliumWeb-SemiBoldItalic.ttf");

	QString newAppFont = QGuiApplication::font().toString();

	qDebug() << "New default font:" << newAppFont;

	QQmlApplicationEngine engine;
	QQmlContext * context = engine.rootContext();

	context->setContextProperty("defAppFont", defAppFont);
	context->setContextProperty("newAppFont", newAppFont);

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
