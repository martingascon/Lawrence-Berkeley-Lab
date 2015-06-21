//************** Copyright: Martin Gascon. Stanford University ***************************************
//YOKOGAWA DL 6154 
//included libraries    
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define N 2500			       // maximum number of data per pulse
using namespace std;
int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t datay[N],x[N],y[N],ysum[N],yn[N],d,e,f,g,tp=0,la=0,lb=0,zero=0,HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0, max[N],area[N],bs=0,aux=0,Aprom=0,DTprom=0,eprom=0.2,dy[2000];

//ofstream *out = new ofstream("AddedPulse.txt",ios::app);
Int_t i,j,k,m,ini=0,fin=0,pulTrue=1,rt=0,shift=0,truepul=0;  			
char tit[100]="",xaxis[100]="time (#mus)",yaxis[100]="voltage (a.u.)",*sepa,file[100],ci[100]="",bq[100]="",ar[100],fitf[100]="[0]*exp(-x/[1])",fitf2[100]="[0]*exp(x/[1])",fitf3[100]="[0]+[1]*exp(-x/[2])-[3]*exp(-x/[4])",res, dt[100]=" ";
m=sprintf(bq,"HUnit");
TCanvas *c1 = new TCanvas("c1","Graph2D example",200,10,1200,400);   
c1->SetFillColor(0);   c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1); c1->GetFrame()->SetBorderSize(10);
c1->Divide(3,1);


gROOT->SetStyle("Plain"); gStyle->SetOptStat(0); gStyle->SetOptFit(0);  
TH1I *H = new TH1I("H","H",N,0,0.1);  // declaration of the histogram	 
switch (argc)		
	{case 1:MsgError();	exit(1);
		break;	
	case 2: m=sprintf(file,"%s.csv",argv[1]);
		break;
	case 3: m=sprintf(file,"%s.csv",argv[1]);	tp=atoi(argv[2]);
		break;
	case 5: m=sprintf(file,"%s.csv",argv[1]);
		tp=atoi(argv[2]);	ini=atoi(argv[3]);	fin=atoi(argv[4]);
		break;	
       	default:MsgError(); 	exit(1); 
		break;
	};
ifstream *in = new ifstream(file);

for (i=0;i<N;i++) {ysum[i]=0;}
				
if(!*in){
	cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {	
	do	{
		*in >> ci;
		i=1;		
		if ((strstr(ci,bq)!=NULL))	// until it find HUnit
			{
			i=0;	//cout << ci << endl;
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
	zero=-1*HOff/HRes;
	cout << " zero= "<< zero << endl;
	for (j=ini;j<(fin+1);j++) 	
		{
		for (i=0;i<N;i++) {x[i]=0,y[i]=0,yn[i]=0,datay[i]=0;} // initiate the vectors
		area[j]=0;	
		pulTrue=1;                                      // by default it is a good pulse. (0 bad pulse)		
		*in >> ci;					 // cout << ci << endl;  //read the dummy first line
		for (i=0;i<N;i++)
 			{
			*in >> ci; 
			sepa=strtok(ci,","); k=0;		//cout << ci << endl;
			while (sepa != NULL)
				{
				if (k==0) datay[i]=atof(sepa); //cout << datosy[i] << endl;
				sepa = strtok(NULL,",");
				k++;
				}
			}
		//for (i=0;i<100;i++)  aux=aux+datay[i]*1000; 	  // I obtain the baseline
		//bs=aux/100;	//bs=0;				  // Baseline averaging 100 channels
		
		max[j]=0,area[j]=0; 
		for (i=0;i<(N-1);i++)                                 
			{
			x[i]=(HOff+i*HRes)*1000000;		// convert to us
			y[i]=-datay[i]*1000+bs;//+bs;		// convert to mV	
			//cout << " data = "<< y[i] << endl;
			if (max[j]<y[i]) max[j]=y[i];		// find the max value in y
			area[j]=area[j]+y[i];		
			}
 		cout << " max = "<< max[j] << endl;
		rt=0;
		//if (bs<-10) pulTrue=0;  
		//if (bs>10) pulTrue=0;  
		for (i=0;i<(N-1);i++) 	yn[i]=y[i]/max[j];   		//  NORMALIZE THE PULSE.                          
		for (i=0;i<(N-1);i++)   if (yn[i]>0.5) {rt=i; i=N;}	//  CALCULATES THE MIDDLE POINT OF THE RISE TIME.                              
		//for (i=0;i<(100);i++)  	if (yn[i]>0.1) pulTrue=0; 	//  DISCARD ALL PULSES TRIGGERING BEFORE 100 X 2 ns = 200 ns.             
		//for (i=0;i<(100);i++)  	if (yn[i]<-0.1) pulTrue=0; 
		//for (i=1250;i<2500;i++) if (yn[i]>0.7) pulTrue=0; 
		//if (max[j]<300.0) pulTrue=0; 				 //  DISCARD ALL PULSES WHOSE AMP IS LOWER THAN (mV)

		//cout << "s= "<< shift << " "<< rt;
		shift=rt-zero;    	//shift=0; 				//  calculates the shifting
		//if (shift>150) pulTrue=0;				//  DISCARD ALL PULSES triggering before (channels)
		//if (shift<-150) pulTrue=0;				//  DISCARD ALL PULSES triggering after (channels)
		//if (area[j]<0) pulTrue=0;
		
		if (pulTrue==1)
			{
			if (shift>-0.0000001)						//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{						// SHIFT>0 MEANS THAT THE PULSE TRIGGERED BEYOND 0	
				for (i=0;i<N-shift;i++)   yn[i]=yn[i+shift];    // PUT THE PULSE IN 0
				for (i=N-shift;i<N;i++)   yn[i]=0;              // FILL WITH ZEROS    
				}
			if (shift<0)						//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{						// SHIFT<0 MEANS THAT THE PULSE TRIGGERED BEFORE 0				
				for (i=0;i<-shift;i++)     yn[i]=0;             // FILL WITH ZEROS    
				for (i=-shift;i<N;i++)     yn[i]=yn[i+shift];   // PUT THE PULSE In 0         		
				}
			TGraph *gr2 = new TGraph(N-1,x,yn);
			la=(HOff+rt*HRes)*1000000;lb=(HOff+(rt+2000)*HRes)*1000000;
			TF1 *f2 = new TF1("f2",fitf,la+0.03,lb); 
			f2->SetParameter(0,1);	 f2->SetParameter(1,0.4);
			gr2->Fit("f2","QR");
			e=f2->GetParameter(1);  	g=f2->GetParError(1); 
			dy[truepul]=e;			
			if (truepul==5)  eprom=DTprom/truepul;
			if ((e>eprom*0.15)&&(e<eprom*20))
				{
				c1->cd(1);
				if (truepul==0) gr2->Draw("alp");  
				else gr2->Draw("lpSAME");
				for (i=0;i<N;i++)                            	     
					{				
					ysum[i]=ysum[i]+y[i];
					area[j]=area[j]+y[i];
					}
				truepul++;
				DTprom=DTprom+e;
				Aprom=Aprom+area[j];	
				cout << "Area= " << area[j] << "| AMPmax = " << max[j] << "| Shift = " << shift << "| Decay Time ="<< e << "| Entry: " << j << endl;
				H->Fill(e);
				}
			//}			
			}
		}    
	
	//for (i=0;i<(N-1);i++)      
	//	*out << x[i] << "	" << ysum[i] << endl;


	c1->cd(2);
	Float_t sig=0,prome=0;
	for (j=0;j<truepul;j++) 
		prome=prome+dy[j];
	prome=prome/truepul;
	for (j=0;j<truepul;j++) 
		sig=sig+(dy[j]-prome)*(dy[j]-prome);
	sig=sqrt(sig/truepul);
	cout << "sigma es " << sig << endl;
	
	TGraph *gr1 = new TGraph(N-1,x,ysum);
	gr1->SetLineColor(4); 	gr1->SetLineWidth(1);  gr1->SetMarkerColor(4); 	gr1->SetMarkerStyle(19);
	m=sprintf(tit,"temp = %.0f K",tp);						
	gr1->SetTitle(tit);
	gr1->GetXaxis()->SetTitle(xaxis);  	gr1->GetYaxis()->SetTitle(yaxis);			
	gr1->GetXaxis()->CenterTitle();	        gr1->GetYaxis()->CenterTitle();			
	gr1->Draw("ALP");  
	gPad->SetLogy();
	
///////////////////////////////////////////////////////decay time calculation	
	TF1 *f1 = new TF1("f1",fitf,la+0.01,lb); 
	f1->SetParameter(0,1000);	        f1->SetParameter(1,0.400);				
	gr1->Fit("f1","R");
	d=f1->GetParameter(0);  	e=f1->GetParameter(1);  	f=f1->GetParError(0); 	g=f1->GetParError(1);
	if (g<0.01) g=0.01;

///////////////////////////////////////////////////////rise time calculation		
	Float_t rta=0,rtb=0,rt=0,maxsum=0,ysnor[N];
	for (i=0;i<(N-1);i++)                                 
			if (maxsum<ysum[i]) maxsum=ysum[i];		// find the max value in yn
	for (i=0;i<(N-1);i++) 	ysnor[i]=ysum[i]/maxsum;   		//  NORMALIZE THE YN PULSE.    
   	for (i=0;i<(1500);i++) 
 		if (ysnor[i]>0.1) {rta=x[i]; i=1500;} 
	for (i=0;i<(1500);i++) 
 		if (ysnor[i]>0.9) {rtb=x[i]; i=1500;} 
	cout << "rta= "<< rta << " rtb = "<< rtb << endl;
	TF1 *f2 = new TF1("f2","pol1",rta,rtb); 	
	gr1->Fit("f2","R");
	rt=f2->GetParameter(0);
	//rt=rt*maxsum;
  	//cout << " Rise time= " << rt << endl; 
//////////////////////////////////////////////////////////// total function fit
	
	Float_t f3a,f3b,f3c,f3d,f3e;
	TF1 *f3 = new TF1("f3",fitf3,rta,lb); 
	f3->SetParameter(0,0);	        
	f3->SetParameter(1,e);				
	f3->SetParameter(2,f);	
	f3->SetParameter(3,200);	
	f3->SetParameter(4,0.05);
	f3->SetLineColor(kRed);	
	f3->SetLineWidth(3);	
	gr1->Fit("f3","R");
	f3a=f3->GetParameter(0);  	
	f3b=f3->GetParameter(1);  	//f=f1->GetParError(0); 	g=f1->GetParError(1);
	f3c=f3->GetParameter(2);
	f3d=f3->GetParameter(3);
	f3e=f3->GetParameter(4);
	

	cout << "f3a= "<< f3a << " f3b = "<< f3b << " f3c= "<< f3c << " f3d = "<< f3d << " f3e= "<< f3e << endl;
	cout << " Decay time= " << f3c*1000 << " ns " <<endl; 
	cout << " Rise time= " << f3e*1000 << " ns " <<endl; 

//////////////////////////////////////////////////////////// 

//TF1 *f4 = new TF1("f4","158*exp(-x/0.48)-200*exp(-x/0.05)",-0.03,4); 
//f4->Draw("same");
//f4->SetLineColor(kRed);
//	TF1 *f4 = new TF1("f4",fitf3,rta,lb); 




	TLatex *tx = new TLatex();  tx->SetNDC(); tx->SetTextFont(62); tx->SetTextColor(36); tx->SetTextAlign(12);
	tx->SetTextSize(0.04);      tx->SetTextColor(1);
	m=sprintf(dt,"#tau_{SrI2} = (%.3f #pm %.2f)  #mus",e,g);	
	tx->DrawLatex(0.5,0.7,dt);
	c1->cd(3);
	H->Draw(); H->Rebin(125);
	/*TF1 *f3 = new TF1("f3","landau",0,0.1); 
	f3->SetParameter(0,1);	f3->SetParameter(1,0.4); f3->SetParameter(2,0.007);	
	H->Fit("f3","QR"); 	d=f3->GetParameter(1);	 e=f3->GetParError(1);
	m=sprintf(ar,"#tau_{SrI2}^{MPV}= (%.2f #pm %.2f) #mus",d,e);	// Introduce una leyenda con datos
	tx->DrawLatex(0.5,0.7,ar);	*/
	cout << "True pulses ="<< truepul << " Aprom =" << Aprom/truepul << " DTprom =" << DTprom/truepul << endl;
	}
delete in; 
//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;
}
