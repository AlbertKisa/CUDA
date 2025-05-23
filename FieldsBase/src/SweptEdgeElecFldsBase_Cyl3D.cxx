#include <SweptEdgeElecFldsBase_Cyl3D.hxx>

#include<GridFaceData.cuh>
#include<GridEdgeData.hxx>
#include<GridFace.hxx>
#include<GridEdge.hxx>


SweptEdgeElecFldsBase_Cyl3D::
SweptEdgeElecFldsBase_Cyl3D()
  :FieldsBase()
{
}


SweptEdgeElecFldsBase_Cyl3D::
SweptEdgeElecFldsBase_Cyl3D(const FieldsDefineCntr* theCntr, 
		      PhysDataDefineRule theRule)
  :FieldsBase(theCntr, theRule)
{
}


SweptEdgeElecFldsBase_Cyl3D::
SweptEdgeElecFldsBase_Cyl3D(const FieldsDefineCntr* theCntr)
  :FieldsBase(theCntr)
{
}


SweptEdgeElecFldsBase_Cyl3D::
~SweptEdgeElecFldsBase_Cyl3D()
{
  m_Datas.clear();
}


void 
SweptEdgeElecFldsBase_Cyl3D::
Setup()
{
  FieldsBase::Setup();

  m_Datas.clear();

  switch(m_Rule)
    {
    case EXCLUDING:
      {
	GetGridGeom_Cyl3D()->GetAllGridVertexDatasNotOfMaterialTypesOfPhysRgn(m_Materials, true, m_Datas);
	break;
      }
    case INCLUDING:
      {
	GetGridGeom_Cyl3D()->GetAllGridVertexDatasOfMaterialTypesOfPhysRgn(m_Materials, true, m_Datas);
	break;
      }
    case NORULE:
      {
	GetGridGeom_Cyl3D()->GetAllGridVertexDatasOfPhysRgn(true, m_Datas);
	break;
      }
    }
}


bool 
SweptEdgeElecFldsBase_Cyl3D::
IsPhysDataMemoryLocated() const
{
  bool result = true;

  Standard_Integer nb = m_Datas.size();
  for(Standard_Integer index = 0; index<nb; index++){
    bool tmp = m_Datas[index]->IsPhysDataDefined();
    result = result && tmp;
    tmp = m_Datas[index]->IsSharedDFacesPhysDataDefined();
    result = result && tmp;
  }

  return result;
}
