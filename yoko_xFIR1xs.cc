
//************** Copyright: Martin Gascon. Stanford University ***************************************
//Este programa representa un pulso del osciloscopio YOKOGAWA DL 6154 
//included libraries    

#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 





#define N 2500 					// Número máximo de Datos por Canal

using namespace std;

int main(int argc, char **argv)
{//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

char f1[100], ejex[100]="time (channels)",ejey[100]="voltage (V)";
Float_t x[N],datosy[N],datosy2[N]; 
Float_t y1[N],sum11,sum21,phi1[N],Emax1; 
Float_t	y2[N],sum12,sum22,phi2[N],Emax2; 

char title[100]="", xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)";
char file[100], ci[100]="",bq[100]="";
Int_t i,j,k,pulso,ini=0,fin=0,tot=0;  

Int_t I,F, L=50, G=50;



TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1000,400);     //Definición de canvas 400 era 800
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->Divide(2,1);

gROOT->SetStyle("Default");

for (i=0;i<N;i++)    phi1[i]=0;       
for (i=0;i<N;i++)    phi2[i]=0;  
     
//*********************************** Cuerpo del programa   *************************************

if (argc<2){
	cout << "Falta el nombre del archivo a representar" << "\n";
	cout << "************************************************************************" << "\n";
	cout << "pulsoyoko [nombre-fichero][sin extensión] 				 " << "\n";
	cout << "									 " << "\n";
	cout << "******* Copyright: GENP (Univ. Santiago de Compostela) M.Gascón.********" << "\n";
	exit(1);
	}
else 	{
	switch (argc)
		{
		case 2: sprintf(f1,"%s.csv",argv[1]);
			break;

		case 4: sprintf(f1,"%s.csv",argv[1]);
			L=atoi(argv[2]);G=atoi(argv[3]);
			F=2*L+G;
			break;

		};
	}


F=2*L+G; // width of the filter
I=N-F-1; // limit of integration


ifstream *in = new ifstream(f1);
char *sepa;
Float_t HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0;
sprintf(bq,"block%s",argv[2]);
cout << bq << endl;
cout << " Pulses: " << tot+1 << endl;
cout << " L = " << L << " G = " << G << endl;

for (i=0;i<N;i++)     x[i]=0;  

if(!*in){
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
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

	*in >> ci;//  cout << ci << endl;    // throw away the first because it is blockXX
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
			x[i]=i; //  *0.02-50;                           // x está en us 
			y1[i]=datosy[i];


			//cout << x[i] << " =x y= " << y1[i] << endl;		
			}

	sprintf(bq,"block");	
			   

   /*	sum11=0;						// start for XFIR for pulse 1.....................
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
*/
	TGraph *gr1 = new TGraph(N-1,x,y1);
	gr1->SetLineColor(4);					
	gr1->SetLineWidth(1);				
	gr1->SetMarkerColor(4);					
	gr1->SetMarkerStyle(19);
	sprintf(title,"Pulse %d",j);						
	gr1->SetTitle(title);
	gr1->GetXaxis()->SetTitle(xaxis);			
	gr1->GetYaxis()->SetTitle(yaxis);			
	gr1->GetXaxis()->CenterTitle();				
	gr1->GetYaxis()->CenterTitle();			
	//c1->cd(1+(j-ini)*2);					
	//gr1->Draw("AL");  				
 	TGraph *gr2 = new TGraph(I-F,x,phi1);			// Declaración del gráfico.
	gr2->SetLineColor(4);					
	gr2->SetLineWidth(1);					
	gr2->SetMarkerColor(4);					
	gr2->SetMarkerStyle(19);		
	sprintf(title,"XFIR of Pulse %d",j);			
	gr2->SetTitle(title);					
	gr2->GetXaxis()->SetTitle(xaxis);			
	gr2->GetYaxis()->SetTitle("Amplitud (a.u.)");		
	gr2->GetXaxis()->CenterTitle();				
	gr2->GetYaxis()->CenterTitle();				
	//c1->cd(2+(j-ini)*2);
	//gr2->Draw("AL");  		
	c1->cd(1);						// Me cambio al marco 1 en el que se divide el canvas
	gr1->Draw("AL");
	//c1->cd(2);							// Me cambio al marco 2 en el que se divide el canvas
	//gr2->Draw("AL");






	sum11=0;						// comienza XFIR para pulso 1.....................
       	sum21=0;
       	for (k=0;k<=L;k++)                              	// Caculo las dos primeras sumas
       	        {
       	        sum11+=y1[k];
       	        sum21+=y1[L+G+k];	
       	        //sum12+=y2[k];
       	        //sum22+=y2[L+G+k];
	         }

	for (i=0;i<(I-F);i++)                           	//El bloque se deplaza I-F veces 
       	        {                                       	// sum2-sum1 me da la energia
       	        phi1[i]=(sum21-sum11);                     	//le sumo un elemento a la derecha
       	        sum11=sum11+y1[i+L+1]-y1[i];        		//le resto un elemento a la izquierda
       	        sum21=sum21+y1[F+1+i]-y1[L+G+i];    		//a sum1 y suma dos, antes que sumar
       	        //phi2[i+F]=(sum22-sum12);                     	//le sumo un elemento a la derecha
       	        //sum12=sum12+y2[i+L+1]-y2[i];        		//le resto un elemento a la izquierda
       	        //sum22=sum22+y2[F+1+i]-y2[L+G+i];    		//a sum1 y suma dos, antes que sumar

		c1->cd(1);					// Me cambio al marco 1 en el que se divide el canvas
		TGraph *gr4 = new TGraph(I,x,phi1);		// Declaración del gráfico.
		gr4->SetLineColor(2);					// Color de la linea 0=blanco 1=negro, 2=rojo
		gr4->SetLineWidth(1);					// Ancho de la linea
		gr4->SetMarkerColor(2);					// Color del punto 0=blanco 1=negro, 2=rojo
		gr4->SetMarkerStyle(19);				// Estilo del punto 21 = cuadrado
		gr4->SetTitle("FIR pulse");					// Escribe como título del grafico lo que hay en titulo
		gr4->GetXaxis()->SetTitle(ejex);			// Escribe como titulo del eje x lo que hay en ejex
		gr4->GetYaxis()->SetTitle("FIR amplitude (a.u.)");			// Escribe como titulo del eje y lo que hay en ejey
		gr4->GetXaxis()->CenterTitle();				// Para centrar el titulo del eje x
		gr4->GetYaxis()->CenterTitle();	
	
		if (i%19==0) c1->Update();
		Float_t	xb1[4]={L+G+i,F+i,F+i,L+G+i},yb1[4]={-0.02,-0.02,0.25,0.25}; 	
		Float_t	xb2[4]={i,L+i,L+i,i},yb2[4]={-0.02,-0.02,0.25,0.25}; 
		TCutG *g1= new TCutG("corte1",4,xb1,yb1);
		TCutG *g2= new TCutG("corte2",4,xb2,yb2);
		g1->SetFillColor(3); g1->SetFillStyle(3001); //g1->SetLineWidth(1);  		
		g2->SetFillColor(2); g2->SetFillStyle(3001); //g1->SetLineWidth(1);    
		if (i%19==0) g1->Draw("F"); 
		if (i%19==0) g2->Draw("F");
		c1->cd(2);				// Me cambio al marco 1 en el que se divide el canvas
		/*TGraph *gr2 = new TGraph(I-F,x,phi2);
		if (i%20==0) c1->Update();	
		Float_t	xb3[4]={L+G+i,F+i,F+i,L+G+i},yb3[4]={-0.02,-0.02,0.25,0.25}; 	
		Float_t	xb4[4]={i,L+i,L+i,i},yb4[4]={-0.02,-0.02,0.25,0.25}; 
		TCutG *g3= new TCutG("corte3",4,xb3,yb3);
		TCutG *g4= new TCutG("corte4",4,xb4,yb4);
		g3->SetFillColor(2); g3->SetFillStyle(3001); //g1->SetLineWidth(1);    
		g4->SetFillColor(3); g4->SetFillStyle(3001); //g1->SetLineWidth(1);  
		if (i%20==0)  if (i%20==0) g4->Draw("F");//g3->Draw("F");
		if (i%20==0) c1->Update();*/	
		//c1->cd(3);						// Me cambio al marco 1 en el que se divide el canvas
		//if (i%20==0) gr1->Draw("AL");		
		//c1->cd(4);						// Me cambio al marco 1 en el que se divide el canvas
		if (i%19==0) gr4->Draw("AL");c1->Update();
		//gROOT->ProcessLine(".!sleep 0.00005");		
		/*if (i%19==0)
			{Char_t ch[100];
			sprintf(ch,"fig_%04d.png",i);
			c1->Print(ch);
			}	*/			
		}
	Emax1=phi1[0];
	for (k=0;k<(I-F);k++)
      	   if (Emax1<phi1[k]) Emax1=phi1[k];           	 	// calculo el máximo de la energía
	cout << "Emax1: " << Emax1 << endl;			// termina XFIR PARA PULSO 1 ............................
	//Emax2=phi2[0];
	//for (k=0;k<(I-F);k++)
            	//   if (Emax2<phi2[k]) Emax2=phi2[k];     	// calculo el máximo de la energía
	//cout << "Emax2: " << Emax2 << endl;
								// termina XFIR PARA PULSO 2 ............................
	

	c1->cd(0);






	}

theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}

