
#ifndef _IntCurvesFace_NewShapeIntersector_HeaderFile
#include <IntCurvesFace_NewShapeIntersector.hxx>
#endif


#ifndef _TopoDS_Shape_HeaderFile
#include <TopoDS_Shape.hxx>
#endif
#ifndef _gp_Lin_HeaderFile
#include <gp_Lin.hxx>
#endif
#ifndef _Adaptor3d_HCurve_HeaderFile
#include <Adaptor3d_HCurve.hxx>
#endif
#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#ifndef _TopoDS_Face_HeaderFile
#include <TopoDS_Face.hxx>
#endif

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <IntCurvesFace_NewIntersector.hxx>
#include <Bnd_BoundSortBox.hxx>
#include <Bnd_HArray1OfBox.hxx>
#include <ElCLib.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>

//-- ================================================================================
IntCurvesFace_NewShapeIntersector::IntCurvesFace_NewShapeIntersector() {
  nbfaces=0;
  done=Standard_False;
  PtrJetons=NULL;
  PtrJetonsIndex=NULL;
}
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::Load(const TopoDS_Shape& shape,
					  const Standard_Real tol) { 
  PtrJetons=NULL;
  PtrJetonsIndex=NULL;
  if(nbfaces) { 
    Destroy();
  }
  TopExp_Explorer Ex;
  Standard_Integer i;
  for(nbfaces=0,i=0,Ex.Init(shape,TopAbs_FACE); Ex.More(); i++,Ex.Next()) { 
    nbfaces++;
    TopoDS_Face currentface = TopoDS::Face(Ex.Current());
    PtrIntersector.Append((void *)(new IntCurvesFace_NewIntersector(currentface,tol)));
  }  
}
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::Destroy() { 
  if(PtrJetons) { 
    delete ((Standard_Integer *)PtrJetons);
    PtrJetons=NULL;
  }
  if(PtrJetonsIndex) { 
    delete ((Standard_Integer *)PtrJetonsIndex);
    PtrJetonsIndex=NULL;
  }
  for(Standard_Integer i=1; i<=nbfaces; i++) { 
    IntCurvesFace_NewIntersector *Ptr = (IntCurvesFace_NewIntersector *)PtrIntersector.ChangeValue(i);
    delete Ptr;
  }
  done=Standard_False;
  nbfaces=0;
  PtrIntersector.Clear(); 
  IndexPt.Clear();  IndexFace.Clear();   IndexIntPnt.Clear();IndexPar.Clear();
}
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::Perform(const gp_Lin& L,
					     const Standard_Real ParMin,
					     const Standard_Real ParMax) { 
  done = Standard_False;
  for(Standard_Integer i=1; i<=nbfaces; i++) { 
    IntCurvesFace_NewIntersector *Ptr = (IntCurvesFace_NewIntersector *)PtrIntersector.ChangeValue(i);
    Ptr->Perform(L,ParMin,ParMax);
  }
  SortResult();
}
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::PerformNearest(const gp_Lin& L,
						    const Standard_Real ParMin,
						    const Standard_Real _ParMax) { 

  Standard_Integer i;
  Standard_Integer* _PtrJetons=(Standard_Integer *)PtrJetons;
  Standard_Integer* _PtrJetonsIndex=(Standard_Integer *)PtrJetonsIndex;


  if(nbfaces>2) { 
    if(PtrJetons==NULL) { 
      PtrJetons      = (void *) new Standard_Integer [nbfaces];
      PtrJetonsIndex = (void *) new Standard_Integer [nbfaces];
      Standard_Integer *Ptr =(Standard_Integer *)PtrJetons;
      Standard_Integer *PtrI=(Standard_Integer *)PtrJetonsIndex;
      for(i=0;i<nbfaces;i++) { 
	Ptr[i]=0;
	PtrI[i]=i+1;
      }
      _PtrJetons=(Standard_Integer *)PtrJetons;
      _PtrJetonsIndex=(Standard_Integer *)PtrJetonsIndex;
    }
  }

  
  Standard_Integer Indexface=-1;  
  Standard_Real ParMax=_ParMax;
  

  done = Standard_False;
  for(Standard_Integer ii=1; ii<=nbfaces; ii++) { 
    if(_PtrJetons) { 
      i=_PtrJetonsIndex[ii-1];
    }
    else { 
      i=ii;
    }
      
    IntCurvesFace_NewIntersector *Ptr = (IntCurvesFace_NewIntersector *)PtrIntersector.ChangeValue(i);
    if(ParMin<ParMax) { 
      Ptr->Perform(L,ParMin,ParMax);
      if(Ptr->IsDone()) {
	Standard_Integer n=Ptr->NbPnt();
	for(Standard_Integer j=1;j<=n;j++) { 
	  Standard_Real w=Ptr->WParameter(j);
	  if(w<ParMax) { 
	    ParMax=w;	    
	    Indexface=ii-1;
	  }
	}
      }
      else { 
	done = Standard_False;
	return;
      }
    }
  }
  if(PtrJetons && Indexface>=0) { 
    _PtrJetons[Indexface]++;

    Standard_Integer im1;
    for(im1=Indexface-1,i=Indexface; i>=1 && _PtrJetons[i]>_PtrJetons[i-1]; i--,im1--) { 
      Standard_Integer t=_PtrJetonsIndex[i];
      _PtrJetonsIndex[i]=_PtrJetonsIndex[im1];
      _PtrJetonsIndex[im1]=t;
      t=_PtrJetons[i];
      _PtrJetons[i]=_PtrJetons[im1];
      _PtrJetons[im1]=t;
    }
    //--for(Standard_Integer dd=0; dd<nbfaces;dd++) { if(_PtrJetons[dd]) { printf("\n<%3d %3d %3d>",dd,_PtrJetons[dd],_PtrJetonsIndex[dd]); }  } 
    //--printf("\n");
  }
  SortResult();
}
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::Perform(const Handle(Adaptor3d_HCurve)& HCu,
					     const Standard_Real ParMin,
					     const Standard_Real ParMax) { 
  done = Standard_False;
  for(Standard_Integer i=1; i<=nbfaces; i++) { 
    IntCurvesFace_NewIntersector *Ptr = (IntCurvesFace_NewIntersector *)PtrIntersector.ChangeValue(i);
    Ptr->Perform(HCu,ParMin,ParMax);
  }
  SortResult();
}
//-- ================================================================================
//-- PtrIntersector   : Sequence d addresses 
//-- IndexPt          : 1 2 3 .... n   points avant le tri 
//-- IndexFace        : Numero de la face (de l intersector) du point IndexPt(i)
//-- IndexIntPnt      : Numero du point  IndexPt(i) dans l'intersector IndexFace(IndexPt(i))
//-- IndexPar         : W parameter du point IndexPt(i)
//--
//-- En resume, pour chaque point indice par K = IndexPt(i) on a 
//--      * la face a laquelle il appartient                  : IndexFace(K)
//--      * le numero du point dans l'intersecteur FaceCurve  : IndexIntPnt(K)
//--      * le parametre W du point sur la courbe             : IndexPar(K)
//--
//-- SortResult Trie les points par ordre croissant de W 
//-- (remet a jour le tableau d index TabPt(.))
//-- 
//-- ================================================================================
void IntCurvesFace_NewShapeIntersector::SortResult() { 
  done = Standard_True;
  Standard_Integer nbpnt=0;
  IndexPt.Clear();  IndexFace.Clear();  IndexIntPnt.Clear();IndexPar.Clear();
  //-- -----------------------------------------------------
  //-- r e c u p e r a t i o n   d e s   r e s u l t a t s  
  //--
  for(Standard_Integer f=1; f<=nbfaces; f++) { 
    IntCurvesFace_NewIntersector *Ptr = (IntCurvesFace_NewIntersector *)PtrIntersector.ChangeValue(f);
    if(Ptr->IsDone()) { 
      Standard_Integer n=Ptr->NbPnt();
      for(Standard_Integer j=1;j<=n;j++) { 
	IndexPt.Append(++nbpnt);
	IndexFace.Append(f);
	IndexIntPnt.Append(j);
	IndexPar.Append(Ptr->WParameter(j));
      }
    }
    else { 
      done = Standard_False;
      return;
    }
  }
  //-- -----------------------------------------------------
  //-- t r i   s e l o n   l  e   p a r a m e t r e   w 
  //--
  Standard_Boolean triok;
  do { 
    triok=Standard_True;
    for(Standard_Integer ind0=1;ind0<nbpnt;ind0++) { 
      Standard_Integer ind  =IndexPt(ind0);
      Standard_Integer indp1=IndexPt(ind0+1);
      if(IndexPar(ind) > IndexPar(indp1)) { 
	IndexPt(ind0)  =indp1;
	IndexPt(ind0+1)=ind;
	triok=Standard_False;
      }
    }
  }
  while(triok==Standard_False);
}
//-- ================================================================================
//-- Creation le 28 jan 98
//-- 
