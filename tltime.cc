//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
Int_t i=0,N=20000,n1=0,n2=0;  // initial parameters
Float_t minx, maxx,miny,maxy,ymax,ymin,ave1=0; 		      
Char_t ci[100], f1[100],f2[100],f3[100],f4[100],scint[100]="NaI",doped[100],sample[100]="00000",title[100]="",*sepa;
//Char_t fitf[100]="[0]+x*[1]";
//Char_t fitf3[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]";
//Char_t fitf3b[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]";
//Char_t fitf4[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]*exp(-x/[7])";

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
gStyle->SetOptTitle(0);  
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Thermoluminescence",0,10,750,400);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						
 
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TPad *pad2 = new TPad("pad2","",0,0,1,1);
pad2->SetFillStyle(4000); 		//will be transparent
pad2->SetFillColor(0);
pad2->SetFrameFillStyle(4000);
pad1->Draw(); 
pad1->cd();
 
  
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		// FILENAME 	
		break;						 
	case 3: sprintf(f1,"%s.txt",argv[1]);		// FILENAME 	
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME 
		break;						 
	case 5: sprintf(f1,"%s.txt",argv[1]);		// FILENAME 	
		sprintf(f2,"%s.txt",argv[2]);		// FILENAME 
		sprintf(f3,"%s.txt",argv[3]);		// FILENAME 	
		sprintf(f4,"%s.txt",argv[4]);		// FILENAME 
		break;						 


default:
		MsgError();
		exit(1);
		break;

	};   

sepa=strtok(argv[1],"-");  
sprintf(sample,"%s",sepa);
cout << "sample# = "<< sample << endl;
sepa=strtok(NULL,"-"); 
sprintf(scint,"%s",sepa);
cout << "scint = "<< scint << endl;
sepa=strtok(NULL,"-"); 
sprintf(doped,"%s",sepa);
cout << "doped = "<< doped << endl;
cout << "***************************"<< endl;

ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	Float_t x[N],y[N],y2[N],y3[N],y4,y5,y6,y7,aux;
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
	while (!in->eof())
			{
			*in >>  x[i] >> y[i] >> y2[i] >> y3[i] >> y4 >> y5 >> y6 >> y7;		
			//= (aux); aux
			//if (i>7195) cout <<x[i]<<" "<<y[i]<<" "<<y2[i]<<" "<<y3[i]<<" "<<y4<<" "<<y5<<" "<<y6<<" "<<y7<<endl;
			//if (i<2) ave1=ave1+aux;
			i++;
			}


	n1=i-1; cout << "n1: " << n1 << endl;
	delete in;
 	minx=GetMin(x,n1);	cout << " min in Time (s): " << minx << endl;
	maxx=GetMax(x,n1);	cout << " max in Time (s): "<< maxx << endl;
	miny=GetMin(y3,n1);	cout << " min in counts: " << miny << endl;
	maxy=GetMax(y3,n1);	cout << " max in counts: "<< maxy << endl;
	ymin = GetMin(y2,n1);  cout << " min in T: "<< ymin << endl;
   	ymax = GetMax(y2,n1);  cout << " max in T: "<< ymax << endl;
 
 
	TH1F *hframe1 = pad1->DrawFrame(minx,miny,maxx,maxy);
	TGraph *gr1 = new TGraph(n1,x,y3);		// Graph declaration
	gr1->SetLineColor(2);					
	gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr1->GetXaxis()->SetTitle("Time (s)");				
	gr1->GetYaxis()->SetTitle("Intensity (cts)");				
	gr1->GetXaxis()->CenterTitle();		
	gr1->GetXaxis()->SetRangeUser(minx,maxx);			
	gr1->GetYaxis()->CenterTitle();	
	gr1->Draw("AL");
	PrintLatex2(Form("%s:%s (%s)",scint,doped,sample),0.6,0.95,kBlack);
 

	TGraph *gr2 = new TGraph(n1,x,y);		
	gr2->SetLineColor(4);					
	gr2->SetLineWidth(2);						
 
	TGraph *gr3 = new TGraph(n1,x,y2);		
	gr3->SetLineColor(4);					
	gr3->SetLineWidth(2);		
	gr3->SetLineStyle(9);	
			
	PrintLatex2(Form("%s","- Counts"),0.12,0.85,kRed);
	PrintLatex2(Form("%s","- Temperature"),0.12,0.80,4);
	PrintLatex2(Form("%s","-- Set Point"),0.12,0.75,4);

   	Double_t dy = (ymax-ymin)/0.5; 		//10 per cent margins top and bottom
	Double_t dx = (maxx-minx)/0.8;
	pad2->Draw();
  	pad2->cd();
	pad2->Range(minx-0.1*dx,ymin-0.1*dy,maxx+0.1*dx,ymax+0.1*dy);
 	
	gr2->Draw("sameL");
	gr3->Draw("sameL");

	TGaxis *axis = new TGaxis(maxx,ymin,maxx,ymax,ymin,ymax,515,"+L");
	axis->SetTitle("Temperature (K)");
	axis->SetTitleSize(0.05);	
	axis->SetTitleColor(4);	
	axis->SetTitleOffset(0.88);
	axis->CenterTitle();	
	axis->SetLabelColor(kBlue);
	axis->SetLabelSize(0.05);
	axis->Draw();	
	pad1->cd();

	}


theApp->Run(kTRUE);
delete theApp;
return 0;
}
