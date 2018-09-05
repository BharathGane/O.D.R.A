//train SVM
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
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ml/ml.hpp"

void help();

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc,char** argv) {
     FileStorage readpositivexml(argv[1],FileStorage::READ);
     FileStorage readnegativexml(argv[2],FileStorage::READ);

     Mat pMat;
     readpositivexml["DescriptorOfImages"]>>pMat;
     int pRow=pMat.rows,pCol=pMat.cols;

     Mat nMat;
     readnegativexml["DescriptorOfImages"]>>nMat;
     int nRow=nMat.rows,nCol=nMat.cols;

     readpositivexml.release();
     readnegativexml.release();

     Mat PNDescriptor(pRow+nRow,pCol,CV_32FC1);
     memcpy(PNDescriptor.data,pMat.data,sizeof(float)*pCol*pRow);     

     int startP=sizeof(float)*pMat.cols*pMat.rows;
     memcpy(&(PNDescriptor.data[startP]),nMat.data,sizeof(float)*nCol*nRow);

     Mat labels(pRow+nRow,1,CV_32SC1,Scalar(-1));
     labels.rowRange(0,pRow)=Scalar(1);

     Ptr<SVM> svm=SVM::create();
     svm->setType(SVM::C_SVC);
     svm->setCoef0(0.5);
     svm->setDegree(3);
     svm->setGamma(0);
     svm->setKernel(SVM::LINEAR);
     TermCriteria criteria(TermCriteria::MAX_ITER,10000,1e-6);
     svm->setTermCriteria(criteria);
     svm->setNu(0.8);
     svm->setP(10);
     svm->setC(0.01);

     svm->train(PNDescriptor,ROW_SAMPLE,labels);
     svm->save(argv[3]);
     return -1;
}

