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
#ifndef __itktubeConvertImagesToCSVFilter_h
#define __itktubeConvertImagesToCSVFilter_h

#include <itkProcessObject.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageRegionIterator.h>

#include "tubeMessage.h"

namespace itk
{
namespace tube
{
/** \class ConvertImagesToCSV
 */

 template< class TInputMask, class TInputImage >
 class ConvertImagesToCSVFilter : public ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef ConvertImagesToCSVFilter              Self;
  typedef ProcessObject                         Superclass;
  typedef SmartPointer< Self >                  Pointer;
  typedef SmartPointer< const Self >            ConstPointer;

  typedef TInputMask                            InputMaskType;
  typedef typename InputMaskType::Pointer       MaskPointer;
  typedef typename InputMaskType::PixelType     MaskPixelType;
  typedef typename InputMaskType::IndexType     MaskIndexType;
  typedef ImageFileReader< InputMaskType >      MaskReaderType;
  typedef ImageRegionIterator< InputMaskType >  MaskIteratorType;

  typedef TInputImage                           InputImageType;
  typedef typename InputImageType::Pointer      ImagePointer;
  typedef typename InputImageType::PixelType    InputPixelType;
  typedef typename InputImageType::IndexType    IndexType;
  typedef ImageFileReader< InputImageType >     ReaderType;
  typedef ImageRegionIterator< InputImageType > IteratorType;


  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConvertImagesToCSVFilter, ProcessObject);

  /** ImageDimension constants */
  itkStaticConstMacro( ImageDimension, unsigned int,
                      TInputMask::ImageDimension );

  itkSetObjectMacro(InputMask, InputMaskType);
  itkGetObjectMacro(InputMask, InputMaskType);

  itkGetMacro(Output, vnl_matrix <InputPixelType>);

  itkGetMacro(Stride, unsigned int);
  itkSetMacro(Stride, unsigned int);
  itkGetMacro(NumImages, unsigned int);
  itkSetMacro(NumImages, unsigned int);
  itkSetMacro(NumberRows, unsigned int);
  itkGetMacro(NumberRows, unsigned int);
  void AddImage(InputImageType*);

  //void Update( void );

protected:

  ConvertImagesToCSVFilter ( void );
  ~ConvertImagesToCSVFilter( void ) {};
  virtual void GenerateData() ITK_OVERRIDE;
  virtual void PrintSelf( std::ostream & os, Indent indent ) const;

private:
  ConvertImagesToCSVFilter ( const Self& );
  void operator=( const Self& );

  typename InputMaskType::Pointer                  m_InputMask;
  vnl_matrix <InputPixelType>                      m_Output;
  std::vector< typename InputImageType::Pointer >  m_ImageList;
  int                                              m_Stride;
  unsigned int                                     m_NumImages;
  unsigned int                                     m_NumberRows;
  
}; // End class ConvertImagesToCSVFilter

} // End namespace tube

} // End namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itktubeConvertImagesToCSVFilter.hxx"
#endif

#endif // End !defined(_itktubeConvertImagesToCSVFilter_h)
