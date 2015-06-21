//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.


int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES		//15348-Ba1Br1I1-4Eu2-OptEx-12_18_2012-Emission300nm this format of files
Int_t N=50000,i;  
Float_t x[N],y[N]; 	
Char_t f1[100],f2[100],f3[100],f4[100],f5[100],f6[100], f7[100],f8[100], scint[100]="NaI",sample[100]="00000",dopant[100],emis[100]="220 nm";
char *info[100],compound[100]="";


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

TLegend *legend=new TLegend(0.75,0.85,0.98,0.98);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);	 
		break;
	case 3: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A   excitation 1
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME-B   emission 1
		break;
	case 5: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A   excitation 1
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME-B   emission 1
		sprintf(f3,"%s.txt",argv[3]);		// FILENAME-A   excitation 2
		sprintf(f4,"%s.txt",argv[4]);		// FILENAME-B   emission 2
		break;	
	case 7: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A   excitation 1
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME-B   emission 1
		sprintf(f3,"%s.txt",argv[3]);		// FILENAME-A   excitation 2
		sprintf(f4,"%s.txt",argv[4]);		// FILENAME-B   emission 2
		sprintf(f5,"%s.txt",argv[5]);		// FILENAME-A   excitation 3
		sprintf(f6,"%s.txt",argv[6]);		// FILENAME-B   emission 3
		break;	

	case 9: sprintf(f1,"%s.txt",argv[1]);		// FILENAME-A   excitation 1
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME-B   emission 1
		sprintf(f3,"%s.txt",argv[3]);		// FILENAME-A   excitation 2
		sprintf(f4,"%s.txt",argv[4]);		// FILENAME-B   emission 2
		sprintf(f5,"%s.txt",argv[5]);		// FILENAME-A   excitation 3
		sprintf(f6,"%s.txt",argv[6]);		// FILENAME-B   emission 3
		sprintf(f7,"%s.txt",argv[7]);		// FILENAME-A   excitation 4
		sprintf(f8,"%s.txt",argv[8]);		// FILENAME-B   emission 4		
		break;	

	default:
 		MsgError();
		exit(1);
		break;
	};   
 




 
//GetInfo(argv[1], sample, scint, dopant);
if (argc>1)
	{
	GetInfo(argv[1], sample, scint, dopant);
	Read_FTRw(f1,x,y,N);
	for (i=0;i<275;i++)   if (x[i]<300) {x[i]=300;y[i]=0;}
	TGraph *gr1 = new TGraph(N-1,x,y);		
	Plot_Tw(gr1, 1, kGreen+3);
	gr1->GetYaxis()->SetTitleOffset(1.2);
	gr1->GetXaxis()->SetTitle("Wavelenght (nm)");				
	gr1->GetYaxis()->SetTitle("Intensity (a.u.)");	
	gr1->GetYaxis()->SetLabelSize(0.04);	
	gr1->SetLineWidth(3);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.70,0.95,kGreen+3);
	//legend->AddEntry(gr1,Form("%s","emission = 255 nm"),"l");
	//gr1->GetXaxis()->SetRangeUser(220,1090);
	}

Float_t Max=GetMax(y,N), Max2=0; cout << Max << endl; // calculate the max of emission 1 to normalize for the rest

if (argc>2)
	{
	GetInfo(argv[2], sample, scint, dopant);
	Read_FTRw(f2,x,y,N);
	for (i=0;i<100;i++)   if (x[i]>397) {x[i]=1000; y[i]=0;}  
	TGraph *gr2 = new TGraph(N-1,x,y);
	Plot_Tw(gr2, 0,kGreen+3);
	gr2->SetLineStyle(9);
	//legend->AddEntry(gr2,Form("%s","excitation = 540 nm"),"l");
	//gr2->GetXaxis()->SetRangeUser(275,990);
	}



if (argc>3)
	{
	GetInfo(argv[3], sample, scint, dopant);
	Read_FTRw(f3,x,y,N);
	Max2=GetMax(y,N); cout << Max2 << endl;
	for (i=0;i<N;i++) y[i]=y[i]/Max2*Max;
	for (i=0;i<275;i++)   if (x[i]<300) {x[i]=300;y[i]=0;}
	TGraph *gr3 = new TGraph(N-1,x,y);
	Plot_Tw(gr3, 0, 2);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s",compound),0.70,0.85,kRed);
	//legend->AddEntry(gr3,Form("%s",compound),"l");
	//legend->AddEntry(gr3,Form("%s",scint),"l");
	}

if (argc>4)
	{
	GetInfo(argv[4], sample, scint, dopant);
	Read_FTRw(f4,x,y,N);	
	//Float_t Max2=GetMax(y,N); cout << Max2 << endl;
	for (i=0;i<N;i++) y[i]=y[i]/Max2*Max;

	for (i=0;i<100;i++)   if (x[i]>424) {x[i]=424;y[i]=0;}
	TGraph *gr4 = new TGraph(N-1,x,y);		
	Plot_Tw(gr4, 0, 2);
	gr4->SetLineStyle(9);gr4->SetLineWidth(3);
	//legend->AddEntry(gr4,Form("%s",scint),"l");
	}




if (argc>5)
	{
	GetInfo(argv[5], sample, scint, dopant);
	Read_FTRw(f5,x,y,N);


	for (i=0;i<100;i++)   if (x[i]>275) {x[i]=1150;y[i]=0;}
 	for (i=0;i<N;i++)   y[i]=y[i]*3*186;  

	TGraph *gr5 = new TGraph(N-1,x,y);
	Plot_Tw(gr5, 0, 4);
	gr5->SetLineStyle(9);gr5->SetLineWidth(3);
	//legend->AddEntry(gr4,Form("%s",scint),"l");
	}

if (argc>6)
	{
	GetInfo(argv[6], sample, scint, dopant);
	Read_FTRw(f6,x,y,N);
	
	for (i=0;i<260;i++)   if (x[i]<260) {x[i]=260;y[i]=0;}
	for (i=0;i<N;i++)   y[i]=y[i]*3*186;  


	TGraph *gr6 = new TGraph(N-1,x,y);	
	Plot_Tw(gr6, 0, 4);
	//legend->AddEntry(gr4,Form("%s",scint),"l");
	}


if (argc>7)
	{
	GetInfo(argv[7], sample, scint, dopant);
	Read_FTRw(f7,x,y,N);
	for (i=0;i<418;i++)   if (x[i]>418) {x[i]=1150;y[i]=0;}
 	for (i=0;i<N;i++)   y[i]=y[i]*0.6*186;  
	TGraph *gr7 = new TGraph(N-1,x,y);
	Plot_Tw(gr7, 0, 1);
	gr7->SetLineStyle(9);gr7->SetLineWidth(3);
	//legend->AddEntry(gr4,Form("%s",scint),"l");
	}

if (argc>8)
	{
	GetInfo(argv[8], sample, scint, dopant);
	Read_FTRw(f8,x,y,N);
	
	for (i=0;i<400;i++)   if (x[i]<340) {x[i]=340;y[i]=0;}
	for (i=0;i<N;i++)   y[i]=y[i]*0.6*186;  


	TGraph *gr8 = new TGraph(N-1,x,y);	
	Plot_Tw(gr8, 0, 1);
	//legend->AddEntry(gr4,Form("%s",scint),"l");
	}


//legend->Draw();

theApp->Run(kTRUE);						
delete theApp;
return 0;
}
