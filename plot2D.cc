//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"

#define GAUSSIANS 1 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t xc[22] = {8.5,20.7,33.1,45.5,57.9,70.1,82.5,94.9,107.3,119.7,131.9,144.3,156.7,169.1,181.3,193.7,206.1,218.5,230.9,243.1,255.5,267.9};
Float_t yc[16] = {7.5,19.7,32.1,44.5,56.9,69.1,81.5,93.9,106.3,118.7,130.9,143.3,155.7,168.1,180.3,192.5}; 
   
Char_t f1[100];

gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(1);     // display fit parameters 1 = on, 0 = off
set_plot_style();

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.dat",argv[1]);		// FILENAME 	
		break;						 
default:
		MsgError();
		exit(1);
		break;

	};   

cout << "***************************"<< endl;
Float_t x[1000],y[1000],z[1000];
Char_t ci[100],ci2[100],ci3[100];
Int_t l,k,p=0;

ifstream *in = new ifstream(f1);
if(!*in)
	{
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else  
	{
	///////// reads the coordinates		// (x1,y1) (x2,y1) ... (xn,y1) (x2,y2) .. (xn,y2) etc.	
	while (!in->eof()) 						
	 	{
	 	*in >> ci >> ci2 >> ci3;  			 
		x[p] = atof(ci); 	// convierto a entero 
		y[p] = atof(ci2);
		z[p] = atof(ci3);
		p++;
		}
	Int_t points=p;

	Float_t xlow = GetMin(x,points);
	Float_t xup = GetMax(x,points);

	Float_t ylow = GetMin(y,points);
	Float_t yup = GetMax(y,points);
	
	Int_t nbinx = 21;
	Int_t nbiny = points/nbinx;

	////////////////////////////////////////////////  CON TGRAPH2D
	TGaxis::SetMaxDigits(4);
	TCanvas *c2b = new TCanvas("c2b","OE Mapping TGraph2D (Integral)",0,100,555*nbinx/nbiny*1.15,555); 
	c2b->SetFillColor(0);
	c2b->GetFrame()->SetFillColor(0); 
	c2b->GetFrame()->SetBorderMode(-1);
	TVirtualPad *vp2 =  c2b->cd(1);
	vp2->SetFillColor(10);
	vp2->SetBorderSize(2);
	vp2->SetFrameFillColor(0);
	vp2->SetLeftMargin(.15);
	vp2->SetRightMargin(.15);
	vp2->SetBottomMargin(.1);
	vp2->SetTopMargin(.05);


	

 	TH2F *H = new TH2F("H","H",21,xc,15,yc);    
	//TH2F *H = new TH2F();    
	for (p=0;p<points;p++)                                             
			{
			H->SetBinContent(xc[p],yc[p],z[p]);
	 		}
	        H->SetMarkerStyle(21);
		H->SetMarkerSize(0.1);
		H->GetXaxis()->SetTitle("Position X (#mum)");
		H->GetYaxis()->SetTitle("Position Y (#mum)");
	
		H->GetXaxis()->CenterTitle();
		H->GetYaxis()->CenterTitle();		
		H->GetXaxis()->SetTitleOffset(1.2);
		H->GetYaxis()->SetTitleOffset(1.6);
		//H->GetXaxis()->SetLimits(200,xpos[cols+1]);
   		//H->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
		H->SetContour(99); 
		H->Draw("cont4z"); 
		//ReverseYAxis(H); 
 
 	TCanvas *c2 = new TCanvas("c2","OE Mapping TH2F (Integral)",0,600,555*nbinx/nbiny*1.15,555); 
	c2->SetFillColor(0);
	c2->GetFrame()->SetFillColor(0); 
	c2->GetFrame()->SetBorderMode(-1);
	TVirtualPad *vp =  c2->cd(1);
	vp->SetFillColor(10);
	vp->SetBorderSize(2);
	vp->SetFrameFillColor(0);
	vp->SetLeftMargin(.15);
	vp->SetRightMargin(.15);		
	vp->SetBottomMargin(.1);
	vp->SetTopMargin(.05);


	TGraph2D *H2 = new TGraph2D(points,x,y,z);   
	H2->SetNpy(499);  
	H2->SetNpx(499);
	H2->SetMarkerStyle(21);
	H2->SetMarkerSize(0.1);	   
//	H2->GetXaxis()->SetLimits(xpos[0],xpos[cols+1]);
//	H2->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
	H2->Draw("colz");     
	ReverseYAxis(H2);	
	H2->GetYaxis()->SetLabelSize(0);
	H2->GetXaxis()->SetTitle("Position X (#mum)");
	H2->GetYaxis()->SetTitle("Position Y (#mum)");
	H2->GetXaxis()->SetTitleOffset(1.2);
	H2->GetYaxis()->SetTitleOffset(1.6);
	H2->GetXaxis()->CenterTitle();
	H2->GetYaxis()->CenterTitle();	

/**/

 /*	 TH2F *H = new TH2F();    
	 for (p=0;p<points;p++)                                             
			{
			H->SetBinContent(x[p],y[p],z[p]);
	 		}
	        H->SetMarkerStyle(21);
		H->SetMarkerSize(0.1);
		H->GetXaxis()->SetTitle("Position X (#mum)");
		H->GetYaxis()->SetTitle("Position Y (#mum)");
	
		H->GetXaxis()->CenterTitle();
		H->GetYaxis()->CenterTitle();		
		H->GetXaxis()->SetTitleOffset(1.2);
		H->GetYaxis()->SetTitleOffset(1.6);
		//H->GetXaxis()->SetLimits(200,xpos[cols+1]);
   		//H->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
		H->SetContour(99); 
		H->Draw("cont4z"); 
		ReverseYAxis(H);*/
	}

	





theApp->Run(kTRUE);
delete theApp;
return 0;
}
