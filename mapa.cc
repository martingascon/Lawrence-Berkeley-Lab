//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define GRAPH 1
#define COMPS 1

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  
set_plot_style();


Int_t i,k,N=5000,aux=0,rows=1,cols=1,points=0;
Float_t x[N],y[10][N],xc[N],yc[N];
//tc=0, p0[900],p1[900],q0[900],q1[900]; 	
//char ci[100]="",f1[100],ci2[100],ci3[100]="";


#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
