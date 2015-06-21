//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include <math.h> 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define N 10000 				       // Data max number

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t x[N],y[N],ex[N],ey[N], datax[N],datay[N],datay2[N],errorx[N],errory[N],errory2[N],d,f; 		      
Int_t i,k,a=20,b=1400;  
char fitf[100]="sqrt([0]/x+[1])",fitf2[100]="[0]*sqrt([1]/x)";
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100];
char latex1[100];

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
//c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->SetLogx(); 
//c1->SetLogy(); 


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(file1,"%s.txt",argv[1]);		// FILENAME 	
		break;		
	case 3: sprintf(file1,"%s.txt",argv[1]);		// FILENAME 	
		sprintf(file2,"%s.txt",argv[2]);	
		break;		
				 
	case 4: sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
 		sprintf(file2,"%s.txt",argv[2]);	
		sprintf(file3,"%s.txt",argv[3]);
		break;
	case 5: sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.txt",argv[2]);	
		sprintf(file3,"%s.txt",argv[3]);	
		sprintf(file4,"%s.txt",argv[4]);	
	case 6: sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.txt",argv[2]);	
		sprintf(file3,"%s.txt",argv[3]);	
		sprintf(file4,"%s.txt",argv[4]);	
		sprintf(file5,"%s.txt",argv[5]);	
		break;
	case 7: sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		sprintf(file2,"%s.txt",argv[2]);	
		sprintf(file3,"%s.txt",argv[3]);	
		sprintf(file4,"%s.txt",argv[4]);	
		sprintf(file5,"%s.txt",argv[5]);		
		sprintf(file6,"%s.txt",argv[6]);
		break;
	case 8: sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
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
		cout << datay2[i] << endl;
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];   
	y[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]=errory2[k];
	}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(20);
gr1->SetMarkerSize(1.5);
gr1->GetXaxis()->SetTitle("Energy photon (keV)");	
gr1->GetYaxis()->SetTitle("Energy resolution (%)");   	     
gr1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();	
gr1->GetXaxis()->SetTitleOffset(1.2);			
gr1->GetYaxis()->SetTitleOffset(1.2);
gr1->GetXaxis()->SetLabelColor(1);			
gr1->GetYaxis()->SetLabelColor(1);
gr1->GetXaxis()->SetMoreLogLabels();
gr1->SetMarkerColor(kRed);
TAxis *axis = gr1->GetXaxis();
axis->SetLimits(20,1850); // along X 
gr1->Draw("ap");	
	TLatex *tx1 = new TLatex();
	tx1->SetNDC();
	tx1->SetTextSize(0.04);
	tx1->SetTextColor(kRed);
 	tx1->DrawLatex(0.7,0.8,"tx1");
 

TF1 *f1 = new TF1("f1",fitf2,a,b); 
f1->SetParameter(0,3);				
f1->SetParameter(1,1);
f1->SetLineColor(kRed);	
f1->SetLineStyle(9);
Float_t aux=f1->GetParameter(1);
if (aux < 0) aux = 0;
gr1->Fit("f1","R+");
cout << "a= " << sqrt(f1->GetParameter(0)) << ", b= " << sqrt(aux) << endl;


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
			*in2 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k];         
		y[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]=errory2[k];
		}
	
	TGraphErrors *gr2 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
	gr2->SetMarkerColor(kBlue);
	gr2->SetMarkerStyle(20);
	gr2->SetMarkerSize(1.5);
	gr2->Draw("samep");
	
	TLatex *tx2 = new TLatex();
	tx2->SetNDC();
	tx2->SetTextSize(0.04);
	tx2->SetTextColor(kBlue);
 	tx2->DrawLatex(0.7,0.7,"tx2");
	
	TF1 *f2 = new TF1("f2",fitf2,a,b); 
	f2->SetParameter(0,3);				
	f2->SetParameter(1,1);
	f2->SetLineColor(kBlue);
	f2->SetLineStyle(9);
	gr2->Fit("f2","R");


	cout << "a= " << sqrt(f2->GetParameter(0)) << ", b= " << sqrt(f2->GetParameter(1)) << endl;
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
			*in3 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i]; 
			i++;
			}
		while (!in3->eof());
		}
	for (k=0;k<i-1;k++)
		{
		x[k]=datax[k];         
		y[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]=errory2[k];

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
 	tx3->DrawLatex(0.7,0.6,"tx3");
	TF1 *f3 = new TF1("f3",fitf2,a,b); 
	f3->SetParameter(0,3);				
	f3->SetParameter(1,1);				
	f3->SetLineColor(kGreen+3);
	f3->SetLineStyle(9);
	gr3->Fit("f3","R");	
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; ex[k]=0; ey[k]= 0; } // initiate vectors	
	
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
			*in4 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
 		x[k]=datax[k];         
		y[k]=datay2[k];
		ex[k]=errorx[k];         
		ey[k]=errory2[k];

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
	tx4->DrawLatex(0.7,0.5,"tx4");	
	TF1 *f4 = new TF1("f4",fitf2,a,b); 
	f4->SetParameter(0,3);				
	f4->SetParameter(1,1);				

	f4->SetLineColor(kBlack);
	f4->SetLineStyle(9);
	gr4->Fit("f4","R");
	for (k=0;k<i-1;k++) {x[k]=0; y[k]=0; ex[k]=0; ey[k]= 0;} // initiate vectors		

	}



gStyle->SetOptFit(0);             		        
theApp->Run(kTRUE);				
delete theApp;
return 0;
}
