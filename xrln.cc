
//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h" 
 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t n=0;  //number of points
Float_t x[5000],y[5000],yn[5000]; 		      
Char_t f1[100],f2[100],f3[100],f4[100],f5[100],f6[100],scint[100]="",sample[100]="00000",dopant[100]="",compound[100]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
gStyle->SetOptTitle(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","XRL",200,100,1200,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						


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
	case 6: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
		sprintf(f5,"%s.txt",argv[5]);	
   		break;
	case 7: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
		sprintf(f5,"%s.txt",argv[5]);	
		sprintf(f6,"%s.txt",argv[6]);	
   		break;

default:
		MsgError();
		exit(1);
		break;

	};   


if (argc>1)
	{
	GetInfo(argv[1], sample, scint, dopant);
	Read_XRL(f1, x, y, n);
	Normalize(y, yn, n);
	//Normalizeby(yn, yn, 0.25, n);
	TGraph *gr1 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr1,1,2);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.50,0.85,2);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.85,2);
	}
	


if (argc>2)
	{
	GetInfo(argv[2], sample, scint, dopant);
	Read_XRL(f2, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr2 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr2,0,4);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.50,0.80,4);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.80,4);
	}



if (argc>3)
	{
	GetInfo(argv[3], sample, scint, dopant);
	Read_XRL(f3, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr3 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr3,0,kGreen+3);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.50,0.75,kGreen+3);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.75,kGreen+3);
	}


if (argc>4)
	{
	GetInfo(argv[4], sample, scint, dopant);
	Read_XRL(f4, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr4 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr4,0,1);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.50,0.70,1);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.70,1);
	}






if (argc>5)
	{
	GetInfo(argv[5], sample, scint, dopant);
	Read_XRL(f5, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr5 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr5,0,6);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.50,0.65,6);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.65,6);
	}





if (argc>6)
	{
	GetInfo(argv[6], sample, scint, dopant);
	Read_XRL(f6, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr6 = new TGraph(n-1,x,yn);		 
	Plot_XRL(gr6,0,9);
	PrintLatex2(Form("- %s",compound),0.50,0.60,9);
	//PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.60,9);
	}





theApp->Run(kTRUE);
delete theApp;
return 0;
}
