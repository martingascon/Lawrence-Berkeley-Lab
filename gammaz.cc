//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

#define GRAPH 1

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,reb=8,N=8192;  
Float_t x[N],y[N],yn[N],y2[N],yn2[N],ys[N],days=0; 		      
char f1[100],f2[100];

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
gStyle->SetOptTitle(0);

#if GRAPH
TCanvas *c1 = new TCanvas("Graph2D example","Gamma-Vision Spectrum",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.12);
vp->SetTopMargin(.07);   



						
#endif 

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;		 
	case 3: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		break;
default:
		MsgError();
		exit(1);
		break;

	};   





if (argc>2)
	{
	Read_GV2(f1,y,days,N);
	Normalizeby(y, yn,0.610645694,N);
	Read_GV2(f2,yn2,days,N);
	//Normalize(y2, yn2, N);
	for (Int_t p=0;p<N;p++)
		{
		ys[p]=y[p]-yn2[p];
		if (ys[p]<0) ys[p]=0;
		}
	TH1F *H2 = new TH1F("H2",f2,N,0,N-1);  // declaration of the histogram	
	//Normalize(y, yn, N);
	Plot_PHM(H2, ys, 1, 2, N);
	//H2->Scale(1.5);
	PrintLatex2(Form("%s",argv[1]),0.5,0.80,2);
	}










gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off


theApp->Run(kTRUE);
delete theApp;
return 0;
}
