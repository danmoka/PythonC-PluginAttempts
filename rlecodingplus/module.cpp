// данный файл содержит описание функции подсчета коэффициента сжатия метоом RLE.

#include <pybind11/pybind11.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

// Метод подсчета коэффициента сжатия.
// Return - коэффициент (от 0 до 1).
// Attributes - изображение, представленное в виде класса Mat библиотеки OpenCV.
double GetRleRatio(Mat& image)
{
	// accept only char type matrices
	CV_Assert(image.depth() == CV_8U);
	const int channels = image.channels();
	bool isFirst = true;
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		uchar prev;
		int count = 1;
		double result = 0;
		for (it = image.begin<uchar>(), end = image.end<uchar>(); it != end; ++it, isFirst = true)
		{
			if (isFirst)
			{
				prev = *it;
				isFirst = false;
			}
			else
			{
				if (abs(prev - *it) < 3)
				{
					count++;
				}
				else
				{
					result++;
					prev = *it;
					count = 1;
				}
			}

		}
		result++;
		result = result * 2.0 / (image.rows*image.cols);
		return result;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		int count = 1;
		double result = 0;
		uchar prevR, prevG, prevB;

		for (it = image.begin<Vec3b>(), end = image.end<Vec3b>(); it != end; ++it)
		{
			if (isFirst)
			{
				prevB = (*it)[0];
				prevR = (*it)[2];
				prevG = (*it)[1];
				isFirst = false;
			}
			else
			{
				if (abs(prevB - (*it)[0]) < 2 && abs(prevG - (*it)[1]) < 2 && abs(prevR - (*it)[2]) < 2)
				{
					count++;
				}
				else
				{
					// cout << "count=" << count << " pixel = " << prevB <<" "<<prevG<<" "<<prevR<<endl;
					result++;
					prevB = (*it)[0];
					prevR = (*it)[2];
					prevG = (*it)[1];
					count = 1;
				}
			}
		}
		result++;
		result = result * 4.0 / (image.rows*image.cols * 3);
		return result;
	}
	}
	return 1;
}

// Метод, реализующий вызов функции подсчета коэффициента сжатия.
double rle_impl() {
	Mat image;
	image = imread("C:\\Users\\danii\\Desktop\\picture.jpg"); // Read the file , IMREAD_COLOR
	double result = GetRleRatio(image);
	return result;
}

namespace py = pybind11;

// Код, который делает доступным метод rle_impl() из питона. 
// rle - под каким именем будет вызван метод из питона.
PYBIND11_MODULE(rlecodingplus, m) {
	m.def("rle", &rle_impl, R"pbdoc(
        Compute a rle.
    )pbdoc");

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}