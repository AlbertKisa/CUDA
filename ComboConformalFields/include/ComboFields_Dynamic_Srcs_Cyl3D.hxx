#ifndef _ComboFields_Dynamic_Srcs_Cyl3D_HeaderFile
#define _ComboFields_Dynamic_Srcs_Cyl3D_HeaderFile

#include  <FieldsDefineBase.hxx>
#include  <ComboFields_Dynamic_SrcBase.hxx>


class ComboFields_Dynamic_Srcs_Cyl3D: public FieldsDefineBase
{
public:
  ComboFields_Dynamic_Srcs_Cyl3D();
  ComboFields_Dynamic_Srcs_Cyl3D(const FieldsDefineCntr* theCntr);
  virtual ~ComboFields_Dynamic_Srcs_Cyl3D();


public:
  void SetAttrib(const string& theWorkDir,
		 const TxHierAttribSet& theFaceBndTha);


  void Append(ComboFields_Dynamic_SrcBase* _oneNewSrc);

  virtual void Advance();

  virtual void Advance_SI_J(const Standard_Real si_scale);
  virtual void Advance_SI_MJ(const Standard_Real si_scale);

  virtual void Advance_SI_Elec_0(const Standard_Real si_scale);
  virtual void Advance_SI_Mag_0(const Standard_Real si_scale);

  virtual void Advance_SI_Elec_1(const Standard_Real si_scale);
  virtual void Advance_SI_Mag_1(const Standard_Real si_scale);


  virtual void Advance_SI_Elec_Damping_0(const Standard_Real si_scale, Standard_Real damping_scale);
  virtual void Advance_SI_Mag_Damping_0(const Standard_Real si_scale);

  virtual void Advance_SI_Elec_Damping_1(const Standard_Real si_scale, Standard_Real damping_scale);
  virtual void Get_Parameters(int idx, Standard_Real& Ebar, Standard_Real& Ebar2);
  virtual void Get_VBar(int idx, Standard_Real& VBar);
  virtual void Get_SrcData(Standard_Real** amp, Standard_Integer& amp_size);
  virtual void Get_SrcDataVec(int idx, vector<GridEdgeData*>* MurEdgeDatas, vector<GridEdgeData*>* FreeEdgeDatas,
                              vector<GridVertexData*>* MurSweptEdgeDatas, vector<GridVertexData*>* FreeSweptEdgeDatas);
  virtual void Advance_SI_Mag_Damping_1(const Standard_Real si_scale);

  virtual void Setup();
  virtual void addCurrTime(int idx, Standard_Real scale);

protected:
  vector<ComboFields_Dynamic_SrcBase*> m_Srcs_Cyl3D;
};


#endif
