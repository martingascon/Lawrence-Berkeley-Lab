//#************** Copyright: Martin Gascon. Lawrence Berkeley National Lab ***************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

#define N 10000 				       // maximun number of points

#define EC 100 // Reference energy
#define LL 8 	// defines lower limit
#define HL 110   // defines higher limit



int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];    
Float_t datax[N],datay[N],datay2[N],errorx[N],errory[N],errory2[N],ref=0,dref=0; 		      
Int_t i,k;  
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100];
char latex3[100],latex4[100],latex5[100],latex6[100],latex7[100];
//char fitf[100]="([0]+[1]*x)*([2]-[3]*exp(-x*[4]))";//)" 
//char fitf2[100]="([0]-[1]*exp(-x*[2])+[3]*exp(x*[4]))";//)" 
char fitf2[100]="pol1";//)" 
gROOT->SetStyle("Plain"); 
Char_t scint[100]="NaI",dopant[100]="",sample[100]="00000";


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
//c1->SetLogx();
//c1->SetRange(10,0.5,3000,1.90);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
//*********************************** Cuerpo del programa   *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		break;
	case 3: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		break;
	case 4: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		break;
	case 5: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);
		break;
	case 6: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);
		sprintf(file5,"%s.txt",argv[5]);
		break;
	case 7: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);	
		sprintf(file5,"%s.txt",argv[5]);
		sprintf(file6,"%s.txt",argv[6]);
		break;
	case 8: sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(file2,"%s.txt",argv[2]);
		sprintf(file3,"%s.txt",argv[3]);
		sprintf(file4,"%s.txt",argv[4]);	
		sprintf(file5,"%s.txt",argv[5]);
		sprintf(file6,"%s.txt",argv[6]);
		sprintf(file7,"%s.txt",argv[7]);	
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   

GetInfo_ALS(file1,sample,scint,dopant);

ifstream *in = new ifstream(file1);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		*in >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
		if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
		i++;
		}
	}

for (k=0;k<i-1;k++)
		{
		x[k]=datax[k];   
		y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl;
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey2[k]=errory2[k];
		}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);	
gr1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();	
gr1->GetXaxis()->SetTitle("Energy photon (keV)");		// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("Relative Light Yield");         // Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->SetTitleOffset(1.2);			
gr1->GetYaxis()->SetTitleOffset(1.2);
gr1->GetXaxis()->SetLabelColor(1);			
gr1->GetYaxis()->SetLabelColor(1);
gr1->GetXaxis()->SetMoreLogLabels();
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(20);
gr1->SetMarkerSize(1.5);
//gr1->GetXaxis()->SetLimits(10,1400);
TAxis *axis = gr1->GetXaxis();
axis->SetLimits(LL,HL); // along X 
gr1->Draw("alp");	
 /*
TSpline3 *s = new TSpline3("grs",gr1);
s->SetLineColor(kRed);
s->Draw("same");

 */
TLine *tl= new TLine();
tl->SetLineStyle(9);
tl->DrawLine(LL,1,HL,1);

delete in;

PrintLatex2(Form("%s (%s)",scint,sample),0.7,0.45,2);


TF1 *f1 = new TF1("f1",fitf2,20,1450); 
f1->SetParameter(0,1);				
f1->SetParameter(1,1);				
f1->SetParameter(2,1);	
f1->SetParameter(3,5);
f1->SetParameter(4,-0.15);
f1->SetLineColor(kRed);
f1->SetLineStyle(9);
//gr1->Fit("f1","R");	
for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors


if (argc>2)
	{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in2->eof())
			{
			
			*in2 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i];  
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		y[k]=(datay[k]);	
		//y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= errory[k];
		//ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr2 = new TGraphErrors(k,x,y,ex,ey);			
	gr2->SetMarkerColor(kBlue);
	gr2->SetMarkerStyle(20);
	gr2->SetMarkerSize(1.5);
	gr2->Draw("lpsame");					
	delete in2;	
	GetInfo_ALS(file2,sample,scint,dopant);
	PrintLatex2(Form("%s (%s)",scint,sample),0.7,0.40,kBlue);
	TF1 *f2 = new TF1("f2",fitf2,20,1400); 
	f2->SetParameter(0,1);				
	f2->SetParameter(1,1);				
	f2->SetParameter(2,1 );	
	f2->SetParameter(3,5);
	f2->SetParameter(4,-0.15);
	f2->SetLineColor(kBlue);
	f2->SetLineStyle(9);
	//gr2->Fit("f2","R");	
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors

	}


if (argc>3)
	{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) 
		{cout << " ERROR OPENING FILE " <<  file3 << endl; 
		return 1;
		}
	else    {
		i=0;
		do
			{
			*in3 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i];  cout << datax[i] <<  " " << datay[i] << endl;
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " 662 ------" << datax[i] << endl;}
						
			i++;
			}while (!in3->eof());
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		//y[k]=datay[k];
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		//ey[k]= errory[k];
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr3 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr3->SetMarkerColor(kGreen+3);
	gr3->SetMarkerStyle(20);
	gr3->SetMarkerSize(1.5);
	gr3->Draw("psame");					// Pinta el gráfico A:marco P=puntos L=linea C=curva			
	delete in3;	
	TLatex *tx3 = new TLatex();
	tx3->SetNDC();
	tx3->SetTextSize(0.04);
	tx3->SetTextColor(kGreen+3);
	tx3->DrawLatex(0.7,0.35,latex3);
	TF1 *f3 = new TF1("f3",fitf2,20,1400); 
	f3->SetParameter(0,1);				
	f3->SetParameter(1,1);				
	f3->SetParameter(2,1 );	
	f3->SetParameter(3,5);
	f3->SetParameter(4,-0.15);
	f3->SetLineColor(kGreen+3);
	f3->SetLineStyle(9);
	//gr3->Fit("f3","R");	
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors	
	}


if (argc>4)
	{
	ifstream *in4 = new ifstream(file4);
	if(!*in4) 
		{cout << " ERROR OPENING FILE " <<  file4 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in4->eof())
			{
			datax[i]=0;errorx[i]=0;datay[i]=0;errory[i]=0;datay2[i]=0;errory2[i]=0;
			*in4 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;   cout << datax[i] <<  " " << datay[i] << endl;
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " 662 ------" << datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		//y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		y[k]=datay[k];
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		//ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey[k]= errory[k];
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr4 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr4->SetMarkerColor(kBlack);
	gr4->SetMarkerStyle(20);
	gr4->SetMarkerSize(1.5);
	gr4->Draw("psame");					// Pinta el gráfico A:marco P=puntos L=linea C=curva			
	delete in4;	
	TLatex *tx4 = new TLatex();
	tx4->SetNDC();
	tx4->SetTextSize(0.04);
	tx4->SetTextColor(kBlack);
	tx4->DrawLatex(0.7,0.30,latex4);	
	TF1 *f4 = new TF1("f4",fitf2,20,1400); 
	f4->SetParameter(0,1);				
	f4->SetParameter(1,1);				
	f4->SetParameter(2,1);	
	f4->SetParameter(3,5);
	f4->SetParameter(4,-0.15);
	f4->SetLineColor(kBlack);
	f4->SetLineStyle(9);
	//gr4->Fit("f4","R");
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors		
	}

if (argc>5)
	{
	ifstream *in5 = new ifstream(file5);
	if(!*in5) 
		{cout << " ERROR OPENING FILE " <<  file5 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in5->eof())
			{
			*in5 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr5 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr5->SetMarkerColor(kOrange);
	gr5->SetMarkerStyle(20);
	gr5->SetMarkerSize(1.5);
	gr5->Draw("psame");					// Pinta el gráfico A:marco P=puntos L=linea C=curva			
	delete in5;	
	TLatex *tx5 = new TLatex();
	tx5->SetNDC();
	tx5->SetTextSize(0.04);
	tx5->SetTextColor(kOrange);
	tx5->DrawLatex(0.7,0.25,latex5);
	TF1 *f5 = new TF1("f5",fitf2,20,1400); 
	f5->SetParameter(0,1);				
	f5->SetParameter(1,1);				
	f5->SetParameter(2,1);	
	f5->SetParameter(3,5);
	f5->SetParameter(4,-0.15);
	f5->SetLineColor(kOrange);
	f5->SetLineStyle(9);
	//gr5->Fit("f5","R");
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors		
	}


if (argc>6)
	{
	ifstream *in6 = new ifstream(file6);
	if(!*in6) 
		{cout << " ERROR OPENING FILE " <<  file6 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in6->eof())
			{
			*in6 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr6 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr6->SetMarkerColor(kMagenta);
	gr6->SetMarkerStyle(20);
	gr6->SetMarkerSize(1.5);
	gr6->Draw("psame");					// Pinta el gráfico A:marco P=puntos L=linea C=curva			
	delete in6;	
	TLatex *tx6 = new TLatex();
	tx6->SetNDC();
	tx6->SetTextSize(0.04);
	tx6->SetTextColor(kMagenta);
	tx6->DrawLatex(0.7,0.20,latex6);	
	TF1 *f6 = new TF1("f6",fitf2,20,1400); 
	f6->SetParameter(0,1);				
	f6->SetParameter(1,1);				
	f6->SetParameter(2,1);	
	f6->SetParameter(3,5);
	f6->SetParameter(4,-0.15);
	f6->SetLineColor(kMagenta);
	f6->SetLineStyle(9);
	//gr6->Fit("f6","R");	
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; y2[k]=0; ex[k]=0; ey[k]= 0; ey2[k]=0;} // initiate vectors		
	}





if (argc>7)
	{
	ifstream *in7 = new ifstream(file7);
	if(!*in7) 
		{cout << " ERROR OPENING FILE " <<  file7 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in7->eof())
			{
			*in7 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==EC) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k]; 
		y[k]=(datay[k])/ref*EC/datax[k]; cout << x[k] <<  " " << y[k] << endl; 
		y2[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]= EC/datax[k]*1*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datay[k])));
		ey2[k]=errory2[k];
		}

	TGraphErrors *gr7 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr7->SetMarkerColor(kCyan);
	gr7->SetMarkerStyle(20);
	gr7->SetMarkerSize(1.5);
	gr7->Draw("psame");					// Pinta el gráfico A:marco P=puntos L=linea C=curva			
	delete in7;	
	TLatex *tx7 = new TLatex();
	tx7->SetNDC();
	tx7->SetTextSize(0.04);
	tx7->SetTextColor(kCyan);
	tx7->DrawLatex(0.7,0.15,latex7);
	TF1 *f7 = new TF1("f7",fitf2,20,1400); 
	f7->SetParameter(0,1);				
	f7->SetParameter(1,1);				
	f7->SetParameter(2,1);	
	f7->SetParameter(3,5);
	f7->SetParameter(4,-0.15);
	f7->SetLineColor(kCyan);
	f7->SetLineStyle(9);
	//gr7->Fit("f7","R");	
	}













	
/*
gr1->Fit("f1","R+");
d=f1->GetParameter(0);
f=f1->GetParError(0);

TSpline3 *s = new TSpline3("grs",gr1,"0",2000,200);
s->Draw("Csame");
TF1 *f1 = new TF1("f1",fitf,20,1400); 
f1->SetParameter(0,-900);				
f1->SetParameter(1,0.005);				
f1->SetParameter(2,-0.01);	
f1->SetParameter(3,1);
f1->SetParameter(4,0.001);
f1->SetLineColor(kRed);
gr1->Fit("f1","R");	
*/


gStyle->SetOptTitle(0);   
gStyle->SetOptFit(0);         
gStyle->SetOptStat(0);  
					
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;




}
