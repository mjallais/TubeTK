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
#ifndef __tubeMinimumSpanningTreeVesselConnectivity_hxx
#define __tubeMinimumSpanningTreeVesselConnectivity_hxx

#include "tubeMinimumSpanningTreeVesselConnectivity.h"


namespace tube
{

template< unsigned int VDimension >
MinimumSpanningTreeVesselConnectivity< VDimension >
::MinimumSpanningTreeVesselConnectivity( void )
{
  m_MinimumSpanningTreeVesselConnectivityFilter =
    MinimumSpanningTreeVesselConnectivityFilterType::New();
}

template< unsigned int VDimension >
void
MinimumSpanningTreeVesselConnectivity< VDimension >
::SetRootTubeIdList( const TubeIdListType & rootTubeIdList )
{
  return m_MinimumSpanningTreeVesselConnectivityFilter->
    SetRootTubeIdList( rootTubeIdList );
}

template< unsigned int VDimension >
const std::vector< itk::IndexValueType > &
MinimumSpanningTreeVesselConnectivity< VDimension >
::GetRootTubeIdList( void ) const
{
  return m_MinimumSpanningTreeVesselConnectivityFilter->
    SetRootTubeIdList( rootTubeIdList );
}

template< unsigned int VDimension >
void
MinimumSpanningTreeVesselConnectivity< VDimension >
::PrintSelf( std::ostream & os, itk::Indent indent ) const
{
  Superclass::PrintSelf( os, indent );
  os << "Filter = " << m_MinimumSpanningTreeVesselConnectivityFilter
    << std::endl;
}

} // end namespace tube

#endif
