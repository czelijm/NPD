#include "ModelLoading.hpp"//My loading functions
#include "NPDLibraries_serial.hpp"
#include "TimeMeasure.hpp"
#include <omp.h>


//openCV name space
using namespace cv;
//C++ name space
using namespace std;

int main(void)
{

//inicialization or deklaration of variables and arrays======================================================
//Detector model----------------------------------------------------------------------------------------------
//struct
	NDPDetectorModel NDPDetectorModel_Frontal;
	NDPDetectorModel NDPDetectorModel_Uncontrained;
//poiter to struct
	NDPDetectorModel *pointer_NDPDetectorModel_Frontal=&NDPDetectorModel_Frontal;
	NDPDetectorModel *pointer_NDPDetectorModel_Uncontrained=&NDPDetectorModel_Uncontrained;

//END of Detector model---------------------------------------------------------------------------------------

//Continer for detected feces---------------------------------------------------------------------------------
	vector<Rect> Filtred_DetectedFacesVector;
//END of Continer for detected feces--------------------------------------------------------------------------

//Other Variables---------------------------------------------------------------------------------------------

	int ErrorRegister=0;
	int *pointer_ErrorRegister=&ErrorRegister;

//END of inicialization or deklaration of variables and arrays================================================


//Open files, initialization variables/arrays================================================================
	//char* Path_ModelUnconstrain_P = Path_ModelUnconstrain;
	*pointer_ErrorRegister=loadNPDModel((char*)Path_ModelUnconstrain,pointer_NDPDetectorModel_Uncontrained,pointer_ErrorRegister);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		return -1;
	}

//END of Open files, initialization variable/arrays==========================================================

//Image Initialization=======================================================================================

//Load image-------------------------------------------------------------------------------------------------
	Mat Image =imread((char*)ImagePath1);
	if (Image.empty())
	{
		printf("Error E%d\r Cannot load image\r", ImageOpenError);
		return -1;
	}
	Mat *pointer_Image=&Image;
//END of Load image------------------------------------------------------------------------------------------

//END of Image Initialization================================================================================

//EDIT----------------------------------
	double StartAlgoritmTime=omp_get_wtime();//HowMuchTimeWasPassed(clock());
//EDIT----------------------------------

//IMAGE PROCESSING============================================================================================
	FaceDetectionByNDP(pointer_Image,&Filtred_DetectedFacesVector,pointer_NDPDetectorModel_Uncontrained);
//END of IMAGE PROCESSING=====================================================================================

//EDIT----------------------------------
	double EndAlgoritmTime=omp_get_wtime();//HowMuchTimeWasPassed(clock());
	cout<<EndAlgoritmTime-StartAlgoritmTime<<endl;
//EDIT----------------------------------
//Image Show=================================================================================================
	imshow("FaceDetection",*pointer_Image);
//wait util key press
	waitKey(0=='q');
//END of Image Show==========================================================================================

//Memory Free================================================================================================
//Memory for image Free
		Image.release();
//Memory for NDPDetectorModel
	NPDModelMemoryFree(pointer_NDPDetectorModel_Uncontrained);
//END of Memory Free===========================================================================================

	return 0;
}//END of int main(void)=======================================================================================

