//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
#define THD 5  // THRESHOLD OF NOISE

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{

//********************************** SETTINGS ***********************************
Float_t MIDL=1.1e-5;	  	// DEFAULT MINIMAL DETECTION LIMIT //3.1e-5 for intense emission Eu2     1.1e-6 for rest
Float_t MXDL=8.1e-1;	  	// DEFAULT MAXIMAL DETECTION LIMIT
Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
Int_t miny=0, maxy=2395;	// LIMITS OF THE EXCITATION ==> (228,595)
//******************************************************************************


//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,i,l=0,aux=0;  // initial parameters
Float_t exc[2000],emis[2000],value[2000][2000];		      
Char_t f1[100],scint[100]="NaI",doped[100]="",sample[100]="00000",title[100]="",ci[2048]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Optical Excitation",100,100,1200,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		// FILENAME 	
		break;						 
default:
		MsgError();
		exit(1);
		break;

	};   

GetInfo(f1,sample,scint,doped);
cout << "***************************"<< endl;
sprintf(title,"Afteglow - %s - Sample %s ",scint,sample);
GetCompound(scint,doped,scint);

ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	*in >> ci; *in >> ci;			// removes  "Time (s)"
	k=0;
	while (aux==0)		// reads the times
		{
		*in >> ci;
		exc[k]= atof(ci);
		if ((k>10)&&(exc[k]<exc[k-1])) 	
			{aux=1;exc[k]=exc[k-1]+5; cout << "last exc: " << exc[k] << endl; }  //first emission (220 nm) is lower than last time point (thousand of seconds);
		else 	k++;    
		}
	Int_t xsteps=k;			// Nb of steps in times
	Float_t minv=1;
	Float_t maxv=0;
	Int_t msteps=690;
	
	for (l=0;l<msteps;l++)			
		for (k=0;k<xsteps+1;k++)		
			{
			if (aux==1) aux=0;
			else *in >> ci;	
			if (k==0) 
				{
				emis[l] = atof(ci);   //	cout << "emi: " << l <<" " << emis[l] << endl;				
				}	 
			else 
				{	
				value[l][k-1]=atof(ci); //if (l==0) cout <<  value[l][k-1] << endl;
				if (value[l][k-1]<0) value[l][k-1]= 0; // if the value is neg. put 0
				if (value[l][k-1]<minv) minv=value[l][k-1]; // find min value of the matrix
				if (value[l][k-1]>maxv) maxv=value[l][k-1]; // find max value of the matrix
				}
			}

	//Int_t msteps=msteps; // Nb of steps in emission

	cout << "Time. steps: " << xsteps << " emis. steps: " << msteps << endl;
	cout << "min: "<< minv << " // max:" << maxv << endl;

	MIDL=minv;
	MXDL=maxv;



	exc[xsteps]=exc[xsteps-1]+5;//	we add the last value. 
	emis[msteps]=emis[msteps-1]+0.4;	//931.9	we add the last value. 
 	cout << "exc[xteps]: " << exc[xsteps] <<" " << emis[msteps] << endl;		








	TH2F *H = new TH2F("H","H",msteps,emis,xsteps,exc);  // declaration of the histogram	 
/*	for (l=0;l<msteps;l++)
		for (k=0;k<xsteps;k++)	
			H->SetBinContent(l,k,value[l][k]);
	
	H->SetMarkerStyle(21);
	H->SetMarkerSize(0.1);
	H->SetTitle(title);
	H->GetXaxis()->SetTitle("Emission (nm)");
	H->GetYaxis()->SetTitle("Time (s)");
	H->GetXaxis()->CenterTitle();
	H->GetYaxis()->CenterTitle();
	//H->GetXaxis()->SetRangeUser(minx,maxx);
	//H->GetYaxis()->SetRangeUser(miny,maxy);
	gStyle->SetPalette(1);
	//H->Draw("COLZ");           	
	//H->Draw("PCOL"); 
	H->SetContour(25); 
	H->Draw("contz"); 
  	//H->Draw("mercator");
 	//c1->SetLogz(); 
	H->GetZaxis()->SetRangeUser(MIDL/2,MXDL*2);
	//H->GetZaxis()->SetRangeUser(0,MXDL/2);  // for the paper CBI
	//H->Smooth(1);
	//H->Smooth(1);
	H->Smooth(1);

*/
	PrintLatex2(Form("%s",scint),0.15,0.85,kBlack);

	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
