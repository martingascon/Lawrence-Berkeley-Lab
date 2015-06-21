//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{

//********************************** SETTINGS ***********************************
Float_t MIDL=100;	  	// DEFAULT MINIMAL DETECTION LIMIT //3.1e-5 for intense emission Eu2     1.1e-6 for rest
Float_t MXDL=2.357e+07;	  	// DEFAULT MAXIMAL DETECTION LIMIT
Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
Int_t miny=0, maxy=595;	// LIMITS OF THE EXCITATION ==> (228,595)



//******************************************************************************


//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,l=0,aux=0,reb=1;  // initial parameters  //
Float_t exc[1000],tim[1000],emis[1000],value[1000][1000]; 		      
Char_t f1[100],scint[100]="NaI",doped[100]="",sample[100]="00000",title[100]="",ci[2048]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Spectrally resolved Thermoluminescence",100,100,600,400);
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
sprintf(title,"THERMOLUMINESCENCE - %s - Sample %s ",scint,sample);

GetCompound(scint,doped,scint);

ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	*in >> ci; *in >> ci;			// removes "Time (s)"
	k=0;
	while (aux==0)		// reads the temperatures
		{
		*in >> ci;
		if ((strstr(ci,"Temperature")!=NULL)) 
			 aux=1;
		else 	{
			k++;
			tim[k]= atof(ci);
			//cout << tim[k] << endl;
			}    
		}
	Int_t xsteps=k;			

	// Nb of steps in exc
	for (l=0;l<xsteps;l++)		// put them in order
		{
		*in >> ci;
		exc[l]= atof(ci);
		if ((l>0)&&(exc[l]<(exc[l-1]))) 
			exc[l]=exc[l-1]+0.001;
		if ((l>0)&&(exc[l]==(exc[l-1]))) 
			exc[l]=exc[l-1]+0.001;
		//cout << exc[l] << endl;
		}
	Float_t minv=MXDL;
	Float_t maxv=0;
	aux=0;  
	l=0;
	while ((aux==0)&&(!in->eof())) 		
		{
		for (k=0;k<xsteps+1;k++)		
			{
			*in >> ci;
			if (k==0) 
				{
				emis[l] = atof(ci);  
				if ((l>0)&&(emis[l]<emis[l-1]))
					{
					aux=1;
					}	
				//cout << "emi: " << emis[l] << endl; 
				}			
			else 
				{	
				value[l][k-1]=atof(ci); //cout <<  value[l][k-1] << endl;
				if (value[l][k-1]<0) value[l][k-1]= -value[l][k-1]; // 0; if the value is neg. put 0/-value
				if (value[l][k-1]<minv) minv=value[l][k-1]; // find min value of the matrix
				if (value[l][k-1]>maxv) maxv=value[l][k-1]; // find max value of the matrix
				}
			}
		l++;
		}		
	Int_t msteps=l-1;		
	cout << "exc. steps: " << xsteps << "     emis. steps: " << msteps << endl;
	cout << "min: "<< minv << " // max:" << maxv << endl;

	exc[xsteps]=exc[xsteps-1]+1;	//we add the last value. 
	emis[msteps]=emis[msteps-1]+1;	//cout << "exc[xsteps]: "<< exc[xsteps] << " // emis[msteps]:" << emis[msteps] << endl;	//931.9		we add the last value. 
	TH2F *H = new TH2F("H","H",msteps,emis,xsteps,exc);  // declaration of the histogram	 
	for (l=0;l<msteps;l++)
		for (k=0;k<xsteps;k++)	
			H->SetBinContent(l,k,value[l][k]);

	MIDL=maxv*0.05;                                   
	MXDL=maxv;

	H->SetMarkerStyle(21);
	H->SetMarkerSize(0.1);
	H->SetTitle(title);
	H->GetXaxis()->SetTitle("Emission (nm)");
	H->GetYaxis()->SetTitle("Temperature (K)");
	H->GetXaxis()->CenterTitle();
	H->GetYaxis()->CenterTitle();
	H->GetXaxis()->SetRangeUser(minx,maxx);
	H->GetYaxis()->SetRangeUser(miny,maxy);
	gStyle->SetPalette(1);
	//H->Draw("COLZ");           	//H->Draw("PCOL"); 
	H->SetContour(100); 
	H->Draw("contz"); 
  	//H->Draw("mercator");
 	//c1->SetLogz(); 
	H->GetZaxis()->SetRangeUser(0,MXDL);  
	H->Smooth(1);
 	PrintLatex2(Form("%s",scint),0.15,0.85,kBlack);



	TCanvas *c2 = new TCanvas("c2","Kitis method",600,10,300,200);  // calculate the 
	c2->SetFillColor(0);
	c2->GetFrame()->SetFillColor(0); 
	c2->GetFrame()->SetBorderMode(-1);
	c2->GetFrame()->SetBorderSize(10);	
					
	TH1 *projY = H->ProjectionX("",250,800,"");
	TH1 *backY;
	backY=projY->ShowBackground(50);
	//projY->Add(backY,-1);
	projY->Draw(); 	
	projY->ShowPeaks(3.5);
	








	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
