//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"
 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** SETTINGS ***********************************
Float_t MIDL=10000;	  	// DEFAULT MINIMAL DETECTION LIMIT //3.1e-5 for intense emission Eu2     1.1e-6 for rest
Float_t MXDL=2.357e+07;	  	// DEFAULT MAXIMAL DETECTION LIMIT
Int_t minx=199, maxx=810;	// LIMITS OF THE EMISSION   ==> (200,931)
Int_t miny=0, maxy=300;		// LIMITS OF THE EXCITATION ==> (228,595)
Int_t la=350;			// integration lower limit
Int_t lb=650;			// integration higher limit
Float_t sens=4;			//sensitivity for searching peaks
//******************************************************************************


//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t k,l=0,aux=0; //reb=1,peaks=1;//,xsteps,msteps;	 // initial parameters  //
Float_t exc[1000],tim[100],emis[1000], value[1000][1000],T1=40,T2=160; 		      
Char_t f1[100],scint[100]="NaI",doped[100]="",sample[100]="00000",title[100]="",ci[2048]="";

gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Spectrally resolved Thermoluminescence",100,10,600,400);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		 
		break;						 
	case 3: sprintf(f1,"%s.txt",argv[1]);	 	
		sens=atoi(argv[2]);		 		 
		break;	
	case 4: sprintf(f1,"%s.txt",argv[1]);	 
		la=atof(argv[2]);			  
		lb=atof(argv[3]);
		break;	
	case 5: sprintf(f1,"%s.txt",argv[1]);		 
		la=atoi(argv[2]);			  
		lb=atoi(argv[3]);
		sens=atof(argv[4]);	
		break;	
	case 6: sprintf(f1,"%s.txt",argv[1]);		 
		la=atoi(argv[2]);			  
		lb=atoi(argv[3]);
		T1=atof(argv[4]);			  
		T2=atof(argv[5]);
		break;	
	case 7: sprintf(f1,"%s.txt",argv[1]);		 
		la=atoi(argv[2]);			  
		lb=atoi(argv[3]);
		T1=atof(argv[4]);			  
		T2=atof(argv[5]);
 		sens=atof(argv[6]);
		break;	

default:
		MsgError();
		exit(1);
		break;

	};   

GetInfo(f1,sample,scint,doped);
cout << "***************************"<< endl;
sprintf(title,"THERMOLUMINESCENCE - %s - Sample %s ",scint,sample);

//GetCompound(scint,doped,scint);

//TH2F *H = new TH2F("H","H");  
//Read_TL(f1, exc, emis, xsteps, msteps, H);

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
	H->SetContour(8); //c1->SetLogz(); 
	H->Draw("surf2");  //H->Draw("mercator");//H->Draw("COLZ"); //H->Draw("PCOL");  	
	//H->GetZaxis()->SetRangeUser(MIDL,MXDL);
	//H->Smooth(1);
	//H->Smooth(1);
	//H->Smooth(1);
	PrintLatex2(Form("%s",scint),0.15,0.85,kBlack);




//////////////////////////////////////////////////////////////////////////////////////////////////// calculations of the peaks  

	TCanvas *c2 = new TCanvas("c2","Kitis method",1500,10,600,400);  // calculate the 
	c2->SetFillColor(0);
	c2->GetFrame()->SetFillColor(0); 
	c2->GetFrame()->SetBorderMode(-1);
	c2->GetFrame()->SetBorderSize(10);	
					
	TH1 *projY = H->ProjectionY("",250,800,"");
	TH1 *backY;
	backY=projY->ShowBackground(50);
	projY->Add(backY,-1);
	projY->Draw(); 	//projY->ShowPeaks(3.5);
	Int_t npeaks = 10;
	TH1F *h2 = (TH1F*)projY->Clone("h2");	//h2->Rebin(reb);
	TSpectrum *s = new TSpectrum(2*npeaks);
	
   	Int_t nfound = s->Search(h2,sens,"new");	
 	cout << " Found " << nfound << " candidate peaks to fitn" << endl;
 	c2->Update();
	projY->ShowPeaks(sens);
   
 	//Estimate background using TSpectrum::Background
   	//TH1 *hb = s->Background(projY,100,"same");
   	//if (hb) c2->Update();
 

	Float_t xp[10],yp[10]; 	// find the parameters for kitis function
	Int_t bin[10];
	Float_t *xpeaks = s->GetPositionX();
	cout << " Peaks:  Temp  - bin  - Max Intensity    "  << endl;
	for (Int_t p=0;p<nfound;p++) 
		{
      		xp[p] = xpeaks[p];
      		bin[p] = projY->GetXaxis()->FindBin(xp[p]);
      		yp[p] = projY->GetBinContent(bin[p]);
		cout << " Peak " << p << " - " << xp[p] << " - " << bin[p] << " - " << yp[p] << endl;
 		}
	cout << "****************************************************************************" << endl;
	Float_t Trap[10];
	Int_t p=0;
	/////////////////////////////////////////////////////////////////////// FITING FUNCTION///////////////////////////////////////////
	for (p=0;p<nfound;p++) 
		{ 	
		TF1 *ff  = new TF1("ff",tlfit,xp[p]-100,xp[p]+100,3);  
		ff->SetParameters(0.20,xp[p],yp[p]); 
		ff->FixParameter(1,xp[p]);	
		ff->FixParameter(2,yp[p]);	
		projY->Fit(ff,"NQR+");
		//ff->SetLineColor(2+p);
		Trap[p]= ff->GetParameter(p);
 		cout << " Trap " << p << " - " << Trap[p] << " eV " << endl;
		}
	//nfound=3;		// solo en caso de que encontremos muchos o pocos
	if (nfound==2)
		{
		TF1 *ff = new TF1("ff2",tlfit2,T1,T2,6);   
		ff->SetParameters(0.20,0.26,xp[0],yp[0],xp[1],yp[1]);
		ff->SetParLimits(2,xp[0]*0.50,xp[0]*1.50);// FixParameter(2,xp[0]);	
		ff->SetParLimits(3,yp[0]*0.50,yp[0]*1.50);//FixParameter(3,yp[0]);
 		ff->SetParLimits(4,xp[1]*0.50,xp[1]*1.50);//FixParameter(4,xp[1]);	
		ff->SetParLimits(5,yp[1]*0.50,yp[1]*1.50);//FixParameter(5,yp[1]);
		projY->Fit(ff,"R+");
		for (Int_t p=0;p<nfound;p++) 
			{
			Trap[p]= ff->GetParameter(p);
			PrintLatex2(Form("#DeltaE_{%d} =%0.2f eV",p+1,Trap[p]),0.30,0.85-0.05*p,2);
			}
		}
	if (nfound==3)
		{
		TF1 *ff = new TF1("ff",tlfit3,T1,T2,9);  
		ff->SetParameters(0.26,0.22,0.30,xp[0],yp[0],xp[1],yp[1],xp[2],yp[2]);
		ff->SetParLimits(3,xp[0]*0.96,xp[0]*1.04);// FixParameter(2,xp[0]);	
		ff->SetParLimits(4,yp[0]*0.50,yp[0]*1.50);//FixParameter(3,yp[0]);
 		ff->SetParLimits(5,xp[1]*0.50,xp[1]*1.10);//FixParameter(4,xp[1]);	
		ff->SetParLimits(6,yp[1]*0.50,yp[1]*1.50);//FixParameter(5,yp[1]);
 		ff->SetParLimits(7,xp[2]*0.50,xp[2]*1.50);//FixParameter(4,xp[1]);	
		ff->SetParLimits(8,yp[2]*0.50,yp[2]*1.50);//FixParameter(5,yp[1]);
  		ff->SetNpx(1000);
		projY->Fit(ff,"R+");
 		for (Int_t p=0;p<nfound;p++) 
			{
			Trap[p]= ff->GetParameter(p);
			PrintLatex2(Form("#DeltaE_{%d} =%0.2f eV",p+1,Trap[p]),0.30,0.85-0.05*p,2);
			}
		}
  	if (nfound==4)
		{
		TF1 *ff  = new TF1("ff",tlfit4,T1,T2,12);   
		ff->SetParameters(0.26,0.22,0.53,0.2,xp[0],yp[0],xp[1],yp[1],xp[2],yp[2],xp[3]);//,xp[3],yp[3]);
		ff->SetParLimits(4,xp[0]*0.96,xp[0]*1.04);// FixParameter(2,xp[0]);	
		ff->SetParLimits(5,yp[0]*0.50,yp[0]*1.50);//FixParameter(3,yp[0]);
 		ff->SetParLimits(6,xp[1]*0.50,xp[1]*1.50);//FixParameter(4,xp[1]);	
		ff->SetParLimits(7,yp[1]*0.30,yp[1]*1.80);//FixParameter(5,yp[1]);
 		ff->SetParLimits(8,xp[2]*0.50,xp[2]*1.50);//FixParameter(4,xp[1]);	
		ff->SetParLimits(9,yp[2]*0.50,yp[2]*1.50);//FixParameter(5,yp[1]);
 		ff->SetParLimits(10,xp[3]*0.50,xp[3]*1.50);//FixParameter(4,xp[1]);	
		ff->SetParLimits(11,yp[3]*0.40,yp[3]*1.60);//FixParameter(5,yp[1]);
		ff->SetLineColor(2);
		projY->Fit(ff,"R+");
		for (Int_t p=0;p<nfound;p++) 
			{
			Trap[p]= ff->GetParameter(p);
			PrintLatex2(Form("#DeltaE_{%d} =%0.2f eV",p+1,Trap[p]),0.30,0.85-0.05*p,2);
			}
		}

/*	if (nfound==5)
		{
 		TF1 *ff  = new TF1("ff",tlfit4,70,280,15);    
		ff->SetParameters(Trap[0],Trap[1],Trap[2],Trap[3],Trap[4],xp[0],yp[0],xp[1],yp[1],xp[2],yp[2],xp[3);//);
		ff->SetParLimits(5,xp[0]*0.96,xp[0]*1.04);// FixParameter(2,xp[0]);	
		ff->SetParLimits(6,yp[0]*0.30,yp[0]*1.70);//FixParameter(3,yp[0]);
 		ff->SetParLimits(7,xp[1]*0.96,xp[1]*1.04);//FixParameter(4,xp[1]);	
		ff->SetParLimits(8,yp[1]*0.90,yp[1]*1.10);//FixParameter(5,yp[1]);
 		ff->SetParLimits(9,xp[2]*0.96,xp[2]*1.04);//FixParameter(4,xp[1]);	
		ff->SetParLimits(10,yp[2]*0.70,yp[2]*1.30);//FixParameter(5,yp[1]);
 		ff->SetParLimits(11,xp[3]*0.90,xp[3]*1.10);//FixParameter(4,xp[1]);	
		ff->SetParLimits(12,yp[3]*0.50,yp[3]*1.50);//FixParameter(5,yp[1]);
 		ff->SetParLimits(13,xp[4]*0.90,xp[4]*1.10);//FixParameter(4,xp[1]);	
		ff->SetParLimits(14,yp[4]*0.50,yp[4]*1.50);//FixParameter(5,yp[1]);
		ff->SetLineColor(2);
		projY->Fit(ff,"R+");
		for (Int_t p=0;p<nfound;p++) 
			{
			Trap[p]= ff->GetParameter(p);
			PrintLatex2(Form("#DeltaE_{%d} =%0.2f eV",p+1,Trap[p]),0.30,0.85-0.05*p,2);
			}
		}
*/
	PrintLatex2(Form("%s",scint),0.15,0.85,kBlack);
	
 
/*
	TCanvas *c3 = new TCanvas("c3","IR method",1530,510,600,400);
	c3->SetFillColor(0);
	c3->GetFrame()->SetFillColor(0); 
	c3->GetFrame()->SetBorderMode(-1);
	c3->GetFrame()->SetBorderSize(10);						

	TVirtualPad *vp =  c3->cd(1);
	vp->SetFillColor(10);
	//vp->SetLogy();
	vp->SetBorderSize(2);
	vp->SetFrameFillColor(0);
	vp->SetLeftMargin(.12);
	vp->SetRightMargin(.01);
	vp->SetBottomMargin(.15);
	vp->SetTopMargin(.01);
	Float_t Im=projY->GetMaximum();
	Float_t Tm=projY->GetMaximumBin();
	Tm = exc[(int)Tm];
	Float_t minH=projY->GetMinimum();
	cout << "min H: "<< minH << "  max H: "<< minH << endl;
	cout << "Im: "<< Im << "   Tm: "<< Tm << endl;

	Float_t Ys[xsteps],LogYs[xsteps],invXs[xsteps];
  	Int_t len=0;
	for (k=1;k<xsteps;k++)		
			{
			Ys[k-1]=(projY->GetBinContent(k));
			if (Ys[k-1]==0) 
				{
				len=k-1;				
				k=xsteps;
				}
			//Ys[k-1]=Ys[k-1]-minHis;
			if (Ys[k-1]<1) Ys[k-1]=1;
			LogYs[k-1]=TMath::Log(Ys[k-1]);
			invXs[k-1]=11604.519/exc[k];   // constant 1/kB = 11604.519 K/eV			
			//cout << "xx: "<< k  << " " << Ys[k] << endl;
			}



	TGraph *gr0 = new TGraph(len,invXs,LogYs);		// Graph declaration
	gr0->SetLineColor(2);					
	gr0->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(2);						
	gr0->SetMarkerStyle(20);					
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitle("1/kT (eV)^{-1}");				
	gr0->GetYaxis()->SetTitle("ln(TL)");				
	gr0->GetXaxis()->SetTitleSize(0.06);
	gr0->GetYaxis()->SetTitleSize(0.06);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	gr0->Draw("AL");

	Float_t max=GetMax(LogYs,len);
	Float_t min=GetMin(LogYs,len);

	Float_t max2=max-(max-min)*0.05;
	Float_t min2=min+(max-min)*0.70 ;

	cout << "max: "<< max  << "  min =" << min << endl;	
	cout << "max2: "<< max2  << "  min2 =" << min2 << endl;
	Float_t X0=0,X1=0,Trape=0;
  	for (k=0;k<len-1;k++)		 
			{
			if (LogYs[k]>min2) 
				{
				X0=invXs[k];				
				k=len;						
				}
			}
 	for (k=0;k<len-1;k++)	 
			{
			if (LogYs[k]>max2) 
				{
				X1=invXs[k];				
				k=len;						
				}
			
			}
	cout << "X0: "<< X0  << "  X1 =" << X1 << endl;
	//TF1 *g1    = new TF1("g1","pol1",X0,X1);
	TF1 *g1    = new TF1("g1","pol1",63,68);  //////////////////////////////////////////// FITING FUNCTION ///////////////////////////////////////////
	gr0->Fit(g1,"R");	
	Trape= g1->GetParameter(1);
  	PrintLatex2(Form("#DeltaE = %0.2f eV",Trape),0.7,0.90,2);
 
*/

	 

	
	
theApp->Run(kTRUE);

	cout << "Do you want to save your data into levels.txt (y/n)?" << endl;  
	Char_t res;	
	cin >> res;
	if (res=='s'||res=='y')
	  	{
		ofstream *out = new ofstream(Form("%s_lev.txt",argv[1]),ios::app);
		for (Int_t p=0;p<nfound;p++) 
			*out << std::fixed << std::setprecision(3) << Trap[p] << endl;
		} 



delete theApp;
return 0;
	


	}

}
