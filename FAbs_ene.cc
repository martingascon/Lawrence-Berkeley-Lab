//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define DATABASE 0
#define N 2000 	// Maximum number of data to represent

using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

TCanvas *c = new TCanvas("Absorption Coefficient","Absorption Coefficient",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TLegend *legend=new TLegend(0.5,0.15,0.88,0.25);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

// DECLARATION OF VARIABLES
Float_t wv[N],wv2[N],T[N],R[N],A[N];   	// T: Transmittance, R: Reflectance, A: absortion coeff.	
Float_t D1=1,D2=1,D3=1,D4=1; 			 	// Default thickness 1 micron 
Int_t nt=0,nr=0;  			// nt,nr: number of data points in Transm/Reflection fs
char f[100],f2[100],f3[100],f4[100],f5[100],f6[100],f7[100],f8[100];

switch (argc)
	{
	case 3: sprintf(f,"%s-T.txt",argv[1]);                // Filename f for transmission
		sprintf(f2,"%s-R.txt",argv[1]); 		// Filename f for reflection
		D1=atof(argv[2]);                                // Thickness of the measurement in um
		break;
	case 5: sprintf(f,"%s-T.txt",argv[1]);                // Filename f for transmission
		sprintf(f2,"%s-R.txt",argv[1]); 		// Filename f for reflection
		D1=atof(argv[2]);                                // Thickness of the measurement in um
		sprintf(f3,"%s-T.txt",argv[3]);                // Filename f for transmission
		sprintf(f4,"%s-R.txt",argv[3]); 		// Filename f for reflection
		D2=atof(argv[4]);  
		break;
	case 7: sprintf(f,"%s-T.txt",argv[1]);                // Filename f for transmission
		sprintf(f2,"%s-R.txt",argv[1]); 		// Filename f for reflection
		D1=atof(argv[2]);                              // Thickness of the measurement in um
		sprintf(f3,"%s-T.txt",argv[3]);                // Filename f for transmission
		sprintf(f4,"%s-R.txt",argv[3]); 		// Filename f for reflection
		D2=atof(argv[4]);  
		sprintf(f5,"%s-T.txt",argv[5]);                // Filename f for transmission
		sprintf(f6,"%s-R.txt",argv[5]); 	       // Filename f for reflection
		D3=atof(argv[6]);  
		break;


	case 9: sprintf(f,"%s-T.txt",argv[1]);                // Filename f for transmission
		sprintf(f2,"%s-R.txt",argv[1]); 		// Filename f for reflection
		D1=atof(argv[2]);                              // Thickness of the measurement in um
		sprintf(f3,"%s-T.txt",argv[3]);                // Filename f for transmission
		sprintf(f4,"%s-R.txt",argv[3]); 		// Filename f for reflection
		D2=atof(argv[4]);  
		sprintf(f5,"%s-T.txt",argv[5]);                // Filename f for transmission
		sprintf(f6,"%s-R.txt",argv[5]); 	       // Filename f for reflection
		D3=atof(argv[6]);  
		sprintf(f7,"%s-T.txt",argv[7]);                // Filename f for transmission
		sprintf(f8,"%s-R.txt",argv[7]); 	       // Filename f for reflection
		D4=atof(argv[8]);  
		break;

	default:
		MsgError();
		exit(1);
		break;
	};   


D1=D1/1000; D2=D2/1000; D3=D3/1000; D4=D4/1000;		// to convert from nm to um

Char_t ti[10];
GetTime(f,ti);          // Get the time the f was modified



#if DATABASE
TH2F *abs =new TH2F(ti,"Abs coef",10000,1.1,6,10000,0,100);
abs->SetXTitle("Wavelenght (nm)");
abs->SetYTitle("Absorption coeff. (cm^{-1}) .10^{4}");	
#endif



Read_FTRe(f,wv,T,nt);
Read_FTRe(f2,wv2,R,nr);
Calc_Abs(wv,T,R,A,nr,D1);
TGraph *gr1 = new TGraph(nr,wv,A);		// Graph declaration
Plot_Abs(gr1,1,4);
legend->AddEntry(gr1,Form("S-00%c%c    d ~ %2.1f nm",argv[1][5],argv[1][6],D1*1000),"l");

if (argc>4)      
	{
	Read_FTRe(f3,wv,T,nt);
	Read_FTRe(f4,wv2,R,nr);
	Calc_Abs(wv,T,R,A,nr,D2);
	TGraph *gr2 = new TGraph(nr,wv,A);		// Graph declaration
	Plot_Abs(gr2,0,2);
	legend->AddEntry(gr2,Form("S-00%c%c    d ~ %2.1f nm",argv[3][5],argv[3][6],D2*1000),"l");
	}

if (argc>6)      
	{
	Read_FTRe(f5,wv,T,nt);
	Read_FTRe(f6,wv2,R,nr);
	Calc_Abs(wv,T,R,A,nr,D3);
	TGraph *gr3 = new TGraph(nr,wv,A);		// Graph declaration
	Plot_Abs(gr3,0,80);
	legend->AddEntry(gr3,Form("S-00%c%c    d ~ %2.1f nm",argv[5][5],argv[5][6],D3*1000),"l");
	}

if (argc>8)      
	{
	Read_FTRe(f7,wv,T,nt);
	Read_FTRe(f8,wv2,R,nr);
	Calc_Abs(wv,T,R,A,nr,D4);
	TGraph *gr4 = new TGraph(nr,wv,A);		// Graph declaration
	Plot_Abs(gr4,0,1);
	legend->AddEntry(gr4,Form("S-00%c%c    d ~ %2.1f nm",argv[7][5],argv[7][6],D4*1000),"l");
	}


#if DATABASE

//abs->Fill(wv[i],A[i]); put in a for....
TFile *rootfile=new TFile("DATABASE.root","UPDATE");
TTree *tree = new TTree("tree","AbsCoef");
tree->Branch("AC","TGraph",&gr0,N,0);
tree->Branch("TH2F","TH2F",&abs,10000,0);	
//tree->Branch(file,"TGraph",&gr0,i-1,0);
c->Write();
abs->Write();
gr0->Write(); 
tree->Fill();
tree->Write();
rootfile->Close();
delete rootfile;
#endif

PrintLatex2(Form("%c%c%c on %c%c%c",argv[1][0],argv[1][1],argv[1][2],argv[1][8],argv[1][9],argv[1][10]),0.05,0.95,1);

legend->Draw();
theApp->Run(kTRUE);						
delete theApp;
return 0;
}
