/*
 * ModelLoading.c
 *
 *      Author: marek
 */
#include "ModelLoading.hpp"

//Function definitions=======================================================================================

int loadNPDModel(char *Path_Model , NDPDetectorModel*pointer_NDPDetectorModel_Frontal, int*pointer_ErrorRegister)
{
	FILE *plik;

	int temporaryVariable=2;
	int *pointer_temporaryVariable=&temporaryVariable;

	char PathToFile[200]="";
//Open files, initialization variables/arrays================================================================

//NumerOfBranchNodes------------------------------------------------------------------------------------------------
//add to char char
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_NumerOfBranchNodes);

	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);

		return FileInitializationError;
	}

	fclose(plik);
	//Clearing array
	memset(&PathToFile[0],0, sizeof(PathToFile));
//printf("%d",pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes);
//END of NumerOfBranchNodes-----------------------------------------------------------------------------------------

//NumerOfScales------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_NumerOfScales);

	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfScales);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}

	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
	//printf("%d\n", pointer_NDPDetectorModel_Frontal->NumerOfScales);//ok
//END of NumerOfScales-----------------------------------------------------------------------------------------
//ObjectSize------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_ObjectSize);


	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableInt(plik,&pointer_NDPDetectorModel_Frontal->ObjectSize);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}

	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
	//printf("%d\n", pointer_NDPDetectorModel_Frontal->ObjectSize);//ok
//END of ObjectSize-----------------------------------------------------------------------------------------
//NumerOfStages------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_NumerOfStages);

	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfStages);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}

	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
	//printf("%d\n", pointer_NDPDetectorModel_Frontal->NumerOfStages);//ok
//END of NumerOfStages-----------------------------------------------------------------------------------------
//NumerOfBranchLeaf------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_NumerOfLeafNodes);

	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfLeafNodes);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}

	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
	//printf("%d\n", pointer_NDPDetectorModel_Frontal->NumerOfLeafNodes);//ok
//END of NumerOfBranchLeaf-----------------------------------------------------------------------------------------

//ScaleFactor------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_ScaleFactor);

	plik = fopen(PathToFile,"r");

	*pointer_ErrorRegister = loadFileToVariableFloat(plik,&pointer_NDPDetectorModel_Frontal->ScaleFactor);

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}

	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
	//printf("%f\n", pointer_NDPDetectorModel_Frontal->ScaleFactor);//ok
//END of ScaleFactor-----------------------------------------------------------------------------------------


//CutPoint----------------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_CutPoint);

	plik = fopen(PathToFile,"r");

	//utworzenie macierzy
	pointer_NDPDetectorModel_Frontal->CutPoint=(int**)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,sizeof(int*));
	pointer_NDPDetectorModel_Frontal->CutPoint[0]=(int*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes*2,sizeof(int));
	for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)
	{
		pointer_NDPDetectorModel_Frontal->CutPoint[index1]=pointer_NDPDetectorModel_Frontal->CutPoint[0]+2*index1;
	}//END of for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)



//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToMatrix2(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,pointer_temporaryVariable, (pointer_NDPDetectorModel_Frontal->CutPoint)  );//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);

		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
//END of CutPoint----------------------------------------------------------------------------------------------------------

//Piksel1InNDP----------------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_Piksel1InNDP);

	plik = fopen(PathToFile,"r");

	//utworzenie macierzy
	pointer_NDPDetectorModel_Frontal->Piksel1InNDP=(long int**)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,sizeof(long int*));
	if (pointer_NDPDetectorModel_Frontal->Piksel1InNDP==NULL)
	{
		printf("Error E%d ", MemeoryAllocationErrorMessage);
		printf(MemeoryAllocationErrorMessage);
		return FileInitializationError;
	}
	pointer_NDPDetectorModel_Frontal->Piksel1InNDP[0]=(long int*)calloc((pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes)*(pointer_NDPDetectorModel_Frontal->NumerOfScales),sizeof(long int));
	if (pointer_NDPDetectorModel_Frontal->Piksel1InNDP[0]==NULL)
	{
		printf("Error E%d ", MemeoryAllocationErrorMessage);
		printf(MemeoryAllocationErrorMessage);
		return FileInitializationError;
	}
	for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)
	{
		pointer_NDPDetectorModel_Frontal->Piksel1InNDP[index1]=pointer_NDPDetectorModel_Frontal->Piksel1InNDP[0]+(pointer_NDPDetectorModel_Frontal->NumerOfScales)*index1;
	}//END of for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)

//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToMatrixLong(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,&pointer_NDPDetectorModel_Frontal->NumerOfScales, pointer_NDPDetectorModel_Frontal->Piksel1InNDP  );//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
//END of Piksel1InNDP----------------------------------------------------------------------------------------------------------

//Piksel2InNDP----------------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_Piksel2InNDP);

	plik = fopen(PathToFile,"r");

	//*pointer_temporaryVariable=30;

	//utworzenie macierzy
	pointer_NDPDetectorModel_Frontal->Piksel2InNDP=(long int**)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,sizeof(long int*));
	pointer_NDPDetectorModel_Frontal->Piksel2InNDP[0]=(long int*)calloc((pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes)*(pointer_NDPDetectorModel_Frontal->NumerOfScales),sizeof(long int));
	for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)
	{
		pointer_NDPDetectorModel_Frontal->Piksel2InNDP[index1]=pointer_NDPDetectorModel_Frontal->Piksel2InNDP[0]+(pointer_NDPDetectorModel_Frontal->NumerOfScales)*index1;
	}//END of for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)

//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToMatrixLong(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,&pointer_NDPDetectorModel_Frontal->NumerOfScales, pointer_NDPDetectorModel_Frontal->Piksel2InNDP  );//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
//END of Piksel2InNDP----------------------------------------------------------------------------------------------------------
//NDPTable----------------------------------------------------------------------------------------------------------
	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_NDPTable);

	plik = fopen(PathToFile,"r");

	*pointer_temporaryVariable=256;

	//int NDPTable[*pointer_temporaryVariable][*pointer_temporaryVariable];
	//long int (*pointer_CutPoint)[2]=CutPoint; //ok
	//int **pointer_CutPoint=CutPoint[0][0];
//utworzenie macierzy
	pointer_NDPDetectorModel_Frontal->NDPTable=(int**)calloc(*pointer_temporaryVariable,sizeof(int*));
	pointer_NDPDetectorModel_Frontal->NDPTable[0]=(int*)calloc((*pointer_temporaryVariable)*(*pointer_temporaryVariable),sizeof(int));
	for (int index1 = 0; index1 < *pointer_temporaryVariable; ++index1)
	{
		pointer_NDPDetectorModel_Frontal->NDPTable[index1]=pointer_NDPDetectorModel_Frontal->NDPTable[0]+index1*(*pointer_temporaryVariable);
	}//END of for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes; ++index1)


//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToMatrix2(plik,pointer_temporaryVariable,pointer_temporaryVariable, pointer_NDPDetectorModel_Frontal->NDPTable );//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
//END of NDPTable----------------------------------------------------------------------------------------------------------
//StageThreshold----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_StageThreshold);

	plik = fopen(PathToFile,"r");

//	float StageThreshold[*pointer_NumerOfStages];
	//int (*pointer_CutPoint)[2]=CutPoint;ok
	//int *pointer_StageThreshold=StageThreshold[0];
	pointer_NDPDetectorModel_Frontal->StageThreshold=(float*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfStages,sizeof(float));



//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayFloat(plik,&pointer_NDPDetectorModel_Frontal->NumerOfStages, pointer_NDPDetectorModel_Frontal->StageThreshold);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));

//END of StageThreshold----------------------------------------------------------------------------------------------------------
//TreeRoot----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_TreeRoot);

	plik = fopen(PathToFile,"r");

//	int TreeRoot[*pointer_NumerOfStages];
	//int (*pointer_CutPoint)[2]=CutPoint;ok
	//int *pointer_StageThreshold=StageThreshold[0];
	pointer_NDPDetectorModel_Frontal->TreeRoot=(int*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfStages,sizeof(int));


//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfStages, pointer_NDPDetectorModel_Frontal->TreeRoot);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));

//END of TreeRoot----------------------------------------------------------------------------------------------------------
//LeftChild----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_LeftChild);

	plik = fopen(PathToFile,"r");

	//int LeftChild[*pointer_NumerOfBranchNodes];
	pointer_NDPDetectorModel_Frontal->LeftChild=(int*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,sizeof(int));

//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes, pointer_NDPDetectorModel_Frontal->LeftChild);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));

//END of LeftChild----------------------------------------------------------------------------------------------------------
//RightChild----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_RightChild);

	plik = fopen(PathToFile,"r");

	//int LeftChild[*pointer_NumerOfBranchNodes];
	pointer_NDPDetectorModel_Frontal->RightChild=(int*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes,sizeof(int));

//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfBranchNodes, pointer_NDPDetectorModel_Frontal->RightChild);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));

//END of RightChild----------------------------------------------------------------------------------------------------------
//Fit----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_Fit);

	plik = fopen(PathToFile,"r");

//	float StageThreshold[*pointer_NumerOfStages];
	//int (*pointer_CutPoint)[2]=CutPoint;ok
	//int *pointer_StageThreshold=StageThreshold[0];
	pointer_NDPDetectorModel_Frontal->Fit=(float*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfLeafNodes,sizeof(float));



//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayFloat(plik,&pointer_NDPDetectorModel_Frontal->NumerOfLeafNodes, pointer_NDPDetectorModel_Frontal->Fit);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));

//END of Fit----------------------------------------------------------------------------------------------------------

//Window Size----------------------------------------------------------------------------------------------------------

	strcat(PathToFile, Path_Model);
	strcat(PathToFile, NameFile_WindowSize);

	plik = fopen(PathToFile,"r");

//	int TreeRoot[*pointer_NumerOfStages];
	//int (*pointer_CutPoint)[2]=CutPoint;ok
	//int *pointer_StageThreshold=StageThreshold[0];
	pointer_NDPDetectorModel_Frontal->WindowSize=(int*)calloc(pointer_NDPDetectorModel_Frontal->NumerOfScales,sizeof(int));


//na końcu to wskaznik do macierzy
	*pointer_ErrorRegister = loadFileToArrayInt(plik,&pointer_NDPDetectorModel_Frontal->NumerOfScales, pointer_NDPDetectorModel_Frontal->WindowSize);//ok

	if(*pointer_ErrorRegister==FileInitializationError)
	{
		printf("Error E%d\r File Initialization Error\r", FileInitializationError);
		printf(PathToFile);
		return FileInitializationError;
	}
	fclose(plik);
	memset(&PathToFile[0],0, sizeof(PathToFile));
//END of Window Size----------------------------------------------------------------------------------------------------------

//END of Open files, initialization variable/arrays==========================================================

	return 0;
}//END of int loadNPDModel(char *Path_Model , NDPDetectorModel*pointer_NDPDetectorModel_Frontal, int*pointer_ErrorRegister)


void NPDModelMemoryFree(NDPDetectorModel *pointer_NDPDetectorModel_Frontal)
{
		free(pointer_NDPDetectorModel_Frontal->CutPoint[0]);
		free(pointer_NDPDetectorModel_Frontal->CutPoint);

		free(pointer_NDPDetectorModel_Frontal->Piksel1InNDP[0]);
		free(pointer_NDPDetectorModel_Frontal->Piksel1InNDP);

		free(pointer_NDPDetectorModel_Frontal->Piksel2InNDP[0]);
		free(pointer_NDPDetectorModel_Frontal->Piksel2InNDP);

		free(pointer_NDPDetectorModel_Frontal->NDPTable[0]);
		free(pointer_NDPDetectorModel_Frontal->NDPTable);

		free(pointer_NDPDetectorModel_Frontal->StageThreshold);

		free(pointer_NDPDetectorModel_Frontal->TreeRoot);

		free(pointer_NDPDetectorModel_Frontal->LeftChild);

		free(pointer_NDPDetectorModel_Frontal->RightChild);

		free(pointer_NDPDetectorModel_Frontal->Fit);

		free(pointer_NDPDetectorModel_Frontal->WindowSize);

}//END of void NPDModelMemoryFree(NDPDetectorModel NDPDetectorModel_Frontal)


//int loadFileToVariableINT(FILE *plik,int *pointer_variable)---------------------------------------------------------
int loadFileToVariableInt(FILE *plik,int *pointer_variable)
{

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		//printf("błąd otwarcia pliku");
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}//END of if(plik==NULL)

	//odczyt z pliku
	fscanf(plik,"%d",pointer_variable);

	return 0;
}//END of int loadFileToVariableInt(FILE *plik,int *pointer_variable)--------------------------------------------

//int loadFileToVariableFloat(FILE *plik,float *pointer_variable)------------------------------------------------
int loadFileToVariableFloat(FILE *plik,float *pointer_variable)
{

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		//printf("błąd otwarcia pliku");
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}//END of if(plik==NULL)

	//odczyt z pliku
	fscanf(plik,"%f",pointer_variable);

	return 0;
}//END of int loadFileToVariableFloat(FILE *plik,float *pointer_variable)---------------------------------------

//int loadFileToMatrix2(FILE *plik, int *size1, int *size2, int (*pointer_matrix)[2])---------------------------
int loadFileToMatrix2(FILE *plik, int *size1, int *size2, int (**pointer_matrix))//ok
{
	int IterationIndex1;
	int IterationIndex2;

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}

	//for(int IterationIndex1 = *size1, IterationIndex1!=0,IterationIndex1-- )
	for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)
	{
		if(feof(plik)){printf(OpenFileErrorMessage); break;}

		for(IterationIndex2=0; IterationIndex2<*size2; IterationIndex2++)
				{
					if(feof(plik)){printf(OpenFileErrorMessage); break;}

					//podajemy tutaj adres dlatego nie ma gwiazdki przed nawiasem
					fscanf(plik,"%d",(*(pointer_matrix+IterationIndex1)+IterationIndex2) );//ok


				}//END of for(IterationIndex2=0; IterationIndex2<*size2; IterationIndex2++)

	}//END of for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)

	if ( feof(plik) )
	{
		return FileInitializationError;
	}

	return 0;
}
//END of int loadFileToMatrix2(FILE *plik, int *size1, int *size2, int (*pointer_matrix)[2])-----------------
//int loadFileToMatrix30(FILE *plik, int *size1, int *size2, int (*pointer_matrix)[30])---------------------------
int loadFileToMatrixLong(FILE *plik, int *size1, int *size2, long int (**pointer_matrix))//ok
{
	int IterationIndex1;
	int IterationIndex2;

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}

	//for(int IterationIndex1 = *size1, IterationIndex1!=0,IterationIndex1-- )
	for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)
	{
		if(feof(plik)){printf(OpenFileErrorMessage); break;}

		for(IterationIndex2=0; IterationIndex2<*size2; IterationIndex2++)
				{
					if(feof(plik)){printf(OpenFileErrorMessage); break;}

					//podajemy tutaj adres dlatego nie ma gwiazdki przed nawiasem
					fscanf(plik,"%d",(*(pointer_matrix+IterationIndex1)+IterationIndex2) );//ok


				}//END of for(IterationIndex2=0; IterationIndex2<*size2; IterationIndex2++)

	}//END of for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)

	if ( feof(plik) )
	{
		return FileInitializationError;
	}

	return 0;
}
//END of int loadFileToMatrix30(FILE *plik, int *size1, int *size2, int (*pointer_matrix)[30])--------------

//int loadFileToArrayFloat(FILE *plik, int *size1, float *pointer_matrix)--------------------------------
int loadFileToArrayFloat(FILE *plik, int *size1, float *pointer_matrix)//ok
{
	int IterationIndex1;

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}

	//for(int IterationIndex1 = *size1, IterationIndex1!=0,IterationIndex1-- )
	for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)
	{
		if(feof(plik)){printf(OpenFileErrorMessage); break;}
		//podajemy tutaj adres dlatego nie ma gwiazdki przed nawiasem
		fscanf(plik,"%f", (pointer_matrix+IterationIndex1) );//ok


	}//END of for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)

	if ( feof(plik) )
	{
		return FileInitializationError;
	}

	return 0;
}//END of int loadFileToArrayFloat(FILE *plik, int *size1, float *pointer_matrix)--------------------------------
int loadFileToArrayInt(FILE *plik, int *size1, int *pointer_matrix)//ok
{
	int IterationIndex1;

	//sprawdzenie poprawności odtworzenia pliku
	if(plik==NULL)
	{
		printf(OpenFileErrorMessage);
		return FileInitializationError;
	}

	//for(int IterationIndex1 = *size1, IterationIndex1!=0,IterationIndex1-- )
	for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)
	{
		if(feof(plik)){printf(OpenFileErrorMessage); break;}
		//podajemy tutaj adres dlatego nie ma gwiazdki przed nawiasem
		fscanf(plik,"%d", (pointer_matrix+IterationIndex1) );//ok


	}//END of for(IterationIndex1=0; IterationIndex1<*size1; IterationIndex1++)

	if ( feof(plik) )
	{
		return FileInitializationError;
	}

	return 0;
}//END of //int loadFileToArrayInt(FILE *plik, int *size1, int *pointer_matrix)--------------------------------


//END of Function definitions================================================================================
