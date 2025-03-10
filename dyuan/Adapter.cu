// #include "Adapter.cuh"

// void Adapter::EMOp1()
// {
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance();
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_MJ(1.0);
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_Mag_Damping_0(1.0);

//     void (*funcPtr)() = &g_AdvanceMagCntr_WithDamping_m_Mphi;
//     std::cout << reinterpret_cast<void *>(funcPtr) << std::endl;
// }

// void Adapter::EMGraph1()
// {
//     cudaStreamBeginCapture(graphs->computeStream, cudaStreamCaptureModeGlobal);

//     dim3 block(256);
//     dim3 grid((unsigned int)ceil(theEMFields_Cyl3D->m_MphiDatasNum / (float)block.x));

//     g_AdvanceMagCntr_WithDamping_m_Mphi<<<grid, block, 0, graphs->computeStream>>>(
//         theEMFields_Cyl3D->m_h_d_MphiFuncArray_Cyl3D, theEMFields_Cyl3D->m_MphiDatasNum, m_h_d_MphiDatasPtr, m_h_d_EzrDatasPtr);

//     block.x = 256;
//     grid.x = ((unsigned int)ceil(theEMFields_Cyl3D->m_MzrDatasNum / (float)block.x));

//     g_AdvanceMagCntr_WithDamping_m_Mzr<<<grid, block, 0, graphs->computeStream>>>(
//         theEMFields_Cyl3D->m_h_d_MzrFuncArray_Cyl3D, theEMFields_Cyl3D->m_MzrDatasNum, m_h_d_MzrDatasPtr, m_h_d_EphiDatasPtr, m_h_d_EzrDatasPtr);

//     cudaStreamEndCapture(graphs->computeStream, &graphs->EMGraph1);
//     cudaGraphInstantiate(&graphs->EMGraphExec1, graph->EMGraph1, NULL, NULL, 0);
// }

// void Adapter::EMOp2()
// {
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_Mag_Damping_1(1.0);
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_J(1.0);
//     theEMFields_Cyl3D->m_FldSrcs_Cyl3D->Advance_SI_Elec_Damping_0(1.0, theEMFields_Cyl3D->m_Damping);
// }

// Adapter::~Adapter()
// {
//     // cudaGraphDestory();
//     // cudaGraphExecDestory();
//     // cudaStreamDestory();
// }