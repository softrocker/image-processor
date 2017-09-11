#include "MainWindow.h"
#include "GraphicsView.h"
#include <QLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QPushbutton>
#include <iostream>
#include <string>
#include <locale.h>
#include "DataTransfer.h"
#include "ImageAlgorithms.h"
#include <QDebug>

//#include <thread>
//include <asyncinfo.h>
//#include <future>
#include <QImageReader>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	createSettings();
	createActions();
	createMenu();
	createViewsAndScenes();
	createLayouts();

	image_ = QImage();
}

void MainWindow::createSettings()
{
	setlocale(LC_ALL, "russian");
}

void MainWindow::createActions()
{
	//file actions:
	actionLoadImage_ = new QAction(tr("&Load image..."), this);
	actionLoadImage_->setStatusTip(tr("Load image to file"));
	connect(actionLoadImage_, &QAction::triggered, this, &MainWindow::loadImage);

	actionSaveImage_ = new QAction(tr("&Save image..."), this);
	actionSaveImage_->setStatusTip(tr("Load image to file"));
	connect(actionSaveImage_, &QAction::triggered, this, &MainWindow::saveImage);

	actionExit_ = new QAction(tr("&Exit"), this);
	actionExit_->setStatusTip(tr("Exit"));
	connect(actionExit_, &QAction::triggered, this, &MainWindow::close);

	//operation actions:
	actionOperInverseColors_ = new QAction(tr("&Invert colors..."), this);
	actionOperInverseColors_->setStatusTip(tr("Invert colors"));
	connect(actionOperInverseColors_, &QAction::triggered, this, &MainWindow::invertColors);
}


void::MainWindow::createViewsAndScenes()
{
	scene_ = new QGraphicsScene(this);
	view_ = new GraphicsView(scene_);
	view_->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::createLayouts()
{
	QWidget* mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	QLayout* imagesLayout = new QHBoxLayout();
	imagesLayout->addWidget(view_);

	QLayout* mainLayout = new QVBoxLayout();
	mainLayout->addItem(imagesLayout);
	mainWidget->setLayout(mainLayout);
}

void MainWindow::createMenu()
{
	QMenu* menuMain = menuBar()->addMenu(tr("File"));
	menuMain->addAction(actionLoadImage_);
	menuMain->addAction(actionSaveImage_);
	menuMain->addAction(actionExit_);

	QMenu* menuOperations = menuBar()->addMenu(tr("Operations"));
	menuOperations->addAction(actionOperInverseColors_);
}

void MainWindow::loadImage()
{
	/*QImage img = DataTransfer::loadImg(this);
	if (!img.isNull())
	{
		scene_->clear();
		scene_->addPixmap(QPixmap::fromImage(img));
		image_ = img;
	}*/

	QString imageName = DataTransfer::imageName(this);
	QImageReader reader(imageName);
	qDebug() << "Image size:" << reader.size();
//	if (!img.isNull())
	{
		//cv::Mat m = cv::imread(imageName.toStdString());
		
		scene_->clear();
	//	reader.setClipRect(QRect(0,0,22000,22000));
		qDebug() << "image size:" << reader.size();
		image_ = reader.read();
		qDebug() << "Image size:" << image_.size();
		QPixmap pixmap(imageName);
		scene_->addPixmap(QPixmap::fromImage(image_));
	}
	
}

void MainWindow::saveImage()
{
	DataTransfer::saveImage(this, image_);
}

void MainWindow::updateImage()
{
	scene_->update();
}

MainWindow::~MainWindow()
{

}

void MainWindow::invertColors()
{
	ImageAlgorithms::invertColors(image_); //std::future<void>f(std::async(doSomeWork, std::ref(image_)));/*doSomeWork(image_);*///std::future<void>f(std::async(doSomeWork, image_));
	scene_->clear();
	scene_->addPixmap(QPixmap::fromImage(image_));
	//scene_->update();
}