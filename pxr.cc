//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h"
#include "HTCF.h"
#include <math.h> 

 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = variable-type; theApp variable-name you define;* is a pointer to one character
//Int_t i=0,k,N=2000,nsteps=0,COMP=5;  // initial parameters
Int_t n=0;  //number of points
Float_t minx, maxx; 
Float_t x[5000],y[5000],yn[5000]; 
Char_t f1[100],f2[100],f3[100],f4[100],f5[100],f6[100],f7[100],scint[100]="",sample[100]="00000",dopant[100]="",compound[100]="";		      
//Float_t xmax=4850,xmin=0.1;
//xmax=GetMax(x,nsteps);
//xmin=GetMin(x,nsteps);





std::string ci;
gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0); 
gStyle->SetOptFit(0);    
gStyle->SetOptTitle(0);
set_plot_style();

TCanvas *c1 = new TCanvas("c1","Optical Excitation",200,100,1200,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.txt",argv[1]);		 	
		break;						 
	case 3: sprintf(f1,"%s.txt",argv[1]);		 	
		sprintf(f2,"%s.txt",argv[2]);	
		break;		
	case 4: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		break;
	case 5: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
   		break;
	case 6: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
		sprintf(f5,"%s.txt",argv[5]);	
   		break;
	case 7: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
		sprintf(f5,"%s.txt",argv[5]);	
		sprintf(f6,"%s.txt",argv[6]);	
   		break;
   		break;
	case 8: sprintf(f1,"%s.txt",argv[1]);		 
		sprintf(f2,"%s.txt",argv[2]);	
		sprintf(f3,"%s.txt",argv[3]);	
		sprintf(f4,"%s.txt",argv[4]);	
		sprintf(f5,"%s.txt",argv[5]);	
		sprintf(f6,"%s.txt",argv[6]);	
   		sprintf(f7,"%s.txt",argv[7]);		
		break;
default:
		MsgError();
		exit(1);
		break;

	};   

if (argc>1)
	{
	GetInfo(argv[1], sample, scint, dopant);
	Read_PXR(f1, x, y, n);
	Normalize(y, yn, n);
	TGraph *gr1 = new TGraph(n-1,x,yn);
	//TH1F *gr1 = new TH1F("H",f1,n-1,x);
	//Plot_PXRh(gr1,x,yn,1,2,n);
	Plot_PXR(gr1,1,2);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.85,2);
	}
	
if (argc>2)
	{
	GetInfo(argv[2], sample, scint, dopant);
	Read_PXR(f2, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr2 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr2,0,4);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.80,4);
	}

if (argc>3)
	{
	GetInfo(argv[3], sample, scint, dopant);
	Read_PXR(f3, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr3 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr3,0,kGreen+3);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.75,kGreen+3);
	}

if (argc>4)
	{
	GetInfo(argv[4], sample, scint, dopant);
	Read_PXR(f4, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr4 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr4,0,1);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.70,1);
	}

if (argc>5)
	{
	GetInfo(argv[5], sample, scint, dopant);
	Read_PXR(f5, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr5 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr5,0,6);
	GetCompound(scint, dopant, compound);
	PrintLatex2(Form("- %s (%s)",compound,sample),0.50,0.65,6);
	}

if (argc>6)
	{
	GetInfo(argv[6], sample, scint, dopant);
	Read_PXR(f6, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr6 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr6,0,9);
	PrintLatex2(Form("%s:%s",scint,dopant),0.50,0.60,9);
	}

 if (argc>7)
	{
	GetInfo(argv[7], sample, scint, dopant);
	Read_PXR(f7, x, y, n);	
	Normalize(y, yn, n);
	TGraph *gr7 = new TGraph(n-1,x,yn);		 
	Plot_PXR(gr7,0,kGray+1);
	PrintLatex2(Form("%s:%s",scint,dopant),0.50,0.55,kGray+1);
	}


/*

//functions to fit
Char_t fitf1[100]="[0]+exp([1]+x*[2])";
Char_t fitf1b[100]="[0]+exp([1]+x*[2])";
Char_t fitf1c[100]="[0]+exp([1]+x*[2])";

Char_t fitf2[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])";
Char_t fitf3[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])";
Char_t fitf4[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])+exp([7]+x*[8])";
Char_t fitf5[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])+exp([7]+x*[8])+exp([9]+x*[10])";	

	
	TF1 *e1 = new TF1("e1","expo",xmin,xmax);
	TF1 *e2 = new TF1("e2","expo(0)+expo(2)",xmin,xmax);
	TF1 *e3 = new TF1("e3","expo(0)+expo(2)+expo(4)",xmin,xmax);
	TF1 *e4 = new TF1("e4","expo(0)+expo(2)+expo(4)+expo(6)",xmin,xmax);
	TF1 *e5 = new TF1("e5","expo(0)+expo(2)+expo(4)+expo(6)+expo(8)",xmin,xmax);

	TF1 *f1 = new TF1("f1",fitf1,xmin,xmax);
	TF1 *f2 = new TF1("f2",fitf2,xmin,xmax);
	TF1 *f3 = new TF1("f3",fitf3,xmin,xmax);
	TF1 *f4 = new TF1("f4",fitf4,xmin,xmax);
	TF1 *f5 = new TF1("f5",fitf5,xmin,xmax);


	gr1->Fit(e1,"NQR+");
	Float_t e1_p0 = e1->GetParameter(0);
	Float_t e1_p1 = e1->GetParameter(1);

	gr1->Fit(e2,"NQR+");
	Float_t e2_p0 = e2->GetParameter(0);
	Float_t e2_p1 = e2->GetParameter(1);
	Float_t e2_p2 = e2->GetParameter(2);
	Float_t e2_p3 = e2->GetParameter(3);

	gr1->Fit(e3,"NQR+");
	Float_t e3_p0 = e3->GetParameter(0);
	Float_t e3_p1 = e3->GetParameter(1);
	Float_t e3_p2 = e3->GetParameter(2);
	Float_t e3_p3 = e3->GetParameter(3);
	Float_t e3_p4 = e3->GetParameter(4);
	Float_t e3_p5 = e3->GetParameter(5);

	gr1->Fit(e4,"NQR+");
	Float_t e4_p0 = e4->GetParameter(0);
	Float_t e4_p1 = e4->GetParameter(1);
	Float_t e4_p2 = e4->GetParameter(2);
	Float_t e4_p3 = e4->GetParameter(3);
	Float_t e4_p4 = e4->GetParameter(4);
	Float_t e4_p5 = e4->GetParameter(5);
	Float_t e4_p6 = e4->GetParameter(6);
	Float_t e4_p7 = e4->GetParameter(7);
	
	gr1->Fit(e5,"NQR+");
	Float_t e5_p0 = e5->GetParameter(0);
	Float_t e5_p1 = e5->GetParameter(1);
	Float_t e5_p2 = e5->GetParameter(2);
	Float_t e5_p3 = e5->GetParameter(3);
	Float_t e5_p4 = e5->GetParameter(4);
	Float_t e5_p5 = e5->GetParameter(5);
	Float_t e5_p6 = e5->GetParameter(6);
	Float_t e5_p7 = e5->GetParameter(7);
	Float_t e5_p8 = e5->GetParameter(8);
	Float_t e5_p9 = e5->GetParameter(9); 




	cout << " \n ***************************** FIT WITH EXTRA VARIABLE********************** "  << endl;

	f1->SetParameter(0,y[0]);
	f1->SetParameter(1,e1_p0);
	f1->SetParameter(2,e1_p1);
	gr1->Fit("f2","NQR+");
	f1->SetLineColor(1); 	
	if (COMP==1) {gr1->Fit("f1","R"); f1->Draw("same");}


	f2->SetParameter(0,y[0]);
	f2->SetParameter(1,e2_p2);
	f2->SetParameter(2,e2_p3);
	f2->SetParameter(3,e2_p0);
	f2->SetParameter(4,e2_p1);
	gr1->Fit("f2","NQR+");
	gr1->Fit("f2","NQR+");
	f2->SetLineColor(1); 	
	if (COMP==2) {gr1->Fit("f2","R"); f2->Draw("same");}

	

	f3->SetParameter(0,y[0]);
	f3->SetParameter(1,e3_p0);
	f3->SetParameter(2,e3_p1);
	f3->SetParameter(3,e3_p2);
	f3->SetParameter(4,e3_p3);
	f3->SetParameter(5,e3_p4);
	f3->SetParameter(6,e3_p5);
	gr1->Fit("f3","NQR+");
	gr1->Fit("f3","NQR+");
	gr1->Fit("f3","NQR+");
	f3->SetLineColor(1); 	
	if (COMP==3) {gr1->Fit("f3","R"); f3->Draw("same");}


	f4->SetParameter(0,y[0]);
	f4->SetParameter(1,e4_p0);
	f4->SetParameter(2,e4_p1);
	f4->SetParameter(3,e4_p2);
	f4->SetParameter(4,e4_p3);
	f4->SetParameter(5,e4_p4);
	f4->SetParameter(6,e4_p5);
	f4->SetParameter(7,e4_p6);
	f4->SetParameter(8,e4_p7);
	gr1->Fit("f4","NQR+");
	gr1->Fit("f4","NQR+");
	gr1->Fit("f4","NQR+");
	f4->SetLineColor(1); 	
	if (COMP==4) {gr1->Fit("f4","R"); f4->Draw("same");}

	f5->SetParameter(0,y[0]);
	f5->SetParameter(1,e5_p0);
	f5->SetParameter(2,e5_p1);
	f5->SetParameter(3,e5_p2);
	f5->SetParameter(4,e5_p3);
	f5->SetParameter(5,e5_p4);
	f5->SetParameter(6,e5_p5);
	f5->SetParameter(7,e5_p6);
	f5->SetParameter(8,e5_p7);
	f5->SetParameter(9,e5_p8);
	f5->SetParameter(10,e5_p9);
	gr1->Fit("f5","NQR+");
	gr1->Fit("f5","NQR+");
	gr1->Fit("f5","NQR+");
	f5->SetLineColor(1); 	
	if (COMP==5) {gr1->Fit("f5","R"); f5->Draw("same");}
 

     //************************************ calculo del chi2  
	

GetX2_NDF(f1);
GetX2_NDF(f2);
GetX2_NDF(f3);
GetX2_NDF(f4);
GetX2_NDF(f5);
 	

Float_t t1,t2,t3,t4,t5,tot;
Float_t a1,a2,a3,a4,a5;

Float_t tau[3],tauerr[3],amp[3];

if (COMP==1)
	{
	legend->AddEntry(gr1,Form("%s (%s)",scint,sample),"l");
	a1=f1->GetParameter(1);
	t1=f1->GetParameter(2);
	tot=std::exp(a1)/t1;
	for (k=0;k<1;k++)			
		{
		
		tau[k]= -1/f1->GetParameter(k*2+2);
		tauerr[k]=f1->GetParError(k*2+2)/(tau[k]*tau[k]); 
		amp[k]= f1->GetParameter(k*2+1);
		amp[k]= (std::exp(amp[k]))/tot*100;  
		if (tauerr[k]<0.01) tauerr[k]=0.01;
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}
	}


if (COMP==2)
	{
	legend->AddEntry(gr1,Form("%s (%s)",scint,sample),"l");
	a1=f2->GetParameter(1);
	a2=f2->GetParameter(3);
	t1=f2->GetParameter(2);
	t2=f2->GetParameter(3);

	tot=std::exp(a1)/t1+std::exp(a2)/t2;
	for (k=0;k<2;k++)			
		{
	
		tau[k]= -1/f2->GetParameter(k*2+2);
		tauerr[k]=f2->GetParError(k*2+2)/(tau[k]*tau[k]); 
		if (tauerr[k]<0.01) tauerr[k]=0.01;
		amp[k]= f2->GetParameter(k*2+1);
		amp[k]= std::exp(amp[k])/tau[k]/tot*100;  	
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}
	}


if (COMP==3)
	{
	legend->AddEntry(gr1,Form("%s (%s)",scint,sample),"l");
	t1=f3->GetParameter(1);
	t2=f3->GetParameter(3);
	t3=f3->GetParameter(5);
	tot=std::exp(t1)+std::exp(t2)+std::exp(t3);
  	for (k=0;k<3;k++)			
		{
		amp[k]= f3->GetParameter(k*2+1);
		amp[k]= std::exp(amp[k])/tot*100;  		
		tau[k]= -1/f3->GetParameter(k*2+2);
		tauerr[k]=f3->GetParError(k*2+2)/(tau[k]*tau[k]); 
		if (tauerr[k]<0.1) tauerr[k]=0.1;
		}
	Float_t aux;		
	aux=amp[0]; amp[0]=amp[2]; amp[2]=aux;
	aux=tau[0]; tau[0]=tau[2]; tau[2]=aux;

	for (k=0;k<3;k++)
		{
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}	

	TF1 *er1 = new TF1("er1",fitf1,2,4600);   
	er1->SetParameters(f3->GetParameter(0),f3->GetParameter(1),f3->GetParameter(2));	
	//er1->SetLineColor(kGreen+3);
 	er1->SetLineStyle(9);
	er1->Draw("same");
	TF1 *er2 = new TF1("er2",fitf1b,1,500); 
	
	er2->SetParameters(f3->GetParameter(0),f3->GetParameter(3),f3->GetParameter(4));
	er2->SetLineStyle(9);
  	//er2->SetLineColor(2);
	er2->Draw("same");
	TF1 *er3 = new TF1("er3",fitf1c,1,120); 
	er3->SetParameters(f3->GetParameter(0),f3->GetParameter(5),f3->GetParameter(6));
	er3->SetLineStyle(9);
	//er3->SetLineColor(5);
  	er3->Draw("same");
	}



if (COMP==4)
	{
	legend->AddEntry(gr1,Form("%s (%s)",scint,sample),"l");
	t1=f4->GetParameter(1);
	t2=f4->GetParameter(3);
	t3=f4->GetParameter(5);
	t4=f4->GetParameter(7);
	tot=std::exp(t1)+std::exp(t2)+std::exp(t3)+std::exp(t4);
  	for (k=0;k<4;k++)			
		{
		amp[k]= f4->GetParameter(k*2+1);
		amp[k]= std::exp(amp[k])/tot*100; cout << amp[k]  <<endl;		
		tau[k]= -1/f4->GetParameter(k*2+2);
		tauerr[k]=f4->GetParError(k*2+2)/(tau[k]*tau[k]); 
		if (tauerr[k]<0.1) tauerr[k]=0.1;
		//legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}




	Float_t aux;		
	aux=amp[0]; amp[0]=amp[1]; amp[1]=aux;
	aux=tau[0]; tau[0]=tau[1]; tau[1]=aux;

	for (k=0;k<4;k++)
		{
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}	

	TF1 *er1 = new TF1("er1",fitf1,2,100);   
	er1->SetParameters(f4->GetParameter(0),f4->GetParameter(1),f4->GetParameter(2));	
	//er1->SetLineColor(kGreen+3);
 	er1->SetLineStyle(9);
	er1->Draw("same");
	TF1 *er2 = new TF1("er2",fitf1,1,120); 
	
	er2->SetParameters(f4->GetParameter(0),f4->GetParameter(3),f4->GetParameter(4));
	er2->SetLineStyle(9);
  	//er2->SetLineColor(2);
	er2->Draw("same");
	TF1 *er3 = new TF1("er3",fitf1,1,4600); 
	er3->SetParameters(f4->GetParameter(0),f4->GetParameter(5),f4->GetParameter(6));
	er3->SetLineStyle(9);
	//er3->SetLineColor(5);
  	er3->Draw("same");


	TF1 *er4 = new TF1("er4",fitf1,1,4600); 
	er4->SetParameters(f4->GetParameter(0),f4->GetParameter(7),f4->GetParameter(8));
	er4->SetLineStyle(9);
	//er3->SetLineColor(5);
  	er4->Draw("same");




	}


if (COMP==5)
	{
	legend->AddEntry(gr1,Form("%s (%s)",scint,sample),"l");
	t1=f5->GetParameter(1);
	t2=f5->GetParameter(3);
	t3=f5->GetParameter(5);
	t4=f5->GetParameter(7);
	t5=f5->GetParameter(9);
	tot=std::exp(t1)+std::exp(t2)+std::exp(t3)+std::exp(t4)+std::exp(t5);
  	for (k=0;k<5;k++)			
		{
		amp[k]= f5->GetParameter(k*2+1);
		amp[k]= std::exp(amp[k])/tot*100; cout << amp[k]  <<endl;		
		tau[k]= -1/f5->GetParameter(k*2+2);
		tauerr[k]=f5->GetParError(k*2+2)/(tau[k]*tau[k]); 
		if (tauerr[k]<0.01) tauerr[k]=0.01;
		legend2->AddEntry(gr1,Form("#tau_{%d} = (%0.1f #pm %0.1f) ns   (I = %2.1f %)",k+1,tau[k],tauerr[k],amp[k]),"p");
		}
	}


	legend->Draw();
	legend2->Draw();


	//}


/*
*/

		
	//}*/	

theApp->Run(kTRUE);
delete theApp;
return 0;
}
