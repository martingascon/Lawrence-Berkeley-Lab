//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
#define THD 1.2  // THRESHOLD OF NOISE

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{

//********************************** SETTINGS ***********************************
//Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
//Int_t miny=200, maxy=800;	// LIMITS OF THE EXCITATION ==> (228,910)
//******************************************************************************
Float_t LA=120;  // limites de projection
Float_t LB=460;

//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,l=0,aux=0;  // initial parameters
Float_t exc[150],emis[5000],value[5000][150]; 		      
Char_t f1[100],f2[100], scint[100]="NaI",doped[100]="",sample[100]="00000",title[100]="",ci[2048]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","OSL 1",100,100,700,500);
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
	case 3: sprintf(f1,"%s.txt",argv[1]);		// FILENAME 	
		sprintf(f2,"%s.txt",argv[2]);
		break;	
default:
		MsgError();
		exit(1);
		break;

	};   

cout << "***************************"<< endl;
GetInfo(f1,sample,scint,doped);
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
	Float_t excc[150];
	for (k=0;k<xsteps;k++)		
			{
			excc[k]=1240/exc[xsteps-1-k];
			}
	excc[xsteps]= excc[xsteps-1]+0.0005;	  

	Float_t minv=1;
	Float_t maxv=0;
	while (!in->eof())
		{
		for (k=0;k<xsteps+1;k++)		
			{
			if (aux==1) aux=0;
			else *in >> ci;	
			if (k==0) {emis[l] = atof(ci);} 				// cout << "emi: " << emis[l] << endl;}
			else 
				{	
				value[l][k-1]=atof(ci); 				//cout <<  value[l][k-1] << endl;
				if (emis[l]>exc[k]) value[l][k-1]= 0;
				if (value[l][k-1]<0) value[l][k-1]= -value[l][k-1];	//0; // if the value is neg. put 0
				if (value[l][k-1]<minv) minv=value[l][k-1]; 		// find min value of the matrix
				if (value[l][k-1]>maxv) maxv=value[l][k-1]; 		// find max value of the matrix   
				}
			}

		l++;
		}


	Int_t msteps=l-1;	
	cout << "exc. steps: " << xsteps << "     emis. steps: " << msteps << endl;
	cout << "min: "<< minv << " // max:" << maxv << endl;

	
 	for (l=0;l<msteps;l++)			
	 	for (k=0;k<xsteps;k++)		
	 		{
			if ((exc[k]>(emis[l]-15)) && (exc[k]<(emis[l]+15))) value[l][k]=0;
	 		}

	exc[xsteps]= exc[xsteps-1]+0.4;	  	//we add the last value. 
	emis[msteps]=emis[msteps-1]+0.4; 	//we add the last value. 
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
	gStyle->SetPalette(1);
	H->SetContour(100); 
	H->Draw("contz");
	H->GetZaxis()->SetRangeUser(minv*1.1,maxv);  
	H->Smooth(1);
	PrintLatex2(Form("%s",scint),0.65,0.85,kBlack);

	TH2F *Hc = new TH2F("Hc","Hc",msteps,emis,xsteps,excc);  // declaration of the histogram	 
	for (l=0;l<msteps;l++)
		for (k=0;k<xsteps;k++)	
			Hc->SetBinContent(l,k,value[l][xsteps-1-k]);
	H->Smooth(3);
	H->GetXaxis()->SetRangeUser(380,500);
	PrintLatex2(Form("%s (Ceramic Sample)",sample),0.25,0.95,kBlack);
/*
	TCanvas *c3 = new TCanvas("c3","PROJECTIONS ",1000,600,600,400);         ////////////////////////// Profile Y
	c3->SetFillColor(0);
	c3->GetFrame()->SetFillColor(0); 
	c3->GetFrame()->SetBorderMode(-1);
	c3->GetFrame()->SetBorderSize(10);	
	c3->cd();



					
	TH1 *projY = Hc->ProjectionY(" ",LA,LB,"");
	


	//projY->Draw();

	//Float_t minH=projY->GetMinimum();
	TH1 *backY;
	backY=projY->ShowBackground(100);
	//backY->Draw("same");	
 	TH1 *projY2=(TH1*)projY->Clone();
	projY2->Add(backY,-1);
	projY2->Draw("same");	
*/
/*
 recomendacion de david

TGraph *ScaleAxis(TGraph *g=Double_t factor=1){

 Double_t *X=g->GetX();
 Double_t *Y=g->GetY();
 Int_t N=g->GetN();
 TGraph *gout=new TGraph();
 for(Int_t i=0;i<N,i++)
   gout->SetPoint(i,X[i]*factor,Y[i]);

 return gout;
}


 TGraph *g=ScaleAxis(gin,factor)
*/

//	if (argc==3) /////////////////////////////////////////////////////////////////////////////////////////////////// background spectrum
	//	{

/*
		TCanvas *c2 = new TCanvas("c2","OSL2 ",700,50,600,400);         ////////////////////////// Profile Y
		c2->SetFillColor(0);
		c2->GetFrame()->SetFillColor(0); 
		c2->GetFrame()->SetBorderMode(-1);
		c2->GetFrame()->SetBorderSize(10);	
		c2->cd();

 		cout << "***************************"<< endl;
		GetInfo(f2,sample,scint,doped);
		sprintf(title,"Optical Excitation - %s - Sample %s ",scint,sample);
		GetCompound(scint,doped,scint);
		ifstream *in2 = new ifstream(f2);
		if(!*in2)
			{
			 cout << " ERROR OPENING FILE " <<  f2 << endl; 
			}
		else    {
			Int_t aux2=0;
			Float_t exc2[150],emis2[5000],value2[5000][150]; 		
			*in2 >> ci; *in2 >> ci;			// removes  "Wavelength (nm)"
			k=0,l=0;
			while (aux2==0)		// reads the excitation
				{
				*in2 >> ci;
				exc2[k]= atof(ci);
				if ((k>10)&&(exc2[k]<exc2[k-1])) 	
					{aux2=1;exc2[k]=0;}  //first emission is lower than last exc point;
				else 	k++;    
				}
			Int_t xsteps2=k;	
			Float_t excc2[150];
			for (k=0;k<xsteps2;k++)		
				{
				excc2[k]=1240/exc2[xsteps2-1-k];
				}
			excc2[xsteps2]= excc2[xsteps2-1]+0.0005;	

			Float_t minv2=1;
			Float_t maxv2=0;
			while (!in2->eof())
				{
				for (k=0;k<xsteps2+1;k++)		
					{
					if (aux2==1) aux2=0;
					else *in2 >> ci;	
					if (k==0) 
						{
						emis2[l] = atof(ci);
						//cout << "emi: " << emis2[l] << endl;	
						}
					else 
						{	
						value2[l][k-1]=atof(ci); 				//cout <<  value[l][k-1] << endl;
						if (emis2[l]>exc2[k]) value2[l][k-1]= 0;
						if (value2[l][k-1]<0) value2[l][k-1]= -value2[l][k-1];	//0; // if the value is neg. put 0
						if (value2[l][k-1]<minv2) minv2=value2[l][k-1]; 		// find min value of the matrix
						if (value2[l][k-1]>maxv2) maxv2=value2[l][k-1]; 		// find max value of the matrix
						}
					}
				l++;
				}

			Int_t msteps2=l-1;	
			cout << "exc. steps2: " << xsteps2 << "     emis. steps2: " << msteps2 << endl;
			cout << "min: "<< minv2 << " // max:" << maxv2 << endl;
			for (l=0;l<msteps2;l++)			
				for (k=0;k<xsteps2;k++)		
					{
					if ((exc2[k]>(emis2[l]-15)) && (exc2[k]<(emis2[l]+15))) value2[l][k]=0;   
					}
			exc2[xsteps2]= exc2[xsteps2-1]+0.4;	  	//we add the last value. 
			emis2[msteps2]=emis2[msteps2-1]+0.4; 	//we add the last value. 
			TH2F *H2 = new TH2F("H2","H2",msteps2,emis2,xsteps2,exc2);  // declaration of the histogram	 
			for (l=0;l<msteps2;l++)
				for (k=0;k<xsteps2;k++)	
					{
					H2->SetBinContent(l,k,value2[l][k]);	
					}


			H2->SetMarkerStyle(21);
			H2->SetMarkerSize(0.1);
			H2->SetTitle(title);
			H2->GetXaxis()->SetTitle("Emission (nm)");
			H2->GetYaxis()->SetTitle("Excitation (nm)");
			H2->GetXaxis()->CenterTitle();
			H2->GetYaxis()->CenterTitle();
			gStyle->SetPalette(1);
			H2->SetContour(100); 
			H2->Draw("contz"); 
			//H2->Smooth(1);
			PrintLatex2(Form("%s",scint),0.65,0.85,kBlack);
			TH2F *H2c = new TH2F("H2c","H2c",msteps2,emis2,xsteps2,excc2);  // declaration of the histogram	 
			for (l=0;l<msteps2;l++)
				for (k=0;k<xsteps2;k++)	
						H2c->SetBinContent(l,k,value2[l][xsteps2-1-k]);


				
			TH1 *projY2 = H2c->ProjectionY("p2",LA,LB,"");
			c3->cd();
			projY2->Draw("same");



		//	}
		}




*/













	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
