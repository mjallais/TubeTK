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

project( vtkSlicer${MODULE_NAME}ModuleMRML )

set( KIT ${PROJECT_NAME} )

set( ${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_MRML_EXPORT" )
set( ${KIT}_INCLUDE_DIRECTORIES )

set( ${KIT}_SRCS
    vtkMRMLSpatialObjectsDisplayNode.cxx
    vtkMRMLSpatialObjectsDisplayNode.h )

list( APPEND ${KIT}_SRCS
     vtkMRMLSpatialObjectsDisplayPropertiesNode.cxx
     vtkMRMLSpatialObjectsDisplayPropertiesNode.h
     vtkMRMLSpatialObjectsGlyphDisplayNode.cxx
     vtkMRMLSpatialObjectsGlyphDisplayNode.h
     vtkMRMLSpatialObjectsLineDisplayNode.cxx
     vtkMRMLSpatialObjectsLineDisplayNode.h
     vtkMRMLSpatialObjectsNode.cxx
     vtkMRMLSpatialObjectsNode.h
     vtkMRMLSpatialObjectsStorageNode.cxx
     vtkMRMLSpatialObjectsStorageNode.h
     vtkMRMLSpatialObjectsTubeDisplayNode.cxx
     vtkMRMLSpatialObjectsTubeDisplayNode.h )

set( ${KIT}_TARGET_LIBRARIES
    ${ITK_LIBRARIES}
    ${MRML_LIBRARIES} )

SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES} )
