/*
 * NPDLibraries.hpp
 *
 *      Author: marek
 */

#ifndef NPDLIBRARIES_HPP_
#define NPDLIBRARIES_HPP_

#include <vector>//vector

#include <opencv2/highgui.hpp>//Mat object
#include <opencv2/imgproc/imgproc.hpp>//BGR2GRAY
#include <opencv2/opencv.hpp>//multimap

#include <iostream>//cout
#include "ModelLoading.hpp"//My loading functions
#include <stdlib.h>//do dynamicznego przydzielania pamięci

#include <omp.h>

//definition========================================================================================================
//image Paths
#define ImagePath1 ".\\lena.png"

//#define DetectionColor (125,255,125)
#define DetectionColor Scalar(0,255,6)

//END of definition==================================================================================================

using namespace std;
using namespace cv;


//Variables==========================================================================================================

//END of Variables===================================================================================================



//functions==========================================================================================================

void nonMaximumSupression(vector<Rect>*,vector<Rect>*,float *);
void drawingFaces(Mat*,vector<Rect>*, Scalar, int);
void FaceDetectionByNDP(Mat*,vector<Rect>*,NDPDetectorModel*);


vector<int> stageOfChoosenFaces(Mat* , vector<int>* , vector<int>* , vector<int>* , vector<float>* , vector<int>* , float* );
int Find(vector<int>*, int);
int DeterminingNumberOfGroups(Mat*, vector<int>*);
vector<float> Logistic(vector<float>*, vector<int>*);
//END of //functions==========================================================================================================



#endif /* NPDLIBRARIES_HPP_ */
