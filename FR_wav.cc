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
Float_t x[N],y[N]; 	
Int_t i,m;  
char ci[100],title[100]="title",file[100];

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
	case 2: m=sprintf(file,"%s.txt",argv[1]);	 
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   


ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {
	
	i=0;
	while (!in->eof())
		{
		*in >> ci;  	*in >> ci;	  *in >> ci;  	*in >> ci;	  // takes away the first line
		*in >> x[i] >> y[i];
		i++;
		}
	TGraph *gr0 = new TGraph(i-1,x,y);		// Graph declaration
	gr0->SetLineColor(4);					
	gr0->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(4);						
	gr0->SetMarkerStyle(20);						
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitle("Wavelength (nm)");				
	gr0->GetYaxis()->SetTitle("Reflectance (%)");				
	gr0->GetXaxis()->SetTitleSize(0.06);
	gr0->GetYaxis()->SetTitleSize(0.06);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	gr0->Draw("Ac");

	TLatex *tx = new TLatex();
	tx->SetNDC();
	tx->SetTextFont(62);
	tx->SetTextAlign(12);
	tx->SetTextSize(0.04);
	tx->SetTextColor(4);
	tx->DrawLatex(0.4,0.95,argv[1]);
	}

theApp->Run(kTRUE);						
delete theApp;
return 0;
}
