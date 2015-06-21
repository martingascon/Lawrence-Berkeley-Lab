//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.


int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES		//15348-Ba1Br1I1-4Eu2-OptEx-12_18_2012-Emission300nm this format of files
Int_t N=50000;  
Float_t x[N],y[N],yn[N]; 	
Char_t f1[100],f2[100],f3[100],f4[100], scint[100]="NaI",sample[100]="00000",dopant[100],emis[100]="220 nm";
char *info[100];


TCanvas *c = new TCanvas("c","Graph2D",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c->cd(1);
vp->SetFillColor(10);
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);

TLegend *legend=new TLegend(0.75,0.85,0.98,0.98);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);	 
		break;
	case 3: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f2,"%s.txt",argv[2]);
		break;
	case 4: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		break;
	case 5: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		sprintf(f4,"%s.txt",argv[4]);
		break;	
	default:
 		MsgError();
		exit(1);
		break;
	};   
 





GetInfo(argv[1], sample, scint, dopant);
if (argc>1)
	{
	GetInfo(argv[1], sample, scint, dopant);
	Read_OE1D(f1,x,y,N);
	//Substract(y, 120, N);
	//Normalize(y, yn, N);
	Normalizeby(y, yn, 0.05, N);

	TGraph *gr1 = new TGraph(N-1,x,yn);		
	Plot_OE1D(gr1, 1, 2);
	gr1->GetYaxis()->SetTitleOffset(1.2);
	gr1->GetXaxis()->SetTitle("Wavelenght (nm)");				
	gr1->GetYaxis()->SetTitle("Intensity (a.u.)");	
	legend->AddEntry(gr1,Form("%s",scint),"l");
	//gr0->GetXaxis()->SetRangeUser(275,490);
	}
 
if (argc>2)
	{
	GetInfo(argv[2], sample, scint, dopant);
	Read_OE1D(f2,x,y,N);
	Normalizeby(y, yn,0.05, N);
	//Normalize(y, yn, N);
	TGraph *gr2 = new TGraph(N-1,x,yn);	
	Plot_OE1D(gr2, 0, 4);
	legend->AddEntry(gr2,Form("%s",scint),"l");
	//gr1->GetXaxis()->SetRangeUser(275,490);
	}



if (argc>3)
	{
	GetInfo(argv[3], sample, scint, dopant);
	Read_OE1D(f3,x,y,N);
	Normalizeby(y, yn, 0.0025, N);
	TGraph *gr3 = new TGraph(N-1,x,y);		
	Plot_OE1D(gr3, 0, kGreen+3);
	legend->AddEntry(gr3,Form("%s",scint),"l");
	}

if (argc>4)
	{
	GetInfo(argv[4], sample, scint, dopant);
	Read_OE1D(f4,x,y,N);
	TGraph *gr4 = new TGraph(N-1,x,y);		
	Plot_OE1D(gr4, 0, 6);
	legend->AddEntry(gr4,Form("%s",scint),"l");
	}









legend->Draw();

theApp->Run(kTRUE);						
delete theApp;
return 0;
}
