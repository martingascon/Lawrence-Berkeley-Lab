//************** Copyright: Martin Gascon. LBNL *************************************** 
//This program represents pulses from the oscilloscope YOKOGAWA DL 6104 
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

Float_t datosy[N],x[N]; 		
Int_t i,j,k,l,pulso,fini=0,ffin=0,tot=0,Draw=1,Reb=1;  			
char title[100], file[100], ci[100]="",bq[100]="";

Float_t y1[N],sum11,sum21,phi1[N],Emax1; 
Int_t I=2000, L=50, G=1, F=2*L+G;
Float_t Gain=50;//10000/(2*L);  // Gain in the spectroscopic amplifier

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,800,600);     //Definición de canvas
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
//c1->Divide(2,2);


gROOT->SetStyle("Plain");
//gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

TH1I *H1 = new TH1I("H1",file,8192,0,8191); 
//ofstream *out = new ofstream("espectro.mca"); 


switch (argc)		
	{
	case 1: MsgError();
		exit(1);
		break;	
	case 2: sprintf(file,"%s.csv",argv[1]);
		break;
	case 3: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=fini;
		break;
	case 4: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=atoi(argv[3]);
		break;		

	case 5: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=fini;
		L=atoi(argv[3]);G=atoi(argv[4]);
		break;
	case 6: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=atoi(argv[3]);
		L=atoi(argv[4]);G=atoi(argv[5]);
		break;		
	case 7: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=atoi(argv[3]);
		L=atoi(argv[4]);G=atoi(argv[5]);
		Gain=atof(argv[6]);
		break;	
	case 8: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=atoi(argv[3]);
		L=atoi(argv[4]);G=atoi(argv[5]);
		Reb=atoi(argv[6]);
		Gain=atof(argv[7]);
		break;		
 	case 9: sprintf(file,"%s.csv",argv[1]);
		fini=atoi(argv[2]);ffin=atoi(argv[3]);
		L=atoi(argv[4]);G=atoi(argv[5]);
		Reb=atoi(argv[6]);
		Gain=atof(argv[7]);		
		Draw=atoi(argv[8]);
		break;	     	
	default:
		MsgError();
		exit(1);
		break;
	};

F=2*L+G; // width of the filter
I=N-F-1; // limit of integration


tot=ffin-fini;
pulso=atoi(argv[1]);
char *sepa;
Float_t HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0;
sprintf(bq,"block%s",argv[2]);
cout << bq << endl;
cout << " FILES: " << tot+1 << endl;
cout << " L = " << L << " G = " << G << endl;
cout << " Pulses: " << (tot+1)*1600 << endl;



for (l=fini;l<(ffin+1);l++) 	
	{
	cout << "." << endl; 
	sprintf(file,"%s%d.csv",argv[1],l);
	ifstream *in = new ifstream(file);
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
				*in >> ci;//  throw away the units line
				}		
	
			}
		while (i!=0);   ///////////////////////////////////////////// read the first lines until it find block(ini)
	
	
		for (j=0;j<(1600+1);j++) 					//////// start to read data for each pulse (each j)
			{
			*in >> ci;    // 			// throw away the first because it is blockXX
			for (i=0;i<N-1;i++)              			// read 2500 points per pulse
	 			{
				*in >> ci; 					// read first number
				//if ((strstr(ci,"block")!=NULL))	i=N; 
				sepa=strtok(ci,","); k=0;			// strok the comma from the line
				datosy[i]=atof(sepa);
				}
	
		
			for (k=0;k<i;k++)      					// load data in x and y1                           
				{	
				x[k]=(HOff+k*HRes)*1000000;			// convert to us
				//y1[k]=datosy[k]*1000;	   			// convert to mV	
				//x[k]=i;					// convert to us
				y1[k]=-datosy[k];	   			// convert to mV		

				//if ((k%100)==0) cout << x[k] << " =x y= " << y1[k] << endl;		
				}
	
			sprintf(bq,"block");	
				   
	
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
			H1->Fill((Emax1)*Gain);           // lleno el histograma
	
			}    
	    
		}

	delete in; 	
	}


	sprintf(title,"Total pulses %d",(tot+1)*1600);
H1->SetMarkerColor(7);  H1->SetFillColor(0);  H1->SetLineColor(2);  H1->SetLineWidth(1);  H1->SetMarkerStyle(8); H1->SetMarkerSize(1);  H1->SetTitle(title);   
H1->GetXaxis()->SetTitle("Channel");         H1->GetYaxis()->SetTitle(" Counts "); H1->GetXaxis()->CenterTitle(); H1->GetYaxis()->CenterTitle(); 
//H1->Rebin(8); 

c1->cd(1); H1->Draw();
c1->cd(0);
if (Draw!=0)
	{

	sprintf(title,"MCA_L%dG%d_Ga%f.mca",L,G,Gain);
	ofstream *out = new ofstream(title);                 	//genero el fich del espect para guardar datos
 	*out << "<<DATA>>" << endl; 			// para escribir el histograma 1 en un fichero mca llamado espectro
	for (j=0;j<8192;j++)				// para escribir el histograma 1 en un fichero mca llamado espectro
        	*out << H1->GetBinContent(j) << endl;   // para escribir el histograma 1 en un fichero mca llamado espectro	
	*out << "<<END>>" << endl; 	
	}

//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;


}
