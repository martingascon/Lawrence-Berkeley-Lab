//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

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
Float_t x[N],y[N]; 	
Int_t i;  
char title[100]="title",ti[100];
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100],file8[100];

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
	case 2: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		break;
	case 3: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		break;
	case 4: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);	 
		break;
	case 5: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);
		break;
	case 6: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);	 
		sprintf(file4,"%s.txt",argv[4]);
		sprintf(file5,"%s.txt",argv[5]);
		break;
	case 7: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);
		sprintf(file5,"%s.txt",argv[5]);
		sprintf(file6,"%s.txt",argv[6]);
		break;
	case 8: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);	 
		sprintf(file4,"%s.txt",argv[4]);
		sprintf(file5,"%s.txt",argv[5]);
		sprintf(file6,"%s.txt",argv[6]);
		sprintf(file7,"%s.txt",argv[7]);
		break;
	case 9: sprintf(file1,"%s.txt",argv[1]);	 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);
		sprintf(file5,"%s.txt",argv[5]);
		sprintf(file6,"%s.txt",argv[6]);
		sprintf(file7,"%s.txt",argv[7]);
		sprintf(file8,"%s.txt",argv[8]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   



i=0;
Read_FTRw(file1, x, y, i);
TGraph *gr1 = new TGraph(i-1,x,y);		// Graph declaration
gr1->SetLineColor(4);					
gr1->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
gr1->SetMarkerColor(4);						
gr1->SetMarkerStyle(20);						
gr1->SetTitle(title);					
gr1->GetXaxis()->SetTitle("Wavelength (nm)");				
gr1->GetYaxis()->SetTitle("Transmitance (%)");				
gr1->GetXaxis()->SetTitleSize(0.06);
gr1->GetYaxis()->SetTitleSize(0.06);
gr1->GetXaxis()->SetLabelSize(0.05);
gr1->GetYaxis()->SetLabelSize(0.05);
gr1->GetXaxis()->CenterTitle();					
gr1->GetYaxis()->CenterTitle();	
gr1->Draw("Ac");

TLatex *tx = new TLatex();
tx->SetNDC();
tx->SetTextFont(62);
tx->SetTextAlign(12);
tx->SetTextSize(0.04);
tx->SetTextColor(4);
GetTime(file1,ti);

tx->DrawLatex(0.8,0.20,argv[1]);

if (argc>2)
	{
	Read_FTRw(file2, x, y, i);
	TGraph *gr2 = new TGraph(i-1,x,y);		// Graph declaration
	gr2->SetLineColor(2);					
	gr2->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr2->SetMarkerColor(4);						
	gr2->Draw("samec");
	tx->SetTextColor(2);
	
	tx->DrawLatex(0.8,0.25,argv[2]);
	}

if (argc>3)
	{
	Read_FTRw(file3, x, y, i);
	TGraph *gr3 = new TGraph(i-1,x,y);		// Graph declaration
	gr3->SetLineColor(kGreen+3);					
	gr3->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr3->SetMarkerColor(kGreen+3);						
	gr3->Draw("samec");
	tx->SetTextColor(kGreen+3);
	tx->DrawLatex(0.8,0.30,argv[3]);
	}

if (argc>4)
	{
	Read_FTRw(file4, x, y, i);
	TGraph *gr4 = new TGraph(i-1,x,y);		// Graph declaration
	gr4->SetLineColor(kBlack);					
	gr4->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr4->SetMarkerColor(kBlack);						
	gr4->Draw("samec");
	tx->SetTextColor(kBlack);
	tx->DrawLatex(0.8,0.35,argv[4]);
	}

if (argc>5)
	{
	Read_FTRw(file5, x, y, i);
	TGraph *gr5 = new TGraph(i-1,x,y);		// Graph declaration
	gr5->SetLineColor(kMagenta+1);					
	gr5->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr5->SetMarkerColor(kMagenta+1);						
	gr5->Draw("samec");
	tx->SetTextColor(kMagenta+1);
	tx->DrawLatex(0.8,0.40,argv[5]);
	}

if (argc>6)
	{
	Read_FTRw(file6, x, y, i);
	TGraph *gr6 = new TGraph(i-1,x,y);		// Graph declaration
	gr6->SetLineColor(kOrange-3);					
	gr6->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr6->SetMarkerColor(kOrange-3);						
	gr6->Draw("samec");
	tx->SetTextColor(kOrange-3);
	tx->DrawLatex(0.8,0.45,argv[6]);
	}

if (argc>7)
	{
	Read_FTRw(file7, x, y, i);
	TGraph *gr7 = new TGraph(i-1,x,y);		// Graph declaration
	gr7->SetLineColor(kYellow+3);					
	gr7->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr7->SetMarkerColor(kYellow+3);						
	gr7->Draw("samec");
	tx->SetTextColor(kYellow+3);
	tx->DrawLatex(0.8,0.50,argv[7]);
	}

if (argc>8)
	{
	Read_FTRw(file8, x, y, i);
	TGraph *gr8 = new TGraph(i-1,x,y);		// Graph declaration
	gr8->SetLineColor(kCyan+2);					
	gr8->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr8->SetMarkerColor(kCyan+2);						
	gr8->Draw("samec");
	tx->SetTextColor(kCyan+2);
	tx->DrawLatex(0.8,0.55,argv[8]);
	}


theApp->Run(kTRUE);						
delete theApp;
return 0;
}
