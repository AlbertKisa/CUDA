#include <GridGeometry.hxx>
#include <BaseFunctionDefine.hxx>



/****************************************************************/
/*
 * Function : 
 * Purpose  : 
 */
/****************************************************************/
void  
GridGeometry::
GetAllGridEdgeDatasOfMaterialTypesOfPhysRgn(const set<Standard_Integer>& theMaterials, 
					    const bool isExcludingAxis, 
					    vector<GridEdgeData*>& theDatas) const
{

  TxSlab2D<Standard_Integer> subRgn = GetZRGrid()->GetPhysRgn();
  GetGridEdgeDatasOfMaterialTypesOfSubRgn( theMaterials,subRgn,isExcludingAxis,theDatas);
}


/****************************************************************/
/*
 * Function : 
 * Purpose  : 
 */
/****************************************************************/
void 
GridGeometry::
GetGridEdgeDatasOfMaterialTypesOfSubRgn(const set<Standard_Integer>& theMaterials,
					const TxSlab2D<Standard_Integer>& subRgn,
					const bool isExcludingAxis, 
					vector<GridEdgeData*> & theDatas) const
{
  for(Standard_Integer dir = 0; dir<2; dir++){
    GetGridEdgeDatasOfMaterialTypesOfSubRgn( dir, theMaterials,subRgn,isExcludingAxis,theDatas);
  }
}


/****************************************************************/
/*
 * Function : 
 * Purpose  : 
 */
/****************************************************************/
void 
GridGeometry::
GetGridEdgeDatasOfMaterialTypesOfSubRgn(const Standard_Integer edgeDir,
					const set<Standard_Integer>& theMaterials,
					const TxSlab2D<Standard_Integer>& subRgn,
					const bool isExcludingAxis, 
					vector<GridEdgeData*> & theDatas) const
{
  Standard_Size theGlobalEIndxVec[2];
  Standard_Size theGlobalEIndx;

  Standard_Integer Dir0 = edgeDir;
  Standard_Integer Dir1 = (Dir0+1)%2;


  TxSlab2D<Standard_Integer> theRgn = GetZRGrid()->GetXtndRgn() & subRgn;
  if((theRgn.isPureZeroSpace()) || (!theRgn.isDefinedProperly())) return;

  for(Standard_Size index0 = theRgn.getLowerBound(Dir0); index0<theRgn.getUpperBound(Dir0); index0++){
    theGlobalEIndxVec[Dir0] = index0;
    for(Standard_Size index1 = theRgn.getLowerBound(Dir1); index1<=theRgn.getUpperBound(Dir1); index1++){

      if( (edgeDir==0) && (index1<2) && isExcludingAxis) continue;

      theGlobalEIndxVec[Dir1] = index1;

      GetZRGrid()->FillEdgeIndx(edgeDir, theGlobalEIndxVec, theGlobalEIndx);
      GridEdge* tmpGridEdge = m_Edges[edgeDir]+theGlobalEIndx;
      
      const vector<GridEdgeData*>& tmpDatas = tmpGridEdge->GetEdges();
      Standard_Size nb = tmpDatas.size();
      
      for(Standard_Size j=0;j<nb;j++){
	Standard_Integer tmpMaterial = tmpDatas[j]->GetEMMaterialType();
	if(Bit_Set_BoolOpt_AND(tmpMaterial,theMaterials)){
	  theDatas.push_back(tmpDatas[j]);
	}
      }
    }
  }
}
