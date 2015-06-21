//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

#define N 2000 	// Maximum number of data to represent
using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0


int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Float_t x[N],x2[N],y[N],z[N]; 	
	      
Int_t i,k;  
char ci[100],title[100]="title",f1[100],f2[100];

TCanvas *c = new TCanvas("c","Graph2D",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TPad *pad1 = new TPad("pad1","",0,0,1,1);
TPad *pad2 = new TPad("pad2","",0,0,1,1);
pad2->SetFillStyle(4000); //will be transparent
pad1->Draw(); 
pad1->cd();

switch (argc)
	{
	case 2: sprintf(f1,"%s-T.txt",argv[1]);                // Filename file columns
		sprintf(f2,"%s-R.txt",argv[1]); 
		break;
	case 3: sprintf(f1,"%s.txt",argv[1]);               // Filename file for transmission
		sprintf(f2,"%s.txt",argv[2]); 		    // Filename file for reflection
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   

ifstream *in = new ifstream(f1);  
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  f1 << endl; 
	return 1;
	}
else    {
	
	i=0;
	while (!in->eof())
		{
		*in >> ci;  *in >> ci; *in >> ci; *in >> ci;	  // takes away the first line
		*in >> x[i] >> y[i];
		x[i]=(float)(1240/x[i]);
		i++;
		}
	}
delete in;

#if FILES 
	sprintf(f1,"%s_E.txt",argv[1]);              
	ofstream *out = new ofstream(f1,ios::trunc); 		
	*out << "Energy (eV)" << "\t" << "Transmittance (%)" << endl;	
	for (k=0;k<i;k++)     
		*out << x[k] << "\t" << y[k] <<endl;
	delete out;
#endif


ifstream *in2 = new ifstream(f2);
if(!*in2) 
	{cout << " ERROR OPENING FILE " <<  f2 << endl; 
	return 1;
	}
else   
	{
	i=0;
	while (!in2->eof())
			{
			*in2 >> ci;  *in2 >> ci; *in2 >> ci; *in2 >> ci;	  // takes away the first line
			*in2 >> x2[i] >> z[i];
			x2[i]=(float)(1240/x2[i]);
			i++;
			}
	}

delete in2;

#if FILES 
           
	sprintf(f2,"%s_E.txt",argv[2]); 
	ofstream *out2 = new ofstream(f2,ios::trunc); 	
	*out2 << "Energy (eV)" << "\t" << "Reflectance (%)" << endl; 
	for (k=0;k<i;k++)     
		*out2 << x2[k] << "\t" << z[k] <<endl;
	delete out2;
#endif


ifstream *in3 = new ifstream(f1);  
if(!*in3) 
	{cout << " ERROR OPENING FILE " <<  f1 << endl; 
	return 1;
	}
else    {
	
	i=0;
	while (!in3->eof())
		{
		*in3 >> ci;  *in3 >> ci; *in3 >> ci; *in3 >> ci;	  // takes away the first line
		*in3 >> x[i] >> y[i];
		i++;
		}
	}

ifstream *in4 = new ifstream(f2);
if(!*in4) 
	{cout << " ERROR OPENING FILE " <<  f2 << endl; 
	return 1;
	}
else   
	{
	i=0;
	while (!in4->eof())
			{
			*in4 >> ci;  *in4 >> ci; *in4 >> ci; *in4 >> ci;	  // takes away the first line
			*in4 >> x2[i] >> z[i];
			i++;
			}
	}

	c->cd();
	TGraph *gr0 = new TGraph(i-1,x2,z);		// Graph declaration
	gr0->SetLineColor(4);					
	gr0->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(4);						
	gr0->SetMarkerStyle(20);					
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitle("Energy (eV)");				
	gr0->GetYaxis()->SetTitle("Reflectance (%)");				
	gr0->GetXaxis()->SetTitleSize(0.05);
	gr0->GetYaxis()->SetTitleSize(0.05);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->SetTitleOffset(0.90);
	gr0->GetYaxis()->SetTitleOffset(0.77);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	gr0->GetXaxis()->SetRangeUser(1.1272,6.2);	
	gr0->Draw("Ac");

	TLatex *tx = new TLatex();
	tx->SetNDC();
	tx->SetTextFont(62);
 	tx->SetTextAlign(12);
	tx->SetTextSize(0.04);
	tx->SetTextColor(1);
	sprintf(ci,"Sample 00%c%c",argv[1][5],argv[1][6]);
	tx->DrawLatex(0.25,0.85,ci);
	

	TGraph *gr0b = new TGraph(i-1,x,y);				// Graph declaration
	gr0b->SetLineColor(2);					
	gr0b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0b->SetMarkerColor(2);						
	gr0b->SetMarkerStyle(20);					
	gr0b->SetTitle(title);					

   	Double_t ymin = gr0b->GetHistogram()->GetMinimum();
   	Double_t ymax = gr0b->GetHistogram()->GetMaximum();
   	Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom
   	Double_t xmin = 1.1272;
   	Double_t xmax = 6.2;
   	Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
 	pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
 	pad2->Draw();
  	pad2->cd();
	gr0b->Draw("][samec");
	TGaxis *axis = new TGaxis(xmax,ymin,xmax,ymax,ymin,ymax,505,"+L");
	axis->SetTitle("Transmittance (%)");
	axis->SetTitleSize(0.05);	
	axis->SetTitleColor(2);	
	axis->SetTitleOffset(0.88);
	axis->CenterTitle();	
	axis->SetLabelColor(kRed);
	axis->SetLabelSize(0.05);
	axis->Draw();	
	tx->SetTextColor(2);
	//tx->DrawLatex(0.3,0.93,argv[2]);


theApp->Run(kTRUE);						
delete theApp;
return 0;
}
