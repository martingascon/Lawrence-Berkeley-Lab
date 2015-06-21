//************** Copyright: Martin Gascon. Stanford University ***************************************
//Este programa representa un pulso del osciloscopio YOKOGAWA DL 6154 
//included libraries    

#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.


#define N 2500				       // maximum number of data per pulse
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t datosy[N],x[N],y[N]; 		
Int_t i,j,m,pulso,ini=0,fin=0,tot=0;  			
char title[100]="", xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)";
char file[100], ci[100]="",bq[100]="";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,600,400);   
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

gROOT->SetStyle("Default");
//gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


switch (argc)		
	{
	case 1: MsgError();
		exit(1);
		break;	
	case 2: m=sprintf(file,"%s.csv",argv[1]);
		break;
	case 3: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=ini;
		break;
	case 4: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		break;		
       	default:
		MsgError();
		exit(1);
		break;
	};

pulso=atoi(argv[1]);

ifstream *in = new ifstream(file);
char *sepa;
Int_t k;
Float_t HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0;
m=sprintf(bq,"block%s",argv[2]);
cout << bq << endl;

if(!*in){
	cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {	
		
	do	{
		*in >> ci;
		i=1;		
		if ((strstr(ci,bq)!=NULL))	// until it find blockXX, being XX the pulse number
			{
			i=0;cout << ci << endl;
			}
	
		if ((strstr(ci,"HResolution,")!=NULL))	// to find the horizontal resolution
			{
			sepa=strtok(ci,"HResolution,"); k=0;
			while (sepa != NULL)			
				{
				if (k==0) HRes0=atof(sepa); 
				if (k==1) HRes1=atof(sepa);
				sepa = strtok(NULL,",");
				k++;
				}
			HRes=HRes0*TMath::Power(10,HRes1);
			cout << " Horizontal resolution: "<< HRes << endl;
			}
		if ((strstr(ci,"HOffset,")!=NULL))	// to find the horizontal offset
			{
			sepa=strtok(ci,"HOffset,"); k=0;
			while (sepa != NULL)			
				{
				if (k==0) HOff=atof(sepa); 
				if (k==1) HOff1=atof(sepa);
				sepa = strtok(NULL,",");
				k++;
				}
			HOff=HOff*TMath::Power(10,HOff1);	
			cout << " Horizontal Offset: "<< HOff << endl;
			}		

		}
	while (i!=0);   ///////////////////////////////////////////// read the first lines until it find block
	for (j=ini;j<(fin+1);j++) 	
		{
		*in >> ci;//  cout << ci << endl;
		for (i=0;i<N-1;i++)
 			{
			*in >> ci; 
			sepa=strtok(ci,","); k=0;
			//cout << ci << endl;
			while (sepa != NULL)
				{
				if (k==0) datosy[i]=atof(sepa); //cout << datosy[i] << endl;
				sepa = strtok(NULL,",");
				k++;
				}
			}

		m=sprintf(bq,"block");		
	  

		for (i=0;i<(N-1);i++)                                 
			{
			x[i]=(HOff+i*HRes)*1000000;// convert to us
			y[i]=-datosy[i]*1000;	   // convert to mV	
			}   


		TGraph *gr1 = new TGraph(N-1,x,y);
		gr1->SetLineColor(4);					
		gr1->SetLineWidth(1);				
		gr1->SetMarkerColor(4);					
		gr1->SetMarkerStyle(19);
		m=sprintf(title,"Pulse %d to %d",ini,fin);						
		gr1->SetTitle(title);
		gr1->GetXaxis()->SetTitle(xaxis);			
		gr1->GetYaxis()->SetTitle(yaxis);			
		gr1->GetXaxis()->CenterTitle();				
		gr1->GetYaxis()->CenterTitle();				
		//gr1->GetYaxis()->SetRangeUser(-15,5);				
		//c1->cd(1+(j-ini));					
		if (tot==0)
				{
				gr1->Draw("AL");  				
				tot=1;
				}
   		else		
			{
			gr1->Draw("sameL");
			for (i=0;i<(N*3);i++) k=1; 
			//system("delay(0.01)");
			}  
		//gr1->update();		
		}    
    	//theApp->Run(kTRUE);
	}
delete in; 
//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;


}
