///************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries    
#include "libraries.h" 
#include "functions.h" 

#define N 2500		// maximum number  of data to represent
#define FILES 0		
#define GRAPH 1

using namespace std;  	//std contains all the classes, objects and functions of the standard C++ library.

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
Float_t datay[N],x[N],y[N],ysum[N],yn[N],d,e,f,g,h,l,o,p,h2,l2,tp=0,la=0,lb=0,zero=0,HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0; 
Float_t max[N],area[N],bs=0,aux=0,Aprom=0,DTprom=0,eprom=0.2,dy[2000],dy2[2000],ai=0,as=10;
Int_t i,j,k,m,ini=1,fin=1600,pulTrue=1,rt=0,mx=0,truepul=0,shift=0;  			
Char_t tit[100]="",xaxis[100]="time (#mus)",yaxis[100]="voltage (a.u.)",*sepa,file[100],ci[100]="",bq[100]="",ar[100],file2[100],res, dt[100]=" ";


//ofstream *out = new ofstream("AddedPulse.txt",ios::app);
m=sprintf(bq,"HUnit");


#if GRAPH
TCanvas *c1 = new TCanvas("c1","Graph2D example",200,10,1200,400);   
c1->SetFillColor(0);   c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1); c1->GetFrame()->SetBorderSize(10);
c1->Divide(2,1);
#endif 

//c1->SetLogy();

gROOT->SetStyle("Plain"); gStyle->SetOptStat(0); gStyle->SetOptFit(0);  


switch (argc)		
	{case 1:MsgError();	exit(1);
		break;	
	case 2: m=sprintf(file,"%s.csv",argv[1]); 
		break;
	case 4: m=sprintf(file,"%s.csv",argv[1]);	ini=atoi(argv[2]);	fin=atoi(argv[3]);
		break;	
	case 5: m=sprintf(file,"%s.csv",argv[1]);	ini=atoi(argv[2]);	fin=atoi(argv[3]);  tp=atof(argv[4]);
		break;	
       	default:MsgError(); 	exit(1); 
		break;
	};
ifstream *in = new ifstream(file);          // open the file
for (i=0;i<N;i++) {ysum[i]=0;}
if(!*in){
	cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {	
	while (!in->eof())	
		{    
		*in >> ci;  	*in >> ci;	  *in >> ci;  	*in >> ci;	  // takes away the first line
		*in >> x[i] >> y[i];
		i++;
		}



	for (j=ini;j<(fin+1);j++) 	
		{
		for (i=0;i<N;i++) {x[i]=0,y[i]=0,yn[i]=0,datay[i]=0;} // initiate the vectors
		for (i=0;i<N;i++)
 			{
			*in >> ci; 
			sepa=strtok(ci,","); k=0;		//cout << ci << endl;        // removed comma
			while (sepa != NULL)
				{
				if (k==0) datay[i]=atof(sepa); //cout << datosy[i] << endl;     atof converts character to float
				sepa = strtok(NULL,",");
				k++;
				}
			
			}
		aux=0;		
		for (i=0;i<100;i++)  aux=aux+datay[i]*1000; 	  // I obtain the baseline
		bs=aux/100;	//bs=0;				  // Baseline averaging X channels
		max[j]=0,area[j]=0; 
		
	
		for (i=0;i<(N-1);i++)                                 
			{
						
			x[i]=(HOff+i*HRes)*1000000;		// convert to us
			y[i]=-datay[i]*1000+bs;//+bs;		// convert to mV and invert the signal	
			if (max[j]<y[i]) max[j]=y[i];		// find the max value in y 
			area[j]=area[j]+y[i];			//cout << " Y= "<< y[i] << " x= "<< x[i]<< endl;
		
			
			}

//smoothing		

/*		TH1F *H = new TH1F("H",file,N,x[0],x[N-1]);  // declaration of the histogram	
		for (i=0;i<(N-1);i++)                                 
			{
			H->SetBinContent(i,y[k]);		// fill the histogram
			
			}		

		H->Smooth(16);
		//H->Draw();		
		for (i=0;i<(N-1);i++)  
			{
			y[i]=H->GetBinContent(i);		
			cout << " Y= "<< y[i] << " x= "<< x[i]<< endl;
			}
		H->Delete();	
*/

		rt=0;   
		for (i=0;i<(N-1);i++) 	yn[i]=y[i]/max[j];   		//  NORMALIZE THE PULSE.                          
		for (i=0;i<(N-1);i++)   if (yn[i]>0.3) {rt=i; i=N;}	//  CALCULATES THE MIDDLE POINT OF THE RISE TIME.                              	
		

		//for (i=0;i<(N-1);i++)   if (yn[i]>0.999) {mx=i; i=N;}	//  CALCULATES THE MIDDLE POINT OF THE RISE TIME.		
		
/*		sum11=0,sum21=0;						// start for XFIR for pulse 1.....................
     	   	for (k=0;k<=L;k++)                              	// two first addings
	       	        {
	       	        sum11+=y[k];
	       	        sum21+=y[L+G+k];	
		        }
	
		for (i=0;i<(I-F);i++)                           	//Block displaces I-F times 
	       	        {                                       	// sum2-sum1 gives me the energy
	       	        phi1[i]=(sum21-sum11);                     	// add element on the right
	       	        sum11=sum11+y[i+L+1]-y[i];        		// substract element on the left
	       	        sum21=sum21+y[F+1+i]-y[L+G+i];    		// a sum1 y suma dos, antes que sumar
			}
		Emax1=phi1[0];
		for (k=0;k<(I-F);k++)
	      	   if (Emax1<phi1[k]) 
			{Emax1=phi1[k]; mx=k;}           	 	// calculate the maximum in energy
		//cout <<  "MX=" << mx+F << endl;				// end of XFIR for PULSE 1 ............................
*/
		for (i=0;i<450;i++)  	if (yn[i]>0.2) pulTrue=0; 	// DISCARD ALL PULSES TRIGGERING BEFORE ch xx
		for (i=0;i<2500;i++)  	if (yn[i]<-0.2) pulTrue=0; 

  		//for (i=1500;i<1600;i++) if (y[i]>70) pulTrue=0;  
		//for (i=500;i<800;i++) if (y[i]>3.5) pulTrue=0; 
		//for (i=800;i<1500;i++) if (y[i]>1.5) pulTrue=0;         // it was y[i]>60 for LSO, you can also use yn[i]>0.4
		//for (i=700;i<900;i++) if (yn[i]>0.5) pulTrue=0; 
		for (i=500;i<520;i++) if (yn[i]<0.1) pulTrue=0; 
		for (i=700;i<2000;i++) if (yn[i]>0.6) pulTrue=0;
		for (i=900;i<2000;i++) if (yn[i]>0.4) pulTrue=0; 
		for (i=2000;i<2500;i++) if (yn[i]>0.2) pulTrue=0; 
		//if (mx>90+rt) pulTrue=0; 
		//if (max[j]>Amax) pulTrue=0;
 		//if (max[j]<Amin) pulTrue=0; 
		
		//if (yn[1000]<0.1) pulTrue=0; 
		//cout << " s= "<< shift << "   rt "<< rt<< endl;
		shift=rt-zero;    					//  calculates the shifting
		//shift=shift+mx+F-zero;
		if (shift>250) pulTrue=0;				//  DISCARD ALL PULSES triggering before (channels)
		if (shift<-250) pulTrue=0;				//  DISCARD ALL PULSES triggering after (channels)
		//if (area[j]<0) pulTrue=0;	
		if (pulTrue==1)
			{
			if (shift>0)							//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{							// SHIFT>0 MEANS THAT THE PULSE TRIGGERED BEYOND 0	
				for (i=0;i<N-shift;i++)   y[i]=yn[i+shift]*max[j];    	// PUT THE PULSE IN 0
				for (i=N-shift;i<N;i++)   y[i]=0;              		// FILL WITH ZEROS    
				}
			if (shift<0)							//  ADD ONLY THOSE PULSES THAT FULFILLED THE CONDITION
				{							// SHIFT<0 MEANS THAT THE PULSE TRIGGERED BEFORE 0				
				for (i=0;i<-shift;i++)     y[i]=0;             		// FILL WITH ZEROS    
				for (i=-shift;i<N;i++)     y[i]=yn[i+shift]*max[j];   	// PUT THE PULSE In 0         		
				}
			
			TGraph *gr2 = new TGraph(N-1,x,y); 		// individual graphs 
			gr2->SetLineColor(1); 	gr2->SetLineWidth(0);  gr2->SetMarkerColor(1); 	gr2->SetMarkerStyle(9);
			gr2->GetXaxis()->SetTitle(xaxis);  	gr2->GetYaxis()->SetTitle(yaxis);			
			gr2->GetXaxis()->SetTitleSize(0.05);	gr2->GetYaxis()->SetTitleSize(0.05);	
			gr2->GetXaxis()->CenterTitle();	        gr2->GetYaxis()->CenterTitle();			

			la=(HOff+(rt-shift+20)*HRes)*1000000;lb=(HOff+(rt+1100)*HRes)*1000000;
			
			//#ifdef Elem
				//TF1 *f2 = new TF1("f2",fitf,la,lb);  // for 1 component
				TF1 *f2 = new TF1("f2",fitf4,la,lb);	 // for two components
			//#endif			



			switch (Elem)	// FIT DEPENDING ON ELEMENT	
				{
				case 1: // for CsI(Tl)-1comp
					//la=(HOff+(rt-shift+30)*HRes)*1000000;lb=(HOff+(rt+1900)*HRes)*1000000;
					f2->SetParameter(0,7);	f2->SetParameter(1,1),
					gr2->Fit("f2","QR");
					e=f2->GetParameter(1);  g=f2->GetParError(1); 
					break;	
				case 2: // for CsI(Tl)-2comp

					f2->SetParameter(0,7);	f2->SetParameter(1,0.25),
					f2->SetParameter(2,1);	f2->SetParameter(3,0.90),
					gr2->Fit("f2","QR");
					e=f2->GetParameter(1);  g=f2->GetParError(1); 
					ai=0.01,as=100;						// range of dtime to accept.
					//if ((e>0.001)&&(e<125)&&(h>0.001)&&(h<125))    		// for two components 
					h=f2->GetParameter(3);  l=f2->GetParError(3); 		// for two components 
					break;	
				case 3: // for LaBr3
					la=(HOff+(rt-shift+50)*HRes)*1000000;lb=(HOff+(rt-shift+1550)*HRes)*1000000; 
					f2->SetParameter(0,5);	 f2->SetParameter(1,0.035);
					gr2->Fit("f2","QR");
					e=f2->GetParameter(1);  g=f2->GetParError(1); 
					ai=0.9,as=0.009;
					break;
				case 4: // for LSO 	
					//la=(HOff+(rt-shift+40)*HRes)*1000000;lb=(HOff+(rt+1100)*HRes)*1000000;
					f2->SetParameter(0,1);	 f2->SetParameter(1,0.040);     // first component 40 ns
					f2->SetParameter(2,1);	f2->SetParameter(3,0.007),	 // 2nd component 7 ns
					gr2->Fit("f2","QR");
					e=f2->GetParameter(1);  g=f2->GetParError(1); 	
					h=f2->GetParameter(3);  l=f2->GetParError(3); 		
					///cout << e << " e // h  " << h << endl; 					
					ai=0.03,as=0.06;
					break;	
				};

 			

			m=sprintf(tit,"P = %.0f kpsi",tp);						
			gr2->SetTitle(tit);


			//if ((e>ai)&&(e<as)&&(h>0.001)&&(h<25)) 
				{			
				dy[truepul]=e;	
				dy2[truepul]=h;					// for two components 
				#if GRAPH 
					c1->cd(1);
				#endif
				if (truepul==0) gr2->Draw("alp");  
				else gr2->Draw("lpSAME");
				for (i=0;i<N;i++)                            	     
					{				
					ysum[i]=ysum[i]+y[i];			
					area[j]=area[j]+y[i];
					}

				truepul++;
				cout << "A= " << area[j] << "| AMPmax = " << max[j] << "| Sft = " << shift << "| DT ="<< e << "| Entry: " << j << endl;
				}
			

			}
		}    
	
	//for (i=0;i<(N-1);i++)     *out << x[i] << "	" << ysum[i] << endl;

	#if GRAPH 
		c1->cd(2);
	#endif
	Float_t sig1=0,sig2=0,ave1=0,ave2=0;                	// ave2 is for two components 
 	for (j=0;j<truepul;j++) 
		{
		ave1=ave1+dy[j];			
		 if ((Elem==2)||(Elem==4)) ave2=ave2+dy2[j];  				// for two components 
		}			
	ave1=ave1/truepul;
	if ((Elem==2)||(Elem==4)) 
		ave2=ave2/truepul; 				//cout << "ave= " << ave1 << endl;
	for (j=0;j<truepul;j++) 
		{
		sig1=sig1+(dy[j]-ave1)*(dy[j]-ave1); 		// for two components 
		if ((Elem==2)||(Elem==4)) sig2=sig2+(dy2[j]-ave2)*(dy2[j]-ave2);				
		}
	sig1=sqrt(sig1/truepul); 		
 	if ((Elem==2)||(Elem==4))
		sig2=sqrt(sig2/truepul);				// for two components 								


#if FILES 
	m=sprintf(file2,"DT_output_%d.txt",(int)tp);
	ofstream *out = new ofstream(file2,ios::app); 		// file recording all the centroids and resolution info.
	Float_t xaux=0;
	for (i=0;i<N;i++)     
	 	if (max[0]<ysum[i]) max[0]=ysum[i];		// find the max value in y
	for (i=0;i<N;i++)            
		{	
		xaux=(HOff+i*HRes)*1000000;
		*out << std::fixed << std::setprecision(4) << xaux << "\t" << ysum[i]/max[0]*100 << endl;
		}
#endif

	TGraph *gr1 = new TGraph(N-1,x,ysum);
	gr1->SetLineColor(4); 	gr1->SetLineWidth(1);  gr1->SetMarkerColor(4); 	gr1->SetMarkerStyle(19);
	gr1->GetXaxis()->CenterTitle();	        gr1->GetYaxis()->CenterTitle();		//m=sprintf(tit,"T = %.0f K",tp);	
	m=sprintf(tit,"Entries = %d",truepul);					
	gr1->SetTitle(tit);
	gr1->GetXaxis()->SetTitle(xaxis);  	gr1->GetYaxis()->SetTitle(yaxis);			
	gr1->GetXaxis()->CenterTitle();	        gr1->GetYaxis()->CenterTitle();			
	gr1->GetXaxis()->SetTitleSize(0.05);	gr1->GetYaxis()->SetTitleSize(0.05);	
	gr1->Draw("ALP");  
	gPad->SetLogy();
	
///////////////////////////////////////////////////////decay time calculation	

	//la=(HOff+(rt-shift-30)*HRes)*1000000;lb=(HOff+(rt+1800)*HRes)*1000000;           // when using rise time
	la=(HOff+(rt-shift+50)*HRes)*1000000;lb=(HOff+(rt+2500)*HRes)*1000000;
	
	#ifdef Elem
		TF1 *f1 = new TF1("f1",fitf4,la,lb);  // for 1 component    // fitf = 1 component,fitf3 with Rise time, fitf4 = 2 components ,  fitf5 with traps
		//TF1 *f1 = new TF1("f1",fitf4,la,lb);	 // for two components
	#endif	

	switch (Elem)	// FIT DEPENDING ON ELEMENT	
		{

		case 1: // for CsI(Tl)-1comp
			//la=(HOff+(zero+20)*HRes)*1000000;lb=(HOff+(zero+1800)*HRes)*1000000;
			f1->SetParameter(0,7);	 f1->SetParameter(1,1);
			gr1->Fit("f1","QR");
			e=f1->GetParameter(1);  g=f1->GetParError(1); 
			break;	

		case 2: // for CsI(Tl)-2comp
			//la=(HOff+(zero+20)*HRes)*1000000;lb=(HOff+(zero+1800)*HRes)*1000000;
			f1->SetParameter(0,7);	 f1->SetParameter(1,1);
			f1->SetParameter(2,4); f1->SetParameter(3,0.06);				//  for two components	
			gr1->Fit("f1","QR");
			e=f1->GetParameter(1);  g=f1->GetParError(1); 
			h=f1->GetParameter(3);  l=f1->GetParError(3); 		//  for two components
			break;	
		case 3: // for LaBr3
			//la=(HOff+(zero+100)*HRes)*1000000;lb=(HOff+(zero+950)*HRes)*1000000;
			//la=(HOff+(rt+200)*HRes)*1000000;lb=(HOff+(rt+1300)*HRes)*1000000;
			f1->SetParameter(0,5);	 f1->SetParameter(1,0.024);	
			gr1->Fit("f1","QR");
			e=f1->GetParameter(1);  g=f1->GetParError(1); 
			break;
		case 4: // for LSO 	
			//la=(HOff+(rt-shift+2)*HRes)*1000000;lb=(HOff+(rt+1600)*HRes)*1000000;
			f1->SetParameter(0,7000);	 f1->SetParameter(1,0.04);	
			f1->SetParameter(2,5300); f1->SetParameter(3,0.009); // 	f1->SetParameter(4,0.006);	
			gr1->Fit("f1","QR");
			e=f1->GetParameter(1);  g=f1->GetParError(1); 
			h=f1->GetParameter(3);  l=f1->GetParError(3); 		 
			break;	
		};

	
	gr1->Fit("f1","QR");
	d=f1->GetParameter(0); 	f=f1->GetParError(0);	e=f1->GetParameter(1); 	g=f1->GetParError(1);
	if ((Elem==2)||(Elem==4))	{	
			h=f1->GetParameter(3); 		
			l=f1->GetParError(3);		
			o=f1->GetParameter(2); 	
			p=f1->GetParError(2);               
			}			
	if (g<0.01) g=0.01;
	

	TLatex *tx1 = new TLatex();
	tx1->SetNDC();
	tx1->SetTextSize(0.04);
	tx1->SetTextColor(kBlack);
	char latex1[100];

	switch (Elem)	// LEYEND
		{


		case 1: // for CsI(Tl)-1comp
			m=sprintf(latex1,"#tau_{1} = (%0.2f #pm %0.2f) #mus ",e,g);
			tx1->DrawLatex(0.6,0.80,latex1);
			#if GRAPH
			c1->cd(1);
			#endif
			m=sprintf(latex1,"#tau_{1} = (%0.1f #pm %0.1f) ns ",ave1*1000,sig1*1000);
			tx1->DrawLatex(0.6,0.80,latex1);
			break;	
		case 2: // for CsI(Tl)-2comp
			m=sprintf(latex1,"#tau_{1} = (%0.2f #pm %0.2f) #mus    I_{1} = (%0.1f #pm %0.1f) %%",e,g,d/(d+o)*100,d/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);
			tx1->DrawLatex(0.4,0.80,latex1);
			m=sprintf(latex1,"#tau_{2} = (%0.2f #pm %0.2f) #mus    I_{2} = (%0.1f #pm %0.1f) %%",h,l,o/(d+o)*100,o/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);	
			tx1->DrawLatex(0.4,0.70,latex1);	
			#if GRAPH
			c1->cd(1);
			#endif
			m=sprintf(latex1,"#tau_{1} = (%0.3f #pm %0.3f) #mus ",ave1,sig1);
			tx1->DrawLatex(0.6,0.80,latex1);
			m=sprintf(latex1,"#tau_{2} = (%0.3f #pm %0.3f) ns ",ave2,sig2);	//  for two components	
			tx1->DrawLatex(0.6,0.70,latex1);				//  for two components		
			break;	
		case 3: // for LaBr3
			m=sprintf(latex1,"#tau_{1} = (%0.2f #pm %0.2f) #mus    I_{1} = (%0.1f #pm %0.1f) %%",e,g,d/(d+o)*100,d/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);
			tx1->DrawLatex(0.4,0.80,latex1);
			#if GRAPH
			c1->cd(1);
			#endif
			m=sprintf(latex1,"#tau_{1} = (%0.1f #pm %0.1f) #mus ",ave1*1000,sig1*1000);
			tx1->DrawLatex(0.6,0.80,latex1);
			break;
		case 4: // for LSO 	
			m=sprintf(latex1,"#tau_{1} = (%0.1f #pm %0.1f) ns    I_{1} = (%0.1f #pm %0.1f) %%",e*1000,g*1000,d/(d+o)*100,d/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);
			tx1->DrawLatex(0.4,0.80,latex1);
			m=sprintf(latex1,"#tau_{2} = (%0.1f #pm %0.1f) ns    I_{2} = (%0.1f #pm %0.1f) %%",h*1000,l*1000,o/(d+o)*100,o/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);		
			tx1->DrawLatex(0.4,0.75,latex1);	
		      //m=sprintf(latex1,"#tau_{r} = (%0.1f #pm %0.1f) ns    I_{r} = (%0.1f #pm %0.1f) %%",h2*1000,l2*1000,o/(d+o)*100,o/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100);		 				//tx1->DrawLatex(0.4,0.85,latex1);
			m=sprintf(latex1,"I_{2}/I_{1} = (%0.3f #pm %0.3f)",o/d,o/d*sqrt(f*f/(d*d)+p*p/(o*o)));		//  for two components	
			tx1->DrawLatex(0.6,0.65,latex1);
			#if GRAPH
			c1->cd(1);
			#endif
			m=sprintf(latex1,"#tau_{1} = (%0.1f #pm %0.1f) ns ",ave1*1000,sig1*1000);
			tx1->DrawLatex(0.6,0.80,latex1);
			m=sprintf(latex1,"#tau_{2} = (%0.1f #pm %0.1f) ns ",ave2*1000,sig2*1000);	//  for two components	
			tx1->DrawLatex(0.6,0.70,latex1);				//  for two components		
			break;	
		};





	//gr2->SetTitle(tit);
///////////////////////////////////////////////////////rise time calculation		
/*	Float_t rta=0,rtb=0,rt=0,maxsum=0,ysnor[N];
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
	rt=f2->GetParameter(0);*/



/*
	
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

	TLatex *tx = new TLatex();  tx->SetNDC(); tx->SetTextFont(62); tx->SetTextColor(36); tx->SetTextAlign(12);
	tx->SetTextSize(0.04);      tx->SetTextColor(1);
	m=sprintf(dt,"#tau_{SrI2} = (%.3f #pm %.2f)  #mus",e,g);	
	tx->DrawLatex(0.5,0.7,dt);*/
	//cout << "Valid pulses ="<< truepul << "  " << latex1 << endl;


#if FILES 
	ofstream *out2 = new ofstream("DTvsP.txt",ios::app); // file recording all the decay times as function of T
	//ofstream *out2b = new ofstream("DTvsP2.txt",ios::app); // file recording all the decay times as function of T      only for rise time
	//*out2 <<  tp << std::fixed << std::setprecision(1) <<"\t0.1\t" << ave1*1000 << "\t" << sig1*1000 << endl;  // *1000 is in ns
	//*out2 <<  tp << std::fixed << std::setprecision(2) <<"\t0.1\t" << ave1 << "\t" << sig1 << "\t" << ave2 << "\t" << sig2 <<endl; // for CsI(Tl)
	*out2 <<  tp << std::fixed << std::setprecision(2) <<"\t0.1\t" << e*1000 << "\t" << g*333 << "\t" << h*1000 << "\t" << l*3000 <<endl; // for lso
	//*out2b <<  tp << std::fixed << std::setprecision(2) <<"\t0.1\t" << h2*1000 << "\t" << l2*1000 << "\t" << d/(d+o)*100 << "\t" << d/(d+o)*sqrt(f*f/(d*d)+p*p/(o*o))*100 <<endl; 
	
	ofstream *out3 = new ofstream("TruePulses.txt",ios::app); // file recording number of pulses as function of T
	*out3 <<  tp << std::fixed << std::setprecision(1) <<"\t0.1\t" << truepul << "\t" << endl;
#endif
	
cout << "True pulses ="<< truepul << " Aprom =" << Aprom/truepul << " DTprom =" << DTprom/truepul << endl;
	}
delete in; 	

#if GRAPH				
	c1->cd(0);
	theApp->Run(kTRUE);						
	delete theApp;
#endif 
return 0;
}
