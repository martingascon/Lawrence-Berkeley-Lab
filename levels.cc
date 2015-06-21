//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1
#define FIT 0

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

// DECLARATION OF VARIABLES
Char_t f1[100], f2[100], ci[100]="", ci2[100]="";
Int_t i, sample[10]; 
Float_t dBG=0,BG=0, E[10], dE[10];

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c->cd(1);
vp->SetFillColor(10);
//vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);





switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		break;		

	case 2: sprintf(f1,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		sprintf(f2,"%s.txt",argv[2]);	
		break;		


	default:
		MsgError();
		exit(1);
		break;
	};   




ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {


	

	*in >> ci; 
	if (strstr(ci,"BandGap")!=NULL) 
		{
		*in >> ci >> ci2;  
		BG = atof(ci);	
		dBG = atof(ci2);	
		cout << "bandgap: " <<  BG << "+-" << dBG << endl;
		}
	i=0;
	while (!in->eof())
		{
		*in >> sample[i] >> E[i] >> dE[i];  
		cout << "s: " <<  sample[i] << " -- " << E[i] << endl;
		i++;
		}
	sample[i]=0;
	 
   	c->Range(-10,-2,10,12);
	TGaxis *axis1 = new TGaxis(-8,0,-8,10,0,10,50510,"");
	axis1->SetName("axis1");
	axis1->SetTitle("Energy (eV)");
   	axis1->Draw();
	
	// Draw first element ///////////////////////////////////
	// put the Valence Band 
	TLine *l1 = new TLine(-6,0,-3,0);         // line for the VB 1st element.
	l1->SetLineWidth(2);	
    	l1 ->Draw();
	PrintLatex(Form("BaCl_{2} (%d)",sample[0]),-6,-0.7,1);  // name 1st element.

	// put the conduction band
	TLine *l2=new TLine(-6,BG,-3,BG);         // line for the VB 1st element.
	l2->SetLineWidth(2);	
    	l2->Draw();
	PrintLatex(Form("CB"),-7,BG ,1);  // name 1st element.

	// put the first trap 
	TLine *l3=new TLine(-5,BG-E[0],-2,BG-E[0]);         // line for the VB 1st element.
	l3->SetLineWidth(2);	
    	l3->Draw();
	PrintLatex_small(Form("#DeltaE_{%d} = %0.2f #pm %0.2f",1,E[0],dE[0]),-1.7,BG-E[0],1);  // name 1st element.

	i=0;
	while (sample[i]==sample[i+1])
		{
		i++;
		TLine *l3=new TLine(-5,BG-E[i],-2,BG-E[i]);         // line for the VB 1st element.
		l3->SetLineWidth(2);	
    		l3->Draw("same");
		PrintLatex_small(Form("#DeltaE_{%d} = %0.2f #pm %0.2f",i+1, E[i],dE[i]),-1.7,BG-E[i],1);  // name 1st element.
		}

	// Draw the second element ////////////////////////////////////////////////////////////////////
 	// put the Valence Band 
	TLine *l4=new TLine(3,0,6,0);         // line for the VB 1st element.
	l4->SetLineWidth(2);	
    	l4->Draw();
	PrintLatex(Form("BaCl_{2} (%d)",sample[i+1]),3,-0.7,1);  // name 1st element.

	// put the conduction band
	TLine *l5=new TLine(3,BG,6,BG);         // line for the VB 1st element.
	l5->SetLineWidth(2);	
    	l5->Draw();
	PrintLatex(Form("CB"),2,BG ,1);  // name 1st element.

	// put the first trap 
	TLine *l6=new TLine(4,BG-E[i+1],7,BG-E[i+1]);         // line for the VB 1st element.
	l6->SetLineWidth(2);	
    	l6->Draw();
	PrintLatex_small(Form("#DeltaE_{%d} = %0.2f #pm %0.2f",1,E[0],dE[0]),-1.7,BG-E[0],1);  // name 1st element.
	
	while (sample[i+1]==sample[i+2])
		{
		i++;
		TLine *l6=new TLine(4,BG-E[i+1],7,BG-E[i+1]);         // line for the VB 1st element.
		l6->SetLineWidth(2);	
    		l6->Draw("same");
		PrintLatex_small(Form("#DeltaE_{%d} = %0.2f #pm %0.2f",i+1, E[i+1],dE[i+1]),7.3,BG-E[i+1],1);  // name 1st element.
		}

	}


#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
