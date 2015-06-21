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
Int_t k, N=10000,empts=0,qepts=0,napts=0,chsource=1,phNaI=0,n=0;
Float_t x[N],y[N]; 	
Float_t xb[N],yb[N],xc[N],yc[N],yn[N];
Float_t norm=1,norm2=1,norm3=1,area1=0,area2=0,area3=0;


char file[100],file2[100],file3[100],scint[100]="",sample[100]="00000",dopant[100]="";

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
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
	case 1: MsgError();
		exit(1);
		break;
	case 4: sprintf(file,"%s.txt",argv[1]);                	// EMISSION FROM htcf viewer
		phNaI=atoi(argv[2]);				// PHM photopeak channel of the NaI(Tl)
		chsource=atoi(argv[3]);				// PHM photopeak channel of the file		
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   



sprintf(file2,"/home/martin/misProgs/cc3/support_files/QE_6231_100_PMT_v2.txt");   	// Quantum efficiency PMT or APD
sprintf(file3,"/home/martin/misProgs/cc3/support_files/13144_XRL.txt");  

Read_XRL(file3, xc, yc, n);  //////////////////////////////////////////////// NaI(Tl) emission



		// XRL OF NaI(Tl) as reference 

napts=n-1; cout << "Emision points for NaI(Tl) : " << napts << endl;
	xc[napts]=xc[napts-1]+1; yc[napts]=0;
	norm3=GetMax(yc,empts);
	for (k=0;k<napts;k++)			
		{
		area3=area3+yc[k]*(xc[k+1]-xc[k]);
		}

	for (k=0;k<napts;k++)			
		{
		yc[k]=(float)yc[k]/area3;
		}

	cout << "Maximum emission for NaI: "<< norm3  <<  "    Area 3 = " << area3  << endl;





TGraph *gr3 = new TGraph(napts,xc,yc);

TSpline3 *s3 = new TSpline3("sgr3c",gr3);
s3->SetLineColor(kGreen+3);
s3->SetLineWidth(3);
//s3->Draw("same");

Plot_XRL(gr3,1,kGreen+3);
gr3->GetYaxis()->SetRangeUser(0,0.011);	

GetInfo(argv[1], sample, scint, dopant); //////////////////////////////////////////////// FILE TO CALIBRATE
Read_XRL(file, x, y, n);

empts=n-1; cout << "Emision points : " << empts << endl;           
x[empts]=x[empts-1]+1; y[empts]=0;
norm=GetMax(y,empts);
for (k=0;k<empts;k++)		//calculate the area of file 1	
	{
	area1=area1+y[k]*(x[k+1]-x[k]);
	}

for (k=0;k<empts;k++)			
	{
	yn[k]=(float)y[k]/area1;  		
	}

cout << "Maximum emission= "<< norm  << "    Area 1 = " << area1 <<endl;

TGraph *gr1 = new TGraph(n-1,x,yn);		 



TSpline3 *s1 = new TSpline3("sgr1",gr1);			// spline of the file to be ploted
s1->SetLineWidth(3);
s1->SetLineColor(kRed);
s1->Draw("same");


Read_XRL(file2, xb, yb, n);  //////////////////////////////////////////////// PMT QUANTUM EFFICIENCY

qepts=n-1; cout << "QE curve points : " << qepts << endl;
xb[qepts]=xb[qepts-1]+1; yb[qepts]=0;
norm2 = GetMax(yb,qepts);

for (k=0;k<qepts;k++)			
	{
	yb[k]=yb[k]/100*1.085; // just in case you use the pmt ouside the glovebox
	area2=area2+yb[k]*(xb[k+1]-xb[k]);	
	}
cout << "Maximum QE(%): " << norm2  << "    Area 2 = " << area2  << endl;

 
TGraph *gr2 = new TGraph(qepts,xb,yb);		 
//Plot_XRL(gr2,0,4);



PrintLatex2(Form("NaI(Tl)"),0.40,0.85,kGreen+3);
PrintLatex2(Form("%s(%s)",scint,dopant),0.40,0.80,2);
PrintLatex2(Form("PMT 6231-100 QE"),0.40,0.75,kBlue);
PrintLatex2(Form("Convolution %s+PMT QE",scint),0.40,0.70,kMagenta+2);
PrintLatex2(Form("Convolution NaI(Tl)+PMT QE"),0.40,0.65,kCyan+2);

 	Double_t ymin = gr2->GetHistogram()->GetMinimum();
   	Double_t ymax = gr2->GetHistogram()->GetMaximum();
   	Double_t dy = (ymax-ymin)/0.8; 						//10% margins top and bottom
   	Double_t xmin = 230;//  gr3->GetHistogram()->GetMinimum();			// min of NaI(Tl)
   	Double_t xmax = 950; //gr3->GetHistogram()->GetMaximum();                      // max of NaI(Tl)
   	Double_t dx = (xmax-xmin)/0.8; 						//10% margins left and right
 	pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
 	pad2->Draw();
  	pad2->cd();

	gr2->SetLineColor(kBlue);					
	gr2->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr2->SetMarkerColor(kBlue);						
	gr2->SetMarkerStyle(20);					
	gr2->GetXaxis()->SetTitle("Wavelength (nm)");
	gr2->GetYaxis()->SetTitle("Intensity (a.u.)");					
	gr2->GetXaxis()->SetTitleSize(0.05);
	gr2->GetYaxis()->SetTitleSize(0.05);
	gr2->GetXaxis()->SetLabelSize(0.05);
	gr2->GetYaxis()->SetLabelSize(0.05);
	gr2->GetXaxis()->SetTitleOffset(0.90);
	gr2->GetYaxis()->SetTitleOffset(0.90);
	gr2->GetXaxis()->CenterTitle();					
	gr2->GetYaxis()->CenterTitle();	
	gr2->GetXaxis()->SetRangeUser(230,950);	
	


	gr2->Draw("][samec");
	TGaxis *axis = new TGaxis(xmax,ymin,xmax,ymax,ymin,ymax,505,"+L");
	axis->SetTitle("Quantum efficiency (%)");
	axis->SetTitleSize(0.05);	
	axis->SetTitleColor(kBlue);	
	axis->SetTitleOffset(0.88);
	axis->CenterTitle();	
	axis->SetLabelColor(kBlue);
	axis->SetLabelSize(0.05);
	axis->Draw();	
	
	TSpline3 *s2 = new TSpline3("sgr2b",gr2);
	s2->SetLineColor(kBlue);
	s2->SetLineWidth(3);
//	s2->Draw("same");











pad1->cd();

/////////////////////////////////////////////////////////////////////////////////////// CALCULATIONS!!!!!!!!!!!

Float_t lamb[450],em1[450],em2[450],qe[450],lo1[450],lo2[450],lo1tot=0,lo2tot=0;
 
for (k=250;k<700;k++)			
	{
	lamb[k-250]=k;
	em1[k-250]= s1->Eval(k);		//cout << em1[k] << endl;			// evaluation on the same points as file
	qe[k-250]=  s2->Eval(k);		//cout << qe[k] << endl;	
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
Plot_XRL(gr4,0,kMagenta+2);


TGraph *gr5 = new TGraph(450,lamb,lo2);
Plot_XRL(gr5,0,kCyan+2);

cout << "Area of Sample  x QE = " << lo1tot << endl;
cout << "Area of NaI(Tl) x QE = " << lo2tot << endl;

Float_t source=0,lysource=0,lyNaI=25000;


source = lo1tot*phNaI/lo2tot;
lysource= chsource/source*lyNaI;

cout << "******************* SUMMARY ****************" <<endl;
cout << "Considering that NaI(Tl) has " << lyNaI <<" ph/MeV" <<endl;
cout << "and the Photopeak of NaI(Tl) is around channel " << phNaI <<endl;
cout << "your crystal produce: "<< lysource << " ph/MeV" <<endl;
cout << "****************************************************" <<endl;






PrintLatex2(Form("LY = %2.0f%s",lysource," ph/MeV"),0.6,0.4,kRed);


#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
