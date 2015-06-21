//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h" 

#define N 2000 	// Maximum number of data to represent
using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define GRAPH 1

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

TCanvas *c = new TCanvas("FTR","FTR",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TLegend *legend=new TLegend(0.12,0.80,0.38,0.90);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

// DECLARATION OF VARIABLES
Float_t wv[N],wv2[N],T[N],R[N]; 	
Int_t nt=0,nr=0;  
Char_t ci[100],title[100]="title",f1[100],f2[100],f3[100],f4[100],f5[100],f6[100],*sepa, scint[10]="",sample[10]="";



switch (argc)
	{
	case 2: sprintf(f1,"%s-T.txt",argv[1]);                // name file columns
		sprintf(f2,"%s-R.txt",argv[1]); 
		break;
	case 3: sprintf(f1,"%s-T.txt",argv[1]);                // Filename file columns
		sprintf(f2,"%s-R.txt",argv[1]); 
		sprintf(f3,"%s-T.txt",argv[2]);                // Filename file columns
		sprintf(f4,"%s-R.txt",argv[2]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   



Char_t ti[10];
GetTime(f1,ti);          // Get the time the file was modified

Read_FTRw(f1,wv,T,nt);
Read_FTRw(f2,wv2,R,nt);

c->cd();
TGraph *gr1 = new TGraph(nt,wv2,R);
TGraph *gr1b = new TGraph(nt,wv,T);
legend->AddEntry(gr1,"Reflection","l");
legend->AddEntry(gr1b,"Transmission","l");
Plot_TR(gr1,gr1b,1,4,2);
gr1->GetXaxis()->SetRangeUser(200,1049);
//gr1->GetYaxis()->SetRangeUser(0.01,19);
GetInfo(argv[1], sample);
PrintLatex3(sample, 2, 1,1);


/*
if (argc>2)
	{

	Read_FTRw(f3,wv,T,nt);
	Read_FTRw(f4,wv2,R,nr);
	TGraph *gr2 = new TGraph(nt,wv2,R);
	TGraph *gr2b = new TGraph(nt,wv,T);
	legend->AddEntry(gr2,"Reflection","l");
	legend->AddEntry(gr2b,"Transmission","l");
	Plot_TR(gr2,gr1b,0,6);
	PrintLatex("TITLE", 4, 1,1);
	}





*/





legend->Draw();
theApp->Run(kTRUE);						
delete theApp;
return 0;
}
