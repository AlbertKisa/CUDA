#ifndef _ComboFields_Dynamic_EdgeElecSrc_HeaderFile
#define _ComboFields_Dynamic_EdgeElecSrc_HeaderFile

#include <ComboFields_Dynamic_SrcBase.hxx>

#include <TxHierAttribSet.h>
#include <TFunc.hxx>


class ComboFields_Dynamic_EdgeElecSrc : public ComboFields_Dynamic_SrcBase
{

public:
  ComboFields_Dynamic_EdgeElecSrc();
  ComboFields_Dynamic_EdgeElecSrc(const FieldsDefineCntr* theCntr, 
				  PhysDataDefineRule theRule);

  virtual ~ComboFields_Dynamic_EdgeElecSrc();

  virtual void SetAttrib(const TxHierAttribSet& tha);


public:
  virtual void Setup();
  virtual void Advance();

private:
  void SetupRgn();


protected:
  Standard_Integer m_Dir;
  Standard_Size m_FirstVertexIndex[2];
  Standard_Size m_GridEdgeNum;

  Standard_Real m_StartTime;
  Standard_Real m_EndTime;

  vector<GridEdgeData*> m_Datas;

  TFunc* m_tfuncPtr;
};

#endif
