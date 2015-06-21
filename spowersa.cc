//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include <math.h> 

#define GRAPH 1
#define SECONDARIES 0
#define PROFILES 0


using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t i,k,l,m;  
Int_t N=500000;
Float_t x[N],y[N],x2[N],y2[N]; //[n] refers to a vector 		      
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100];
char latex3[100],title[100]=""; //,latex4[100],latex5[100],latex6[100],latex7[100];
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
c1-> SetLogy();
c1-> SetLogx();
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


Float_t xa,ya,ya2,ya3,ya4;

ifstream *in = new ifstream(file1);
if(!*in)cout << " ERROR OPENING FILE " <<  file1 << endl; 
else    {
	l=0;	
	m=0;	
	for (i=0;i<N;i++)
		{
				
		*in >>  xa >> ya >> ya2 >> ya3 >> ya4;  // last one is the flag of primary/secondary
		xa=xa*1000;
		#if SECONDARIES	 
		if (ya4==0)		
			{
			x[l]=xa;                 
			y[l]=ya3;
			l++;
			}
		else
			{
			x2[m]=xa;                 
			y2[m]=ya3;
			m++;
			}
		#else 		
			x[l]=xa;                 
			y[l]=ya3;
			l++;
			if (ya4!=0) m++;		
		#endif 		
		}


	}
delete in;

cout <<	"number of primaries: " << l-m << "  (" << (l-m)/float(l)*100.0 << "%)" << endl;
cout <<	"number of secondaries: " << m << "  (" << m/float(l)*100.0 << "%)" << endl;

//////////////////////////////////  calculation of minimum and maximum for x and y

Float_t Mx,My,mx,my;

Mx=GetMax(x,l);
mx=GetMin(x,l);
My=GetMax(y,l);
my=GetMin(y,l);

if (mx<0.0001) mx=0.001;  // mx and my can't be 0 because I want log-scale
if (my<0.01) my=0.01;

////////////////////////////////////////////  putting the log-scale in the 2D histogram.
Int_t nbins=N/1000;
Double_t xbins[nbins+1];
Double_t ybins[nbins+1];
SetLogTH2F(mx,Mx,my,My,nbins,xbins,ybins);

//////////////////////////////////////////////////////////////


TH2F *H = new TH2F("H",file1,nbins,xbins,nbins,ybins);  // declaration of the histogram	 
for (k=0;k<l;k++)			
	H->Fill(x[k],y[k]);		// fill the histogram
H->SetMarkerColor(7);
H->SetFillColor(0);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Energy (keV)");
H->GetYaxis()->SetTitle("dEdx (MeV.cm^{2}/g)");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();
H->GetXaxis()->SetRangeUser(0.002,1400);
H->GetYaxis()->SetRangeUser(0.1,400);
H->Draw("colZ");
c1-> SetLogz();
PrintLatex2("Geant 4",0.7,0.85,kBlue);
PrintLatex2("NaI",0.03,0.95,kBlack);

#if SECONDARIES	 
PrintLatex2("Primaries",0.4,0.95,kRed);
TCanvas *c2 = new TCanvas("c2","Stopping power",530,10,500,350);
c2->SetFillColor(0);
c2->GetFrame()->SetFillColor(0); 
c2->GetFrame()->SetBorderMode(-1);
c2->GetFrame()->SetBorderSize(10);						
c2-> SetLogy();
c2-> SetLogx();

TH2F *Hs = new TH2F("Hs",file1,nbins,xbins,nbins,ybins);  // declaration of the histogram for secondaries 
for (k=0;k<m;k++)			
	Hs->Fill(x2[k],y2[k]);		// fill the histogram
Hs->SetMarkerColor(7);
Hs->SetFillColor(0);
Hs->SetLineColor(2);
Hs->SetLineWidth(2);
Hs->SetMarkerStyle(8);
Hs->SetMarkerSize(1);
Hs->SetTitle(title);
Hs->GetXaxis()->SetTitle("Energy (keV)");
Hs->GetYaxis()->SetTitle("dEdx (MeV.cm^{2}/g)");
Hs->GetXaxis()->CenterTitle();
Hs->GetYaxis()->CenterTitle();
Hs->GetXaxis()->SetRangeUser(0.002,1400);
Hs->GetYaxis()->SetRangeUser(0.1,400);
Hs->Draw("colZ");

PrintLatex2("Geant 4",0.7,0.85,kBlue);
PrintLatex2("NaI",0.03,0.95,kBlack);
PrintLatex2("Secondaries",0.4,0.95,kRed);
c1->cd();
#endif 	

//////////////////  Calculation of the average for each profile in Y (cut in Energy)
Int_t 	binx=0;
Float_t mean[nbins],Emean[nbins];

#if PROFILES 
	TCanvas *c3 = new TCanvas("c3","Profile in Y",40,40,1200,700);
	c3->SetLogy();
	c3->SetLogx();
	c3->Divide(3,3);
#endif



for (i=1;i<nbins;i++)
	{
	binx=i;
	Emean[i] = (xbins[i]+xbins[i-1])/2;		
	TH1D* py = H->ProjectionY(Form("py_%d",i),binx,binx+1);
	py->SetMarkerColor(kRed);
	py->SetLineColor(kRed);
	py->SetMarkerStyle(8);
	mean[i] = py->GetMean();
	//cout << Emean[i] <<endl;	
	#if PROFILES 
		if ((Emean[i]>0.0105)&&(Emean[i]<0.0106)){c3->cd(1); gPad->SetLogx();py->Draw();PrintLatex2("10 eV",0.8,0.8,2);}
		if ((Emean[i]>0.0254)&&(Emean[i]<0.0257)){c3->cd(2); gPad->SetLogx();py->Draw();PrintLatex2("20 eV",0.8,0.8,2);} 
		if ((Emean[i]>0.0509)&&(Emean[i]<0.0515)){c3->cd(3); gPad->SetLogx();py->Draw();PrintLatex2("50 keV",0.8,0.8,2);}
		if ((Emean[i]>0.1000)&&(Emean[i]<0.1020)){c3->cd(4); gPad->SetLogx();py->Draw();PrintLatex2("100 eV",0.8,0.8,2);}
		if ((Emean[i]>0.2000)&&(Emean[i]<0.2040)){c3->cd(5); gPad->SetLogx();py->Draw();PrintLatex2("200 eV",0.8,0.8,2);} 
		if ((Emean[i]>0.5000)&&(Emean[i]<0.5100)){c3->cd(6); gPad->SetLogx();py->Draw();PrintLatex2("500 eV",0.8,0.8,2);}
		if ((Emean[i]>0.9900)&&(Emean[i]<1.0100)){c3->cd(7); gPad->SetLogx();py->Draw();PrintLatex2("1 keV",0.8,0.8,2);}
		if ((Emean[i]>10.100)&&(Emean[i]<10.200)){c3->cd(8); gPad->SetLogx();py->Draw();PrintLatex2("10 keV",0.8,0.8,2);} 
		if ((Emean[i]>100.00)&&(Emean[i]<102.00)){c3->cd(9); gPad->SetLogx();py->Draw();PrintLatex2("100 keV",0.78,0.8,2);}
	#endif

	}
c1->cd();
TH2F *H2 = new TH2F("H2",file1,nbins,xbins,nbins,ybins); 
for (k=1;k<nbins;k++)			
 	H2->Fill(Emean[k],mean[k]);
H2->SetMarkerColor(kGreen);
H2->SetFillColor(kGreen);
H2->SetLineColor(kGreen);
H2->SetLineWidth(0.6);
H2->SetMarkerStyle(8);
H2->SetMarkerSize(0.5);
H2->Draw("same");

PrintLatex2("Average",0.7,0.8,kGreen);


////////////////////////////////////////////////////////////////////////////////////////////

if (argc>2)         /// NIST/G4 comparison

	{
	Float_t xa[N],ya[N],ya2[N],ya3[N],ya4[N];
	ifstream *in = new ifstream(file2);
	if(!*in)cout << " ERROR OPENING FILE " <<  file2 << endl; 
	else    {

		i=0;	
		for (i=0;i<N;i++)
			{
			*in >>  xa[i] >> ya[i] >> ya2[i] >> ya3[i] >> ya4[i]; 
			}

		}
	delete in;
	c1->cd();
	TH2F *H3 = new TH2F("H3",file2,nbins,xbins,nbins,ybins); 
	for (k=0;k<N;k++)			
		{
	 	xa[k]=xa[k]*1000;		// to convert them in keV
		H3->Fill(xa[k],ya3[k]);
		}
	H3->SetMarkerColor(2);
	H3->SetFillColor(2);
	H3->SetLineColor(2);
	H3->SetLineWidth(1);
	H3->SetMarkerStyle(8);
	H3->SetMarkerSize(1);
	H3->Draw("same");

	TLatex *tx3 = new TLatex();
	tx3->SetNDC();
	tx3->SetTextSize(0.05);
	tx3->SetTextColor(kRed);
	sprintf(latex3,"%s",argv[2]);
	sprintf(latex3,"%s","Bethe-Bloch");
	tx3->DrawLatex(0.7,0.75,latex3);
	}

c1->SaveAs("dEdx_out.png");

//theApp->Run(kTRUE);
delete theApp;
return 0;
}
