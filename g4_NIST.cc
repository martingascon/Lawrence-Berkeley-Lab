//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 

#define GRAPH 1
#define NIST 1

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t N=500000,npoints=0;
Float_t x[N],y[N]; //[n] refers to a vector 		      
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100],Scint[100];

set_plot_style();

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

#if GRAPH
TCanvas *c1 = new TCanvas("c1","Stopping power",0,10,500,350);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						
c1->SetLogy();
c1->SetLogx();

TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);
//legend->SetMargin(0);

#endif 

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(file1,"%s.dat",argv[1]);		// FILENAME 	
		break;						 
	case 3: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		break;
	case 4: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		sprintf(file3,"%s.dat",argv[3]);
		break;
	case 5: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		sprintf(file3,"%s.dat",argv[3]);
		sprintf(file4,"%s.dat",argv[4]);
		break;
	case 6: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		sprintf(file3,"%s.dat",argv[3]);
		sprintf(file4,"%s.dat",argv[4]);
		sprintf(file5,"%s.dat",argv[5]);
		break;
	case 7: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		sprintf(file3,"%s.dat",argv[3]);
		sprintf(file4,"%s.dat",argv[4]);	
		sprintf(file5,"%s.dat",argv[5]);
		sprintf(file6,"%s.dat",argv[6]);
		break;
	case 8: sprintf(file1,"%s.dat",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.dat",argv[2]);
		sprintf(file3,"%s.dat",argv[3]);
		sprintf(file4,"%s.dat",argv[4]);	
		sprintf(file5,"%s.dat",argv[5]);
		sprintf(file6,"%s.dat",argv[6]);
		sprintf(file7,"%s.dat",argv[7]);
		break;
default:
		MsgError();
		exit(1);
		break;

	};   


//////////////////////////////////  calculation of minimum and maximum for x and y
Float_t Mx=961.3,My=241.7,mx=0.001,my=0.01; // take the same numbers for all the scint. 
////////////////////////////////////////////  putting the log-scale in the 2D histogram.
Int_t nbins=N/1000;
Double_t xbins[nbins+1];
Double_t ybins[nbins+1];
LogAxis(mx,Mx,my,My,nbins,xbins,ybins);
//////////////////////////////////////////////////////////////  

/// Bethe Bloch Read-Plot data From Geant4
Int_t Col=4; //blue
sprintf(Scint,"%s",argv[1]);
Read_SPG4(file1,x,y,N);
TH2F *H1 = new TH2F("H1",file1,nbins,xbins,nbins,ybins);  // declaration of the histogram	 
Plot_SPG4(H1,x,y,N,1,Col);				  // 4th param 1 = first plot, 0 = second, third, etc. 
legend->AddEntry(H1,Form("%s:%s-Geant4",Scint,"Tl"),"p");

#if NIST         /// NIST/G4 comparison
Float_t xb[500],yb[500];
TH2F *H1n = new TH2F("H1n","H1n",nbins,xbins,nbins,ybins); 
Read_SPNI(argv[1],xb,yb,npoints);
Plot_SPNI(H1n,xb,yb,npoints,0,Col);
legend->AddEntry(H1n,Form("%s:%s-NIST",Scint,"Tl"),"p");
#endif


if (argc>2)      
	{
	/// Bethe Bloch Read-Plot data From Geant4
	Float_t x2[N],y2[N]; 
	Int_t Col=2;  //Red
	sprintf(Scint,"%s",argv[2]);
	Read_SPG4(file2,x2,y2,N);
	TH2F *H2 = new TH2F("H2",file2,nbins,xbins,nbins,ybins);  // declaration of the histogram	 
	Plot_SPG4(H2,x2,y2,N,0,Col);
	legend->AddEntry(H2,Form("%s:%s-Geant4",Scint,"Eu"),"p");

	#if NIST         /// NIST/G4 comparison
	Float_t x2b[500],y2b[500];
	TH2F *H2n = new TH2F("H2n","H2n",nbins,xbins,nbins,ybins); 
	Read_SPNI(argv[2],x2b,y2b,npoints);
	Plot_SPNI(H2n,x2b,y2b,npoints,0,Col);
	legend->AddEntry(H2n,Form("%s:%s-NIST",Scint,"Eu"),"p");
	#endif
	}

if (argc>3)  
	{
	/// Bethe Bloch Read-Plot data From Geant4
	Float_t x3[N],y3[N]; 
	Int_t Col=80;  //Green
	sprintf(Scint,"%s",argv[3]);
	Read_SPG4(file3,x3,y3,N);
	TH2F *H3 = new TH2F("H3",file3,nbins,xbins,nbins,ybins);  // declaration of the histogram	 
	Plot_SPG4(H3,x3,y3,N,0,Col);
	legend->AddEntry(H3,Form("%s:%s-Geant4",Scint,"Ce"),"p");

	#if NIST         /// NIST/G4 comparison
	Float_t x3b[500],y3b[500];
	TH2F *H3n = new TH2F("H3n","H3n",nbins,xbins,nbins,ybins); 
	Read_SPNI(argv[3],x3b,y3b,npoints);
	Plot_SPNI(H3n,x3b,y3b,npoints,0,Col);
	legend->AddEntry(H3n,Form("%s:%s-NIST",Scint,"Ce"),"p");
	#endif
	}

	
if (argc>4)  
	{

	}


legend->Draw();

theApp->Run(kTRUE);
delete theApp;
return 0;
}
