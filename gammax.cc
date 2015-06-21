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
Float_t x[N],y[N],yn[N],days=0; 		      
char f1[100],f2[100],f3[100],f4[100],f5[100],f6[100],f7[100],f8[100],f9[100];
char latex8[100],latex9[100];


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
	case 2: sprintf(f1,"%s",argv[1]);			
		break;						 
	case 3: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		break;
	case 4: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		break;
	case 5: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);
		break;
	case 6: sprintf(f1,"%s",argv[1]);	
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);
		sprintf(f5,"%s",argv[5]);
		break;
	case 7: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);	
		sprintf(f5,"%s",argv[5]);
		sprintf(f6,"%s",argv[6]);
		break;
	case 8: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);	
		sprintf(f5,"%s",argv[5]);
		sprintf(f6,"%s",argv[6]);
		sprintf(f7,"%s",argv[7]);
		break;
	case 9: sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);	
		sprintf(f5,"%s",argv[5]);
		sprintf(f6,"%s",argv[6]);
		sprintf(f7,"%s",argv[7]);
		sprintf(f8,"%s",argv[8]);
		break;
 	case 10:sprintf(f1,"%s",argv[1]);		
		sprintf(f2,"%s",argv[2]);
		sprintf(f3,"%s",argv[3]);
		sprintf(f4,"%s",argv[4]);	
		sprintf(f5,"%s",argv[5]);
		sprintf(f6,"%s",argv[6]);
		sprintf(f7,"%s",argv[7]);
		sprintf(f8,"%s",argv[8]);
		sprintf(f9,"%s",argv[9]);
		break;


default:
		MsgError();
		exit(1);
		break;

	};   



if (argc>1)
	{
	Read_GV2(f1, y, days,N);
	TH1F *H = new TH1F("H",f1,N,0,N-1);  // declaration of the histogram	 
	//Normalize(y, yn, N);
	Plot_PHM(H, y, 1, 2, N);
	H->Scale(87858.65/53483.8);
	PrintLatex2(Form("%s",argv[1]),0.5,0.85,2);
	}



if (argc>2)
	{
	Read_GV2(f2,y,days,N);
	TH1F *H2 = new TH1F("H2",f2,N,0,N-1);  // declaration of the histogram	
	//Normalize(y, yn, N);
	Plot_PHM(H2, y, 0, 4, N);
	//H2->Scale(1.5);
	PrintLatex2(Form("%s",argv[2]),0.5,0.80,4);
	}



if (argc>3)
	{
	Read_GV2(f3,y,days,N);
	TH1F *H3 = new TH1F("H3",f3,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H3, y, 0, kGreen+3, N);	
	H3->Scale(0.3);
	PrintLatex2(Form("%s",argv[3]),0.5,0.75,kGreen+3);
	}



if (argc>4)
	{
	Read_GV2(f4, y,days,N);
	TH1F *H4 = new TH1F("H4",f4,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H4, y, 0, 1, N);
	H4->Scale(0.3);
	PrintLatex2(Form("%s",argv[4]),0.5,0.70,1);
	}

if (argc>5)
	{
	Read_GV2(f5, y,days,N);
	TH1F *H5 = new TH1F("H5",f5,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H5, y, 0, 6, N);
	H5->Scale(0.01);
	PrintLatex2(Form("%s",argv[5]),0.5,0.65,6);
	}


if (argc>6)
	{
	Read_GV2(f6, y,days,N);
	TH1F *H6 = new TH1F("H6",f6,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H6, y, 0, kCyan+2, N);
	PrintLatex2(Form("%s",argv[6]),0.5,0.60,kCyan+2);
	}


if (argc>7)
	{
	Read_GV2(f7,y,days,N);
	TH1F *H7 = new TH1F("H7",f7,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H7, y, 0, kOrange, N);
	PrintLatex2(Form("%s",argv[7]),0.5,0.55,kOrange);
	}



if (argc>8)
	{
	Read_GV2(f8,y,days,N);
	TH1F *H8 = new TH1F("H8",f8,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H8, y, 0, kMagenta, N);
	PrintLatex2(Form("%s",argv[8]),0.5,0.50,kMagenta);
	}


if (argc>9)
	{
	Read_GV2(f9,y,days,N);
	TH1F *H9 = new TH1F("H9",f9,N,0,N-1);  // declaration of the histogram	
	Normalize(y, yn, N);
	Plot_PHM(H9, y, 0, 14, N);
	PrintLatex2(Form("%s",argv[9]),0.5,0.45,kOrange+4);
	}











gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off


theApp->Run(kTRUE);
delete theApp;
return 0;
}
