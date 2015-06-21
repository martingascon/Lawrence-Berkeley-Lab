//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define N 10000 	// Maximum number of data to represent				 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

// DECLARATION OF VARIABLES
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];  //  
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N]; 		      
Int_t i,k;  
char file[100],serie1[100]="serie 1",serie2[100]="serie 2";
//char fitf[100]="[0]+[1]*exp(-x*[2])";  
char fitf[100]="([0]+[1]*TMath::Log(x*[2]))*[3]+[4]";  

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
//vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);
/*
TH1F *hr = c1->DrawFrame(0,0,100,8000);      
hr->SetXTitle("Time (minutes)");		 
hr->SetYTitle("Photopeak Channel");   	     
hr->GetXaxis()->CenterTitle();			 
hr->GetYaxis()->CenterTitle();			 	
*/

switch (argc)
	{
	case 2: sprintf(file,"%s.txt",argv[1]);                // Filename file for transmission
                break;
	case 4: sprintf(file,"%s.txt",argv[1]);
		sprintf(serie1,"%s",argv[2]);
		sprintf(serie2,"%s",argv[3]);	
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
	i=0;
	while (!in->eof())
		{
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
//TGraphErrors *gr2 = new TGraphErrors(k,x,y2,ex,ey2);			// Declaración del gráfico 2.

TF1 *f1 = new TF1("f1",fitf,0.01,70000); 
f1->SetParameter(0,3280);				
f1->SetParameter(1,60);
f1->SetParameter(2,0.001);
f1->SetParameter(3,0.1);
f1->SetParameter(4,10);
/*
TF1 *f2 = new TF1("f2",fitf,6,75); 
f2->SetParameter(0,5200);				
f2->SetParameter(1,6);
f2->SetParameter(2,0.05);
*/
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(20);
gr1->SetMarkerSize(1.5);
gr1->SetLineColor(2);					
gr1->SetLineWidth(2);				// Line color 0=white 1=black, 2=red
gr1->GetXaxis()->SetTitle("Time (s)");		 
gr1->GetYaxis()->SetTitle("Photopeak Channel");   	     
gr1->GetXaxis()->CenterTitle();			 
gr1->GetYaxis()->CenterTitle();	
gr1->GetYaxis()->SetTitleOffset(1.25);
gr1->GetXaxis()->SetTitleOffset(1.25);

gr1->Draw("AP");					// Pinta el gráfico A:marco P=puntos L=linea C=curva
//gr2->SetMarkerColor(kRed);
//gr2->SetMarkerStyle(21);
//gr2->SetMarkerSize(1.5);
//gr2->Draw("p");


gr1->Fit("f1","R+");
//gr2->Fit("f2","R+");
gr1->Fit("f1","R");

/*
TLegend *legend=new TLegend(0.54,0.61,0.91,0.86);	// Declaración de la leyenda
legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
legend->AddEntry(gr2,serie2,"p");

//sprintf(ar,"",a,b);  				// Introduce una leyenda con datos
//legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda

legend->Draw();	*/

theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
