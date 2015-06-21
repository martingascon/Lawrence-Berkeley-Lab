//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 		// ****** Own functions
#include "HTCF.h"
 
#define GRAPH 1

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);   

Int_t k,reb=1,N=4196,N2=4196,pr=0;   
Float_t data[N],data2[N],data3[N],x[N],x2[N],y[N],y2[N],conv=0,conv2=0,ls=0,at=0;  		      
Char_t f[100],f2[100],f3[100],f4[100],f5[100],f6[100],title[150]="",*sepa,scint[10],sample[10],exc[4],emis[4]; 	             			 
//Char_t fitf[100]="[0]+[1]*exp(-x/[2])";
//Char_t fitf[100]="[0]*exp(-x/[1])";
Char_t fitf[100]="[0]+[1]*exp(-x/[2])";
Char_t fitf2[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";
Char_t fitf2b[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";
Char_t fitf2c[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";

//Char_t fitf3[100]="[0]+[1]*exp(-(x-[3])/[2])+[4]*exp(-(x-[6])/[5])+[7]*exp(-(x-[9])/[8])";
Char_t fitf3[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])";



#if GRAPH
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->SetLogy();						
#endif 

TLegend *legend=new TLegend(0.40,0.70,0.88,0.85);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

TLegend *legend2=new TLegend(0.20,0.20,0.48,0.45);  
legend2->SetTextFont(62);
legend2->SetTextSize(0.04);
legend2->SetFillColor(0);

TLegend *legend3=new TLegend(0.20,0.20,0.48,0.45);  
legend3->SetTextFont(62);
legend3->SetTextSize(0.04);
legend3->SetFillColor(0);

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);                     			// display stats
gStyle->SetOptFit(0);    					// display fit parameters 1 = on, 0 = off

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f,"%s.txt",argv[1]);		 	
		pr=0;
		break;						 
	case 3: sprintf(f,"%s.txt",argv[1]);			 
		sprintf(f2,"%s.txt",argv[2]);
		pr=1;					 
		break;

	case 4: sprintf(f,"%s.txt",argv[1]);			 
		sprintf(f2,"%s.txt",argv[2]);
		pr=atoi(argv[4]);
		break;

	case 5: sprintf(f,"%s.txt",argv[1]);
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		pr=atoi(argv[4]);			
		break;
	case 7: sprintf(f,"%s.txt",argv[1]);
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		sprintf(f4,"%s.txt",argv[4]);
		sprintf(f5,"%s.txt",argv[5]);
		sprintf(f6,"%s.txt",argv[6]);
		pr=1;
		break;
	default:
		MsgError();
		exit(1);
		break;

	};   


if (pr>1) {reb=pr;pr=0;}


sepa=strtok(argv[1],"_");  
sprintf(scint,"%s",sepa);
cout << "scint = "<< scint << endl;
sepa=strtok(NULL,"_"); 
sprintf(sample,"%s",sepa);
cout << "sample# = "<< sample << endl;
sepa = strtok(NULL,"x_");
sprintf(exc,"%s",sepa);
cout << "Excitation = "<< exc << " nm"<< endl;
sepa = strtok(NULL,"m_");
sprintf(emis,"%s",sepa);
cout << "Emission = "<< emis << " nm"<< endl;
cout << "***************************"<< endl;
 
Read_tFluor(f,data,N,conv,at);




#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 
return 0;


//legend->Draw();
//legend2->Draw();


}
