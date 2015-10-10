// Created on: 2015-07-16
// Created by: Irina KRYLOVA
// Copyright (c) 2015 OPEN CASCADE SAS
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

#ifndef _StepDimTol_DatumReferenceModifierWithValue_HeaderFile
#define _StepDimTol_DatumReferenceModifierWithValue_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Standard_Handle.hxx>

#include <MMgt_TShared.hxx>
#include <Standard_Integer.hxx>
#include <StepBasic_LengthMeasureWithUnit.hxx>
#include <StepDimTol_DatumReferenceModifierType.hxx>

class StepDimTol_DatumReferenceModifierWithValue;
DEFINE_STANDARD_HANDLE(StepDimTol_DatumReferenceModifierWithValue, MMgt_TShared)
//! Representation of STEP entity DatumReferenceModifierWithValue
class StepDimTol_DatumReferenceModifierWithValue : public MMgt_TShared
{

public:
  
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumReferenceModifierWithValue();
  
  //! Initialize all fields (own and inherited)
  Standard_EXPORT   void Init (const StepDimTol_DatumReferenceModifierType& theModifierType,
                               const Handle(StepBasic_LengthMeasureWithUnit)& theModifierValue);
  
  //! Returns field ModifierType
  inline StepDimTol_DatumReferenceModifierType ModifierType () const
  {
    return modifierType;
  }
  
  //! Set field ModifierType
  inline void SetModifierType (const StepDimTol_DatumReferenceModifierType &theModifierType)
  {
    modifierType = theModifierType;
  }
  
  //! Returns field ModifierValue
  inline Handle(StepBasic_LengthMeasureWithUnit) ModifierValue()
  {
    return modifierValue;
  }
  
  //! Set field ModifierValue
  inline void SetModifierValue(const Handle(StepBasic_LengthMeasureWithUnit)& theModifierValue)
  {
    modifierValue = theModifierValue;
  }
  
  DEFINE_STANDARD_RTTI(StepDimTol_DatumReferenceModifierWithValue, MMgt_TShared)

private: 
  StepDimTol_DatumReferenceModifierType modifierType;
  Handle(StepBasic_LengthMeasureWithUnit) modifierValue;
};
#endif // _StepDimTol_DatumReferenceModifierWithValue_HeaderFile