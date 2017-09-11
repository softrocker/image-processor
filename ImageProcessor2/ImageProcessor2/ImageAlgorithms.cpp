#include "ImageAlgorithms.h"
#include <QImage>
#include <assert.h>
#include <omp.h>
#include <thread>

void ImageAlgorithms::invertColors(QImage& image)
{
	int imageFormat = image.format();
	assert(image.format() == QImage::Format_RGB32);
	if (image.format() != QImage::Format_RGB32)
	{
		return;
	}
	// Get the line we want
	const int c_rows_count = image.height();
	const int c_cols_count = image.width();
//#pragma omp parallel for
	for (int row = 0; row < c_rows_count; row++)
	{
		for (int col = 0; col < c_cols_count; col++)
		{
			// Go to the pixel we want
			QRgb *line = (QRgb*)image.scanLine(row);
			line += col;
			QRgb color = *line;

			// Actually set the pixel
			const uchar c_value_max = 255;
			*line = qRgb(c_value_max - qRed(color), c_value_max - qGreen(color), c_value_max - qBlue(color));
		}
	}
	
}

void ImageAlgorithms::invertColors2(QImage& image)
{

}
