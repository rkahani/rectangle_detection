#include <stdio.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>


using namespace cv;
using namespace std;
using std::string;

const Scalar red_low(0, 128, 128);//0
const Scalar red_high(40, 255, 255);
const Scalar blue_low(80, 128, 128);//120
const Scalar blue_high(140, 255, 255);
const Scalar white_low(0, 0, 128);
const Scalar white_high(180, 20, 255);

struct data
{
	data(std::vector<Point> v, string s)
	{
		vertices = v;
		description = s;
	}
	std::vector<Point> vertices;
	string description;
	void write(FileStorage& fs) const
	{
		fs <<"boundingPoly" << "{:";
		fs << "vertices" << "[";
		for(int i=0; i < vertices.size(); i++)
		{
			fs << "{:" << "x" << vertices[i].x << "y" << vertices[i].y <<"}:";
		}
		fs << "]";
		fs << "}:";
		fs << "description" << description;
	}
};


void find_rectangles(Mat im_hsv, Scalar low, Scalar high, Point min_size, Point max_size, FileStorage& fs)
{
	std::vector<Point> points;
	Mat im_bin;
	inRange(im_hsv, low, high, im_bin);
	vector<vector<Point>> contours;
	findContours(im_bin, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Rect rect;
	for(int c=0; c<contours.size(); c++)
	{
		rect = boundingRect(contours[c]);
		int width = rect.br().x - rect.tl().x;
		int height = rect.br().y - rect.tl().y;
		// filtering
		if ( width < min_size.x ||  width > max_size.x || height < min_size.y || height > max_size.y || contourArea(contours[c]) < width * height * 0.6) continue;
		points.push_back(rect.tl());
		points.push_back(rect.br());
		data d(points, "Rectangle");
		d.write(fs);
		points.clear();
	}
}

void find_circles(Mat im_hsv, Scalar low, Scalar high, int min_r, int max_r, FileStorage& fs)
{
	std::vector<Point> points;
	Mat im_bin;
	inRange(im_hsv, low, high, im_bin);
	vector<vector<Point>> contours;
	findContours(im_bin, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	float radius;
	Point2f center;
	for(int c=0; c<contours.size(); c++)
	{
		minEnclosingCircle(contours[c], center, radius);
		// filtering
		if ( radius < min_r ||  radius > max_r || contourArea(contours[c]) < 3.14 * (radius ** 2) * 0.9) continue;
		points.push_back(Point(ceil(center.x-radius), ceil(center.y-radius)));
		points.push_back(Point(ceil(center.x+radius), ceil(center.y+radius)));
		data d(points, "Circle");
		d.write(fs);
		points.clear();
	}	
}


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: detector <Image_Path>\n");
        return -1;
    }
    Mat im = imread( argv[1], 1 );
    if ( !im.data )
    {
        printf("No image data \n");
        return -1;
    }
	FileStorage fs("output.json", FileStorage::WRITE);
	int h = im.rows;
	int w = im.cols;
	Mat im_hsv;
    cvtColor(im, im_hsv, cv::COLOR_BGR2HSV);
	// red rectangle
	find_rectangles(im_hsv, red_low, red_high, Point(25, 25), Point(w/3, h/3), fs);
	// white rectangle
	find_rectangles(im_hsv, white_low, white_high, Point(w/3, 25), Point(w+1, h/3), fs);
	// blue circle
	find_circles(im_hsv, blue_low, blue_high, 25, h/3, fs);
	fs.release();
    return 0;
}
