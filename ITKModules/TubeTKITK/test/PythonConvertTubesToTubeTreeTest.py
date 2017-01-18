##############################################################################
#
# Library:   TubeTK
#
# Copyright 2010 Kitware Inc. 28 Corporate Drive,
# Clifton Park, NY, 12065, USA.
#
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
##############################################################################
#!/usr/bin/env python

import os
import sys

def GetRequiredEnvironmentVariable( varName ):
    if varName in os.environ:
        return os.environ[ varName ]
    else:
        print( '%s not found!' )%varName
        print( '  Set environment variable' )
        sys.exit( 1 )

def CheckIfPathExists( path, name ):
    if not os.path.exists( path ):
        print( 'Directory not found!' )
        print( '  %s = %s' )%( name, path )
        sys.exit( 1 )

def AppendSysPath( path ):
    BUILD_TYPE = GetRequiredEnvironmentVariable( 'BUILD_TYPE' )
    # Append path libs
    sys.path.append( os.path.join( os.path.join( path, \
                               'Wrapping/Generators/Python' ), BUILD_TYPE ) )
    # Folder containing *py files (and *a/*so files on Linux)
    sys.path.append( os.path.join( path, 'lib') )
    # Folder containing *lib files on Windows
    sys.path.append( os.path.join( os.path.join( path, \
                                   'lib' ), BUILD_TYPE) )
    # Windows needs this to load the DLL's
    os.environ[ 'PATH' ] += os.pathsep \
                         + os.path.join( os.path.join( path, 'bin' ),\
                         BUILD_TYPE )

# Path for ITK
ITK_BUILD_DIR = GetRequiredEnvironmentVariable( 'ITK_BUILD_DIR' )
CheckIfPathExists( ITK_BUILD_DIR, 'ITK_BUILD_DIR' )
AppendSysPath( ITK_BUILD_DIR )
# Path for TubeTK libs
TubeTK_BUILD_DIR = GetRequiredEnvironmentVariable( 'TubeTK_BUILD_DIR' )
CheckIfPathExists( TubeTK_BUILD_DIR, 'TubeTK_BUILD_DIR' )
AppendSysPath( TubeTK_BUILD_DIR )

import itk
from itk import TubeTKITK

def main():

  print("len(sys.argv) : %s" %len(sys.argv))
  if len(sys.argv) != 7:
    print("Usage: %s inputTREFile outputTREFile rootTubeIdList maxTubeDistanceToRadiusRatio maxContinuityAngleError removeOrphanTubes"%sys.argv[0])
    return 1

  print ("I am here 1")
  inputTREFile=sys.argv[1]
  outputTREFile=sys.argv[2]
  rootTubeIdList=sys.argv[3]
  maxTubeDistanceToRadiusRatio=sys.argv[4]
  maxContinuityAngleError=sys.argv[5]
  removeOrphanTubes=sys.argv[6]

  print ("I am here 2")
  tubeFileReader=itk.SpatialObjectReader.New(FileName=inputTREFile)
  tubeFileReader.Update()
  pTubeGroup=tubeFileReader.GetGroup()

  print ("I am here 3")
  vesselConnectivityFilter=TubeTKITK.MinimumSpanningTreeVesselConnectivity[pTubeGroup].New()
  vesselConnectivityFilter.SetMaxTubeDistanceToRadiusRatio(maxTubeDistanceToRadiusRatio)
  vesselConnectivityFilter.SetMaxContinuityAngleError(maxContinuityAngleError)
  vesselConnectivityFilter.SetRemoveOrphanTubes(removeOrphanTubes)

  print ("I am here 4")
  if (rootTubeIdList.empty()==false):
    IdList= (rootTubeIdList.begin(), rootTubeIdList.end())
    vesselConnectivityFilter.SetRootTubeIdList(IdList)

  print ("I am here 5")
  vesselConnectivityFilter.Update()
  tubeWriter=itk.SpatialObjectWriter.New(Filename=outputTREFile)
  tubeWriter.SetInput(vesselConnectivityFilter.GetOutput())
  tubeWriter.Update()

if __name__ == "__main__":
  sys.exit(main())
