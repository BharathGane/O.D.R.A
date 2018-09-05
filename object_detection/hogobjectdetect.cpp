//detect objects using a SVM trained using hog features from positive and negative images of concerned objects

//#include "types.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <stdarg.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>
#include <highgui.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ml/ml.hpp"
#include <typeinfo>
using namespace cv;
using namespace cv::ml;
using namespace std;

void svmdetector(Ptr<SVM>& svm,vector< float >& hogdetector);

void drawlocations(Mat& draw,const vector< Rect >& objectlocations);

int main(int argc,char** argv) {

    int option = 1;
    int esc=27;

    Mat img,grayimg,draw;
    vector< Rect > objectlocations;
    vector< Point > foundpoints;
    string trainedsvmname=argv[1];

    Ptr<SVM> svm = StatModel::load<SVM>(trainedsvmname);
    HOGDescriptor hog(Size(64,48),Size(8,8),Size(4,4),Size(4,4),9);

    vector < float >  hogdetector;
    svmdetector(svm,hogdetector);

    hog.setSVMDetector(hogdetector);

    if(option==1) {
        img=imread(argv[2]); 
        resize(img,img,Size(1024,1024));
        draw=img.clone();

        objectlocations.clear();

        hog.detectMultiScale(img,objectlocations,0.0,Size(9,9),Size(5,5),1.05,1.5);
        drawlocations(draw,objectlocations);
    }
    exit(0);
    return -1;
}

void svmdetector(Ptr<SVM>& svm,vector< float >& hogdetector) {
    Mat sv=svm->getSupportVectors();
    int svtot=sv.rows;
    Mat alpha,svidx;
    double rho=svm->getDecisionFunction(0,alpha,svidx);

    CV_Assert(alpha.total()==1 && svidx.total()==1 && svtot==1);
    CV_Assert((alpha.type()==CV_64F && alpha.at<double>(0)==1.) || (alpha.type()==CV_32F && alpha.at<float>(0)==1.f));
    CV_Assert(sv.type()==CV_32F);

    hogdetector.clear();
    hogdetector.resize(sv.cols+1);
    memcpy(&hogdetector[0], sv.ptr(),sv.cols*sizeof(hogdetector[0]));
    hogdetector[sv.cols]=(float)-rho;
}

void drawlocations(Mat& draw,const vector< Rect >& objectlocations) {
    if(objectlocations.empty()) exit(0);
    RNG rng(12345);

    vector< Rect >::const_iterator start   =  objectlocations.begin();
    vector< Rect >::const_iterator end     =  objectlocations.end();

    for( ; start!=end ; start++)
      rectangle(draw,*start,Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) ),1);
    cout<<"Center Coordinates: "<<objectlocations[0];

    ofstream file;
    file.open("/home/kishore/Documents/Projects/O.D.R.A/main_controller/coordinates.txt");
    file << objectlocations[0];
    imwrite("/home/kishore/Documents/Projects/O.D.R.A/main_controller/final.png",draw);
    file.close();
}
