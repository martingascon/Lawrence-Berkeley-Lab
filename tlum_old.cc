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
Int_t i=0,k,N=13000,nsteps=0;  // initial parameters
Float_t minx, maxx; 		      
Char_t ci[100], f1[100],f2[100],scint[100]="NaI",sample[100]="00000",title[100]="",*sepa;
Char_t fitf[100]="[0]*exp(-x/[1])+[2]";
Char_t fitf3[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]";
Char_t fitf3b[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]";
//Char_t fitf4[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]*exp(-x/[7])";

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Optical Excitation",200,100,1200,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);

TLegend *legend=new TLegend(0.80,0.80,0.95,0.95);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

TLegend *legend2=new TLegend(0.50,0.60,0.98,0.95);  
legend2->SetTextFont(62);
legend2->SetTextSize(0.04);
legend2->SetFillColor(0);

TLegend *legend3=new TLegend(0.30,0.30,0.58,0.55);  
legend3->SetTextFont(62);
legend3->SetTextSize(0.04);
legend3->SetFillColor(0);




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



default:
		MsgError();
		exit(1);
		break;

	};   

sepa=strtok(argv[1],"_");  
sprintf(scint,"%s",sepa);
cout << "scint = "<< scint << endl;
sepa=strtok(NULL,"_"); 
sprintf(sample,"%s",sepa);
cout << "sample# = "<< sample << endl;
cout << "***************************"<< endl;
sprintf(title,"Pulsed X-Rays Decay Time");




ifstream *in = new ifstream(f1);
if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else    {
	Float_t x,y[N],y2,y3[N],y4,y5,y6,y7;
	while (!in->eof())
			{
			*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
			*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci;*in >> ci; // removes the header
			
			*in >>  x >> y[i] >> y2 >> y3[i] >> y4 >> y5 >> y6 >> y7; cout << ci <<endl;
			//y[i]=y[i]; 
			i++;
			}


	}
/*	nsteps=i-1;cout << nsteps << endl;
	delete in;
 	minx=GetMin(x,nsteps);	cout << minx << endl;
	maxx=GetMax(x,nsteps);	cout << maxx << endl;

	TGraph *gr1 = new TGraph(nsteps,x,y2);		// Graph declaration
	gr1->SetLineColor(2);					
	gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr1->SetMarkerColor(2);						
	gr1->SetMarkerStyle(20);					
	gr1->SetTitle(title);					
	gr1->GetXaxis()->SetTitle("Time (ns)");				
	gr1->GetYaxis()->SetTitle("Intensity (a.u.)");				
	gr1->GetXaxis()->SetTitleSize(0.06);
	gr1->GetYaxis()->SetTitleSize(0.06);
	gr1->GetXaxis()->SetLabelSize(0.05);
	gr1->GetYaxis()->SetLabelSize(0.05);
	gr1->GetXaxis()->CenterTitle();					
	gr1->GetYaxis()->CenterTitle();	
	gr1->Draw("AL");

	TF1 *f1 = new TF1("f1",fitf3,2,4600);
	f1->SetParameter(0,4); // I1 	
	f1->SetParameter(1,1000);  // DT1				
	f1->SetParameter(2,6);			
	f1->SetParameter(3,361);
	f1->SetParameter(4,6);
	f1->SetParameter(5,35);
	f1->SetParameter(6,10);


	//f1->SetParameter(7,35);
	gr1->Fit("f1","R+");
	gr1->Fit("f1","R");



	legend->AddEntry(gr1,Form("%s",scint),"l");
	Float_t tau[3],tauerr[3],amp[3],tot=f1->GetParameter(0)+f1->GetParameter(2)+f1->GetParameter(4);
	for (k=0;k<3;k++)			
		{
		amp[k]=f1->GetParameter(k*2)/tot*100;
		tau[k]=f1->GetParameter(k*2+1);
		tauerr[k]=f1->GetParError(k*2+1);
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%2.0f #pm %2.0f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"l");
		}

	TF1 *e1 = new TF1("e1",fitf,2,4600);   
	e1->SetParameters(amp[0],tau[0],f1->GetParameter(6));	
	//e1->SetLineColor(kGreen+3);
 	e1->SetLineStyle(9);
	e1->Draw("same");
	TF1 *e2 = new TF1("e2",fitf,2,4600); 
	e2->SetParameters(amp[1],tau[1],f1->GetParameter(6));
	e2->SetLineStyle(9);
  	e2->Draw("same");
	TF1 *e3 = new TF1("e3",fitf,2,4600); 
	e3->SetParameters(amp[2],tau[2],f1->GetParameter(6));
	e3->SetLineStyle(9);
  	e3->Draw("same");
	}



legend2->Draw();

if (argc==3)
	{
	ifstream *in2 = new ifstream(f2);
	if(!*in2){
		cout << " ERROR OPENING FILE " <<  f2 << endl; 
		}
	else    {
		Float_t x[N],y[N],y2,y3,y4;
		while ((!in2->eof())&&(i<2000))
				{
				*in2 >>  x[i] >> y[i] >> y2 >> y3 >> y4; 
				i++;
				}
		
		delete in2;
		TGraph *gr2 = new TGraph(nsteps,x,y);		// Graph declaration
		gr2->SetLineColor(4);					
		gr2->SetLineWidth(1);						// Line color 0=white 1=black, 2=red
		gr2->SetMarkerColor(4);						
		gr2->SetMarkerStyle(26);					
		gr2->Draw("sameL");
	
		TF1 *f2 = new TF1("f2",fitf3b,2,4600);
		f2->SetParameter(0,4); // I1 	
		f2->SetParameter(1,1100);  // DT1				
		f2->SetParameter(2,6);			
		f2->SetParameter(3,391);
		f2->SetParameter(4,6);
		f2->SetParameter(5,30);
		f2->SetParameter(6,10);
		gr2->Fit("f2","R+");
		gr2->Fit("f2","R");

		legend->AddEntry(gr2,Form("%s",scint),"l");
		Float_t tau2[3],tauerr2[3],amp2[3],tot2=f2->GetParameter(0)+f2->GetParameter(2)+f2->GetParameter(4);
		for (k=0;k<3;k++)			
			{
			amp2[k]=f2->GetParameter(k*2)/tot2*100;
			tau2[k]=f2->GetParameter(k*2+1);
			tauerr2[k]=f2->GetParError(k*2+1);
			legend3->AddEntry(gr2,Form("#tau_{%d} = (%2.0f #pm %2.0f) ns   (I = %2.1f %)",k+1,tau2[k],tauerr2[k],amp2[k]),"l");
			}
		}

	legend3->Draw();
	}






legend->Draw();


*/
theApp->Run(kTRUE);
delete theApp;
return 0;
}
