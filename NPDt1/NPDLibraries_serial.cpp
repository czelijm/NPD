#include "NPDLibraries.hpp"

void FaceDetectionByNDP(Mat *pointer_Image,vector<Rect> *pointer_Filtred_DetectedFacesVector, NDPDetectorModel *pointer_NDPDetectorModel_Frontal)
{
	//container for detected values------------------------------------------------------------------------------
	pointer_Filtred_DetectedFacesVector->clear();
	//END of container for detected values------------------------------------------------------------------------------
//OPENMP________________________________________________________________________________________________________________________________
//	omp_set_dynamic(1);
//	int numProcs = omp_get_num_procs();
//	int numThreads = numProcs;
//	cout<<numThreads<<"\n";
//	int numThreads = 13;
//	omp_set_num_threads(numThreads);
//OPENMP________________________________________________________________________________________________________________________________

//Mat for processing-----------------------------------------------------------------------------------------
		Mat ImageForProcessingGray;
	//	Mat ImageGray;//only to show result
		Mat *pointer_ImageForProcessingGray=&ImageForProcessingGray;
//END of Mat for processing----------------------------------------------------------------------------------

//Image processing===========================================================================================
	//RGB2Gray convertion----------------------------------------------------------------------------------------
		cvtColor(*pointer_Image,ImageForProcessingGray,COLOR_RGB2GRAY);
	//END of RGB2Gray convertion---------------------------------------------------------------------------------

	//Image  as Array for processing(My way)---------------------------------------------------------------------
		//pointer to Array
		int *ImageAsArray;
		ImageAsArray=(int*) calloc(ImageForProcessingGray.cols*ImageForProcessingGray.rows,sizeof(int));
	//Initialisation
		int ArrayIndex1=0;
		for (int index1 = 0; index1 < ImageForProcessingGray.cols; ++index1)
		{
			for (int index2 = 0; index2 < ImageForProcessingGray.rows; ++index2)
			{
				ImageAsArray[ArrayIndex1]=(int)(ImageForProcessingGray.at<uchar>(index2,index1));
				ArrayIndex1++;
			}//END offor (int index2 = 0; index2 < ImageForProcessingGray.rows; ++index2)

		}//END of 	for (int index1 = 0; index1 < ImageForProcessingGray.cols; ++index1)
	//END of Image  as Array for processing-----------------------------------------------------------------------

//vectors(containers) for detected faces----------------------------------------------------------------------
	vector<Rect> DetectedFacesVector;
//END of vectors(containers) for detected faces----------------------------------------------------------------------

	//For each Scale
	for (int scaleIndex = 0; scaleIndex <pointer_NDPDetectorModel_Frontal->NumerOfScales ; ++scaleIndex)
		{
	//Calculating WindowSep for detection window in current scale
	//can be changed to if statement,
			int	windowStepInCurrentScale;

			/*
			switch (pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex])
			{
			case 0 ... 40:
				windowStepInCurrentScale = (int) floor(pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]*0.1);
				break;

			default:
				windowStepInCurrentScale = (int) floor(pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]*0.05);
				break;
			}
			*/
			if (pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex] >= 0 && pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex] <= 40)
			{
				windowStepInCurrentScale = (int)floor(pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex] * 0.1);
			}
			else
			{
				windowStepInCurrentScale = (int)floor(pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex] * 0.05);
			}

		//offset
			//Initialisation

			int ArrayIndex2=0;
			int temporaryVariable2=0;

			//maximum column lenght (numbre of rows) for given window detection size to check, and offset for another colum number in array
			int temporaryVariable3=ImageForProcessingGray.rows-pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex];

			//memory allocation
			int *offset;
			offset=(int*) calloc(pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]*pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex],sizeof(int));

			//offset - number of piksel in detection window
			for (int index1 = 0; index1 < pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]; ++index1)
			{
				for (int index2 = 0; index2 < pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]; ++index2)
				{
					offset[ArrayIndex2]=temporaryVariable2;
					ArrayIndex2++;
					temporaryVariable2++;
				}//END of for (int index2 = 0; index2 < ImageForProcessingGray.rows; ++index2)
				temporaryVariable2+=temporaryVariable3;

			}//END of 	for (int index1 = 0; index1 < ImageForProcessingGray.cols; ++index1)

			//#pragma omp parallel for //num_threads(4)
		//Slidinng window
			for (int index1 = 0; index1 < ImageForProcessingGray.cols-pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]+1; index1+=windowStepInCurrentScale)
			{
				const int *pointer_PixelToBeIncluded=ImageAsArray+(index1*ImageForProcessingGray.rows);

				for (int index2 = 0; index2 < (ImageForProcessingGray.rows-pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]+1); index2+=windowStepInCurrentScale, pointer_PixelToBeIncluded+=windowStepInCurrentScale)
				{
		//stages
			//variables for detection
					int treeIndex=0;
					float score=0;
					int stageIndex;
			//My idea

					for (stageIndex = 0; stageIndex < pointer_NDPDetectorModel_Frontal->NumerOfStages; ++stageIndex)
					{
			//get root(first) node of tree in this stage
						int node=pointer_NDPDetectorModel_Frontal->TreeRoot[treeIndex];

						while(node>-1)
						{
							int p1=(int)pointer_PixelToBeIncluded[(int)offset[(int)pointer_NDPDetectorModel_Frontal->Piksel1InNDP[(int)node][(int)scaleIndex]]];
							int p2=(int)pointer_PixelToBeIncluded[(int)offset[(int)pointer_NDPDetectorModel_Frontal->Piksel2InNDP[(int)node][(int)scaleIndex]]];
							int featureResponse=(int)pointer_NDPDetectorModel_Frontal->NDPTable[(int)p2][(int)p1];

			//NDP Detection
							if (featureResponse<(int)pointer_NDPDetectorModel_Frontal->CutPoint[node][0] ||
								featureResponse>(int)pointer_NDPDetectorModel_Frontal->CutPoint[node][1])
							{
								node=(int)pointer_NDPDetectorModel_Frontal->LeftChild[node];			//go for left node
							} else
							{
								node=(int)pointer_NDPDetectorModel_Frontal->RightChild[node];   		//go for right node
							}//END of if..................................................................

						}//END of while(node>-1)
						node=-node-1;
						score=score+pointer_NDPDetectorModel_Frontal->Fit[node];
						treeIndex++;
				//if score<pointer_NDPDetectorModel_Frontal->StageThreshold[stageIndex] then this is definitely NOT a FACE
						if (score<pointer_NDPDetectorModel_Frontal->StageThreshold[stageIndex])
						{
							break;
						}

					}//for (stageIndex = 0; stageIndex < pointer_NDPDetectorModel_Frontal->NumerOfStages; ++stageIndex)

				//This is the face!!!!!
					if (stageIndex==pointer_NDPDetectorModel_Frontal->NumerOfStages)//ok!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					{

						Rect DetectedFace(index1,index2,pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex],
														pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]);
						//#pragma omp critical
						//{
						DetectedFacesVector.push_back(DetectedFace);
						//}
					}

				}//for (int index2 = 0; index2 < ImageForProcessingGray.row-pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]+1; ++index2)

			}//END of for (int index1 = 0; index1 < ImageForProcessingGray.cols-pointer_NDPDetectorModel_Frontal->WindowSize[scaleIndex]+1; ++index1)

			free(offset);

		}//END of for (int scaleIndex = 0; scaleIndex <pointer_NDPDetectorModel_Frontal->NumerOfScales ; ++scaleIndex)

//choose best detections
	//Processing on Detected Faces
		float overlappingThreshold=0.01;
		float *pointer_overlappingThreshold=&overlappingThreshold;
		//#pragma omp parallel
		//{
		nonMaximumSupression(&DetectedFacesVector,pointer_Filtred_DetectedFacesVector,pointer_overlappingThreshold);
		//}
		drawingFaces(pointer_Image,pointer_Filtred_DetectedFacesVector,DetectionColor,3);

	//END of Image processing====================================================================================

	//Memory Free================================================================================================
		free(ImageAsArray);

		ImageForProcessingGray.release();
	//END of Memory Free===========================================================================================

}


void nonMaximumSupression(vector<Rect>*DetectedFacesVector,vector<Rect>*Filtred_DetectedFacesVector,float *pointer_overlappingThreshold)
{
	//Filtred_DetectedFacesVector->clear();

	//number of all detections
	const size_t numberOfDetectedFaces=DetectedFacesVector->size();

	//if there no detection then end
	if (!numberOfDetectedFaces)
	{
		return;
	}//END of if (!sizeOfDetectedFaces)

	//container with segregation for ycoordinates for detected face
	multimap<int, size_t> index;

	//make multimap(segregated container), segregation by y coordinate of Rect
	for (size_t index1 = 0; index1 < numberOfDetectedFaces; ++index1)
	{
	//insert pair(argument for segregation, numer order in old container)
		index.insert(pair<int,size_t>(	(int)(*DetectedFacesVector)[index1].br().y,index1 )	);

	}//END of for (size_t index1 = 0; index1 < numberOfDetectedFaces; ++index1)

	while ( index.size()>0 )
	{
		//last element of multimap, iterator
		auto lastDetectedFaceInVector= --index.end();
		//create referention to last element in multimap (with biggest y)
		const Rect& referention_DetectedFaceRect=(*DetectedFacesVector)[lastDetectedFaceInVector->second];
		//add Rect with biggest y to final vector
		Filtred_DetectedFacesVector->push_back(referention_DetectedFaceRect);
		//delete Rect with biggest y from considered vector of detections
		index.erase(lastDetectedFaceInVector);
		//search for overlapping rect in vector, with biggest choosen in referention and delete, this, which overlap more than threshold
		for (auto index1 = index.begin(); index1 != index.end();)
		{
			//create referention to first rect in vector
			const Rect& referention_DetectedFaceRect1=(*DetectedFacesVector)[index1->second];
			float internalArea = (referention_DetectedFaceRect & referention_DetectedFaceRect1).area();
			float commonArea = referention_DetectedFaceRect.area() + referention_DetectedFaceRect1.area() - internalArea;
			float overlap=internalArea/commonArea;
			if (overlap>*pointer_overlappingThreshold)
			{
				index1=index.erase(index1);

			} else
			{
				++index1;

			}//END of for (auto index1 = index.begin(); index1 != index.empty();)

		}//END of for (auto index1 = index.begin(); index1 != index.empty();)

	}//END of while ( index.size()>0)

}//END of void nonMaximumSupression(vector<Rect>*DetectedFacesVector,vector<Rect>*Filtred_DetectedFacesVector,float *pointer_overlappingThreshold)

void drawingFaces(Mat *pointer_Image,vector<Rect>* DetectedFaces2Draw,Scalar colorOfRectangle,int thickness)
{
	for (int index = 0; index < DetectedFaces2Draw->size(); ++index) {

		//rectangle(ImageForProcessingGray,Filtred_DetectedFacesVector[index],255,3);
		rectangle(*pointer_Image,(*DetectedFaces2Draw)[index],colorOfRectangle,thickness);
	}

}//END of void drawingFaces(Mat *pointer_Image,vector<Rect>* DetectedFaces2Draw,Scalar colorOfRectangle,int thickness)


//NO used==============================================================================================================================zz
