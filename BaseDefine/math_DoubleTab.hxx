// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _math_DoubleTab_HeaderFile
#define _math_DoubleTab_HeaderFile

#include <Standard_TypeDefine.hxx>
#include <string.h>


class math_DoubleTab 
{
public:
  math_DoubleTab(const Standard_Integer LowerRow, 
		 const Standard_Integer UpperRow, 
		 const Standard_Integer LowerCol, 
		 const Standard_Integer UpperCol);
  
  math_DoubleTab(const Standard_Address Tab, 
		 const Standard_Integer LowerRow,
		 const Standard_Integer UpperRow, 
		 const Standard_Integer LowerCol, 
		 const Standard_Integer UpperCol);
  
  void Init (const Standard_Real InitValue) ;
  
  math_DoubleTab(const math_DoubleTab& Other);
  
  void Copy (math_DoubleTab& Other)  const;
  
  void SetLowerRow (const Standard_Integer LowerRow) ;
  
  void SetLowerCol (const Standard_Integer LowerCol) ;
  
  Standard_Real& Value (const Standard_Integer RowIndex, const Standard_Integer ColIndex)  const;
  Standard_Real& operator() (const Standard_Integer RowIndex, const Standard_Integer ColIndex)  const
  {
    return Value(RowIndex,ColIndex);
  }

  ~math_DoubleTab()
  {
    Free();
  }

  
private:
  void Allocate() ;
  void Free() ;



private:
  Standard_Address Addr;
  Standard_Real Buf[16];
  bool isAllocated;
  Standard_Integer LowR;
  Standard_Integer UppR;
  Standard_Integer LowC;
  Standard_Integer UppC;
};



inline Standard_Real& math_DoubleTab::Value (const Standard_Integer RowIndex,
					     const Standard_Integer ColIndex) const
{
  return ((Standard_Real*)Addr)[(UppC - LowC + 1) * (RowIndex - LowR) + (ColIndex - LowC)];
}



inline void math_DoubleTab::Copy(math_DoubleTab& Other)const
{
  memmove(Other.Addr, Addr, (int)((UppR - LowR + 1) * (UppC - LowC + 1) * sizeof(Standard_Real)));
}




#endif // _math_DoubleTab_HeaderFile
