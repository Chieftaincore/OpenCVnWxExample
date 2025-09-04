

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int FrontalFaceDetCamera();
int imgshow();

int main()
{
    FrontalFaceDetCamera();
}

int imgShow() {
    cv::Mat img = cv::imread("D:/My_OpenCV/Morph/cicek.jpg");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}


/// <summary>
/// BasicExample of FrontalFaceDetection
/// </summary>
/// <returns></returns>
int FrontalFaceDetCamera() {

    VideoCapture vid(0);
    CascadeClassifier casd;
    Mat matris;

    casd.load("haarcascade_frontalface_default.xml");
    cv:Vec2b yuzler;

    std::vector<cv::Rect> faces;

    while (true) {
        vid.read(matris);
        casd.detectMultiScale(matris, faces, 1.3, 5);

        for (int i = 0; i < faces.size(); i++) {
            rectangle(matris, faces[i].tl(), faces[i].br(), Scalar(50, 90, 190), 3);
        }

        imshow("Kamera", matris);
        waitKey(25);
    }
}
