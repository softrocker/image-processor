#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QGraphicsScene;
class GraphicsView;
class QPushButton;

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
private:
	void createSettings();
	void createMenu();
	void createActions();
	void createLayouts();
	void createViewsAndScenes();

	void loadImage();
	void saveImage();
	void updateImage();


	void invertColors();
	//void addEmptyLabels(QWidget* parent, QLayout* layout, int numberOfLabels);

private:
	QGraphicsScene* scene_;
	GraphicsView* view_;
	QImage image_;

	QAction* actionLoadImage_;
	QAction* actionSaveImage_;
	QAction* actionExit_;

	QAction* actionOperInverseColors_;
};

#endif // STEGO_H
