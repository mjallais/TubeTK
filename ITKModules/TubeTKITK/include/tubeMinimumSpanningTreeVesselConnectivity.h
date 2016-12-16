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
#ifndef __tubeMinimumSpanningTreeVesselConnectivity_h
#define __tubeMinimumSpanningTreeVesselConnectivity_h

// ITK Includes
#include "itkProcessObject.h"

// TubeTK Includes
#include "tubeWrappingMacros.h"

#include "itktubeMinimumSpanningTreeVesselConnectivityFilter.h"

namespace tube
{
template< unsigned int VDimension >
class MinimumSpanningTreeVesselConnectivity :
  public itk::ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef MinimumSpanningTreeVesselConnectivity           Self;
  typedef itk::ProcessObject                              Superclass;
  typedef itk::SmartPointer< Self >                       Pointer;
  typedef itk::SmartPointer< const Self >                 ConstPointer;

  typedef itk::GroupSpatialObject< VDimension >           TubeGroupType;

  typedef itk::VesselTubeSpatialObject< VDimension >      TubeType;
  typedef typename TubeType::Pointer                      TubePointerType;
  typedef typename TubeType::ConstPointer                 TubeConstPointerType;
  typedef itk::IndexValueType                             TubeIdType;
  typedef std::vector< TubeIdType >                       TubeIdListType;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( MinimumSpanningTreeVesselConnectivity, ProcessObject );

  typedef itk::tube::MinimumSpanningTreeVesselConnectivityFilter< VDimension >
    MinimumSpanningTreeVesselConnectivityFilterType;

  tubeWrapSetObjectMacro( Input, TubeGroupType,
    MinimumSpanningTreeVesselConnectivityFilter );

  tubeWrapGetObjectMacro( Output, TubeGroupType,
    MinimumSpanningTreeVesselConnectivityFilter );

  /** Set/Get a list of root tube ids */
  void SetRootTubeIdList( const TubeIdListType & rootTubeIdList );
  const TubeIdListType & GetRootTubeIdList( void ) const;

  /** Set/Get max tube distance */
  tubeWrapSetMacro( MaxTubeDistanceToRadiusRatio, double,
    MinimumSpanningTreeVesselConnectivityFilter );
  tubeWrapGetMacro( MaxTubeDistanceToRadiusRatio, double,
    MinimumSpanningTreeVesselConnectivityFilter );

  /** Set/Get bifurcation angle continuity */
  tubeWrapSetMacro( MaxContinuityAngleError, double,
    MinimumSpanningTreeVesselConnectivityFilter );
  tubeWrapGetMacro( MaxContinuityAngleError, double,
    MinimumSpanningTreeVesselConnectivityFilter );

  /** Set/Get whether or not to remove orphan tubes */
  tubeWrapSetMacro( RemoveOrphanTubes, bool,
    MinimumSpanningTreeVesselConnectivityFilter );
  tubeWrapGetMacro( RemoveOrphanTubes, bool,
    MinimumSpanningTreeVesselConnectivityFilter );
  //tubeWrapBooleanMacro( RemoveOrphanTubes,
  //MinimumSpanningTreeVesselConnectivityFilter );

  tubeWrapCallMacro( Update, MinimumSpanningTreeVesselConnectivityFilter );

protected:
  MinimumSpanningTreeVesselConnectivity( void );
  ~MinimumSpanningTreeVesselConnectivity() {}
  void PrintSelf( std::ostream & os, itk::Indent indent ) const;

private:
  /** itkMinimumSpanningTreeVesselConnectivityFilter parameters **/
  MinimumSpanningTreeVesselConnectivity( const Self & );
  void operator=( const Self & );

  typename MinimumSpanningTreeVesselConnectivityFilterType::Pointer
    m_MinimumSpanningTreeVesselConnectivityFilter;

};
} // End namespace tube

#ifndef ITK_MANUAL_INSTANTIATION
#include "tubeMinimumSpanningTreeVesselConnectivity.hxx"
#endif

#endif // End !defined( __tubeMinimumSpanningTreeVesselConnectivity_h )
