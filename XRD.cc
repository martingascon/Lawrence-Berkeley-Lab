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
Char_t f1[100],f2[100],f3[100],f4[100],f5[100],f6[100],f7[100],scint[100]="",sample[100]="00000",dopant[100]="",compound[100]="";


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
	case 2: sprintf(f1,"%s.dat",argv[1]);		 	
		break;						 
	case 3: sprintf(f1,"%s.dat",argv[1]);		 	
		sprintf(f2,"%s.dat",argv[2]);	
		break;		
	case 4: sprintf(f1,"%s.dat",argv[1]);		 
		sprintf(f2,"%s.dat",argv[2]);	
		sprintf(f3,"%s.dat",argv[3]);	
		break;
	case 5: sprintf(f1,"%s.dat",argv[1]);		 
		sprintf(f2,"%s.dat",argv[2]);	
		sprintf(f3,"%s.dat",argv[3]);	
		sprintf(f4,"%s.dat",argv[4]);	
   		break;
	case 6: sprintf(f1,"%s.dat",argv[1]);		 
		sprintf(f2,"%s.dat",argv[2]);	
		sprintf(f3,"%s.dat",argv[3]);	
		sprintf(f4,"%s.dat",argv[4]);	
		sprintf(f5,"%s.dat",argv[5]);	
   		break;
	case 7: sprintf(f1,"%s.dat",argv[1]);		 
		sprintf(f2,"%s.dat",argv[2]);	
		sprintf(f3,"%s.dat",argv[3]);	
		sprintf(f4,"%s.dat",argv[4]);	
		sprintf(f5,"%s.dat",argv[5]);	
		sprintf(f6,"%s.dat",argv[6]);	
   		break;
	case 8: sprintf(f1,"%s.dat",argv[1]);		 
		sprintf(f2,"%s.dat",argv[2]);	
		sprintf(f3,"%s.dat",argv[3]);	
		sprintf(f4,"%s.dat",argv[4]);	
		sprintf(f5,"%s.dat",argv[5]);	
		sprintf(f6,"%s.dat",argv[6]);	
		sprintf(f7,"%s.dat",argv[7]);
   		break;

default:
		MsgError();
		exit(1);
		break;

	};   


if (argc>1)
	{
	GetInfo(argv[1], sample);
	Read_XRD(f1, x, y, n);
	//Normalizeby(y,y, 1, n);	 
	TH1F *H1 = new TH1F("H1","H1",1452,x);
	Plot_XRD(H1,x,y,n, 1,2);
	PrintLatex2(Form("- %s",sample),0.80,0.85,2);
	}

 

if (argc>2)
	{
	GetInfo(argv[2], sample);
	Read_XRD(f2, x, y, n);	
	//Normalizeby(y,y, 1, n);
    TH1F *H2 = new TH1F("H2","H2",1452,x);
	Plot_XRD(H2,x,y,n, 0,4);
	PrintLatex2(Form("- %s",sample),0.80,0.80,4);
	}



if (argc>3)
	{
	GetInfo(argv[3], sample);
	Read_XRD(f3, x, y, n);	
    TH1F *H3 = new TH1F("H3","H3",1452,x);
	Plot_XRD(H3,x,y,n, 0,kGreen+3);
	PrintLatex2(Form("- %s",sample),0.80,0.75,kGreen+3);
	}


if (argc>4)
	{
	GetInfo(argv[4], sample);
	Read_XRD(f4, x, y, n);	
    TH1F *H4 = new TH1F("H4","H4",1452,x);
	Plot_XRD(H4,x,y,n,0,1);
	PrintLatex2(Form("- %s",sample),0.80,0.70,1);
	}

if (argc>5)
	{
	GetInfo(argv[5], sample);
	Read_XRD(f5, x, y, n);	
    TH1F *H5 = new TH1F("H5","H5",1452,x);
	Plot_XRD(H5,x,y,n,0,6);
	PrintLatex2(Form("- %s",sample),0.80,0.65,6);
	}

/*



if (argc>6)
	{
	GetInfo(argv[6], sample);
	Read_XRD(f6, x, y, n);	
	TGraph *gr6 = new TGraph(n-1,x,y);		 
	Plot_XRD(gr6,0,9);
 	PrintLatex2(Form("- %s",sample),0.80,0.60,9);
	}

if (argc>7)
	{
	GetInfo(argv[7], sample);
	Read_XRD(f7, x, y, n);	
	TGraph *gr7 = new TGraph(n-1,x,y);		 
	Plot_XRD(gr7,0,kOrange);
 	PrintLatex2(Form("- %s",sample),0.80,0.60,kOrange);
	}


/*	
	por si queremos dibujar con un histo.	
	TH1F *H2 = new TH1F("H2","f",1000,0,100);
	for (Int_t k=0;k<n-1;k++)			
		{
		H2->Fill(x[k],y[k]/5);		// fill the histogram
		}
	H2->SetMarkerColor(6);
	H2->SetFillColor(6);
	H2->SetLineColor(6);
	H2->SetLineWidth(2);
	H2->SetMarkerStyle(8);
	H2->SetMarkerSize(1);
	H2->Draw("same");

*/



theApp->Run(kTRUE);
delete theApp;
return 0;
}
