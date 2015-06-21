//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{

//********************************** SETTINGS ***********************************
Float_t MIDL=1.1e-5;	  	// MINIMAL DETECTION LIMIT //3.1e-5 for intense emission Eu2     1.1e-6 for rest
Float_t MXDL=8.1e-3;	  	// MAXIMAL DETECTION LIMIT
Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
Int_t miny=220, maxy=450;	// LIMITS OF THE EXCITATION ==> (228,595)
//******************************************************************************


//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,l=0,aux=0;  // initial parameters
Float_t exc[150],emis[1815],value[2000][100]; 		      
Char_t f1[100],scint[100]="NaI",doped[100]="",sample[100]="00000",title[100]="",ci[2048]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Optical Excitation",200,100,1200,800);
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
sprintf(title,"Optical Excitation - %s - Sample %s ",scint,sample);

GetCompound(scint,doped,scint);

ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	*in >> ci; *in >> ci;			// removes  "Wavelength (nm)"
	k=0;
	while (aux==0)		// reads the excitation
		{
		*in >> ci;
		exc[k]= atof(ci);
		if ((k>10)&&(exc[k]<exc[k-1])) 	{aux=1;exc[k]=0;} //first emission is lower than last exc point;
		else 	k++;    
		}

	Int_t xsteps=k;			// Nb of steps in exc
	Int_t msteps=1814;		// Nb of steps in emission
	Float_t minv=1;
	Float_t maxv=0;

	cout << "exc. steps: " << xsteps << "     emis. steps: " << msteps << endl;
	for (l=0;l<msteps;l++)			
		for (k=0;k<xsteps+1;k++)		
			{
			if (aux==1) aux=0;
			else *in >> ci;	
			if (k==0) {emis[l] = atof(ci);}
			else 
				{	
				value[l][k-1]=atof(ci); 
				if (value[l][k-1]<0) value[l][k-1]=0;//-value[l][k-1]; // remove negatives
				if (value[l][k-1]<minv) minv=value[l][k-1]; // find min value of the matrix
				if (value[l][k-1]<maxv) maxv=value[l][k-1]; // find max value of the matrix
				}
			}
	MIDL=minv;
	MXDL=maxv;
	for (l=0;l<msteps;l++)			
		for (k=0;k<xsteps+1;k++)		
			{
					
	/*		if (value[l][k-1]<MIDL*2) value[l][k-1]=MIDL*1.1; // define minimum threshold of 10
			if ((exc[k-1]>(emis[l]-10)) && (exc[k-1]<(emis[l]+10))) value[l][k-1]=MIDL*1.1;   
			if ((exc[k-1]>295) && (exc[k-1]<315) && (emis[l]>608) && (emis[l]<622)) value[l][k-1]=MIDL*1.1; //subtract issue
			if ((exc[k-1]>emis[k]>608) && (emis[l]<622)) value[l][k-1]=MIDL*1.1;
	*/		}





	exc[xsteps]=595.1;	//595.1;	 
	emis[msteps]=931.9;	//931.9
	TH2F *H = new TH2F("H","H",msteps,emis,xsteps,exc);  // declaration of the histogram	 
		
	for (l=0;l<msteps;l++)
		for (k=0;k<xsteps;k++)	
			H->SetBinContent(l,k,value[l][k]);
 

/*	TH2F *Hf = new TH2F("Hf","Hf",msteps*100,emis,xsteps*100,exc);  // declaration of the histogram
	for (Int_t ll=0;ll<msteps*100;ll++)
		for (Int_t kk=0;kk<xsteps*100;kk++)	
			Hf->SetBinContent(ll,kk,H->Interpolate(emis[ll/100],exc[kk/100]));*/


	H->SetMarkerStyle(21);
	H->SetMarkerSize(0.1);
	H->SetTitle(title);
	H->GetXaxis()->SetTitle("Emission (nm)");
	H->GetYaxis()->SetTitle("Excitation (nm)");
	H->GetXaxis()->CenterTitle();
	H->GetYaxis()->CenterTitle();
	H->GetXaxis()->SetRangeUser(minx,maxx);
	H->GetYaxis()->SetRangeUser(miny,maxy);
	H->Draw("COLZ");           	//H->Draw("PCOL");//H->Draw("contz");	
	c1->SetLogz(); 
	H->GetZaxis()->SetRangeUser(MIDL/2,MXDL);
	H->Smooth(1);
	H->Smooth(1);
	H->Smooth(1);

  	//gPad->Update();
 
	//H->Smooth(1);
	//TPaletteAxis *palette = (TPaletteAxis*)H->GetListOfFunctions()->FindObject("palette");
   	//palette->SetLabelSize(0.03);	
	//palette->SetLabelOffset(0);	
	PrintLatex2(Form("%s (%s)",scint,sample),0.50,0.85,kWhite);

	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
