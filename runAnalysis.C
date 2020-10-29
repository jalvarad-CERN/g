//-----------------------------------------------------------------------------------------
//                                  Header and packages
//-----------------------------------------------------------------------------------------
#include "AliAnalysisAlien.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskMyTask.h"
#include "AliAODInputHandler.h"
#include "TInterpreter.h"
#include "TChain.h"
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//                                          CONTENT
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void runAnalysis()
{
//-----------------------------------------------------------------------------------------
//                                  Local & Test variables
//-----------------------------------------------------------------------------------------
	Bool_t local = 0;
	Bool_t gridTest = 0;
//-----------------------------------------------------------------------------------------
//    since we will compile a class, tell root where to look for headers          
//-----------------------------------------------------------------------------------------
#if !defined (__CINT__) || defined (__CLING__)
	gInterpreter->ProcessLine(".include $ROOTSYS/include");
	gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
	gROOT->ProcessLine(".include $ROOTSYS/include");
	gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif
//-----------------------------------------------------------------------------------------
//                                  Analysis manager
//-----------------------------------------------------------------------------------------
	AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
	AliAODInputHandler *aodH = new AliAODInputHandler();
	mgr->SetInputEventHandler(aodH);
//-----------------------------------------------------------------------------------------
// compile the class and load the add task macro
// here we have to differentiate between using the just-in-time compiler
//-----------------------------------------------------------------------------------------
#if !defined (__CINT__) || defined (__CLING__)
	gInterpreter->LoadMacro("AliAnalysisTaskMyTask.cxx++g");
	AliAnalysisTaskMyTask *task = reinterpret_cast<AliAnalysisTaskMyTask*>(gInterpreter->ExecuteMacro("AddMyTask.C"));
#else
	gROOT->LoadMacro("AliAnalysisTaskMyTask.cxx++g");
	gROOT->LoadMacro("AddMyTask.C");
	AliAnalysisTaskMyTask *task = AddMyTask();
#endif
	if(!mgr->InitAnalysis()) return;
	mgr->SetDebugLevel(2);
	mgr->PrintStatus();
	mgr->SetUseProgressBar(1, 25);
        //---------------------------------------------------------------------------------
        //   Local input, file's path, local analysis 
        //---------------------------------------------------------------------------------
	if(local)
	{
		TChain* chain = new TChain("aodTree");
		chain->Add("LHC18q_296623_AOD_999/AliAOD.root");
		mgr->StartAnalysis("local", chain);
	}
 		//---------------------------------------------------------------------------------
        //  Grid plugin, header paths, upload source files, software version 
        //---------------------------------------------------------------------------------
	else 
	{
		AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
		alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
		alienHandler->SetAdditionalLibs("AliAnalysisTaskMyTask.cxx AliAnalysisTaskMyTask.h");
		alienHandler->SetAnalysisSource("AliAnalysisTaskMyTask.cxx");
		alienHandler->SetAliPhysicsVersion("vAN-20200130_ROOT6-1");
		alienHandler->SetAPIVersion("V1.1x");
		//-------------------------------------------------------------------------
		//      Locate data on grid
		//-------------------------------------------------------------------------
		//	alienHandler->SetGridDataDir("/alice/data/2016/LHC16l");
			alienHandler->SetGridDataDir("/alice/data/2016/LHC16k");
			alienHandler->SetDataPattern("*pass1/AOD/*AOD.root");		
			alienHandler->SetRunPrefix("000");
		//-------------------------------------------------------------------------
		//                  Select runs
		//------------------------------------------------------------------------
		const int nruns = 172;//58; //
		int run_number[nruns] = 
		{258537, 258499, 258477, 258456, 258454, 258452, 258426, 258393, 258391, 258387, 258359, 258336, 258332, 258307, 258306, 258303, 258302, 258301, 258299, 258278, 258274, 258273, 258271, 258270, 258258, 258257, 258256, 258204, 258203, 258202, 258198, 258197, 258178, 258117, 258114, 258113, 258109, 258108, 258107, 258063, 258062, 258060, 258059, 258053, 258049, 258048, 258045, 258042, 258041, 258039, 258019, 258017, 258014, 258012, 258008, 258003, 257992, 257989, 257986, 257979, 257963, 257960, 257958, 257957, 257939, 257937, 257936, 257893, 257892, 257855, 257853, 257851, 257850, 257804, 257803, 257800, 257799, 257798, 257797, 257773, 257765, 257757, 257754, 257737, 257735, 257734, 257733, 257727, 257725, 257724, 257697, 257694, 257692, 257691, 257689, 257688, 257687, 257685, 257684, 257682, 257644, 257642, 257636, 257635, 257632, 257630, 257606, 257605, 257604, 257601, 257595, 257594, 257592, 257590, 257588, 257587, 257566, 257562, 257561, 257560, 257541, 257540, 257539, 257537, 257531, 257530, 257492, 257491, 257490, 257488, 257487, 257474, 257468, 257457, 257433, 257364, 257358, 257330, 257322, 257320, 257318, 257260, 257224, 257209, 257206, 257204, 257145, 257144, 257142, 257141, 257140, 257139, 257138, 257137, 257136, 257100, 257095, 257092, 257086, 257084, 257083, 257082, 257080, 257077, 257028, 257026, 257021, 257012, 257011, 256944, 256942, 256941};
		//{259888, 259868, 259867, 259866, 259860, 259842, 259841, 259822, 259789, 259788, 259781, 259756, 259752, 259751, 259750, 259748, 259747, 259477, 259473, 259396, 259395, 259394, 259389, 259388, 259382, 259378, 259342, 259341, 259340, 259339, 259336, 259334, 259307, 259305, 259303, 259302, 259274, 259273, 259272, 259271, 259270, 259269, 259264, 259263, 259261, 259257, 259204, 259164, 259162, 259118, 259117, 259099, 259096, 259091, 259090, 259088, 258964, 258962};
		for(int i=0; i<nruns; i++) 
			alienHandler->AddRunNumber(run_number[i]);	
		//------------------------------------------------------------------------
		alienHandler->SetSplitMaxInputFileNumber(120);
		alienHandler->SetExecutable("myTask.sh");
		alienHandler->SetTTL(12000);
		alienHandler->SetJDLName("myTask.jdl");
		//-------------------------------------------------------------------------
		alienHandler->SetOutputToRunNo(kTRUE);
		alienHandler->SetKeepLogs(kTRUE);
		//-------------------------------------------------------------------------
		//             Merge result on grid or bellow
		// ------------------------------------------------------------------------
		alienHandler->SetMaxMergeStages(1);
		alienHandler->SetMergeViaJDL(kFALSE);
		//-------------------------------------------------------------------------
		//                    Output folders
		//-------------------------------------------------------------------------
		alienHandler->SetGridWorkingDir("2016k");
		alienHandler->SetGridOutputDir("Output");
		//-------------------------------------------------------------------------
		//               Connect with manager
		//-------------------------------------------------------------------------
		mgr->SetGridHandler(alienHandler);
		//-------------------------------------------------------------------------
		//                Test on grid, number of files, and start
		//-------------------------------------------------------------------------
		if(gridTest) 
		{
			alienHandler->SetNtestFiles(1);
			alienHandler->SetRunMode("test");
			mgr->StartAnalysis("grid");
		}
		//-------------------------------------------------------------------------
		//                             Full mode
		//-------------------------------------------------------------------------
		else 
		{
			alienHandler->SetRunMode("terminate");
			mgr->StartAnalysis("grid");
		}
		//---------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------
//                                     THE END
//-----------------------------------------------------------------------------------------
