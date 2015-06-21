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

Float_t datosy[N],x[N],y[N],la=0,lb=4,e,g, dtimes[N], prom=0, area[N], aprom=0; 		
Int_t i,j,m,pulso,ini=0,fin=0,tot=0,cont=0;  			
char title[100]="", xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)";
char file[100], ci[100]="",bq[100]="",fitf[100]="[0]*exp(-x/[1])",dt[100]=" ";

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1000,600);   
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

gROOT->SetStyle("Plain");
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

	case 6: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		la=atof(argv[4]);lb=atof(argv[5]);
		break;		

       	default:
		MsgError();
		exit(1);
		break;
	};

tot=fin-ini;
if (tot<5)
	{
	c1->Divide(1,(tot+1));
	}
else
	{
	if (tot<10)
		c1->Divide(2,tot/2+1);
	else
		c1->Divide(4,tot/4+1);
	}
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
		for (i=0;i<N;i++)                                 
			{
			x[i]=(HOff+i*HRes)*1000000;// convert to us
			y[i]=-datosy[i]*1000;	   // convert to mV	
			//if (fin==-1) y[i]=-y[i];			
			area[j]=area[j]+y[i];
			}   

		TGraph *gr1 = new TGraph(N-1,x,y);
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
		c1->cd(1+(j-ini));					
		gr1->Draw("ALP");  	
	

		TH1F *H = new TH1F("H",file,N,x[0],x[N-1]);  // declaration of the histogram	 
		for (k=0;k<N;k++)			
			{
			H->SetBinContent(k,y[k]);		// fill the histogram
			}	
		TCanvas *c2 = new TCanvas("c2","Graph2D example",200,10,1000,600);   	
		H->Smooth(160,"R");
		H->Draw();
		

		//TSpline3 *s3 = new TSpline3("s3",gr1->GetX(),gr1->GetY(),gr1->GetN());
   		//s3->SetLineColor(kRed);
   		//gr1->Draw("alp");
  		//s3->Draw("l same");


		if (argc==6)
			{		
			
			TF1 *f2 = new TF1("f2",fitf,la,lb); 
			f2->SetParameter(0,7);	 f2->SetParameter(1,0.5);
			gr1->Fit("f2","QR+");
			gr1->Fit("f2","QR+");
			gr1->Fit("f2","QR");
			e=f2->GetParameter(1);  	g=f2->GetParError(1); 
			if (g<0.01) g=0.01;
			aprom=aprom+area[j];			
			if ((e>0.2)&&(e<1.5)&&cont<10)
		       	 	{
				cout << " Nr: " << cont  << "   prom: " << prom/cont << endl;
				dtimes[cont]=e;
				cont++;
				prom=prom+e;	
				}
			
			if ((e>prom/cont-0.2)&&(e<prom/cont+0.2)&&cont>9)
		       	 	{
				cout << " Nr: " << cont  << "   prom: " << prom/cont << endl;
				dtimes[cont]=e;
				cont++;
				prom=prom+e;	
				}

			TLatex *tx = new TLatex();  tx->SetNDC(); tx->SetTextFont(62); tx->SetTextColor(36); tx->SetTextAlign(12);
			tx->SetTextSize(0.06);      tx->SetTextColor(1);
			m=sprintf(dt,"#tau_{SrI2} = (%.2f #pm %.2f)  #mus",e,g);	
			tx->DrawLatex(0.5,0.3,dt);
			}
   		}    
	}


cout << " pulses: " << cont  << "   area: " << aprom/cont << endl;
/*for (j=0;j<cont;j++) 	
	prom=prom+dtimes[j];
*/
prom=prom/cont;

cout << " pulses: " << cont  << "   prom: " << prom << endl;
delete in; 
//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;


}
