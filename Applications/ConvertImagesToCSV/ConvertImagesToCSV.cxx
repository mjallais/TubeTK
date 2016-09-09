/*=========================================================================

Library:   TubeTK

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/

#include <ios>

// TubeTK includes
#include "itktubeConvertImagesToCSVFilter.h"

// ITK includes
#include <itkTimeProbesCollectorBase.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include <itkSpatialObjectReader.h>
#include <itkSpatialObjectWriter.h>

// Must include CLP before including tubeCLIHelperFunctions
#include "ConvertImagesToCSVCLP.h"

// Must do a forward declaration of DoIt before including
// tubeCLIHelperFunctions
template< class TPixel, unsigned int VDimension >
int DoIt(int argc, char * argv[]);

// Must follow include of "...CLP.h" and forward declaration of int DoIt( ... ).
#include "tubeCLIHelperFunctions.h"

// Your code should be within the DoIt function...
template< class TPixel, unsigned int VDimension >
int DoIt(int argc, char * argv[])
{
	PARSE_ARGS;

	typedef float                                     PixelType;
	typedef itk::Image< PixelType, VDimension >  		ImageType;
	typedef itk::ImageFileReader< ImageType >    ReaderType;

	typedef itk::tube::ConvertImagesToCSVFilter< ImageType >
		ConvertImagesToCSVFilterType;
	typename ConvertImagesToCSVFilterType::Pointer filter =
		ConvertImagesToCSVFilterType::New();

	typename ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(inputImageFileName);
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject & err)
	{
		tube::ErrorMessage("Reading volume: Exception caught: "
			+ std::string(err.GetDescription()));
		return EXIT_FAILURE;
	}
	filter->SetInputImage(reader->GetOutput());

	unsigned int numImages = 0;
	std::vector< typename InputImageType::Pointer > imageList;
	std::vector< std::string > imageFileNameList;
	tube::StringToVector< std::string >(inputImageFileNameList,
		imageFileNameList);
	std::ofstream outFile(outputCSVFileName.c_str());

	filter->SetImageFileNameList(imageFileNameList);

	filter->Update();

	typedef itk::SpatialObjectWriter< VDimension >	CSVWriterType;
	typename CSVWriterType::Pointer soWriter = CSVWriterType::New();
	soWriter->SetFileName(outputCSVFileName);
	soWriter->SetInput(filter->GetOutput());
	soWriter->Update();

	return EXIT_SUCCESS;
}

// Main
int main(int argc, char * argv[])
{
	PARSE_ARGS;

	// You may need to update this line if, in the project's .xml CLI file,
	//   you change the variable name for the inputImageFileName.
	return tube::ParseArgsAndCallDoIt(inputImageFileName, argc, argv);
}
