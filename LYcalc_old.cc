//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h" 

using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1
 

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Int_t k, N=10000,empts=0,qepts=0,napts=0,chsource=1,n=0;
Float_t x[N],y[N]; 	
Float_t xb[N],yb[N],xc[N],yc[N],yn[N];
Float_t norm=1,norm2=1,norm3=1,area1=0,area2=0,area3=0;


char file[100],file2[100],file3[100],scint[100]="",sample[100]="00000",dopant[100]="";

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
vp->SetRightMargin(.10);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);

TLegend *legend=new TLegend(0.7,0.75,0.88,0.85);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 5: sprintf(file,"%s.txt",argv[1]);                // EMISSION FROM htcf viewer
		sprintf(file2,"%s.txt",argv[2]);   		// Quantum efficiency PMT or APD
		sprintf(file3,"%s.txt",argv[3]);   		// XRL OF NaI(Tl) as reference
		chsource=atoi(argv[4]);	
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   



GetInfo(argv[1], sample, scint, dopant); //////////////////////////////////////////////// FILE TO CALIBRATE
Read_XRL(file, x, y, n);
Normalize(y, yn, n);
TGraph *gr1 = new TGraph(n-1,x,yn);		 
Plot_XRL(gr1,1,2);
PrintLatex2(Form("%s:%s",scint,dopant),0.50,0.95,2);

empts=n-1; cout << "Emision points : " << empts << endl;           
x[empts]=x[empts-1]+1; y[empts]=0;
norm=GetMax(y,empts);
for (k=0;k<empts;k++)			
	{
	y[k]=(float)y[k]/norm;  		
	area1=area1+y[k]*(x[k+1]-x[k]);
	}
cout << "Maximum emission= "<< norm  << "    Area 1 = " << area1 <<endl;

TSpline3 *s1 = new TSpline3("sgr1",gr1);			// spline of the file to be ploted
s1->SetLineColor(kRed);
//s->Draw("same");


Read_XRL(file2, xb, yb, n);  //////////////////////////////////////////////// PMT QUANTUM EFFICIENCY

qepts=n-1; cout << "QE curve points : " << qepts << endl;
xb[qepts]=xb[qepts-1]+1; yb[qepts]=0;
norm2 = GetMax(yb,qepts);

for (k=0;k<qepts;k++)			
	{
	yb[k]=yb[k]*1.085/100; 
	area2=area2+yb[k]*(xb[k+1]-xb[k]);	
	}
cout << "Maximum QE(%): " << norm2  << "    Area 2 = " << area2  << endl;


TGraph *gr2 = new TGraph(qepts,xb,yb);		 
//Plot_XRL(gr2,1,2);

TSpline3 *s2 = new TSpline3("sgr2b",gr2);
s2->SetLineColor(kBlue);
s2->Draw("same");


Read_XRL(file3, xc, yc, n);  //////////////////////////////////////////////// NaI(Tl) emission

napts=n-1; cout << "Emision points for NaI(Tl) : " << napts << endl;
	xc[napts]=xc[napts-1]+1; yc[napts]=0;
	norm3=GetMax(yc,empts);
	for (k=0;k<napts;k++)			
		{
		yc[k]=(float)yc[k]/norm3;
		area3=area3+yc[k]*(xc[k+1]-xc[k]);
		}
	cout << "Maximum emission for NaI: "<< norm3  <<  "    Area 3 = " << area3  << endl;

TGraph *gr3 = new TGraph(napts,xc,yc);


TSpline3 *s3 = new TSpline3("sgr3c",gr3);
s3->SetLineColor(kGreen+3);
s3->SetLineWidth(3);
s3->Draw("same");

/////////////////////////////////////////////////////////////////////////////////////// CALCULATIONS!!!!!!!!!!!

Float_t lamb[450],em1[450],em2[450],qe[450],lo1[450],lo2[450],lo1tot=0,lo2tot=0;
 
for (k=250;k<700;k++)			
	{
	lamb[k-250]=k;
	em1[k-250]= s1->Eval(k);	//cout << em1[k] << endl;			// evaluation on the same points as file
	qe[k-250]= s2->Eval(k);		//cout << qe[k] << endl;	
	em2[k-250]= s3->Eval(k);
	lo1[k-250]= em1[k-250]*qe[k-250];	//cout << lo1[k] << endl;	
	lo2[k-250]= em2[k-250]*qe[k-250];
	}


for (k=0;k<450;k++)			
	{
	lo1tot=	lo1tot+lo1[k];			// evaluation on the same points as file
	lo2tot=	lo2tot+lo2[k];	
	}

TGraph *gr4 = new TGraph(450,lamb,lo1);
Plot_XRL(gr4,0,1);


TGraph *gr5 = new TGraph(450,lamb,lo2);
Plot_XRL(gr5,0,kOrange);

cout << "Area of GGAG x QE " << lo1tot << endl;
cout << "Area of NaI(Tl) x QE " << lo2tot << endl;

Float_t source=0,lysource=0,lyNaI=38000,phNaI=6250;


source = lo1tot*phNaI/lo2tot;
lysource= chsource/source*lyNaI;

cout << "Considering that NaI(Tl) has " << lyNaI <<" ph/MeV" <<endl;
cout << "your crystal produce: "<< lysource << " ph/MeV" <<endl;

/*

	for (k=0;k<qepts;k++)			
		{
		cout << s2->Eval(x[k]) << endl;				// evaluation on the same points as file
		sl[k]=(yb[k+1]-yb[k])/(xb[k+1]-xb[k]);			// sl is the area
		ab[k]= (yb[k+1]+yb[k]-sl[k]*(xb[k+1]+xb[k]))/2; 	//cout <<  sl[k] << "  " << ab[k] << endl;
		}




///////////////////////////////// calculations of intersected areas

	cout << "xb = "<< xb[0]  << "    xb[qepts] = " << xb[qepts] <<endl;     


	Int_t lo1=0,lo2=0;
	for (k=0;k<empts;k++)			
		{
		lo1 = lo1 + (s2->Eval(x[k])*s3->Eval(x[k]));
		if ((x[k] > xb[0]) && (x[k] < xb[qepts]) )//&& (y[k] < yb[(int)x[k]]))	
				{
				
				//lo2 = lo2 + (s11->Eval(x[k])*s2->Eval(x[k]));
				//s3->Eval(k)
				//cout << s2->Eval(x[k]) <<" s2  &  s3 " << s3->Eval(k) << endl;
				area12=area12+y[k]*(x[k+1]-x[k])*yb[(int)x[k]];
				//cout << y[k]*(x[k+1]-x[k]) <<"  " << k << " " <<  x[k] << " yb " << yb[(int)x[k]] <<endl;				
				}

		}
	cout << "AREA 12 = "<< area12  << "    Area12/Area2 = " << area12/area2 <<endl;
	cout << "LO1 "<< lo1 << " " <<  endl;

	for (k=0;k<napts;k++)			
		{
		if ((xc[k] > xb[0]) && (xc[k] < xb[qepts]) )//&& (y[k] < yb[(int)x[k]]))	
				{
				area13=area13+yc[k]*(xc[k+1]-xc[k])*yb[(int)xc[k]];
				
				//cout << yc[k]*(xc[k+1]-x[k]) <<"  " << k << " " <<  x[k] << " yb " << yb[(int)x[k]] <<endl;				
				}

		}
	cout << "AREA 13 = "<< area13  << "    Area13/Area3 = " << area13/area3 <<endl;
	cout << "LO2 "<< lo2 << " " <<  endl;

	cout << "Area 12/ Area13 x 40000 ph/Mev = "<< (area12/area13)*40000*2400/3300 <<endl;


*/


	/*for (k=0;k<empts;k++)			
		{
		if (x[k]<xb[0]) yl[k]=0;
		else
			y
			

		y[k]=(float)y[k]/norm;
		dy[k]=(float)dy[k]/norm;	
		if (max<y[k]) max=y[k];
		}*/





//}













legend->Draw();
#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
