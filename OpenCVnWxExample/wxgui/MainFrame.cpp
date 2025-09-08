#include "MainFrame.h"
#include <wx/wx.h>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include <wx/wx.h>

using namespace cv;

static char HaarDetectionCamera(char mode);

enum customIDs {
	fButton_ID = 2,
    pButton_ID = 3,
    uButton_ID = 4,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(fButton_ID, MainFrame::OnHaarFrontButtonClicked)
	EVT_BUTTON(pButton_ID, MainFrame::OnHaarProfileButtonClicked)
	EVT_BUTTON(uButton_ID, MainFrame::OnHaarUpperBodyButtonClicked)
wxEND_EVENT_TABLE()

/// <summary>
/// App MainFrame 
/// </summary>
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* text = new wxStaticText(this, wxID_ANY, "O_O it finally works", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

	wxButton* button = new wxButton(this, fButton_ID, "Front-Face Haar Detection");
	wxButton* button2 = new wxButton(this, pButton_ID, "Profile-Face Haar Detection");
	wxButton* button3 = new wxButton(this, uButton_ID, "Upper-Body Haar Detection");

	text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	sizer->Add(button, 1, wxALIGN_LEFT, 10);
	sizer->Add(button2, 1, wxALIGN_CENTER, 10);
	sizer->Add(button3, 1, wxALIGN_BOTTOM, 10);
	sizer->Add(text, 1, wxALIGN_CENTER);
	this->SetSizer(sizer);

	CreateStatusBar();

	this->Show();
}


void MainFrame::OnHaarFrontButtonClicked(wxCommandEvent& evt) {
    HaarDetectionCamera('F');
}

void MainFrame::OnHaarProfileButtonClicked(wxCommandEvent& evt) {
    HaarDetectionCamera('P');
}

void MainFrame::OnHaarUpperBodyButtonClicked(wxCommandEvent& evt) {
    HaarDetectionCamera('U');
}

/// <summary>
/// ENG For Testing separeta HaarClass XML's on the live camera
/// TUR Ayrý HaarDetection sýnýflarý ve XML dosyalarýný canlý Kamerada test etmek içind
/// </summary>
/// <returns></returns>
static char HaarDetectionCamera(char mode) {

    cv::Scalar renkdegeri;
    std::string ObjectType;

    char Mode;

    Mode = mode;

    VideoCapture vid(0);
    CascadeClassifier casd;
    Mat matris;

    switch (Mode) {
    case 'F':
        casd.load("CascadeXMLs/haarcascade_frontalface_default.xml");
        renkdegeri = Scalar(50, 90, 255);
        ObjectType = "Yuz";

        break;
    case 'P':
        casd.load("CascadeXMLs/haarcascade_profileface.xml");
        renkdegeri = Scalar(155, 90, 255);
        ObjectType = "Profil Yuz";

        break;
    case 'U':
        casd.load("CascadeXMLs/haarcascade_upperbody.xml");
        renkdegeri = Scalar(144, 90, 255);
        ObjectType = "Beden";

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

        putText(matris, ObjectType + " : " + std::to_string(detObject.size()) + "?", cv::Point(10, 70), QT_FONT_NORMAL | FONT_ITALIC, 1,
            Scalar(255, 255, 255), 1);

        imshow("Kamera", matris);

        //TUR Döngüden çýkmak için
        int i = waitKey(25);

        if (i != -1) {
            break;
        }
    }

    return NULL;
}