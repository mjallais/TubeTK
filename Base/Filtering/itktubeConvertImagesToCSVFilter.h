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
#ifndef __itktubeConvertImageToCSVFilter_h
#define __itktubeConvertImageToCSVFilter_h

#include "itkImage.h"
#include <itkImageToImageFilter.h>

namespace itk
{
namespace tube
{
/** \class ConvertImagesToCSV
 * \Description of the class : TODO
 *
 */

 template< class TInputImage >
class ConvertImagesToCSVFilter : public Object
  {
public:
  /** Standard class typedefs. */
  typedef ConvertImagesToCSVFilter			Self;
  typedef Object							Superclass;
  typedef SmartPointer< Self > 				Pointer;
  typedef SmartPointer< const Self >		ConstPointer;
  
  typedef TInputImage                   	ImageType;  
  typedef typename ImageType::Pointer       ImagePointer;
  typedef typename ImageType::PixelType 	PixelType;
  typedef typename ImageType::IndexType 	IndexType;
  
	
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConvertImagesToCSVFilter, Object);

  /** ImageDimension constants */
  itkStaticConstMacro( ImageDimension, unsigned int,
                      TInputImage::ImageDimension );	
	
  typedef itk::GroupSpatialObject< ImageDimension >    CSVFileType;	
	
	
  itkGetMacro( CSVImage, OutputImagePointer );	//???
	
  void SetImageFileNameList ( std::vector< std::string > );	
  
  /* Get the CVS file */
  typename CSVFileType::Pointer GetOutput( void );
	
protected:
  ConvertImagesToCSVFilter ( void );
  ~ConvertImagesToCSVFilter ( void ) {}
	
  void PrintSelf( std::ostream& os, Indent indent ) const;
  virtual void GenerateData( void );	
  
private:
  ConvertImagesToCSVFilter ( const Self& );
  void operator=( const Self& );
  
  typename OutputImageType::Pointer            m_ImageFileNameListImage;
  typename OutputImageType::Pointer            m_CSVFileImage;
  typename InputImageType::ConstPointer        m_InputImage;
   
  std::vector< std::string > m_ImageFileNameList;
  std::ofstream outFile;
  
}; // End class ConvertImagesToCSVFilter

} // End namespace tube

} // End namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itktubeConvertImagesToCSVFilter.hxx"
#endif

#endif // End !defined(_itktubeConvertImagesToCSVFilter_h)
  
  
  
  
  
  
  
  
  
  
  
  
  
  
	
	
	
	
	
	
	
	
	
	
  }
































