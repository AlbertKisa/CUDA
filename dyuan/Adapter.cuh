#include <cuda_runtime.h>

#include "../ComboConformalFields/include/Dynamic_ComboEMFieldsBase.hxx"
// #include "SI_SC_Matrix_EMFields_Cyl3D.hxx"
// #include "NodeField_Cyl3D.cuh"
// #include "Species_Cyl3D.cuh"
// #include "PtclSource_Cyl3D.cuh"
// #include "FieldsDgnSets.hxx"

struct UNIPICGraphs // 每个步骤拆分成多个小的计算图
{

    cudaGraph_t EMGraph1;
    cudaGraph_t EMGraph2;
    cudaGraph_t NodeGraph;
    cudaGraph_t ClearGraph;
    cudaGraph_t SpeciesGraph;
    cudaGraph_t CurrentGraph;
    cudaGraphExec_t EMGraphExec1;
    cudaGraphExec_t EMGraphExec2;
    cudaGraphExec_t NodeGraphExec;
    cudaGraphExec_t ClearGraphExec;
    cudaGraphExec_t SpeciesGraphExec;
    cudaGraphExec_t CurrentGraphExec;

    cudaStream_t computeStream; // 计算Stream
};

class Adapter
{
public:
    Adapter(Dynamic_ComboEMFieldsBase *theEMFields_Cyl3D,
            NodeField_Cyl3D *node_field_Cyl3D,
            Species_Cyl3D *the_species_Cyl3D,
            CLEmit_Cyl3D *cl_emit_Cyl3D,
            FieldsDgnSets *theFldsDgnTool,
            ofstream *DgnStream,
            ofstream *NodeFldsStream,
            ofstream *CurrentDgnStream)
    {
        this->theEMFields_Cyl3D = theEMFields_Cyl3D;
        this->node_field_Cyl3D = node_field_Cyl3D;
        this->the_species_Cyl3D = the_species_Cyl3D;
        this->cl_emit_Cyl3D = cl_emit_Cyl3D;
        this->theFldsDgnTool = theFldsDgnTool;
        this->DgnStream = DgnStream;
        this->NodeFldsStream = NodeFldsStream;
        this->CurrentDgnStream = CurrentDgnStream;
    }

    void test()
    {
        // theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance();
        // theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_MJ(1.0);
        // theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_Mag_Damping_0(1.0);

        // void (*funcPtr)() = &g_AdvanceMagCntr_WithDamping_m_Mphi;
        // std::cout << reinterpret_cast<void *>(funcPtr) << std::endl;

        std::cout << typeid(*theEMFields_Cyl3D).name() << std::endl;
        std::cout << theEMFields_Cyl3D->m_FldSrcs_Cyl3D << std::endl;

        theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance();
        theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_MJ(1.0);
        theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_Mag_Damping_0(1.0);
    }

    void EMOp1();

    void EMGraph1();

    void EMOp2();

    void EMGraph2();

    void EMOp3();

    void NodeGraph();

    void ClearGraph();

    void SpeciesGraph();

    void emitOp();

    void CurrentGraph();

    void dgnOp();

    ~Adapter();

public:
    UNIPICGraphs *graphs;

    Dynamic_ComboEMFieldsBase *theEMFields_Cyl3D;
    NodeField_Cyl3D *node_field_Cyl3D;
    Species_Cyl3D *the_species_Cyl3D;
    CLEmit_Cyl3D *cl_emit_Cyl3D;
    FieldsDgnSets *theFldsDgnTool;
    ofstream *DgnStream;
    ofstream *NodeFldsStream;
    ofstream *CurrentDgnStream;
};
