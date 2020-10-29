

void Post()
{
	//---------------------------------------------------------------------------------
	//                      Constantes   
	//---------------------------------------------------------------------------------
	const int nruns = 58;
	const int mark[10] = {20, 24, 21, 25, 22, 26, 23, 32, 29, 31};
	const char* path = "/Users/*/MyTask";
	const char* runn[nruns] = {"259888", "259868", "259867", "259866", "259860", "259842", "259841", "259822", "259789", "259788", "259781", "259756", "259752", "259751", "259750", "259748", "259747", "259477", "259473", "259396", "259395", "259394", "259389", "259388", "259382", "259378", "259342", "259341", "259340", "259339", "259336", "259334", "259307", "259305", "259303", "259302", "259274", "259273", "259272", "259271", "259270", "259269", "259264", "259263", "259261", "259257", "259204", "259164", "259162", "259118", "259117", "259099", "259096", "259091", "259090", "259088", "258964", "258962"};
	TH1D* hPt[nruns];
	TH1D* hZv[nruns];
	//-----------------------------------------------------------------------------------
	//                            Imprimir lista
	//-----------------------------------------------------------------------------------
	//   for(int i=0; i<nruns; i++)  {  printf("%s\n",runn[i]);   }
	//---------------------------------------------------------------------------------  
	//---------------------------------------------------------------------------------  
	//								MB
	//---------------------------------------------------------------------------------  
	TFile *f0 = 0x0;
	f0 = (TFile*)TFile::Open(Form("%s/AnalysisResults.root",path));
	TDirectory *d0 = new TDirectory();
	d0 = (TDirectory*)f0->Get("MyTask");
	TList* l0 = new TList();
	l0 = (TList*)d0->Get("MyOutputContainer");
	TH1D* hPtMB = (TH1D*)l0->FindObject("fHistPt");
	TH1D* hZvMB = (TH1D*)l0->FindObject("fHistZv");
	// hPtMB->Scale(TMath::Power((hPtMB->Integral()),-1.0));
	 hPtMB->Scale(TMath::Power((hZvMB->Integral()),-1.0));	
	//--------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//                         Loop sobre corridas
	//---------------------------------------------------------------------------------   
	for(int i=0; i<nruns; i++)
	{ 
		TFile *f0 = 0x0;
		f0 = (TFile*)TFile::Open(Form("%s/2016l_1run/000%s/AnalysisResults.root",path,runn[i]));
		//if(!f0)printf("no f0\n");
		TDirectory *d0 = new TDirectory();
		d0 = (TDirectory*)f0->Get("MyTask");
		//if(!d0)printf("no d0\n");
		TList* l0 = new TList();
		l0 = (TList*)d0->Get("MyOutputContainer");
		//if(!l0)printf("no l0\n");
		hPt[i] = (TH1D*)l0->FindObject("fHistPt");
		hPt[i]->SetName(Form("hPt_%s",runn[i]));
		hZv[i] = (TH1D*)l0->FindObject("fHistZv");
		//if(!hPt[i])printf("no hPt[i]\n");
		//hPt[i]->Scale(TMath::Power(325033,-1.0));
		//hPt[i]->Scale(TMath::Power((hPt[i]->Integral()),-1.0));
		hPt[i]->Scale(TMath::Power((hZv[i]->Integral()),-1.0));		
		hPt[i]->Divide(hPtMB);
	}
	//-----------------------------------------------------------------------------------
	//                         CANVAS
	//---------------------------------------------------------------------------------   
	TCanvas *c = new TCanvas("c1","the fit canvas",1000,700);
	//   c->SetFillColorAlpha(kWhite,0);
	c->SetBorderMode(0);
	c->SetBorderSize(2);
	c->SetFrameBorderMode(0);
	//c->SetLogy(); 
	gStyle->SetTitleFont(132,"t"); // tipo de fuente
	gStyle->SetLabelFont(132,"t");  
	gStyle->SetLegendFont(132); 
	//-------------------------------------------------------
	hPtMB->SetTitle(" "); // Título del gráfico
	hPtMB->SetStats(0);
	hPtMB->GetXaxis()->SetTitle("p_{T} (MeV/c)"); //Etiqueta eje X
	hPtMB->GetXaxis()->SetRangeUser(0.1,100000); 
	hPtMB->GetXaxis()->SetTitleFont(132);
	hPtMB->GetXaxis()->SetTitleSize(0.03);
	hPtMB->GetXaxis()->SetLabelFont(132);
	hPtMB->GetXaxis()->SetTitleOffset(1.2);
	hPtMB->GetYaxis()->SetTitle("Ratio");//#LT N_{track} #GT / #LT N_{Ev} #GT"); //Etiqueta eje Y
	hPtMB->GetYaxis()->SetRangeUser(0,2); 
	hPtMB->GetYaxis()->SetTitleFont(132);
	hPtMB->GetYaxis()->SetTitleSize(0.04);
	hPtMB->GetYaxis()->SetLabelFont(132);
	hPtMB->GetYaxis()->SetTitleOffset(1.2);
	//   hPtMB->GetYaxis()->CenterTitle();
	hPtMB->Draw(); 
	//   	hPtMB->SetMarkerStyle(10); 
	//   	hPtMB->SetMarkerSize(1.0);
	hPtMB->SetMarkerColorAlpha(kWhite,0);
	hPtMB->SetLineColorAlpha(kWhite,0);
	//------------------------------------------------------------------------------------
	//						Etiquetas
	//------------------------------------------------------------------------------------
	TLegend* tLeg = new TLegend(0.92,0.01,0.99,0.99); 
	tLeg->SetMargin(0.1); 
	tLeg->SetFillColorAlpha(kWhite,0); 
	tLeg->SetLineColorAlpha(kWhite,0);
	tLeg->Draw();
	//------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------
	///float j[nruns];
	for(int i=0; i<nruns; i++)
	{             
		double j = double(i)/double(nruns);
		Int_t ci = TColor::GetFreeColorIndex();
		TColor *color = new TColor(ci,  0.6 - j/2 , 0, 0.1 + j/3);
		//-------------------------------------------------------
		//	printf("%d\n",i- 10*(i/10));
		//-------------------------------------------------------
		TH1F* hClone = 0x0;
		hClone = (TH1F*)hPt[i]->Clone(Form("hClone_%s",runn[i]));
		TLegendEntry* l= tLeg->AddEntry(hClone,Form("%s",runn[i]),"p"); 
		hClone->SetMarkerStyle(mark[i- 10*(i/10)]); 
		hClone->SetMarkerSize(1.0);
		hClone->SetMarkerColorAlpha(ci,0.5);
		hClone->SetLineColorAlpha(ci,0.5);
		hClone->Draw("same");    
	}
	//-------------------------------------------------------    
	//-------------------------------------------------------
	c->SaveAs("./c.pdf");
	//-----------------------------------------------------
	TFile* fOut = new TFile("./fOut.root", "RECREATE");
	fOut->cd();
	for(int i = 0; i < nruns; ++i)
		hPt[i]->Write();
	c->Write();
	fOut->Close();
	//------------------------------------------------------

}

