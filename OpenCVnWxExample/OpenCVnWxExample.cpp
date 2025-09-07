#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include <wx/wx.h>

using namespace cv;

char HaarDetectionCamera();

class App : public wxApp {

    bool OnInit() {


        wxFrame* window = new wxFrame(NULL, wxID_ANY, "GUI wx", wxDefaultPosition, wxSize(600, 800));
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* text = new wxStaticText(window, wxID_ANY, "O_O it finally works", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

        text->SetFont(wxFont(20,wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        sizer->Add(text,1, wxALIGN_CENTER);

        window->SetSizer(sizer);
        window->Show();

        return true;

    }


};

wxIMPLEMENT_APP(App);


/// <summary>
/// ENG For Testing separeta HaarClass XML's on the live camera
/// TUR Ayrı HaarDetection sınıfları ve XML dosyalarını canlı Kamerada test etmek içind
/// </summary>
/// <returns></returns>
char HaarDetectionCamera() {

    cv::Scalar renkdegeri;

    std::cout << "Modlar :: [F] Front Face Detection \n";
    std::cout << "[P] Profil Face Detection \n";

    std::string Girdi;
    char Mode;

    std::cout << "Mod seciniz :: ";
    std::cin >> Girdi;

    Mode = Girdi[0];

    VideoCapture vid(0);
    CascadeClassifier casd;
    Mat matris;

    switch (Mode) {
    case 'F':
        casd.load("CascadeXMLs/haarcascade_frontalface_default.xml");
        renkdegeri = Scalar(50, 90, 255);
        break;
    case 'P':
        casd.load("CascadeXMLs/haarcascade_profileface.xml");
        renkdegeri = Scalar(155, 90, 255);

        break;
    case 'U':
        casd.load("CascadeXMLs/haarcascade_upperbody.xml");
        renkdegeri = Scalar(144, 90, 255);

        break;
    default:
        std::cout << "Geçersiz Karakter";
        break;
    }

    std::vector<cv::Rect> detObject;

    while (true) {
        vid.read(matris);

        casd.detectMultiScale(matris, detObject, 1.1, 5);

        for (int i = 0; i < detObject.size(); i++) {
            rectangle(matris, detObject[i].tl(), detObject[i].br(), renkdegeri, 3);
        }

        putText(matris, "Yuzler : " + std::to_string(detObject.size()) + "?", cv::Point(10, 70), QT_FONT_NORMAL | FONT_ITALIC, 1,
            Scalar(255, 255, 255), 1);

        imshow("Kamera", matris);
        waitKey(25);
    }

    return NULL;
}

