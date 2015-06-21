//************** Copyright: Martin Gascon. LBNL ***************************************
//YOKOGAWA DL 6154 
//included libraries    
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
using namespace std;  			//std contains all the classes, objects and functions of the standard C++ library.
#define N 2500			       // maximum number of data per pulse
using namespace std;
int main(int argc, char **argv)
{
//********************************** VARIABLE DECLARATION ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t datay[N],x[N],y[N],ysum[N],yn[N],e,g,tp=0,la=0,lb=0,zero=0,HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0, max[N],area[N],bs=0,aux=0,Aprom=0,DTprom=0,eprom=0.2,dy[2000];

//ofstream *out = new ofstream("AddedPulse.txt",ios::app);
Int_t i,j,k,ini=0,fin=0,pulTrue=1,rt=0,shift=0,truepul=0;  			
char tit[100]="",xaxis[100]="time (#mus)",yaxis[100]="voltage (a.u.)",*sepa,file[100],ci[100]="",bq[100]="";
char fitf[100]="[0]+[1]*exp(x*[2])";

Char_t fitf1[100]="[0]+exp([1]+x*[2])";
Char_t fitf2[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])";
Char_t fitf3[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])";
Char_t fitf4[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])+exp([7]+x*[8])";
Char_t fitf5[100]="[0]+exp([1]+x*[2])+exp([3]+x*[4])+exp([5]+x*[6])+exp([7]+x*[8])+exp([9]+x*[10])";

Float_t xmin=0.06,xmax=40;

sprintf(bq,"HUnit");



TCanvas *c1 = new TCanvas("c1","Graph2D example",200,10,1200,400);   
c1->SetFillColor(0);   c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1); c1->GetFrame()->SetBorderSize(10);
c1->Divide(2,1);


gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0); 
gStyle->SetOptFit(0);  
gStyle->SetOptTitle(0);  



TH1I *H = new TH1I("H","H",N,10,70);  // declaration of the histogram	 
switch (argc)		
	{case 1:MsgError();	exit(1);
		break;	
	case 2: sprintf(file,"%s.csv",argv[1]);
		break;
	case 3: sprintf(file,"%s.csv",argv[1]);	
		tp=atoi(argv[2]);
		break;
	case 5: sprintf(file,"%s.csv",argv[1]);
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
		pulTrue=1;
		bs = 0;                                      	// by default it is a good pulse. (0 bad pulse)		
		*in >> ci;						// cout << ci << endl;  //read block line
		for (i=0;i<N;i++)
 			{
			*in >> ci; 
			sepa=strtok(ci,","); k=0;			//cout << ci << endl;
			while (sepa != NULL)
				{
				if (k==0) datay[i]=atof(sepa); //cout << datay[i] << endl;
				sepa = strtok(NULL,",");
				k++;
				}
			}
		
		aux = 0;
		//for (i=0;i<200;i++)  aux=aux+datay[i]*1000; 	  // I obtain the baseline
		//bs=aux/200; 	cout << " BL = " << bs << " mV " << endl;
		//bs=-1000;				  // Baseline averaging 100 channels

		max[j]=0,area[j]=0; 
		for (i=0;i<(N-1);i++)                                 
			{
			x[i]=(HOff+i*HRes)*1000000;		// convert to us
			y[i]=-datay[i]*1000+0.1;//-bs;//-bs; 		// convert to mV and substract the baseline already in mV	
			if (max[j]<y[i]) max[j]=y[i];		// find the max value in y
			}
 		//cout << " max = "<< max[j] << endl;
		

		rt=0;
		if (bs<-1) pulTrue=0;  
		if (bs>1) pulTrue=0;  
		for (i=0;i<(N-1);i++) 	yn[i]=y[i]/max[j];   			//  NORMALIZE THE PULSE.                          
		for (i=0;i<(N-1);i++)    if (yn[i]>0.5) {rt=i; i=N;}		//  CALCULATES THE MIDDLE POINT OF THE RISE TIME.   
		//for (i=0;i<(900);i++)  if (yn[i]>0.3) pulTrue=0;   		//  DISCARD ALL PULSES TRIGGERING BEFORE 100 X 2 ns = 200 ns.             
		for (i=250;i<(260);i++)  if (yn[i]<0.2) pulTrue=0; 
		for (i=300;i<2500;i++) if (yn[i]>0.15) pulTrue=0; 
		//if (max[j]<300.0) pulTrue=0; 				 	//  DISCARD ALL PULSES WHOSE AMP IS LOWER THAN (mV)
		shift=rt-zero;
		cout << "n= " << j << "  s= "<< shift << " rt= "<< rt << endl;
		if (shift>150) pulTrue=0;					//  DISCARD ALL PULSES triggering before (channels)
		if (shift<-150) pulTrue=0;					//  DISCARD ALL PULSES triggering after (channels)
		//if (area[j]<0) pulTrue=0;
		
		if (pulTrue==1)
			{
			if (shift>-0.00000001)					//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{						// SHIFT>0 MEANS THAT THE PULSE TRIGGERED BEYOND 0	
				for (i=0;i<N-shift;i++)   yn[i]=yn[i+shift];    // PUT THE PULSE IN 0
				for (i=N-shift;i<N;i++)   yn[i]=0;              // FILL WITH ZEROS    
				}
			if (shift<=0)						//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{
				for (i=0;i<-shift;i++)     yn[i]=0;             // FILL WITH ZEROS    
				for (i=-shift;i<N;i++)     yn[i]=yn[i+shift];   // PUT THE PULSE In 0         		
				}
			TGraph *gr2 = new TGraph(N-1,x,yn);
			la = 0; lb = 200;	
			//la=(HOff+rt*HRes)*1000000;lb=(HOff+(rt+200)*HRes)*1000000;
			TF1 *f2 = new TF1("f2",fitf,la+0.1,lb); 
			//if (truepul==0) {

			f2->SetParameter(0,-2e-06);	 f2->SetParameter(1,4e-6);  f2->SetParameter(2,-0.03);//}
			//gr2->Fit("f2","R");
			e=f2->GetParameter(2);  	g=f2->GetParError(2); 
			e=-1/e;		cout << "fit  =" << e << " us"<< endl;		
			
			dy[truepul]=e;			
			if (truepul==5)  eprom=DTprom/truepul;
			//if ((e>eprom*0.10)&&(e<eprom*50))
				//{
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
				cout <<"A= "<<area[j]<< "| Amax = "<<max[j]<< "| Sft= " <<shift<< "| D.Time= "<< e << "| #: " <<j<< endl;
				H->Fill(e);
				//}
			}
		}    
	///////////////////////////////////////////////////////////////////////// PULSE OUT
	//for (i=0;i<(N-1);i++)      
	//	*out << x[i] << "	" << ysum[i] << endl;
	///////////////////////////////////////////////////////////////////////// PULSE OUT


	

	c1->cd(2);
	Float_t sig=0,prome=0;
	for (j=0;j<truepul;j++) 
		prome=prome+dy[j];
	prome=prome/truepul;
	for (j=0;j<truepul;j++) 
		sig=sig+(dy[j]-prome)*(dy[j]-prome);
	sig=sqrt(sig/truepul);
	cout << "sigma is " << sig << endl;
	
	aux=0;
	for (i=0;i<200;i++)  aux=aux+ysum[i]; 	  // I obtain the baseline
	bs=aux/200; 	cout << " BL = " << bs << " mV " << endl;

	for (i=0;i<(N-1);i++)                                 
			{
			ysum[i]=ysum[i]-bs;//-bs; 		// convert to mV and substract the baseline already in mV	
			}
	TGraph *gr1 = new TGraph(N-1,x,ysum);
	gr1->SetLineColor(4); 	gr1->SetLineWidth(1);  gr1->SetMarkerColor(4); 	gr1->SetMarkerStyle(19);
	sprintf(tit,"temp = %.0f K",tp);						
	gr1->SetTitle(tit);
	gr1->GetXaxis()->SetTitle(xaxis);  	gr1->GetYaxis()->SetTitle(yaxis);			
	gr1->GetXaxis()->CenterTitle();	        gr1->GetYaxis()->CenterTitle();			
	gr1->Draw("ALP");  
	gPad->SetLogy();
	la = 0; lb = 300;
///////////////////////////////////////////////////////decay time calculation	
	
	TF1 *e3 = new TF1("e3","expo(0)+expo(2)+expo(4)",xmin,xmax);
	TF1 *f3 = new TF1("f3",fitf3,xmin,xmax);


	gr1->Fit(e3,"NQR+");
	Float_t e3_p0 = e3->GetParameter(0);
	Float_t e3_p1 = e3->GetParameter(1);
	Float_t e3_p2 = e3->GetParameter(2);
	Float_t e3_p3 = e3->GetParameter(3);
	Float_t e3_p4 = e3->GetParameter(4);
	Float_t e3_p5 = e3->GetParameter(5);

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
	gr1->Fit("f3","R"); f3->Draw("same");

	Float_t f3_p0 = f3->GetParameter(0);
	Float_t f3_p1 = f3->GetParameter(1);  
	Float_t f3_p2 = f3->GetParameter(2);
	Float_t f3_p3 = f3->GetParameter(3);  
	Float_t f3_p4 = f3->GetParameter(4);
	Float_t f3_p5 = f3->GetParameter(5);
 	Float_t f3_p6 = f3->GetParameter(6);

 	Float_t f3_p0e = f3->GetParError(0);
	Float_t f3_p1e = f3->GetParError(1);
	Float_t f3_p2e = f3->GetParError(2);
	Float_t f3_p3e = f3->GetParError(3);
	Float_t f3_p4e = f3->GetParError(4);
	Float_t f3_p5e = f3->GetParError(5);
	Float_t f3_p6e = f3->GetParError(6);
	
	PrintLatex2(Form("#tau_{1} = (%.0f #pm %.1f)  ns",-1/f3_p6*1000,f3_p6e/(f3_p6*f3_p6)*1000),0.60,0.85,1);
	PrintLatex2(Form("#tau_{2} = (%.0f #pm %.0f)  ns",-1/f3_p4*1000,f3_p4e/(f3_p4*f3_p4)*1000),0.60,0.78,1);
	PrintLatex2(Form("#tau_{3} = (%.0f #pm %.0f)  ns",-1/f3_p2*1000,f3_p2e/(f3_p2*f3_p2)*1000),0.60,0.71,1);


///////////////////////////////////////////////////////rise time calculation		
/*	Float_t rta=0,rtb=0,rt=0,maxsum=0,ysnor[N];
	for (i=0;i<(N-1);i++)                                 
			if (max[0]<ysum[i]) max[0]=ysum[i];		// find the max value in yn
	for (i=0;i<(N-1);i++) 	ysnor[i]=ysum[i]/maxsum;   		//  NORMALIZE THE YN PULSE.    
   	for (i=0;i<(1500);i++) 
 		if (ysnor[i]>0.1) {rta=x[i]; i=1500;} 
	for (i=0;i<(1500);i++) 
 		if (ysnor[i]>0.9) {rtb=x[i]; i=1500;} 
	cout << "rta= "<< rta << " rtb = "<< rtb << endl;
	TF1 *f2 = new TF1("f2",fitf,rta,rtb); 	
	gr1->Fit("f2","NQR");
	rt=f2->GetParameter(0);
	//rt=rt*maxsum;
  	//cout << " Rise time= " << rt << endl; */
//////////////////////////////////////////////////////////// total function fit



//////////////////////////////////////////////////////////// 
	PrintLatex2(Form("Sum of all pulses",truepul),0.40,0.95,1);
	c1->cd(1);
	PrintLatex2(Form("%.0d pulses",truepul),0.40,0.95,1);

	cout << "True pulses ="<< truepul << " Aprom =" << Aprom/truepul << " DTprom =" << DTprom/truepul << endl;
	c1->cd(0);

	}


delete in; 
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;
}
