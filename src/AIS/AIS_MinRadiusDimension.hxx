// Created on: 1998-01-22
// Created by: Sergey ZARITCHNY
// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _AIS_MinRadiusDimension_HeaderFile
#define _AIS_MinRadiusDimension_HeaderFile

#include <AIS_EllipseRadiusDimension.hxx>
#include <DsgPrs_ArrowSide.hxx>

DEFINE_STANDARD_HANDLE(AIS_MinRadiusDimension, AIS_EllipseRadiusDimension)

//! --  Ellipse  Min  radius  dimension  of  a  Shape  which
//! can  be  Edge  or  Face  (planar  or  cylindrical(surface  of
//! extrusion  or  surface  of  offset))
class AIS_MinRadiusDimension : public AIS_EllipseRadiusDimension
{
  DEFINE_STANDARD_RTTIEXT(AIS_MinRadiusDimension, AIS_EllipseRadiusDimension)
public:

  //! Max  Ellipse  radius dimension
  //! Shape  can  be  edge  ,  planar  face  or  cylindrical  face
  Standard_EXPORT AIS_MinRadiusDimension(const TopoDS_Shape& aShape, const Standard_Real aVal, const TCollection_ExtendedString& aText);
  
  //! Max  Ellipse  radius dimension with  position
  //! Shape  can  be  edge  ,  planar  face  or  cylindrical  face
  Standard_EXPORT AIS_MinRadiusDimension(const TopoDS_Shape& aShape, const Standard_Real aVal, const TCollection_ExtendedString& aText, const gp_Pnt& aPosition, const DsgPrs_ArrowSide aSymbolPrs, const Standard_Real anArrowSize = 0.0);

private:
  
  Standard_EXPORT virtual void Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager, const Handle(Prs3d_Presentation)& aPresentation, const Standard_Integer aMode = 0) Standard_OVERRIDE;
  
  Standard_EXPORT virtual void ComputeSelection (const Handle(SelectMgr_Selection)& aSelection, const Standard_Integer aMode) Standard_OVERRIDE;
  
  Standard_EXPORT void ComputeEllipse (const Handle(Prs3d_Presentation)& aPresentation);
  
  Standard_EXPORT void ComputeArcOfEllipse (const Handle(Prs3d_Presentation)& aPresentation);

  gp_Pnt myApexP;
  gp_Pnt myApexN;
  gp_Pnt myEndOfArrow;

};

#endif // _AIS_MinRadiusDimension_HeaderFile
