/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
*=========================================================================*/

#ifndef __itktubeConvertImagesToCSVFilter_hxx
#define __itktubeConvertImagesToCSVFilter_hxx

#include "itktubeConvertImagesToCSVFilter.h"

namespace itk
{

namespace tube
{

/** Constructor */
template< class TInputImage, class TOutputImage >
ConvertImagesToCSVFilter< TInputImage, TOutputImage >::
ConvertImagesToCSVFilter( void )
{
  m_ImageFileNameListImage = NULL;
  m_CSVFileImage = NULL;
  m_InputImage = NULL;
}

/** GenerateData */
template< class TInputImage, class TOutputImage >
void
ConvertImagesToCSVFilter< TInputImage, TOutputImage >::
GenerateData( void )
{
  m_InputImage = this->GetInput();
  
  m_CSVFileImage = this->GetOutput( 0 );
 
  unsigned int numImages = 0;
  for( unsigned int i = 0; i < m_ImageFileNameList.size(); ++i )
    {
    reader = ReaderType::New();
    reader->SetFileName( m)ImageFileNameList[i] );
    char filePath[4096];
    std::string fileName = m_ImageFileNameList[i];
    if( MET_GetFilePath( m_ImageFileNameList[i].c_str(), filePath ) )
      {
      fileName = &( m_ImageFileNameList[i][ strlen( filePath ) ] );
      }
    outFile << fileName << ", ";
    try
      {
      reader->Update();
      }
    catch( itk::ExceptionObject & err )
      {
      tube::ErrorMessage( "Reading volume: Exception caught: "
                          + std::string(err.GetDescription()) );
      return EXIT_FAILURE;
      }
    imageList.push_back( reader->GetOutput() );
    ++numImages;
    }
  outFile << "Class" << std::endl;

  typedef itk::ImageRegionIterator< InputImageType > IteratorType;

  std::vector< IteratorType * > iterList;
  for( unsigned int i = 0; i < numImages; ++i )
    {
    iterList.push_back( new IteratorType( imageList[i],
        imageList[i]->GetLargestPossibleRegion() ) );
    }

  if( stride < 1 )
    {
    stride = 1;
    }

  IteratorType maskIter( maskImage, maskImage->GetLargestPossibleRegion() );
  while( !maskIter.IsAtEnd() )
    {
    if( maskIter.Get() != 0 )
      {
      for( unsigned int i=0; i<numImages; ++i )
        {
        outFile << iterList[i]->Get() << ", ";
        }
      outFile << maskIter.Get() << std::endl;
      }
    for( int s=0; s<stride && !maskIter.IsAtEnd(); ++s )
      {
      for( unsigned int i=0; i<numImages; ++i )
        {
        ++(*iterList[i]);
        }
      ++maskIter;
      }
    }

  for( unsigned int i=0; i<iterList.size(); ++i )
    {
    delete iterList[i];
    }
  iterList.clear();

  outFile.close();
}

template< class TInputImage, class TOutputImage >
void
ConvertImagesToCSVFilter< TInputImage, TOutputImage >::
SetImageFileNameList ( std::vector< std::string > vec)	
{
  m_ImageFileNameList = vec;
}

/** PrintSelf */
template< class TInputImage, class TOutputImage >
void
ConvertImagesToCSVFilter< TInputImage, TOutputImage >::
PrintSelf( std::ostream & os, Indent indent ) const
{
  Superclass::PrintSelf( os, indent );
}

} // End namespace tube

} // End namespace itk
#endif // End !defined( __itktubeConvertImagesToCSVFilter_hxx )



















