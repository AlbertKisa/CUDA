#ifndef _ComboFields_Dynamic_SweptFaceHardMagSrc_HeaderFile
#define _ComboFields_Dynamic_SweptFaceHardMagSrc_HeaderFile

#include <ComboFields_Dynamic_SweptFaceMagSrc.hxx>

#include <TxHierAttribSet.h>
#include <TFunc.hxx>


class ComboFields_Dynamic_SweptFaceHardMagSrc : public ComboFields_Dynamic_SweptFaceMagSrc
{
public:
  ComboFields_Dynamic_SweptFaceHardMagSrc();
  ComboFields_Dynamic_SweptFaceHardMagSrc(const FieldsDefineCntr* theCntr, 
					  PhysDataDefineRule theRule);
  
  virtual ~ComboFields_Dynamic_SweptFaceHardMagSrc();
  

public:
  virtual void Setup();
  virtual void Advance();

  virtual void Advance_SI_Mag_1(const Standard_Real si_scale);

protected:
  Standard_Integer m_PhysDataIndex;
};

#endif
