//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1
#define FIT 1

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv); 
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Int_t N=10000,n=0;
Float_t x[N],y[N]; 	
char f1[100],f2[100],f3[100],f4[100],f5[100];

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c->cd(1);
vp->SetFillColor(10); 
//vp->SetLogx();
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
	case 2: sprintf(f1,"%s.CSV",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		break;		
	case 3: sprintf(f2,"%s.CSV",argv[1]);                // Filename file columns
		sprintf(f3,"%s.CSV",argv[2]);

	case 4: sprintf(f1,"%s.CSV",argv[1]);                // Filename file columns
		sprintf(f2,"%s.CSV",argv[2]);				// columns 
		sprintf(f3,"%s.CSV",argv[3]);	
		break;
	case 5: sprintf(f1,"%s.CSV",argv[1]);                // Filename file columns
		sprintf(f2,"%s.CSV",argv[2]); 
		sprintf(f3,"%s.CSV",argv[3]); 
		sprintf(f4,"%s.CSV",argv[4]); 
		break;

	case 6: sprintf(f1,"%s.CSV",argv[1]);                // Filename file columns
		sprintf(f2,"%s.CSV",argv[2]); 
		sprintf(f3,"%s.CSV",argv[3]); 
		sprintf(f4,"%s.CSV",argv[4]); 
		sprintf(f5,"%s.CSV",argv[5]); 
		break;

	default:
		MsgError();
		exit(1);
		break;
	};   


Read_raman(f1,x,y,n);
TGraph *gr1 = new TGraph(n-1,x,y);
Plot_raman(gr1,1,2);
PrintLatex3(Form("Position 1"), 2, 2,1);
//TGaxis *axis = new TGaxis(100,gPad->GetUymax(),3500,gPad->GetUymax(),100,2.857142857,510,"+L");
//axis->Draw();

if (argc>2)
	{
 	Read_raman(f2,x,y,n);
	TGraph *gr2 = new TGraph(n-1,x,y);
	Plot_raman(gr2,0,4);
	PrintLatex3(Form("Position 2"), 2, 4,2);
	}

if (argc>3)
	{
 	Read_raman(f3,x,y,n);
	TGraph *gr3 = new TGraph(n-1,x,y);
	Plot_raman(gr3,0,kGreen+3);
	PrintLatex3(Form("Position 3"), 2, kGreen+3,3);
	}


if (argc>4)
	{
 	Read_raman(f4,x,y,n);
	TGraph *gr4 = new TGraph(n-1,x,y);
	Plot_raman(gr4,0,1);
	PrintLatex3(Form("Position 4"), 2, 1,4);
	}


if (argc>5)
	{
 	Read_raman(f5,x,y,n);
	TGraph *gr5 = new TGraph(n-1,x,y);
	Plot_raman(gr5,0,kOrange+3);
	PrintLatex3(Form("Position 5"), 2, kOrange+3,5);
	}







#if GRAPH				
	theApp->Run(kTRUE);						
	delete theApp;
#endif 
return 0;


}
