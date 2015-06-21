//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define N 2000 		// Maximum number of data to represent
using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.


int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
char f1[100],f2[100],f3[100],f4[100];
Float_t wv[N],T[N], wv2[N],T2[N];
Int_t nt=0;  


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



switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);	 
		break;
	case 3: sprintf(f1,"%s.txt",argv[1]);	 
		sprintf(f2,"%s.txt",argv[2]);	 
		break;
	case 4: sprintf(f1,"%s.txt",argv[1]);	 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);
		break;
	case 5: sprintf(f1,"%s.txt",argv[1]);	 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);
		sprintf(f4,"%s.txt",argv[4]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   


Read_FTRw(f1,wv,T,nt);
cout << "nt= "<< nt << endl;
c->cd();


TGraph *gr0 = new TGraph(nt,wv,T);
Plot_TR(gr0,1,2);
PrintLatex(argv[1], 1, 2,0);


if (argc>2)
	{
	Read_FTRw(f2,wv2,T2,nt);
	TGraph *gr2 = new TGraph(nt,wv2,T2);
	Plot_TR(gr2,0,4);
	PrintLatex(argv[2], 1, 4,1);
	}


if (argc>3)
	{
	Read_FTRw(f3,wv,T,nt);
	TGraph *gr3 = new TGraph(nt,wv,T);
	Plot_TR(gr3,0,1);
	PrintLatex(argv[3], 1, 1,2);
	}






theApp->Run(kTRUE);						
delete theApp;
return 0;
}
