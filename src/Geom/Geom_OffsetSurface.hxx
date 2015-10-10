// Created on: 1993-03-10
// Created by: JCV
// Copyright (c) 1993-1999 Matra Datavision
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

#ifndef _Geom_OffsetSurface_HeaderFile
#define _Geom_OffsetSurface_HeaderFile

#include <Standard.hxx>
#include <Standard_Type.hxx>

#include <Standard_Real.hxx>
#include <Geom_OsculatingSurface.hxx>
#include <GeomAbs_Shape.hxx>
#include <Geom_Surface.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Integer.hxx>
class Geom_Surface;
class Standard_ConstructionError;
class Standard_RangeError;
class Standard_NoSuchObject;
class Geom_UndefinedDerivative;
class Geom_UndefinedValue;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;
class Geom_BSplineSurface;
class gp_Trsf;
class gp_GTrsf2d;
class Geom_Geometry;


class Geom_OffsetSurface;
DEFINE_STANDARD_HANDLE(Geom_OffsetSurface, Geom_Surface)

//! Describes an offset surface in 3D space.
//! An offset surface is defined by:
//! - the basis surface to which it is parallel, and
//! - the distance between the offset surface and its basis surface.
//! A point on the offset surface is built by measuring the
//! offset value along the normal vector at a point on the
//! basis surface. This normal vector is given by the cross
//! product D1u^D1v, where D1u and D1v are the
//! vectors tangential to the basis surface in the u and v
//! parametric directions at this point. The side of the
//! basis surface on which the offset is measured
//! depends on the sign of the offset value.
//! A Geom_OffsetSurface surface can be
//! self-intersecting, even if the basis surface does not
//! self-intersect. The self-intersecting portions are not
//! deleted at the time of construction.
//! Warning
//! There must be only one normal vector defined at any
//! point on the basis surface. This must be verified by the
//! user as no check is made at the time of construction
//! to detect points with multiple possible normal
//! directions (for example, the top of a conical surface).
class Geom_OffsetSurface : public Geom_Surface
{

public:

  
  //! Constructs a surface offset from the basis surface
  //! S, where Offset is the distance between the offset
  //! surface and the basis surface at any point.
  //! A point on the offset surface is built by measuring
  //! the offset value along a normal vector at a point on
  //! S. This normal vector is given by the cross product
  //! D1u^D1v, where D1u and D1v are the vectors
  //! tangential to the basis surface in the u and v
  //! parametric directions at this point. The side of S on
  //! which the offset value is measured is indicated by
  //! this normal vector if Offset is positive, or is the
  //! inverse sense if Offset is negative.
  //! If isNotCheckC0 = TRUE checking if basis surface has C0-continuity
  //! is not made.
  //! Warnings :
  //! - The offset surface is built with a copy of the
  //! surface S. Therefore, when S is modified the
  //! offset surface is not modified.
  //! - No check is made at the time of construction to
  //! detect points on S with multiple possible normal directions.
  //! Raised if S is not at least C1.
  //! Warnings :
  //! No check is done to verify that a unique normal direction is
  //! defined at any point of the basis surface S.
  Standard_EXPORT Geom_OffsetSurface(const Handle(Geom_Surface)& S, const Standard_Real Offset, const Standard_Boolean isNotCheckC0 = Standard_False);
  
  //! Raised if S is not at least C1.
  //! Warnings :
  //! No check is done to verify that a unique normal direction is
  //! defined at any point of the basis surface S.
  //! If isNotCheckC0 = TRUE checking if basis surface has C0-continuity
  //! is not made.
  //! Exceptions
  //! Standard_ConstructionError if the surface S is not
  //! at least "C1" continuous.
  Standard_EXPORT void SetBasisSurface (const Handle(Geom_Surface)& S, const Standard_Boolean isNotCheckC0 = Standard_False);
  
  //! Changes this offset surface by assigning D as the offset value.
  Standard_EXPORT void SetOffsetValue (const Standard_Real D);
  
  //! Returns the offset value of this offset surface.
  inline Standard_Real Offset() const
  { return offsetValue; }
  
  //! Returns the basis surface of this offset surface.
  //! Note: The basis surface can be an offset surface.
  inline const Handle(Geom_Surface) & BasisSurface() const
  { return basisSurf; }
  
  //! Changes the orientation of this offset surface in the u
  //! parametric direction. The bounds of the surface
  //! are not changed but the given parametric direction is reversed.
  Standard_EXPORT void UReverse();
  
  //! Computes the u  parameter on the modified
  //! surface, produced by reversing the u
  //! parametric direction of this offset surface, for any
  //! point of u parameter U  on this offset surface.
  Standard_EXPORT Standard_Real UReversedParameter (const Standard_Real U) const;
  
  //! Changes the orientation of this offset surface in the v parametric direction. The bounds of the surface
  //! are not changed but the given parametric direction is reversed.
  Standard_EXPORT void VReverse();
  
  //! Computes the  v parameter on the modified
  //! surface, produced by reversing the or v
  //! parametric direction of this offset surface, for any
  //! point of  v parameter V on this offset surface.
  Standard_EXPORT Standard_Real VReversedParameter (const Standard_Real V) const;
  
  //! Returns the parametric bounds U1, U2, V1 and V2 of
  //! this offset surface.
  //! If the surface is infinite, this function can return:
  //! - Standard_Real::RealFirst(), or
  //! - Standard_Real::RealLast().
  Standard_EXPORT void Bounds (Standard_Real& U1, Standard_Real& U2, Standard_Real& V1, Standard_Real& V2) const;
  

  //! This method returns the continuity of the basis surface - 1.
  //! Continuity of the Offset surface :
  //! C0 : only geometric continuity,
  //! C1 : continuity of the first derivative all along the Surface,
  //! C2 : continuity of the second derivative all along the Surface,
  //! C3 : continuity of the third derivative all along the Surface,
  //! CN : the order of continuity is infinite.
  //! Example :
  //! If the basis surface is C2 in the V direction and C3 in the U
  //! direction Shape = C1.
  //! Warnings :
  //! If the basis surface has a unique normal direction defined at
  //! any point this method gives the continuity of the offset
  //! surface otherwise the effective continuity can be lower than
  //! the continuity of the basis surface - 1.
  Standard_EXPORT GeomAbs_Shape Continuity() const;
  

  //! This method answer True if the continuity of the basis surface
  //! is N + 1 in the U parametric direction. We suppose in this
  //! class that a unique normal is defined at any point on the basis
  //! surface.
  //! Raised if N <0.
  Standard_EXPORT Standard_Boolean IsCNu (const Standard_Integer N) const;
  

  //! This method answer True if the continuity of the basis surface
  //! is N + 1 in the V parametric direction. We suppose in this
  //! class that a unique normal is defined at any point on the basis
  //! surface.
  //! Raised if N <0.
  Standard_EXPORT Standard_Boolean IsCNv (const Standard_Integer N) const;
  
  //! Checks whether this offset surface is closed in the u
  //! parametric direction.
  //! Returns true if, taking uFirst and uLast as
  //! the parametric bounds in the u parametric direction,
  //! the distance between the points P(uFirst,v)
  //! and P(uLast,v) is less than or equal to
  //! gp::Resolution() for each value of the   parameter v.
  Standard_EXPORT Standard_Boolean IsUClosed() const;
  
  //! Checks whether this offset surface is closed in the u
  //! or v parametric direction. Returns true if taking vFirst and vLast as the
  //! parametric bounds in the v parametric direction, the
  //! distance between the points P(u,vFirst) and
  //! P(u,vLast) is less than or equal to
  //! gp::Resolution() for each value of the parameter u.
  Standard_EXPORT Standard_Boolean IsVClosed() const;
  

  //! Returns true if this offset surface is periodic in the u
  //! parametric direction, i.e. if the basis
  //! surface of this offset surface is periodic in this direction.
  Standard_EXPORT Standard_Boolean IsUPeriodic() const;
  
  //! Returns the period of this offset surface in the u
  //! parametric direction respectively, i.e. the period of the
  //! basis surface of this offset surface in this parametric direction.
  //! raises if the surface is not uperiodic.
  Standard_EXPORT virtual Standard_Real UPeriod() const Standard_OVERRIDE;
  

  //! Returns true if this offset surface is periodic in the v
  //! parametric direction, i.e. if the basis
  //! surface of this offset surface is periodic in this direction.
  Standard_EXPORT Standard_Boolean IsVPeriodic() const;
  
  //! Returns the period of this offset surface in the v
  //! parametric direction respectively, i.e. the period of the
  //! basis surface of this offset surface in this parametric direction.
  //! raises if the surface is not vperiodic.
  Standard_EXPORT virtual Standard_Real VPeriod() const Standard_OVERRIDE;
  
  //! Computes the U isoparametric curve.
  Standard_EXPORT Handle(Geom_Curve) UIso (const Standard_Real U) const;
  
  //! Computes the V isoparametric curve.
  //!
  //! Te followings methods compute value and derivatives.
  //!
  //! Warnings
  //! An exception is raised if a unique normal vector is
  //! not defined on the basis surface for the parametric
  //! value (U,V).
  //! No check is done at the creation time and we suppose
  //! in this package that the offset surface can be defined
  //! at any point.
  Standard_EXPORT Handle(Geom_Curve) VIso (const Standard_Real V) const;
  

  //! P (U, V) = Pbasis + Offset * Ndir   where
  //! Ndir = D1Ubasis ^ D1Vbasis / ||D1Ubasis ^ D1Vbasis|| is the
  //! normal direction of the basis surface. Pbasis, D1Ubasis,
  //! D1Vbasis are the point and the first derivatives on the basis
  //! surface.
  //! If Ndir is undefined this method computes an approched normal
  //! direction using the following limited development :
  //! Ndir = N0 + DNdir/DU + DNdir/DV + Eps with Eps->0 which
  //! requires to compute the second derivatives on the basis surface.
  //! If the normal direction cannot be approximate for this order
  //! of derivation the exception UndefinedValue is raised.
  //!
  //! Raised if the continuity of the basis surface is not C1.
  //! Raised if the order of derivation required to compute the
  //! normal direction is greater than the second order.
  Standard_EXPORT void D0 (const Standard_Real U, const Standard_Real V, gp_Pnt& P) const;
  

  //! Raised if the continuity of the basis surface is not C2.
  Standard_EXPORT void D1 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V) const;
  
  //! ---Purpose ;
  //! Raised if the continuity of the basis surface is not C3.
  Standard_EXPORT void D2 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV) const;
  

  //! Raised if the continuity of the basis surface is not C4.
  Standard_EXPORT void D3 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D3U, gp_Vec& D3V, gp_Vec& D3UUV, gp_Vec& D3UVV) const;
  

  //! Computes the derivative of order Nu in the direction u and Nv
  //! in the direction v.
  //! ---Purpose ;
  //! Raised if the continuity of the basis surface is not CNu + 1
  //! in the U direction and CNv + 1 in the V direction.
  //! Raised if Nu + Nv < 1 or Nu < 0 or Nv < 0.
  //!
  //! The following methods compute the value and derivatives
  //! on the offset surface and returns the derivatives on the
  //! basis surface too.
  //! The computation of the value and derivatives on the basis
  //! surface are used to evaluate the offset surface.
  //!
  //! Warnings :
  //! The exception UndefinedValue or UndefinedDerivative is
  //! raised if it is not possible to compute a unique offset
  //! direction.
  Standard_EXPORT gp_Vec DN (const Standard_Real U, const Standard_Real V, const Standard_Integer Nu, const Standard_Integer Nv) const;
  

  //! P (U, V) = Pbasis + Offset * Ndir   where
  //! Ndir = D1Ubasis ^ D1Vbasis / ||D1Ubasis ^ D1Vbasis|| is
  //! the normal direction of the surface.
  //! If Ndir is undefined this method computes an approched normal
  //! direction using the following limited development :
  //! Ndir = N0 + DNdir/DU + DNdir/DV + Eps with Eps->0 which
  //! requires to compute the second derivatives on the basis surface.
  //! If the normal direction cannot be approximate for this order
  //! of derivation the exception UndefinedValue is raised.
  //!
  //! Raised if the continuity of the basis surface is not C1.
  //! Raised if the order of derivation required to compute the normal
  //! direction is greater than the second order.
  Standard_EXPORT void Value (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Pnt& Pbasis, gp_Vec& D1Ubasis, gp_Vec& D1Vbasis) const;
  

  //! Raised if the continuity of the basis surface is not C2.
  Standard_EXPORT void D1 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Pnt& Pbasis, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D1Ubasis, gp_Vec& D1Vbasis, gp_Vec& D2Ubasis, gp_Vec& D2Vbasis, gp_Vec& D2UVbasis) const;
  

  //! Raised if the continuity of the basis surface is not C3.
  //! The  following  private  methods
  //! includes common part of local  and  global methods
  //! of  derivative  evaluations.
  Standard_EXPORT void D2 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Pnt& Pbasis, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D1Ubasis, gp_Vec& D1Vbasis, gp_Vec& D2Ubasis, gp_Vec& D2Vbasis, gp_Vec& D2UVbasis, gp_Vec& D3Ubasis, gp_Vec& D3Vbasis, gp_Vec& D3UUVbasis, gp_Vec& D3UVVbasis) const;
  
  Standard_EXPORT void LocalD0 (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, gp_Pnt& P) const;
  
  Standard_EXPORT void LocalD1 (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V) const;
  
  Standard_EXPORT void LocalD2 (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV) const;
  
  Standard_EXPORT void LocalD3 (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D3U, gp_Vec& D3V, gp_Vec& D3UUV, gp_Vec& D3UVV) const;
  
  Standard_EXPORT gp_Vec LocalDN (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, const Standard_Integer Nu, const Standard_Integer Nv) const;
  

  //! Applies the transformation T to this offset surface.
  //! Note: the basis surface is also modified.
  Standard_EXPORT void Transform (const gp_Trsf& T);
  
  //! Computes the  parameters on the  transformed  surface for
  //! the transform of the point of parameters U,V on <me>.
  //!
  //! me->Transformed(T)->Value(U',V')
  //!
  //! is the same point as
  //!
  //! me->Value(U,V).Transformed(T)
  //!
  //! Where U',V' are the new values of U,V after calling
  //!
  //! me->TranformParameters(U,V,T)
  //! This methods calls the basis surface method.
  Standard_EXPORT virtual void TransformParameters (Standard_Real& U, Standard_Real& V, const gp_Trsf& T) const Standard_OVERRIDE;
  
  //! Returns a 2d transformation  used to find the  new
  //! parameters of a point on the transformed surface.
  //!
  //! me->Transformed(T)->Value(U',V')
  //!
  //! is the same point as
  //!
  //! me->Value(U,V).Transformed(T)
  //!
  //! Where U',V' are  obtained by transforming U,V with
  //! th 2d transformation returned by
  //!
  //! me->ParametricTransformation(T)
  //!
  //! This methods calls the basis surface method.
  Standard_EXPORT virtual gp_GTrsf2d ParametricTransformation (const gp_Trsf& T) const Standard_OVERRIDE;
  
  //! Creates a new object which is a copy of this offset surface.
  Standard_EXPORT Handle(Geom_Geometry) Copy() const;
  
  //! returns an  equivalent surface of the offset surface
  //! when  the basis surface   is a canonic  surface or a
  //! rectangular  limited surface on canonic surface or if
  //! the offset is null.
  Standard_EXPORT Handle(Geom_Surface) Surface() const;
  
  //! if Standard_True, L is  the local osculating surface
  //! along U at  the point U,V.   It means that  DL/DU is
  //! collinear to DS/DU .  If IsOpposite == Standard_True
  //! these vectors have opposite direction.
  Standard_EXPORT Standard_Boolean UOsculatingSurface (const Standard_Real U, const Standard_Real V, Standard_Boolean& IsOpposite, Handle(Geom_BSplineSurface)& UOsculSurf) const;
  
  //! if Standard_True, L is the local osculating surface
  //! along V at the point U,V.
  //! It means that  DL/DV is
  //! collinear to DS/DV .  If IsOpposite == Standard_True
  //! these vectors have opposite direction.
  Standard_EXPORT Standard_Boolean VOsculatingSurface (const Standard_Real U, const Standard_Real V, Standard_Boolean& IsOpposite, Handle(Geom_BSplineSurface)& VOsculSurf) const;
  
  //! Returns continuity of the basis surface.
  inline GeomAbs_Shape GetBasisSurfContinuity() const
  { return myBasisSurfContinuity; }

  DEFINE_STANDARD_RTTI(Geom_OffsetSurface,Geom_Surface)

private:

  
  Standard_EXPORT void SetD0 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, const gp_Vec& D1U, const gp_Vec& D1V) const;
  
  Standard_EXPORT void SetD1 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, const gp_Vec& d2u, const gp_Vec& d2v, const gp_Vec& d2uv) const;
  
  Standard_EXPORT void SetD2 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, const gp_Vec& d3u, const gp_Vec& d3v, const gp_Vec& d3uuv, const gp_Vec& d3uvv) const;
  
  Standard_EXPORT void SetD3 (const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D3U, gp_Vec& D3V, gp_Vec& D3UUV, gp_Vec& D3UVV) const;
  
  //! The following  functions  evaluates the  local
  //! derivatives on surface. Useful to manage discontinuities
  //! on the surface.
  //! if    Side  =  1  ->  P  =  S( U+,V )
  //! if    Side  = -1  ->  P  =  S( U-,V )
  //! else  P  is betveen discontinuities
  //! can be evaluated using methods  of
  //! global evaluations    P  =  S( U ,V )
  Standard_EXPORT gp_Vec SetDN (const Standard_Real U, const Standard_Real V, const Standard_Integer Nu, const Standard_Integer Nv, const gp_Vec& D1U, const gp_Vec& D1V) const;
  
  //! This  method locates U,V parameters on basis BSpline surface
  //! and calls LocalDi or Di methods corresponding an order
  //! of derivative and  position
  //! of UV-point relatively the surface discontinuities.
  Standard_EXPORT void LocateSides (const Standard_Real U, const Standard_Real V, const Standard_Integer USide, const Standard_Integer VSide, const Handle(Geom_BSplineSurface)& BSplS, const Standard_Integer NDir, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& D2UV, gp_Vec& D3U, gp_Vec& D3V, gp_Vec& D3UUV, gp_Vec& D3UVV) const;

  Handle(Geom_Surface) basisSurf;
  Handle(Geom_Surface) equivSurf;
  Standard_Real offsetValue;
  Geom_OsculatingSurface myOscSurf;
  GeomAbs_Shape myBasisSurfContinuity;
};

#endif // _Geom_OffsetSurface_HeaderFile