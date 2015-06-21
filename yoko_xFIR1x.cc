//************** Copyright: Martin Gascon. Stanford University ***************************************
//Este programa representa un pulso del osciloscopio YOKOGAWA DL 6154 
//included libraries    

#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.


#define N 5000				       // maximum number of data per pulse
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t datosy[N],x[N],y[N]; 		
Int_t i,j,k,m,pulso,ini=0,fin=0,tot=0;  			
char title[100]="", xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)";
char file[100], ci[100]="",bq[100]="";

Float_t y1[N],sum11,sum21,phi1[N],Emax1; 
Int_t I=2000, L=50, G=1, F=2*L+G;


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,800,600);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
//c1->Divide(2,2);

/*
gROOT->SetStyle("Plain");
//gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  
*/

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

	case 5: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=ini;
		L=atoi(argv[3]);G=atoi(argv[4]);
		break;
	case 6: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		L=atoi(argv[4]);G=atoi(argv[5]);
		break;		
       	default:
		MsgError();
		exit(1);
		break;
	};

F=2*L+G; // width of the filter
I=N-F-1; // limit of integration


tot=fin-ini;
if (tot<5)
	{
	c1->Divide(1,(tot+1)*2);
	}
else
	{
	if (tot<10)
		c1->Divide(2,(tot/2+1)*2);
	else
		c1->Divide(4,(tot/4+1)*2);
	}
pulso=atoi(argv[1]);

ifstream *in = new ifstream(file);
char *sepa;
Float_t HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0;
m=sprintf(bq,"block%s",argv[2]);
cout << bq << endl;
cout << " Pulses: " << tot+1 << endl;
cout << " L = " << L << " G = " << G << endl;

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
			i=0;//cout << ci << endl;
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
	while (i!=0);   ///////////////////////////////////////////// read the first lines until it find block(ini)


	for (j=ini;j<(fin+1);j++) 	//////// start to read data for each pulse (each j)
		{
		*in >> ci;  cout << "." << endl; //    // throw away the first because it is blockXX
		for (i=0;i<N-1;i++)                  // read 2500 points per pulse
 			{
			*in >> ci; 			// read first number
			sepa=strtok(ci,","); k=0;	// strok the comma from the line
			datosy[i]=atof(sepa);
			}

	
		for (i=0;i<(N-1);i++)      			// load data in x and y1                           
			{
			//x[i]=(HOff+i*HRes)*1000000;// convert to us
			//y1[i]=datosy[i]*1000;	   // convert to mV	
			x[i]=i;
			y1[i]=-datosy[i];
			//cout << x[i] << " =x y= " << y1[i] << endl;		
			}

		m=sprintf(bq,"block");	
			   

   		sum11=0;						// start for XFIR for pulse 1.....................
       		sum21=0;
	   	for (k=0;k<=L;k++)                              	// two first addings
	       	        {
	       	        sum11+=y1[k];
	       	        sum21+=y1[L+G+k];	
		        }
	
		for (i=0;i<(I-F);i++)                           	//Block displaces I-F times 
	       	        {                                       	// sum2-sum1 gives me the energy
	       	        phi1[i]=(sum21-sum11);                     	// add element on the right
	       	        sum11=sum11+y1[i+L+1]-y1[i];        		// substract element on the left
	       	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		// a sum1 y suma dos, antes que sumar
			}
		Emax1=phi1[0];
		for (k=0;k<(I-F);k++)
	      	   if (Emax1<phi1[k]) Emax1=phi1[k];           	 	// calculate the maximum in energy
		cout << "Emax1: " << Emax1 << endl;			// end of XFIR for PULSE 1 ............................

		TGraph *gr1 = new TGraph(N-1,x,y1);
		gr1->SetLineColor(4);					
		gr1->SetLineWidth(1);				
		gr1->SetMarkerColor(4);					
		gr1->SetMarkerStyle(19);
		m=sprintf(title,"Pulse %d",j);						
		gr1->SetTitle(title);
		gr1->GetXaxis()->SetTitle(xaxis);			
		gr1->GetYaxis()->SetTitle(yaxis);			
		gr1->GetXaxis()->CenterTitle();				
		gr1->GetYaxis()->CenterTitle();			
		c1->cd(1+(j-ini)*2);					
		gr1->Draw("AL");  				
 
		TGraph *gr2 = new TGraph(I-F,x,phi1);			// Declaración del gráfico.
		gr2->SetLineColor(4);					
		gr2->SetLineWidth(1);					
		gr2->SetMarkerColor(4);					
		gr2->SetMarkerStyle(19);		
		m=sprintf(title,"XFIR of Pulse %d",j);			
		gr2->SetTitle(title);					
		gr2->GetXaxis()->SetTitle(xaxis);			
		gr2->GetYaxis()->SetTitle("Amplitud (a.u.)");		
		gr2->GetXaxis()->CenterTitle();				
		gr2->GetYaxis()->CenterTitle();				
		c1->cd(2+(j-ini)*2);
		gr2->Draw("AL");  		
		}    
    
	}
delete in; 
//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;


}
