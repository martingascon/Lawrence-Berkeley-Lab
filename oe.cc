//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
#define THD 1  // THRESHOLD OF NOISE

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{

//********************************** SETTINGS ***********************************
Float_t MIDL=1.1e-5;	  	// DEFAULT MINIMAL DETECTION LIMIT //3.1e-5 for intense emission Eu2     1.1e-6 for rest
Float_t MXDL=8.1e-1;	  	// DEFAULT MAXIMAL DETECTION LIMIT
Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
Int_t miny=200, maxy=450;	// LIMITS OF THE EXCITATION ==> (228,595)
//******************************************************************************


//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,i,l=0,aux=0;  // initial parameters
Float_t exc[150],emis[5000],value[5000][150], valueext[5000][5000],excext[5000]; 		      
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
		if ((k>10)&&(exc[k]<exc[k-1])) 	
			{aux=1;exc[k]=0;}  //first emission is lower than last exc point;
		else 	k++;    
		}

	Int_t xsteps=k;			// Nb of steps in exc
	Int_t msteps=1815;		// Nb of steps in emission
	Float_t mxm=1;
	Float_t minv=1;
	Float_t maxv=0;
	cout << "exc. steps: " << xsteps << "     emis. steps: " << msteps << endl;
	for (l=0;l<msteps;l++)			
		for (k=0;k<xsteps+1;k++)		
			{
			if (aux==1) aux=0;
			else *in >> ci;	
			if (k==0) {emis[l] = atof(ci); } //cout << "emi: " << emis[l] << endl;} 
			else 
				{	
				value[l][k-1]=atof(ci); //cout <<  value[l][k-1] << endl;
				if (value[l][k-1]<0) value[l][k-1]= -value[l][k-1];//0; // if the value is neg. put 0
				if (value[l][k-1]<minv) minv=value[l][k-1]; // find min value of the matrix
				if (value[l][k-1]>maxv) {maxv=value[l][k-1]; mxm=emis[l];} // find max value of the matrix
				}
			}

	
	cout << "min: "<< minv << " // max:" << maxv << endl;
	//MIDL=minv;
	//MXDL=maxv;
	cout << "max m: "<< mxm  << endl;


	for (l=0;l<msteps;l++)			
		for (k=0;k<xsteps;k++)		
			{
			if (value[l][k]<MIDL*THD) value[l][k]= MIDL*THD; // define minimum threshold of 1000 MIDL
			if ((exc[k]>(emis[l]-20)) && (exc[k]<(emis[l]+20))) value[l][k]=MIDL*THD;   
			//if ((exc[k]>295) && (exc[k-1]<315) && (emis[l]>608) && (emis[l]<622)) value[l][k]=MIDL*1.1; //subtract issue
			//if ((exc[k]>emis[k]>608) && (emis[l]<622)) value[l][k]=MIDL*1.1;		
			}
	exc[xsteps]=595.1;	//595.1;	we add the last value. 
	emis[msteps]=931.9;	//931.9		we add the last value. 
	TH2F *H = new TH2F("H","H",msteps,emis,xsteps,exc);  // declaration of the histogram	 
	for (l=0;l<msteps;l++)
		for (k=0;k<xsteps;k++)	
			H->SetBinContent(l,k,value[l][k]);

	H->SetMarkerStyle(21);
	H->SetMarkerSize(0.1);
	H->SetTitle(title);
	H->GetXaxis()->SetTitle("Emission (nm)");
	H->GetYaxis()->SetTitle("Excitation (nm)");
	H->GetXaxis()->CenterTitle();
	H->GetYaxis()->CenterTitle();
	H->GetXaxis()->SetRangeUser(minx,maxx);
	H->GetYaxis()->SetRangeUser(miny,maxy);
	gStyle->SetPalette(1);
	//	H->Draw("COLZ");           	//H->Draw("PCOL"); 
	H->SetContour(100); 
	H->Draw("contz"); 
  	//H->Draw("mercator");
 	//c1->SetLogz(); 
	H->GetZaxis()->SetRangeUser(MIDL/2,MXDL*2);
	//H->GetZaxis()->SetRangeUser(0,MXDL/2);  // for the paper CBI
	//H->Smooth(1);
	//H->Smooth(1);
	H->Smooth(1);

  	//gPad->Update();
 
	//H->Smooth(1);
	//TPaletteAxis *palette = (TPaletteAxis*)H->GetListOfFunctions()->FindObject("palette");
   	//palette->SetLabelSize(0.03);	
	//palette->SetLabelOffset(0);	
	//PrintLatex2(Form("%s (%s)",scint,sample),0.15,0.85,kBlack);
	PrintLatex2(Form("%s",scint),0.15,0.85,kBlack);

	


	TCanvas *c2 = new TCanvas("c2","Profile",1530,10,600,400);
	c2->SetFillColor(0);
	c2->GetFrame()->SetFillColor(0); 
	c2->GetFrame()->SetBorderMode(-1);
	c2->GetFrame()->SetBorderSize(10);						
	TH1 *projY = H->ProjectionY("",410,430,"");
	Float_t minH=projY->GetMinimum();
	TH1 *backY;
	backY=projY->ShowBackground(100);
	//projY->Add(backY,-1);
	projY->Draw();
















	//new ..............                                                                
/*	TCanvas *c2 = new TCanvas("c2","Optical Excitation ext",1500,100,1200,800);
	Int_t xstepsext = xsteps*20; // extended range in excitation is 1600 (80x20)   
	for (k=0;k<xsteps;k++) 			// fill the vector in excitation. Emission is the same
			for (i=0;i<20;i++)
				{
				excext[k*20+i]= exc[k]+(exc[k+1]-exc[k])/20.0*i;  //cout << k*20+i << " " << excext[k*20+i] << endl;
				}
	excext[xstepsext]=595.1; // we add the last value.    

	
	for (l=0;l<msteps;l++)		*/	// up to here works fine!	// fill the extended matrixmstepsxsteps
		/*for (k=0;k<xsteps;k++)
			{
			for (i=0;i<20;i++)
				{
				valueext[l][k*20+i]= value[l][k]+(value[l][k+1]-value[l][k])/20.0*i; 
				if ((l==0) && (k==0)) {cout << valueext[l][k*20+i] << endl;}	//valueext[l][k*20+i]
				}
			
			}
	TH2F *H2 = new TH2F("H2","H2",msteps,emis,xstepsext,excext);	*/	
	//cout <<  value[0][0] << " " << valueext[0][0] << endl;
	/*for (l=0;l<10;l++)
		for (k=0;k<10;k++)	
			H2->SetBinContent(l,k,valueext[l][k]);*/

/*	H2->SetMarkerStyle(21);
	H2->SetMarkerSize(0.1);
	H2->SetTitle(title);
	H2->GetXaxis()->SetTitle("Emission (nm)");
	H2->GetYaxis()->SetTitle("Excitation (nm)");
	H2->GetXaxis()->CenterTitle();
	H2->GetYaxis()->CenterTitle();
	H2->GetXaxis()->SetRangeUser(minx,maxx);
	H2->GetYaxis()->SetRangeUser(miny,maxy);
	H2->Draw("COLZ");           	//H->Draw("PCOL");//H->Draw("contz");	
	c2->SetLogz(); 
	H2->GetZaxis()->SetRangeUser(MIDL/2,MXDL);
*/
	
	


	/*TH2F *H2 = new TH2F("H2","H2",msteps,emis,xstepsext,excext);  // declaration of the histogram	
	for (l=0;l<50;l++)	//msteps		
		for (k=0;k<50;k++) //xstepsext
			H2->SetBinContent(l,k,valueext[l][k]);

 H2->Draw("COLZ");	  */

/*	TH2F *Hf = new TH2F("Hf","Hf",msteps*100,emis,xsteps*100,exc);  // declaration of the histogram
	for (Int_t ll=0;ll<msteps*100;ll++)
		for (Int_t kk=0;kk<xsteps*100;kk++)	
			Hf->SetBinContent(ll,kk,H->Interpolate(emis[ll/100],exc[kk/100]));*/

/**/

	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
