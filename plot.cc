//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1
#define FIT 0

int main(int argc, char **argv)
{




// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Int_t i,k,m,col=1,col2=2,col3=2, col4=2, col5=2, col6=2, N=10000;
Float_t x[N],y[N],dx[N],dy[N],y2[N],dy2[N],y3[N],dy3[N],y4[N],dy4[N],I1=0,I2=0,I3=0,I4=0,I5=0,I6=0,I7=0,I8=0,I9=0,aux=0,max=0; 	
Float_t xb[N],yb[N],dxb[N],dyb[N],y2b[N],dy2b[N],y3b[N],dy3b[N],y4b[N],dy4b[N],d,e,f,g,h,l,o,p;
Float_t xc[N],yc[N],dxc[N],dyc[N],y2c[N],dy2c[N],y3c[N],dy3c[N],y4c[N],dy4c[N],norm=1,norm2=1,norm3=1,norm4=1;
Float_t xd[N],yd[N],dxd[N],dyd[N],y2d[N],dy2d[N],y3d[N],dy3d[N],y4d[N],dy4d[N];	      

char title[100]="title",file[100],file2[100],xaxis[100]="Wavelength (nm)",yaxis[100]="Normalized Intensity",*ci;
char file3[100],file4[100],file5[100],file6[100],*sepa,latex1[100],tau1[100],tau2[100],Amp1[100],Amp2[100];
///char fitf4[100]="[0]+[1]*exp(-(x)*[2])"; //
//char fitf4[100]="[0]*exp(-x*[1])";
char fitf4[100]="[0]*exp(-x*[1])+[2]*exp(-x*[3])";
//char fitf[100]= "[0]*(1-exp(-2*[1]*x)/(2*[1]*x))";
//char fitf[100]= "[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))+[3]*exp(-0.5*((x-[4])/[5])*((x-[4])/[5]))";
char fitf[100]= "[0]-[1]*(TMath::Log([2]*x))";
// OUTPUT FILES


TLatex *tx = new TLatex();

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c->cd(1);
vp->SetFillColor(10);
//vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);

TLegend *legend=new TLegend(0.5,0.15,0.88,0.25);  
legend->SetTextFont(62);
legend->SetTextSize(0.04);
legend->SetFillColor(0);

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		col=2;
		break;		
	case 3: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		break;
	case 4: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		norm=atof(argv[3]);	
		break;
	case 5: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);
		m=sprintf(file2,"%s.txt",argv[3]);				// columns 
		col2=atoi(argv[4]);		
		break;
	case 6: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		m=sprintf(file2,"%s.txt",argv[3]); 
		m=sprintf(file3,"%s.txt",argv[4]); 
		m=sprintf(file4,"%s.txt",argv[5]); 
		break;
	case 7: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		norm=atof(argv[3]);	
		m=sprintf(file2,"%s.txt",argv[4]); 
		col2=atoi(argv[5]);		
		norm2=atof(argv[6]);
		break;

	case 8: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);	col2=col;	col3=col;	col4=col;	col5=col;	col6=col;// columns 
		m=sprintf(file2,"%s.txt",argv[3]); 
		m=sprintf(file3,"%s.txt",argv[4]); 
		m=sprintf(file4,"%s.txt",argv[5]); 
		m=sprintf(file5,"%s.txt",argv[6]); 
		m=sprintf(file6,"%s.txt",argv[7]); 
		break;

	case 10: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		norm=atof(argv[3]);	
		m=sprintf(file2,"%s.txt",argv[4]); 
		col2=atoi(argv[5]);		
		norm2=atof(argv[6]);
		m=sprintf(file3,"%s.txt",argv[7]); 
		col3=atoi(argv[8]);		
		norm3=atof(argv[9]);
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
	i=0; Int_t cab=1;
	while (!in->eof())
		{
		while (cab)
			{		
			*in >> ci;
			if (isParam(ci))	
			  cout << "car " << ci << endl;
			else
				cab=0;

			
			}

		}


	}

/*
if (col==2) *in >> x[i] >> y[i];
		if (col==4) *in >> x[i] >> dx[i] >> y[i] >> dy[i];  		
		if (col==5) *in >> x[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];
		if (col==6) *in >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];  
		if (col==8) *in >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i];
		if (col==10) *in >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i] >> y4[i] >> dy4[i];
		i++;
		}
	}


for (k=0;k<i-1;k++)			
	{
	y[k]=(float)y[k]/norm;
	dy[k]=(float)dy[k]/norm;	
	if (max<y[k]) max=y[k];
	}

cout << norm << endl;

if (col==2)
	{
	TGraph *gr0 = new TGraph(i-1,x,y);		// Graph declaration
	gr0->SetLineColor(2);					
	gr0->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(2);						
	gr0->SetMarkerStyle(20);					
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitle(xaxis);				
	gr0->GetYaxis()->SetTitle(yaxis);				
	gr0->GetXaxis()->SetTitleSize(0.06);
	gr0->GetYaxis()->SetTitleSize(0.06);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	//gr0->GetXaxis()->SetRangeUser(0,125);
	gr0->Draw("AL");
	legend->AddEntry(gr0,"BBI (ceramic) - HP011713","l");
	}


if ((col==4)||(col==5)||(col==6)||(col==8)||(col==10))
	{
	//TH1F *hr = c->DrawFrame(0,0,100,10000);
	TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,dx,dy);		// Graph declaration
	gr1->SetLineColor(2);					
	gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr1->SetMarkerColor(2);						
	gr1->SetMarkerStyle(20);					
	gr1->SetTitle(title);					
	gr1->GetXaxis()->SetTitle(xaxis);				
	gr1->GetYaxis()->SetTitle(yaxis);				
	gr1->GetXaxis()->SetTitleSize(0.06);
	gr1->GetYaxis()->SetTitleSize(0.06);
	gr1->GetXaxis()->SetLabelSize(0.05);
	gr1->GetYaxis()->SetLabelSize(0.05);
	gr1->GetXaxis()->CenterTitle();					
	gr1->GetYaxis()->CenterTitle();	
	//gr1->GetXaxis->SetLimits(10,100);
	gr1->Draw("AP");

	#if FIT 
		TF1 *f1 = new TF1("f1",fitf,0,60); 				
		f1->SetParameter(0,-121);	
		f1->SetParameter(1,-254);	   
		f1->SetParameter(2,0.6); 		
		gr1->Fit(f1,"R");
		
	#endif

	if (col==5)
		{
		TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,0,dy);		// Graph declaration
		gr1->SetLineColor(2);					
		gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1->SetMarkerColor(2);						
		gr1->SetMarkerStyle(20);					
		gr1->SetTitle(title);					
		gr1->GetXaxis()->SetTitle(xaxis);				
		gr1->GetYaxis()->SetTitle(yaxis);				
		gr1->GetXaxis()->SetTitleSize(0.06);
		gr1->GetYaxis()->SetTitleSize(0.06);
		gr1->GetXaxis()->SetLabelSize(0.05);
		gr1->GetYaxis()->SetLabelSize(0.05);
		gr1->GetXaxis()->CenterTitle();					
		gr1->GetYaxis()->CenterTitle();	
		gr1->Draw("AP");
		}
	if ((col==5)||(col==6)||(col==8)||(col==10)) 	
		{		
		if (col==5)	 	
			{
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,0,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);	
			gr2->SetMarkerSize(0.4);										
			gr2->Draw("lPsame");
			}
		if (col>5)	 	
			{
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,dx,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);

			gr2->GetXaxis()->SetRange(0,1000);								
			gr2->Draw("lPsame");
			}
		if (col>7)
			{		
			TGraphErrors *gr3 = new TGraphErrors(i-1,x,y3,dx,dy3);		// Graph declaration
			gr3->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3->SetLineWidth(2);						
			gr3->SetMarkerColor(kGreen+3);						
			gr3->SetMarkerStyle(20);									
			gr3->Draw("lPsame");
			}
		if (col>9)
			{		
			TGraphErrors *gr4 = new TGraphErrors(i-1,x,y4,dx,dy4);		// Graph declaration
			gr4->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr4->SetLineWidth(2);						
			gr4->SetMarkerColor(kGreen+3);						
			gr4->SetMarkerStyle(20);
			gr4->SetMarkerSize(0.4);										
			gr4->Draw("lPsame");
			}

		}
	}


if (argc>4)
{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in2->eof())
			{
			if (col2==2) *in2 >> xb[i] >> yb[i];
			if (col2==4) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col2==5) *in2 >> xb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i];
			if (col2==6) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i];  
			if (col2==8) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i] >> y3b[i] >> dy3b[i];
			if (col2==10) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i] >> y3b[i] >> dy3b[i] >> y4b[i] >> dy4b[i];
			i++;
			}
		}

	for (k=0;k<i;k++)			
		{
		//norm2=638422.020656;
		yb[k]=yb[k]/norm2;
		dyb[k]=dyb[k]/norm2;	
		//xb[k]=xb[k];
		//xb[k]=xb[k]/1440;
		//dxb[k]=dxb[k]/1440;

		}

	if (col2==2)
		{
		TGraph *gr0b = new TGraph(i-1,xb,yb);		// Graph declaration
		gr0b->SetLineColor(4);					
		gr0b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0b->SetMarkerColor(4);						
		gr0b->SetMarkerStyle(20);					
		gr0b->SetTitle(title);					
		gr0b->GetXaxis()->SetTitle(xaxis);				
		gr0b->GetYaxis()->SetTitle(yaxis);				
		gr0b->GetXaxis()->SetTitleSize(0.06);
		gr0b->GetYaxis()->SetTitleSize(0.06);
		gr0b->GetXaxis()->SetLabelSize(0.05);
		gr0b->GetYaxis()->SetLabelSize(0.05);
		gr0b->GetXaxis()->CenterTitle();					
		gr0b->GetYaxis()->CenterTitle();	
		legend->AddEntry(gr0b,"BBI (ceramic) - LBL Run-1","l");	
		gr0b->Draw("Lsame");
		}


	if ((col2==4)||(col2==5)||(col2==6)||(col2==8)||(col2==10))
		{
		TGraphErrors *gr1b = new TGraphErrors(i-1,xb,yb,dxb,dyb);		// Graph declaration
		gr1b->SetLineColor(4);					
		gr1b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1b->SetMarkerColor(4);						
		gr1b->SetMarkerStyle(20);					
		gr1b->SetTitle(title);					
		gr1b->GetXaxis()->SetTitle(xaxis);				
		gr1b->GetYaxis()->SetTitle(yaxis);				
		gr1b->GetXaxis()->SetTitleSize(0.06);
		gr1b->GetYaxis()->SetTitleSize(0.06);
		gr1b->GetXaxis()->SetLabelSize(0.05);
		gr1b->GetYaxis()->SetLabelSize(0.05);
		gr1b->GetXaxis()->CenterTitle();					
		gr1b->GetYaxis()->CenterTitle();	
		gr1b->Draw("csameP");
	
		if (col2==5)
			{
			TGraphErrors *gr1b = new TGraphErrors(i-1,xb,yb,0,dyb);		// Graph declaration
			gr1b->SetLineColor(4);					
			gr1b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
			gr1b->SetMarkerColor(4);						
			gr1b->SetMarkerStyle(21);					
			gr1b->SetTitle(title);					
			gr1b->GetXaxis()->SetTitle(xaxis);				
			gr1b->GetYaxis()->SetTitle(yaxis);				
			gr1b->GetXaxis()->SetTitleSize(0.06);
			gr1b->GetYaxis()->SetTitleSize(0.06);
			gr1b->GetXaxis()->SetLabelSize(0.05);
			gr1b->GetYaxis()->SetLabelSize(0.05);
			gr1b->GetXaxis()->CenterTitle();					
			gr1b->GetYaxis()->CenterTitle();	
			gr1b->Draw("sameP");
			}
	if ((col2==5)||(col2==6)||(col2==8)||(col2==10)) 	
		{		
		if (col2==5)	 	
			{
			TGraphErrors *gr2b = new TGraphErrors(i-1,xb,y2b,0,dy2b);		// Graph declaration
			gr2b->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2b->SetLineWidth(2);						
			gr2b->SetMarkerColor(4);						
			gr2b->SetMarkerStyle(20);											
			gr2b->Draw("lPsame");
			}
		if (col2>5)	 	
			{
			TGraphErrors *gr2b = new TGraphErrors(i-1,xb,y2b,dxb,dy2b);		// Graph declaration
			gr2b->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2b->SetLineWidth(2);						
			gr2b->SetMarkerColor(4);						
			gr2b->SetMarkerStyle(20);											
			gr2b->Draw("lPsame");
			}
		if (col2>7)
			{		
			TGraphErrors *gr3b = new TGraphErrors(i-1,xb,y3b,dxb,dy3b);		// Graph declaration
			gr3b->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3b->SetLineWidth(2);						
			gr3b->SetMarkerColor(kGreen+3);						
			gr3b->SetMarkerStyle(20);									
			gr3b->Draw("lPsame");
			}
		if (col2>9)
			{		
			TGraphErrors *gr4b = new TGraphErrors(i-1,xb,y4b,dxb,dy4b);		// Graph declaration
			gr4b->SetLineColor(6);						// Line color 0=white 1=black, 2=red
			gr4b->SetLineWidth(2);						
			gr4b->SetMarkerColor(6);						
			gr4b->SetMarkerStyle(20);									
			gr4b->Draw("cPsame");
			}

		}
	}
}

//
if (argc==6||argc>7)
{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) 
		{cout << " ERROR OPENING FILE " <<  file3 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in3->eof())
			{
			if (col3==2) *in3 >> xc[i] >> yc[i];
			if (col3==4) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col3==5) *in3 >> xc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];
			if (col3==6) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];  
			if (col3==8) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i];
			if (col3==10) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i] >> y4c[i] >> dy4c[i];
			i++;
			}
		}

	for (k=0;k<i;k++)			
		{
		norm3=1825763.356755; 
		yc[k]=yc[k]/norm3;
		dyc[k]=dyc[k]/norm3;	
		}

	if (col3==2)
		{
		TGraph *gr0c = new TGraph(i-1,xc,yc);		// Graph declaration
		gr0c->SetLineColor(kGreen+3);					
		gr0c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0c->SetMarkerColor(kGreen+3);						
		gr0c->SetMarkerStyle(20);					
		gr0c->SetTitle(title);					
		gr0c->GetXaxis()->SetTitle(xaxis);				
		gr0c->GetYaxis()->SetTitle(yaxis);				
		gr0c->GetXaxis()->SetTitleSize(0.06);
		gr0c->GetYaxis()->SetTitleSize(0.06);
		gr0c->GetXaxis()->SetLabelSize(0.05);
		gr0c->GetYaxis()->SetLabelSize(0.05);
		gr0c->GetXaxis()->CenterTitle();					
		gr0c->GetYaxis()->CenterTitle();	
		legend->AddEntry(gr0c,"BBI (ceramic) - LBL Run-2","l");		
		gr0c->Draw("Lsame");
		}


	if ((col3==4)||(col3==5)||(col3==6)||(col3==8)||(col3==10))
		{
		TGraphErrors *gr1c = new TGraphErrors(i-1,xc,yc,dxc,dyc);		// Graph declaration
		gr1c->SetLineColor(kGreen+3);					
		gr1c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1c->SetMarkerColor(kGreen+3);						
		gr1c->SetMarkerStyle(20);					
		gr1c->SetTitle(title);					
		gr1c->GetXaxis()->SetTitle(xaxis);				
		gr1c->GetYaxis()->SetTitle(yaxis);				
		gr1c->GetXaxis()->SetTitleSize(0.06);
		gr1c->GetYaxis()->SetTitleSize(0.06);
		gr1c->GetXaxis()->SetLabelSize(0.05);
		gr1c->GetYaxis()->SetLabelSize(0.05);
		gr1c->GetXaxis()->CenterTitle();					
		gr1c->GetYaxis()->CenterTitle();	
		gr1c->Draw("samelP");
	
		if (col3==5)
			{
			TGraphErrors *gr1c = new TGraphErrors(i-1,xc,yc,0,dyc);		// Graph declaration
			gr1c->SetLineColor(kGreen+3);					
			gr1c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
			gr1c->SetMarkerColor(kGreen+3);						
			gr1c->SetMarkerStyle(21);					
			gr1c->SetTitle(title);					
			gr1c->GetXaxis()->SetTitle(xaxis);				
			gr1c->GetYaxis()->SetTitle(yaxis);				
			gr1c->GetXaxis()->SetTitleSize(0.06);
			gr1c->GetYaxis()->SetTitleSize(0.06);
			gr1c->GetXaxis()->SetLabelSize(0.05);
			gr1c->GetYaxis()->SetLabelSize(0.05);
			gr1c->GetXaxis()->CenterTitle();					
			gr1c->GetYaxis()->CenterTitle();	
			gr1c->Draw("sameP");
			}
	if ((col3==5)||(col3==6)||(col3==8)||(col3==10)) 	
		{		
		if (col3==5)	 	
			{
			TGraphErrors *gr2c = new TGraphErrors(i-1,xc,y2c,0,dy2c);		// Graph declaration
			gr2c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr2c->SetLineWidth(2);						
			gr2c->SetMarkerColor(kGreen+3);						
			gr2c->SetMarkerStyle(20);											
			gr2c->Draw("lPsame");
			}
		if (col3>5)	 	
			{
			TGraphErrors *gr2c = new TGraphErrors(i-1,xc,y2c,dxc,dy2c);		// Graph declaration
			gr2c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr2c->SetLineWidth(2);						
			gr2c->SetMarkerColor(kGreen+3);						
			gr2c->SetMarkerStyle(20);											
			gr2c->Draw("lPsame");
			}
		if (col3>7)
			{		
			TGraphErrors *gr3c = new TGraphErrors(i-1,xc,y3c,dxc,dy3c);		// Graph declaration
			gr3c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3c->SetLineWidth(2);						
			gr3c->SetMarkerColor(kGreen+3);						
			gr3c->SetMarkerStyle(20);									
			gr3c->Draw("lPsame");
			}
		if (col3>9)
			{		
			TGraphErrors *gr4c = new TGraphErrors(i-1,xc,y4c,dxc,dy4c);		// Graph declaration
			gr4c->SetLineColor(6);						// Line color 0=white 1=black, 2=red
			gr4c->SetLineWidth(2);						
			gr4c->SetMarkerColor(6);						
			gr4c->SetMarkerStyle(20);									
			gr4c->Draw("Psame");
			}




		}
	}

	ifstream *in4 = new ifstream(file4);
	if(!*in4) 
		{cout << " ERROR OPENING FILE " <<  file4 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in4->eof())
			{
			if (col4==2) *in4 >> xd[i] >> yd[i];
			if (col4==4) *in4 >> xd[i] >> dxc[i] >> yc[i] >> dyc[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col4==5) *in4 >> xd[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];
			if (col4==6) *in4 >> xd[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];  
			if (col4==8) *in4 >> xd[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i];
			if (col4==10) *in4 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i] >> y4c[i] >> dy4c[i];
			i++;
			}
		}

	for (k=0;k<i;k++)			
		{
		norm4= 2.549419E+9; 
		yd[k]=yd[k]/norm4;
		dyd[k]=dyd[k]/norm4;	
		}

	if (col4==2)
		{
		TGraphErrors *gr0d = new TGraphErrors(i-1,xd,yd);		// Graph declaration
		gr0d->SetLineColor(kOrange+2);					
		gr0d->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0d->SetMarkerColor(kOrange+2);						
		gr0d->SetMarkerStyle(20);					
		gr0d->SetTitle(title);					
		gr0d->GetXaxis()->SetTitle(xaxis);				
		gr0d->GetYaxis()->SetTitle(yaxis);				
		gr0d->GetXaxis()->SetTitleSize(0.06);
		gr0d->GetYaxis()->SetTitleSize(0.06);
		gr0d->GetXaxis()->SetLabelSize(0.05);
		gr0d->GetYaxis()->SetLabelSize(0.05);
		gr0d->GetXaxis()->CenterTitle();					
		gr0d->GetYaxis()->CenterTitle();	
		legend->AddEntry(gr0d,"BBI (single Xtal) - LBL ","l");	
		gr0d->Draw("samecP");
		}


	if (col4==4)
		{
		TGraphErrors *gr0d = new TGraphErrors(i-1,xc,yc,dxc,dyc);		// Graph declaration
		gr0d->SetLineColor(6);					
		gr0d->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0d->SetMarkerColor(6);						
		gr0d->SetMarkerStyle(20);					
		gr0d->SetTitle(title);					
		gr0d->GetXaxis()->SetTitle(xaxis);				
		gr0d->GetYaxis()->SetTitle(yaxis);				
		gr0d->GetXaxis()->SetTitleSize(0.06);
		gr0d->GetYaxis()->SetTitleSize(0.06);
		gr0d->GetXaxis()->SetLabelSize(0.05);
		gr0d->GetYaxis()->SetLabelSize(0.05);
		gr0d->GetXaxis()->CenterTitle();					
		gr0d->GetYaxis()->CenterTitle();	
		gr0d->Draw("Lsame");
		}


	
}



if (argc>7)
	{
	ifstream *in5 = new ifstream(file5);
	if(!*in5) 
		{cout << " ERROR OPENING FILE " <<  file5 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in5->eof())
			{
			if (col5==2) *in5 >> xc[i] >> yc[i];
			if (col5==4) *in5 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col5==5) *in5 >> xc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];
			if (col5==6) *in5 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];  
			if (col5==8) *in5 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i];
			if (col5==10) *in5 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i] >> y4c[i] >> dy4c[i];
			i++;
			}
		}


	if (col5==2)
		{
		TGraphErrors *gr0e = new TGraphErrors(i-1,xc,yc);		// Graph declaration
		gr0e->SetLineColor(1);					
		gr0e->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0e->SetMarkerColor(1);						
		gr0e->SetMarkerStyle(20);					
		gr0e->SetTitle(title);					
		gr0e->GetXaxis()->SetTitle(xaxis);				
		gr0e->GetYaxis()->SetTitle(yaxis);				
		gr0e->GetXaxis()->SetTitleSize(0.06);
		gr0e->GetYaxis()->SetTitleSize(0.06);
		gr0e->GetXaxis()->SetLabelSize(0.05);
		gr0e->GetYaxis()->SetLabelSize(0.05);
		gr0e->GetXaxis()->CenterTitle();					
		gr0e->GetYaxis()->CenterTitle();	
		gr0e->Draw("csameP");
		}





	if (col5==4)
		{
		TGraphErrors *gr0e = new TGraphErrors(i-1,xc,yc,dxc,dyc);		// Graph declaration
		gr0e->SetLineColor(1);					
		gr0e->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0e->SetMarkerColor(1);						
		gr0e->SetMarkerStyle(20);					
		gr0e->SetTitle(title);					
		gr0e->GetXaxis()->SetTitle(xaxis);				
		gr0e->GetYaxis()->SetTitle(yaxis);				
		gr0e->GetXaxis()->SetTitleSize(0.06);
		gr0e->GetYaxis()->SetTitleSize(0.06);
		gr0e->GetXaxis()->SetLabelSize(0.05);
		gr0e->GetYaxis()->SetLabelSize(0.05);
		gr0e->GetXaxis()->CenterTitle();					
		gr0e->GetYaxis()->CenterTitle();	
		gr0e->Draw("csameP");
		}

	}

if (argc==8)
	{
	ifstream *in6 = new ifstream(file6);
	if(!*in6) 
		{cout << " ERROR OPENING FILE " <<  file6 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in6->eof())
			{
			*in6 >> x[i] >> y[i];
			i++;
			}
		}

	if (col6==2)
		{
		TGraph *gr0f = new TGraph(i-1,x,y);		// Graph declaration
		gr0f->SetLineColor(6);					
		gr0f->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0f->SetMarkerColor(6);						
		gr0f->SetMarkerStyle(20);					
		gr0f->Draw("csameP");
		}

	}














if (col==100)       //before was 10
	{
	TGraph *gr[10]; Float_t factor=0;		// Graph declaration

 	for (i=200;i<600;i++)
			{
						
			factor=-0.0004231*x[i]*x[i]+0.2514*x[i]-5.25;
			factor=factor/100;
			cout << x[i] << "=x f=" << factor << endl;	
			dx[i]=dx[i]*factor;
			y[i]=y[i]*factor;
			dy[i]=dy[i]*factor;				
			y2[i]=y2[i]*factor;	
			dy2[i]=dy2[i]*factor;		
			y3[i]=y3[i]*factor;
			dy3[i]=dy3[i]*factor;
			y4[i]=y4[i]*factor;
			dy4[i]=dy4[i]*factor;
			}


	gr[0] =  new TGraph(i-1,x,dx);
	gr[1] =  new TGraph(i-1,x,y);	
	gr[2] =  new TGraph(i-1,x,dy);
	gr[3] =  new TGraph(i-1,x,y2);
	gr[4] =  new TGraph(i-1,x,dy2);	
	gr[5] =  new TGraph(i-1,x,y3);
	gr[6] =  new TGraph(i-1,x,dy3);
	gr[7] =  new TGraph(i-1,x,y4);	
	gr[8] =  new TGraph(i-1,x,dy4);
	gr[0]->Draw("AcP");
 	for (i=0;i<1000;i++)
		{
		if ((x[i]>410)&&(x[i]<470)) 	
			{
			//factor=-0.0004231*x[i]*x[i]+0.2514*x[i]-5.25;
			//factor=factor/100;
			//cout << factor << endl;			
			I1=I1+dx[i]-0.125*x[i]+67.75;
			I2=I2+y[i]-0.125*x[i]+67.75;
			I3=I3+dy[i]-0.125*x[i]+67.75;			
			I4=I4+y2[i]-0.125*x[i]+67.75;
			I5=I5+dy2[i]-0.125*x[i]+67.75;
			I6=I6+y3[i]-0.125*x[i]+67.75;
			I7=I7+dy3[i]-0.125*x[i]+67.75;
			I8=I8+y4[i]-0.125*x[i]+67.75;
			I9=I9+dy4[i]-0.125*x[i]+67.75;
			}
		}
	cout << "Integrals I1-I9 =" << I1 << " " << I2 << " "<< I3 << " "<< I4 << " "<< I5 << " "<< I6 << " "<< I7 << " "<< I8 << " "<< I9 << endl;	
	for (m=0;m<9;m++)
		{
		gr[m]->SetLineColor(m);	
		gr[m]->SetLineWidth(2);						
		gr[m]->SetMarkerColor(m);						
		gr[m]->SetMarkerStyle(22);	
		gr[m]->Draw("cPsame");
		}
	}

/*
TLatex *tx = new TLatex();
tx->SetNDC();
tx->SetTextFont(62);
tx->SetTextColor(36);
tx->SetTextAlign(12);
tx->SetTextSize(0.05);
tx->SetTextColor(2);
tx->DrawLatex(0.8,0.40,"Serie 1");*/
/*
TMarker *marker = new TMarker(260,0.83,21);
marker->SetMarkerColor(2);
marker->SetMarkerSize(1.0);
marker->Draw();
*/
/*if ((col==5)||(col==6)||(col==8))
	{
	tx->SetTextColor(4);
	tx->DrawLatex(0.8,0.35,"Serie 2");
	TMarker *marker2 = new TMarker(260,0.79,20);
	marker2->SetMarkerColor(4);
	marker2->SetMarkerSize(1.0);
	marker2->Draw();
	if (col==8) 
		{
		tx->SetTextColor(kGreen+3);
		tx->DrawLatex(0.8,0.30,"Serie 3");
		TMarker *marker3 = new TMarker(260,0.75,22);
		marker3->SetMarkerColor(kGreen+3);
		marker3->SetMarkerSize(1.0);
		marker3->Draw();
		}	

	}



if(argc==2&&col!=2)
{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in2->eof())
			{
			if (col==2) *in2 >> x[i] >> y[i];
			if (col==4) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i];  //if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col==5) *in2 >> x[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];
			if (col==6) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];
			if (col==8) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i];
			if (col==10) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i] >> y4[i] >> dy4[i];
			i++;
			}
		}
	
	for (k=0;k<i;k++)			
		{
		x[k]=x[k]*6.9;                 
		if (norm==1) 	
			{
			y[k]=y[k]/4723;
			dy[k]=dy[k]/4723;	
			}
		cout << y[k] << " " << y[0] << endl;
		}
	
	
	
	if ((col==4)||(col==5)||(col==6)||(col==8))
		{
		TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,dx,dy);		// Graph declaration
		gr1->SetLineColor(kBlue);					
		gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1->SetMarkerColor(kBlue);						
		gr1->SetMarkerStyle(20);					
		gr1->SetTitle(title);					
		gr1->GetXaxis()->SetTitle(xaxis);				
		gr1->GetYaxis()->SetTitle(yaxis);				
		gr1->GetXaxis()->SetTitleSize(0.06);
		gr1->GetYaxis()->SetTitleSize(0.06);
		gr1->GetXaxis()->SetLabelSize(0.05);
		gr1->GetYaxis()->SetLabelSize(0.05);
		gr1->GetXaxis()->CenterTitle();					
		gr1->GetYaxis()->CenterTitle();	
		gr1->Draw("sameP");
		if ((col==5)||(col==6)||(col==8)) 	
			{		
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,dx,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);											
			gr2->Draw("cPsame");
			if (col==8)
				{		
				TGraphErrors *gr3 = new TGraphErrors(i-1,x,y3,dx,dy3);		// Graph declaration
				gr3->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
				gr3->SetLineWidth(2);						
				gr3->SetMarkerColor(kGreen+3);						
				gr3->SetMarkerStyle(20);									
				gr3->Draw("cPsame");
				}
			}
		}
	
}



	legend->Draw();*/
#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
