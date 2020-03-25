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

//definition========================================================================================================
//image Paths
#define ImagePath1 ".\\lena.png"

#define ImagePath2 "Images/120427084436-face-detection-fashion-story-top.jpg"
#define ImagePath3 "Images/apeN7SK.jpg"
#define ImagePath4 "Images/Przechwytywanie.PNG"
#define ImagePath5 "Images/1.jpg"
#define ImagePath6 "Images/aNAAxmK_700b.jpg"
#define ImagePath7 "Images/nikons60_2.jpg"
#define ImagePath8 "Images/imagetest1.jpg"
#define ImagePath9 "Images/imagetest2.png"
#define ImagePath10 "Images/imagetestMelon.jpg"
#define ImagePath11 "Images/indeks.jpeg"
#define ImagePath12 "Images/pr00748-obraz-pulp-fiction.jpg.png"
#define ImagePath13 "Images/morgan-freeman2.jpg"
#define ImagePath14 "Images/key_conference_voting.jpg"
#define ImagePath15 "Images/LiSA-300x226.jpg"
#define ImagePath16 "Images/old-age.jpg"
#define ImagePath17 "Images/3746221-angelina-jolie-669-900.jpg"
#define ImagePath18 "Images/robert-downey-jr-tony-stark.jpg"
#define ImagePath19 "Images/1481536354.227_YsUzaZ_n.jpg"

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
