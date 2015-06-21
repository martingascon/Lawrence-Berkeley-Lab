//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.


/////////////////////////////////////////////////////////////// EDITABLE VALUES
#define GRAPH 1		// GRAPH YES=1  NO=0
#define COMPS 1	   	// NUMBER OF EXPONENTIALS
#define CHA 45	   	// LOWEST LIMIT OF INTEGRATION IN NS
#define CHB 400   	// HIGHEST LIMIT OF INTEGRATION IN NS
#define DIM 512 	// NUMBER OF CHANNELS: 512 or 4096 
////////////////////////////////////////////////////////////////////////////// 
int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp2 = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
//gStyle->SetOptStat(0);
gStyle->SetOptFit(1);  
set_plot_style();

// DECLARATION OF VARIABLES
Int_t i,k, N=DIM,aux=0,rows=1,cols=1,points=0,prompt=0;
Float_t x[N],y[440][N],xc[N],yc[N], tc=0, p0[900],p1[900],q0[900],q1[900]; 	
char ci[100]="",f1[100],ci2[100],ci3[100]="",ci4[100]="";

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		break;		
	
	default:
		MsgError();
		exit(1);
		break;
	};   
///************************************************************************** FILE WITH POSITIONS
ifstream *in2 = new ifstream("Positions.txt");
if(!*in2) 
	{cout << " POSITIONS FILE MISSING - RUN MAP_DTI first on DATAXY! " <<  endl; 
	return 1;
	}
else    {
	i=0;
	*in2 >> rows >> cols; // leo filas y columnas 
	points=rows*cols;
	cout << "ROWS = "<< rows << " COLS = "<< cols << " POINTS = "<< points <<endl;
	while (i<points)
		{
		*in2 >> ci >> ci2; 
		//cout << "x= "<< ci << " y= "<< ci2 <<endl;
		xc[i] = atof(ci);
		yc[i] = atof(ci2);
		i++;
		}
	}

///************************************************************************** FILE WITH POSITIONS



///************************************************************************** FILE WITH TRACES...
ifstream *in = new ifstream(f1);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  f1 << endl; 
	return 1;
	}
else    {
	TCanvas *c1 = new TCanvas("c1","Optical Decay traces",1600,100,800,800);	// all the pulses
	c1->SetFillColor(0);	
	c1->GetFrame()->SetFillColor(0); 
	c1->GetFrame()->SetBorderMode(-1);
	c1->GetFrame()->SetBorderSize(10);		
	c1->Divide(cols,rows);	
	//c1->Divide(5,1);


	do				// encuentro el valor de calibracion en ns/ch				
		{
		*in >> ci;  
		if (strstr(ci,"calibration:")!=NULL)   
			{aux=1; *in >> ci; tc=atof(ci); cout << "Calibration: " <<  tc << " ns/ch" << endl; } 
		} 
	while (aux==0);  
	for (k=0;k<N;k++) x[k]=k*tc;  			// convierto a ns/ch
 	i=0;

	
	while (i<points)
		{
		aux=0, prompt=0;
		do						
	 		{
	 		*in >> ci;  
			if ((strstr(ci,"Prompt")!=NULL))
				prompt=1; 
			if ((strstr(ci,"Decay")!=NULL))   
				aux=1;
	 		} 
		while (aux==0); 
 
		if (prompt) *in >> ci >> ci >> ci3; 
		else *in >> ci >> ci3; 
		 

		for (k=0;k<N;k++)
			{
			if (prompt) *in >> ci >> ci >> ci3; 				
			else *in >> ci >> ci3; 
			y[i][k]=atoi(ci3);//-atoi(ci2); 
 			//cout << "y= "<< y[i][k] << endl;
			}
		TGraph *gr0 = new TGraph(DIM,x,y[i]);
		gr0->SetLineColor(4);					
		gr0->SetLineWidth(2);			// Line color 0=white 	1=black, 2=red
		gr0->SetMarkerColor(4);						
		gr0->SetMarkerStyle(20);					
		gr0->GetXaxis()->CenterTitle();					
		gr0->GetYaxis()->CenterTitle();	
		gr0->GetXaxis()->SetTitle("time (ns)");
		gr0->GetYaxis()->SetTitle("Intensity (a.u.)");
		gr0->GetXaxis()->SetRangeUser(CHA/1.1,CHB*1.1);	
		gPad->SetLogy();

		if (i==0)
			{
			TCanvas *c1b = new TCanvas("c1b","Single pulse",800,800,500,500);	// 1 pulse
			c1b->SetFillColor(0);	
			c1b->GetFrame()->SetFillColor(0); 
			c1b->GetFrame()->SetBorderMode(-1);
			c1b->GetFrame()->SetBorderSize(10);		
			gr0->Draw("Al");
			c1b->cd(1);
			gr0->Draw("Al");
			}

		c1->cd(i+1);
		gr0->Draw("Al");
		#if COMPS==1
			TF1 *g1   = new TF1("g1","expo",CHA,CHB);		//1 exp
		#else
			TF1 *g1   = new TF1("g1","expo(0)+expo(2)",CHA,CHB);	//2 exp
		#endif 
		g1->SetParameter(0,3.6);
		g1->SetParameter(1,-0.002);
		
		g1->SetLineColor(2);
		gr0->Fit(g1,"QR+");
		gr0->Fit(g1,"QR");
		p0[i] = g1->Integral(CHA,CHB);
		p1[i] = -1/g1->GetParameter(1);
		#if COMPS==1
			cout << "p1 " << p1[i] << endl;
		#else
			{
			//q0[i] = g1->Integral(CHA,CHB);
			q1[i] = -1/g1->GetParameter(3);
			Float_t aux = p1[i];
			if (p1[i]<q1[i]) 
				{
				p1[i]=q1[i];
				q1[i]=aux;	
				}
			cout << "p1 " << p1[i] <<  "  // q1 " << q1[i] << endl;


			}
		#endif
		i++;
		}
	
	TCanvas *c2a = new TCanvas("c2a","OE Decay time (ns)",100,100,500*cols/rows,500); 
	c2a->SetFillColor(0);
	c2a->GetFrame()->SetFillColor(0); 
	c2a->GetFrame()->SetBorderMode(-1);
   	 	
	TVirtualPad *vp2 =  c2a->cd(1);
	vp2->SetFillColor(10);
	vp2->SetBorderSize(2);
	vp2->SetFrameFillColor(0);
	vp2->SetLeftMargin(.15);
	vp2->SetRightMargin(.15);
	vp2->SetBottomMargin(.1);
	vp2->SetTopMargin(.05);

	TGraph2D *H2a = new TGraph2D(points,xc,yc,p1);   
   	H2a->SetNpy(499);  
	H2a->SetNpx(499);
	H2a->SetMarkerStyle(21);
	H2a->SetMarkerSize(0.1);	   
	H2a->Draw("colz");     
	ReverseYAxis(H2a);	
	//for (p=0;p<points;p++)
	//	{
	//	TBox *box1 = new TBox(x[p],y[p],x[p]+1,y[p]+1); 			box1->SetFillStyle(0);
  	//		box1->SetLineColor(1);
	//	box1->Draw();
	//	}
	H2a->GetYaxis()->SetLabelSize(0);
	H2a->GetXaxis()->SetTitle("Position X (#mum)");
	H2a->GetYaxis()->SetTitle("Position Y (#mum)");
	H2a->GetXaxis()->SetTitleOffset(1.2);
	H2a->GetYaxis()->SetTitleOffset(1.6);
	H2a->GetXaxis()->CenterTitle();
	H2a->GetYaxis()->CenterTitle();	
	PrintLatex_small(Form("%s [%s]","DT-1 (ns)",argv[1]),0.15,0.98,kBlack);


	#if COMPS==2
		{
		TCanvas *c2b = new TCanvas("c2b","OE Decay time (ns)",800,100,500*cols/rows,500); 
		c2b->SetFillColor(0);
		c2b->GetFrame()->SetFillColor(0); 
		c2b->GetFrame()->SetBorderMode(-1);
   	 	
		TVirtualPad *vp2 =  c2b->cd(1);
		vp2->SetFillColor(10);
		vp2->SetBorderSize(2);
		vp2->SetFrameFillColor(0);
		vp2->SetLeftMargin(.15);
		vp2->SetRightMargin(.15);
		vp2->SetBottomMargin(.1);
		vp2->SetTopMargin(.05);	

		TGraph2D *H2b = new TGraph2D(points,xc,yc,q1);   
	   	H2b->SetNpy(499);  	
		H2b->SetNpx(499);
		H2b->SetMarkerStyle(21);
		H2b->SetMarkerSize(0.1);	   
		H2b->Draw("colz");    	 
		ReverseYAxis(H2b);	
		//for (p=0;p<points;p++)
		//{
		//TBox *box1 = new TBox(x[p],y[p],x[p]+1,y[p]+1); 			box1->SetFillStyle(0);
  		//	box1->SetLineColor(1);
		//box1->Draw();
		//}
		H2b->GetYaxis()->SetLabelSize(0);
		H2b->GetXaxis()->SetTitle("Position X (#mum)");
		H2b->GetYaxis()->SetTitle("Position Y (#mum)");
		H2b->GetXaxis()->SetTitleOffset(1.2);
		H2b->GetYaxis()->SetTitleOffset(1.6);
		H2b->GetXaxis()->CenterTitle();
		H2b->GetYaxis()->CenterTitle();	
		PrintLatex_small(Form("%s [%s]","DT-2 (ns)",argv[1]),0.15,0.98,kBlack);
		}
	#endif


	TCanvas *c3 = new TCanvas("c3","OE-DT INTENSITY",100,800,500*cols/rows,500);	 
	c3->SetFillColor(0);
	c3->GetFrame()->SetFillColor(0); 
	c3->GetFrame()->SetBorderMode(-1);
	c3->GetFrame()->SetBorderSize(10);	
	TVirtualPad *vp3 =  c3->cd(1);
	vp3->SetFillColor(10);
	vp3->SetBorderSize(2);
	vp3->SetFrameFillColor(0);
	vp3->SetLeftMargin(.15);
	vp3->SetRightMargin(.15);
	vp3->SetBottomMargin(.1);
	vp3->SetTopMargin(.05);
		

	TGraph2D *H3 = new TGraph2D(points,xc,yc,p0);
	H3->SetMarkerStyle(21);
	H3->SetMarkerSize(0.1);
	H3->SetNpy(499);  
	H3->SetNpx(499);
	H3->Draw("ColZ"); 	

	ReverseYAxis(H3);
	H3->GetXaxis()->SetTitle("position X (#mum)");	
	H3->GetYaxis()->SetTitle("position Y (#mum)");
	H3->GetXaxis()->SetTitleOffset(1.2);
	H3->GetXaxis()->SetTitleOffset(1.2);
	H3->GetYaxis()->SetTitleOffset(1.6);
	H3->GetXaxis()->CenterTitle();
	H3->GetYaxis()->CenterTitle();	
	H3->GetYaxis()->SetLabelSize(0);		
	PrintLatex_small(Form("%s - %s","DT - Integral (a.u)",argv[1]),0.28,0.98,kBlack);


}



#if GRAPH
	theApp2->Run(kTRUE);						
	delete theApp2;
#endif 

return 0;
}
