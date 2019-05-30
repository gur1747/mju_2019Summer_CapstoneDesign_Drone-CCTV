#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
  
using namespace cv;
using namespace std;
 

int main()
{
    VideoCapture cap( -1 );
  
    if( !cap.isOpened() ) {
        cout << "Cannot open camera" << endl;
        return 0;
    	}

	namedWindow("raw Image");
	namedWindow("edge Image");
	moveWindow("raw Image", 00,20);
	moveWindow("edge Image", 640,20);
	

	cv::VideoWriter writer;
    // problem here
	//writer.open("appsrc ! video/x-raw, framerate=30/1, width=640, height=480 ! autovideoconvert ! autovideosink sync=false", 0, (double)30, cv::Size(640, 480), true);
    //writer.open("appsrc ! video/x-raw, framerate=30/1, width=640, height=480 ! autovideoconvert ! videoflip method=counterclockwise ! autovideosink sync=false", 0, (double)30, cv::Size(640, 480), true);
	//writer.open("appsrc ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host=192.168.0.89 port=5000", 0, (double)30, cv::Size(640, 480), false);
	//writer.open("appsrc ! videoconvert ! x264enc tune=zerolatency ! mpegtsmux ! udpsink host=192.168.0.89 port=5000", 0, (double)30, cv::Size(640, 480), false);
	writer.open("appsrc !  video/x-raw,  width=640, height=480 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! gdppay ! tcpserversink host=192.168.0.31 port=5000", 0, (double)30, cv::Size(640, 480), false);
    if (!writer.isOpened()) {
        printf("=ERR= can't create writer\n");
        return -1;
    	}

    cv::Mat frame,grayImage,edgeImage;
    int key;


    while (true) {
        cap >> frame;
		
        if (frame.empty()) {
            printf("no frame\n");
            break;
        	}
		cv::cvtColor( frame, grayImage, COLOR_RGB2GRAY );
		Canny(grayImage, edgeImage, 80, 150, 3);
		imshow("raw Image",frame);
		imshow("edge Image",edgeImage);
		
	

		writer << edgeImage;
        //writer << frame;
        if ( waitKey(20) == 27 ) break; //ESC키 누르면 종료
    }

    cv::destroyWindow( "video" );
}

