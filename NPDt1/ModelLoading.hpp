/*
 * ModelLoading.h
 *
 *      Author: marek
 */

#ifndef MODELLOADING_HPP_
#define MODELLOADING_HPP_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definition========================================================================================================
	//error index
	#define FileInitializationError 1
	#define MemeoryAllocationError 2
	#define ImageOpenError 4

	//error messages
	#define OpenFileErrorMessage "Couldn't open file\r"
	#define MemeoryAllocationErrorMessage "Couldn't allocate memory\r"

	//path for files
	#define Path_ModelUnconstrain ".\\DetectorsModel\\DetectorModel_Unconstrain\\"


	//file names
	#define NameFile_NumerOfBranchNodes "NumerOfBranchNodes.txt"
	#define NameFile_CutPoint "CutPoint.txt"
	#define NameFile_NumerOfScales "NumberOfScales.txt"
	#define NameFile_ObjectSize "ObjectSize.txt"
	#define NameFile_NumerOfStages "NumerOfStages.txt"
	#define NameFile_NumerOfLeafNodes "NumerOfLeafNodes.txt"
	#define NameFile_ScaleFactor "ScaleFactor.txt"
	#define NameFile_StageThreshold "StageThreshold.txt"
	#define NameFile_TreeRoot "TreeRoot.txt"
	#define NameFile_Piksel1InNDP "Piksel1InNDP.txt"
	#define NameFile_Piksel2InNDP "Piksel2InNDP.txt"
	#define NameFile_LeftChild "LeftChild.txt"
	#define NameFile_RightChild "RightChild.txt"
	#define NameFile_Fit "Fit.txt"
	#define NameFile_NDPTable "NDPTable.txt"
	#define NameFile_WindowSize "WindowSize.txt"
//END of definition=============================================================================================

//inicialization or deklaration of variables and arrays================================================
	typedef struct NDPDetectorModel
	{
		int NumerOfBranchNodes;
		int NumerOfScales;
		int ObjectSize;
		int NumerOfStages;
		int NumerOfLeafNodes;
		float ScaleFactor;
		int **CutPoint;
		float *StageThreshold;
		int *TreeRoot;
		long int **Piksel1InNDP;
		long int **Piksel2InNDP;
		int *LeftChild;
		int *RightChild;
		float *Fit;
		int **NDPTable;
		int *WindowSize;
	}NDPDetectorModel;

//END of inicjalization or deklaration of variables and arrays================================================


//Function definitions=======================================================================================

//int loadFileToVariableINT(FILE *plik,int *pointer_variable)---------------------------------------------------------
int loadFileToVariableInt(FILE *plik,int *pointer_variable);
int loadFileToVariableFloat(FILE *plik,float *pointer_variable);
int loadFileToMatrix2(FILE *plik, int *size1, int *size2, int (**pointer_matrix));//ok
int loadFileToMatrixLong(FILE *plik, int *size1, int *size2, long int (**pointer_matrix));//ok
int loadFileToArrayFloat(FILE *plik, int *size1, float *pointer_matrix);//ok
int loadFileToArrayInt(FILE *plik, int *size1, int *pointer_matrix);
int loadNPDModel(char*, NDPDetectorModel*, int*);
void NPDModelMemoryFree(NDPDetectorModel*);
//END of Function definitions================================================================================



#endif /* MODELLOADING_HPP_ */
