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
Int_t i=0,k,N=20000,n1=0,n2=0;  // initial parameters
Float_t minx, maxx,miny,maxy; 		      
Char_t ci[100], f1[100],f2[100],f3[100],f4[100],scint[100]="NaI",doped[100],sample[100]="00000",title[100]="",*sepa;
Char_t fitf[100]="[0]+x*[1]+x*x*[2]";
//Char_t fitf4[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]*exp(-x/[7])";

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Thermoluminescence",0,10,750,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						
 
c1->cd();

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
sprintf(title,"Thermoluminescence");


ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	Float_t x[N],y[N],y2,y3[N],y4,y5,y6,y7,auxx,aux,aux2,y3b[N],y3c[N],xmin,xmax;
	Int_t j=0;
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
	while (!in->eof())
			{
			*in >> auxx  >> aux >> y2 >> aux2 >> y4 >> y5 >> y6 >> y7;		// cout << ci <<endl;
			if (i>7200) {j=i-7200; x[j]=j; y[j]=aux; y3[j]= aux2;}
			//if (i<2) cout <<x<<" "<<y[i]<<" "<<y2<<" "<<y3[i]<<" "<<y4<<" "<<y5<<" "<<y6<<" "<<y7<<endl;
			i++;
			}
	n1=j-1; cout << "n1: " << n1 << endl;
	delete in;
 	minx=GetMin(y,n1);	cout << " min in T: " << minx << endl;
	maxx=GetMax(y,n1);	cout << " max in T: "<< maxx << endl;
	miny=GetMin(y3,n1);	cout << " min in counts: " << miny << endl;
	maxy=GetMax(y3,n1);	cout << " max in counts: "<< maxy << endl;
	xmin = GetMin(x,n1);  	cout << " min in time: "<< xmin << endl;
   	xmax = GetMax(x,n1);  	cout << " max in time: "<< xmax << endl;

	c1->cd(1);
	TGraph *gr1 = new TGraph(j-1,y,y3);		// Graph declaration
	gr1->SetLineColor(2);					
	gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr1->SetMarkerColor(2);						
	gr1->SetMarkerStyle(20);					
	gr1->SetTitle(title);					
	gr1->GetXaxis()->SetTitle("Temperature (K)");				
	gr1->GetYaxis()->SetTitle("Intensity (cts/deg/Coulomb)");				
	gr1->GetXaxis()->CenterTitle();					
	gr1->GetYaxis()->CenterTitle();	
	gr1->Draw("AL");
	PrintLatex2(Form("%s:%s ",scint,doped),0.7,0.95,kBlack);
	PrintLatex2(Form("%s",argv[1]),0.2,0.85,kRed);
	
	


	}


if (argc>2)
{
	ifstream *in2 = new ifstream(f2);
	if(!*in2){
		cout << " ERROR OPENING FILE " <<  f2 << endl; 
		}


	else
	 	{
		Float_t x[N],y[N],y2,y3[N],y4,y5,y6,y7;
		*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci; // removes the header
		*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci;*in2 >> ci; // removes the header
		i=0;
		while (!in2->eof())
			{
			*in2 >>  x[i] >> y[i] >> y2 >> y3[i] >> y4 >> y5 >> y6 >> y7;		
			i++;
			}
	n2=i-1; cout << "n2: " << n2 << endl;
	delete in2;
 	minx=GetMin(x,n2);	cout << " min in x: " << minx << endl;
	maxx=GetMax(x,n2);	cout << " max in x: "<< maxx << endl;
	TGraph *gr2 = new TGraph(n2,y,y3);		// Graph declaration
	gr2->SetLineColor(4);					
	gr2->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr2->SetMarkerColor(4);						
	gr2->SetMarkerStyle(20);					
	gr2->Draw("sameL");
	PrintLatex2(argv[2],0.60,0.60,kBlue);


 	}


}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
