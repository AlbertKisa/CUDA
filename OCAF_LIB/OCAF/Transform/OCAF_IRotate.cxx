
#include <CAGDDefine.hxx>

#include <OCAF_IRotate.hxx>
#include <OCAF_RotateDriver.hxx>

#include <Tags.hxx>

#include <OCAF_IBooleanOperation.hxx>
#include <OCAF_ICut.hxx>
#include <OCAF_IFuse.hxx>
//#include <OCAF_IPrism.hxx>

#include <TDF_ChildIterator.hxx>
#include <TDF_Data.hxx>
#include <TDF_Label.hxx>
#include <TDF_Reference.hxx>
#include <TDF_Tool.hxx>
#include <TDF_LabelMap.hxx>

#include <TPrsStd_AISPresentation.hxx>

#include <TDataStd_Real.hxx>
#include <TDataStd_Integer.hxx>

#include <TDocStd_Modified.hxx>

#include <TFunction_Function.hxx>
#include <TFunction_Logbook.hxx>

#include <TNaming_NamedShape.hxx>
#include <TNaming.hxx>

#include <TopLoc_Location.hxx>

#include <Standard_ConstructionError.hxx>

#include <gp_Trsf.hxx>

#include <OCAF_Object.hxx>
#include <OCAF_ObjectTool.hxx>

//=======================================================================
//function : GetID
//purpose  :
//=======================================================================

const Standard_GUID& OCAF_IRotate::GetID() {
  static Standard_GUID anID("22D22E65-C69A-11d4-8F1A-0060B0EE18E8");
  return anID;
}


//=======================================================================
//function : MakeRotate
//purpose  : Adds a line object to the document
//=======================================================================
Handle(TDataStd_TreeNode) OCAF_IRotate::MakeRotate_FunctionNode( const Handle(TDataStd_TreeNode)& theNode,
								 Standard_Integer theType,
								 TCollection_ExtendedString& theError)
{
  if (theNode.IsNull() || theNode->Label().IsNull()) {
    theError = NULL_ACCESS_NODE;
    return NULL;
  }

  // 2. Construct an interface "anInterface" used for call OCAF_Object's AddFunction
  OCAF_Object anInterface(theNode);

  // 3. To use "anInterface" to call AddFunction of OCAF_Object
  Handle(TDataStd_TreeNode) aFunctionNode = anInterface.AddFunction(GetID());
  

  if(aFunctionNode.IsNull()) {
    theError = NOTDONE;
    return NULL;
  }

  OCAF_IFunction aFunctionInterface(aFunctionNode);
  aFunctionInterface.SetName("Rotate function");
  aFunctionInterface.SetType(theType);  

  theError = DONE;
  return aFunctionNode;
}


//=======================================================================
//function : MakeRotate
//purpose  : Adds a line object to the document
//=======================================================================
Standard_Boolean OCAF_IRotate::MakeRotate_Execute( TCollection_ExtendedString& theError )
{
  if( myTreeNode.IsNull()) {
    theError = NOTDONE;
    return Standard_False;
  }
  // 5. setup a TFunction_Function's driver "aDriver" from OCAF_RotateDriver
  OCAF_RotateDriver aDriver;
  // 5.1  Initialize the Label of "aDriver"
  aDriver.Init(myTreeNode->Label());
  Handle(TFunction_Logbook) log;
  // 5.2  exacute the function driver
  int a = aDriver.Execute(log);
  //if(aDriver.Execute(log) > 0) {
  if(a > 0) {
    theError = ALGO_FAILED; 
    return Standard_True;
  }

  theError = DONE;
  return Standard_True;
}


//=======================================================================
//function : Constructor
//purpose  :
//=======================================================================
OCAF_IRotate::OCAF_IRotate(const Handle(TDataStd_TreeNode)& aTreeNode)
  :OCAF_IFunction(aTreeNode)
{
  if(myTreeNode.IsNull()) Standard_ConstructionError::Raise("Null TreeNode");  
}

//=======================================================================
//function : SetMoveAttach
//purpose  : Sets a flag whether move attachemnts
//=======================================================================
void OCAF_IRotate::SetMoveAttach(Standard_Boolean theType)
{
  TDF_Label L = GetEntry().FindChild(ARGUMENTS_TAG);
  Handle(TDataStd_Integer) anInt;
  Standard_Integer aType = theType ? 1 : 0;
  TDF_Label aLabel = L.FindChild(TRANSLATE_ARG_MOVE);
  
  if(!aLabel.FindAttribute(TDataStd_Integer::GetID(), anInt)) {
    anInt = TDataStd_Integer::Set(aLabel, aType);
  } else
    anInt->Set(aType);
}

//=======================================================================
//function : GetMoveAttach
//purpose  : Gets a flag whether move attachemnts
//=======================================================================
Standard_Boolean OCAF_IRotate::GetMoveAttach() 
{
  TDF_Label L = GetEntry().FindChild(ARGUMENTS_TAG);
  Handle(TDataStd_Integer) anInt;  
  TDF_Label aLabel = L.FindChild(TRANSLATE_ARG_MOVE);
  
  if(!aLabel.FindAttribute(TDataStd_Integer::GetID(), anInt)) {
    anInt = TDataStd_Integer::Set(aLabel, 0);
  } 
  return anInt->Get() ? Standard_True : Standard_False;
}


//=======================================================================
//function : SetCopyMode
//purpose  : Sets a flag whether to create a copy
//=======================================================================
void OCAF_IRotate::SetCopyMode(Standard_Boolean theType)
{
  TDF_Label L = GetEntry().FindChild(ARGUMENTS_TAG);
  Handle(TDataStd_Integer) anInt;
  Standard_Integer aType = theType ? 1 : 0;
  TDF_Label aLabel = L.FindChild(TRANSLATE_ARG_COPYMODE);
  
  if(!aLabel.FindAttribute(TDataStd_Integer::GetID(), anInt)) {
    anInt = TDataStd_Integer::Set(aLabel, aType);
  } else
    anInt->Set(aType);
}

//=======================================================================
//function : GetCopyMode
//purpose  : Gets a flag whether to create a copy
//=======================================================================
Standard_Boolean OCAF_IRotate::GetCopyMode() 
{
  TDF_Label L = GetEntry().FindChild(ARGUMENTS_TAG);
  Handle(TDataStd_Integer) anInt;  
  TDF_Label aLabel = L.FindChild(TRANSLATE_ARG_COPYMODE);
  
  if(!aLabel.FindAttribute(TDataStd_Integer::GetID(), anInt)) {
    anInt = TDataStd_Integer::Set(aLabel, 0);
  } 
  return anInt->Get() ? Standard_True : Standard_False;
}

