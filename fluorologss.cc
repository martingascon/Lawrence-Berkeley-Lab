//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 		// ****** Own functions

#define GRAPH 1

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);   
Int_t i,k,N=2000; 
Float_t data[N],x[N],x2[N],y[N],y2[N],start,stop;  		      
Char_t f[100],f2[100],f3[100],f4[100],f5[100],f6[100],title[150]="",*sepa,scint[10],sample[10],exc[4]; 	             			 
//Char_t fitf[100]="[0]+[1]*exp(-x/[2])";
//Char_t fitf[100]="[0]*exp(-x/[1])";
/*Char_t fitf[100]="[0]+[1]*exp(-x/[2])";
Char_t fitf2[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";
Char_t fitf2b[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";
Char_t fitf2c[100]="[0]+[1]*exp(-x/[2])+[3]*exp(-x/[4])";

//Char_t fitf3[100]="[0]+[1]*exp(-(x-[3])/[2])+[4]*exp(-(x-[6])/[5])+[7]*exp(-(x-[9])/[8])";
Char_t fitf3[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])";


*/
#if GRAPH
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1200,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->Divide(2,1);				




TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
//vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);


TVirtualPad *vp2 =  c1->cd(2);
vp2->SetFillColor(10);
//vp->SetLogy();
vp2->SetBorderSize(2);
vp2->SetFrameFillColor(0);
vp2->SetLeftMargin(.12);
vp2->SetRightMargin(.01);
vp2->SetBottomMargin(.15);
vp2->SetTopMargin(.01);


TLegend *legend=new TLegend(0.60,0.85,0.98,0.95);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

TLegend *legend2=new TLegend(0.60,0.85,0.98,0.95);  
legend2->SetTextFont(62);
legend2->SetTextSize(0.04);
legend2->SetFillColor(0);

TLegend *legend3=new TLegend(0.20,0.20,0.48,0.45);  
legend3->SetTextFont(62);
legend3->SetTextSize(0.04);
legend3->SetFillColor(0);

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);                     			// display stats
gStyle->SetOptFit(0);    					// display fit parameters 1 = on, 0 = off
#endif
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f,"%s.txt",argv[1]);		 	
		break;						 
	case 3: sprintf(f,"%s.txt",argv[1]);			 
		sprintf(f2,"%s.txt",argv[2]);
		break;
	case 5: sprintf(f,"%s.txt",argv[1]);
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		break;
	case 7: sprintf(f,"%s.txt",argv[1]);
		sprintf(f2,"%s.txt",argv[2]);
		sprintf(f3,"%s.txt",argv[3]);
		sprintf(f4,"%s.txt",argv[4]);
		sprintf(f5,"%s.txt",argv[5]);
		sprintf(f6,"%s.txt",argv[6]);
		break;
	default:
		MsgError();
		exit(1);
		break;

	};   

sepa=strtok(argv[1],"_");  
sprintf(scint,"%s",sepa);
cout << "scint = "<< scint << endl;
sepa=strtok(NULL,"_"); 
sprintf(sample,"%s",sepa);
cout << "sample# = "<< sample << endl;
sepa = strtok(NULL,"x_");
sprintf(exc,"%s",sepa);


Read_eFluor(f,data,N,start,stop);
Float_t bline=0;//,bline2=0;

for (k=0;k<30;k++)   // calculate the baseline;
	bline=bline+data[k];  
bline = bline/30;	
cout << "base line: " << bline << " counts" <<endl; 
N=N-2;
Float_t miny=GetMin(data,N);	cout << miny << endl;
Float_t maxy=GetMax(data,N);	cout << maxy << endl;

c1->cd(1);
i=0;
TH1F *H = new TH1F("H",f,N,start,stop);  // declaration of the histogram	 
for (k=start;k<stop+1;k++)			
	{
	x[i]=k;                 
	y[i]=data[i]-bline;
	H->Fill(x[i],y[i]);
	i++;		 
	}
H->SetMarkerColor(7);
H->SetFillColor(0);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);	 
H->GetXaxis()->SetTitleSize(0.06);
H->GetYaxis()->SetTitleSize(0.06);
H->GetXaxis()->SetLabelSize(0.05);
H->GetYaxis()->SetLabelSize(0.05);
H->GetXaxis()->SetTitle("Wavelength (nm)");
H->GetYaxis()->SetTitle("Intensity (a.u.)");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();	
H->GetXaxis()->SetRangeUser(start,stop);
H->GetYaxis()->SetRangeUser(-40,maxy*1.1);
H->Draw();

legend->AddEntry(H,Form("%s @  %s nm exc",scint,exc),"l");
legend->Draw();

c1->cd(2);

Float_t elow=1240/stop,ehigh=1240/start;

i=0;
for (k=start;k<stop+2;k++)			
	{
	x2[i]=(float)1240/k;
	y2[i]=(data[i]-bline)/(k*k);               
	i++;		 
	}

Float_t maxy2=GetMax(y2,N);	cout << maxy2 << endl;
i=0;
for (k=start;k<stop+2;k++)			
	{
	
	y2[i]=y2[i]/maxy2*maxy;               
	i++;		 
	}

TGraph *gr1 = new TGraph(N,x2,y2);		// Graph declaration
gr1->SetLineColor(2);					
gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr1->SetMarkerColor(2);						
gr1->SetMarkerStyle(20);					
gr1->SetTitle(title);					
gr1->GetXaxis()->SetTitle("Energy (eV)");			
//gr1->GetYaxis()->SetTitle("Intensity (a.u.)");				
gr1->GetXaxis()->SetTitleSize(0.06);
gr1->GetYaxis()->SetTitleSize(0.06);
gr1->GetXaxis()->SetLabelSize(0.05);
gr1->GetYaxis()->SetLabelSize(0.05);
gr1->GetXaxis()->CenterTitle();					
gr1->GetYaxis()->CenterTitle();	
gr1->GetXaxis()->SetRangeUser(elow,ehigh);
gr1->GetYaxis()->SetRangeUser(-40,maxy*1.1);
gr1->Draw("AL");

legend2->AddEntry(gr1,Form("%s @  %s nm exc",scint,exc),"l");
legend2->Draw();

c1->cd(0);

/*


if (argc==5)
	{
	Read_2col(f3, x2, data3, N2);		
	//Read_tFluor(f3,data3,N,conv2,at);
	conv2=1;

for (k=0;k<200;k++)   // calculate the risetime
	if (data2[k+2]>(data2[k]*5)) 
		{rtime2=k; k=200;}
cout << "rise time 2: " << rtime2 << endl; 


for (k=0;k<(rtime-2);k++)   // calculate the baseline;
	bline2=bline2+data3[k];  
bline2 = bline2/(rtime2-2);	
cout << "base line 2: " << bline2 << endl; 
*/

/*	TH1F *H2 = new TH1F("H2",f3,N2,-245.6,4856.353125);  // declaration of the histogram	 
	for (k=0;k<N2;k++)			
		{
		//x2[k]=k*conv;                 
		x2[k]=x2[k]+60;		
		//if (pr==0)
		y2[k]=(data3[k]-31.8)*0.5/2.57+0.02;//-bline2;		//-bline2;		// substract the baseline;
		if (y2[k]<0) y2[k]=0;
		H2->Fill(x2[k],y2[k]);	cout << x2[k] << " " << y2[k] << endl;	// fill the histogram
		}
	H2->SetMarkerColor(4);
	H2->SetFillColor(0);
	H2->SetLineColor(4);
	H2->SetLineWidth(2);
	H2->SetMarkerStyle(8);
	H2->SetMarkerSize(1);
	//H2->Draw("same");
	//H2->Scale(0.005);
	//TF1 *f2 = new TF1("f2",fitf2,(rtime2+5)*conv2,b);
	


	TGraph *gr0 = new TGraph(N2-1,x2,y2);		// Graph declaration
	gr0->SetLineColor(kBlue);					
	gr0->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(kBlue);						
	gr0->SetMarkerStyle(20);					
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitleSize(0.06);
	gr0->GetYaxis()->SetTitleSize(0.06);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	gr0->Draw("Lsame");


	TF1 *f2 = new TF1("f2",fitf3,80,5000);
	f2->SetParameter(0,3.5);	
	f2->SetParameter(1,1000);			
	f2->SetParameter(2,4.88);			
	f2->SetParameter(3,400);	
	f2->SetParameter(4,9.75);
	f2->SetParameter(5,17);
	
	gr0->Fit("f2","R+");	
	//f2->SetParameter(3,rtime2*conv2);
	//H2->Fit("f2","NR+");
	legend->AddEntry(H2,Form("%s @ %s nm exc - %s emis",scint,exc,emis),"l");
	legend2->AddEntry(H2,Form("#tau_{1} = (%2.0f #pm %2.0f) ns",f2->GetParameter(5),f2->GetParError(5)),"l");
	legend2->AddEntry(H2,Form("#tau_{2} = (%2.0f #pm %2.0f) ns",f2->GetParameter(3),f2->GetParError(3)),"l");
	legend2->AddEntry(H2,Form("#tau_{3} = (%2.0f #pm %2.0f) ns",f2->GetParameter(1),f2->GetParError(1)),"l");
	}
	



if (argc==7)
	{
	Read_tFluor(f3,data,N,conv,at);
	Read_tFluor(f4,data2,N,conv2,at);
	TH1F *H3 = new TH1F("H3",f3,N,0,ls);  // declaration of the histogram	 
	for (k=0;k<N;k++)			
		{
		x[k]=k*conv;                 
		y[k]=data[k]-data2[k];
		if (y[k]<0) y[k]=0;
		H3->Fill(x[k],y[k]);		// fill the histogram
		}
	Float_t Maxy2 =  GetMax(y,N);
	H3->SetMarkerColor(kBlue);
	H3->SetFillColor(0);
	H3->SetLineColor(kBlue);
	H3->SetLineWidth(2);
	H3->SetMarkerStyle(8);
	H3->SetMarkerSize(1);
	H3->Scale(Maxy/Maxy2);
	H3->Draw("same");

	TF1 *f3 = new TF1("f3",fitf2b,80,6000);
	f3->SetParameter(0,0.01);	
	f3->SetParameter(1,150);			
	f3->SetParameter(2,100);			
	f3->SetParameter(3,110);
	f3->SetParameter(4,450);

	H3->Fit("f3","NR+");
	H3->Fit("f3","NR");
	legend->AddEntry(H3,Form("%s @  %s nm exc - %s emis",scint,exc,emis),"l");
	legend2->AddEntry(H3,Form("#tau_{1} = (%2.0f #pm %2.0f) ns",f3->GetParameter(2),f3->GetParError(2)),"l");
	legend2->AddEntry(H3,Form("#tau_{2} = (%2.0f #pm %2.0f) ns",f3->GetParameter(4),f3->GetParError(4)),"l");

	Read_tFluor(f5,data,N,conv,at);
	Read_tFluor(f6,data2,N,conv2,at);
	TH1F *H4 = new TH1F("H4",f5,N,0,ls);  // declaration of the histogram	 
	for (k=0;k<N;k++)			
		{
		x[k]=k*conv;                 
		y[k]=data[k]-data2[k];
		if (y[k]<0) y[k]=0;
		H4->Fill(x[k],y[k]);		// fill the histogram
		}
	Float_t Maxy3 =  GetMax(y,N);
	H4->SetMarkerColor(kGreen+3);
	H4->SetFillColor(0);
	H4->SetLineColor(kGreen+3);
	H4->SetLineWidth(2);
	H4->SetMarkerStyle(8);
	H4->SetMarkerSize(1);
	H4->Scale(Maxy/Maxy3);
	H4->Draw("same");

	TF1 *f4 = new TF1("f4",fitf2c,80,6000);
	f4->SetParameter(0,0.01);	
	f4->SetParameter(1,150);			
	f4->SetParameter(2,100);			
	f4->SetParameter(3,110);
	f4->SetParameter(4,450);

	H4->Fit("f4","NR+");
	H4->Fit("f4","NR");
	legend->AddEntry(H4,Form("%s @  %s nm exc - %s emis",scint,exc,emis),"l");
	legend2->AddEntry(H4,Form("#tau_{1} = (%2.0f #pm %2.0f) ns",f4->GetParameter(2),f4->GetParError(2)),"l");
	legend2->AddEntry(H4,Form("#tau_{2} = (%2.0f #pm %2.0f) ns",f4->GetParameter(4),f4->GetParError(4)),"l");












	}






legend2->Draw();

*/


#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 
return 0;

}
