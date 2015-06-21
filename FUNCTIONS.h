//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "libraries.h" 


//***************************** FUNCTIONS DECLARATIONS **********************************
// Palette Definition for ZCol graphs
void set_plot_style();


// Basic functions
Float_t GetMax(Float_t *x, Int_t &n);
Float_t GetMin(Float_t *x, Int_t &n);

// MCA functions
void Read_MCA(char *file, Float_t *datos, Float_t &days, Int_t &n);
void Read_GV(char *file, Float_t *datos,  Float_t &days,  Int_t &n, Int_t &a, Int_t &b);
void Read_GV2(char *file, Float_t *datos,  Float_t &days,  Int_t &n);
void Read_tFluor(char *file, Float_t *data,   Int_t &n, Float_t &conv, Float_t &acqtime);
void Read_eFluor(char *file, Float_t *data,   Int_t &n, Float_t &conv, Float_t &acqtime);

// READ STOPING POWER FILES
void Read_SPG4(char *file, Float_t *x, Float_t *y, Int_t &npoints);
void Plot_SPG4(TH2F *H, Float_t *x,  Float_t *y,  Int_t &npoints, Int_t first, Int_t Color);
// for NIST-stoping power
void Read_SPNI(char *Scint, Float_t *x, Float_t *y, Int_t &npoints);
void Plot_SPNI(TH2F *H, Float_t *x,  Float_t *y,  Int_t &npoints, Int_t first, Int_t Color);


// READ FILMETRICS TRANSMISSION FILES
void Read_FTRe(char *file, Float_t *x, Float_t *y, Int_t &n);
void Read_FTRw(char *file, Float_t *x, Float_t *y, Int_t &n);
void Calc_Abs(Float_t *wv, Float_t *T, Float_t *R, Float_t *A, Int_t &nr, Float_t &D);
void Plot_Abs(TGraph *gr, Int_t first, Int_t Color);
void Plot_TR(TGraph *gr, Int_t first, Int_t Color);

// Get File - attributes
void GetDate(char *file,  char *tim);
void GetTime(char *file,  char *tim);
void OpenFiles(int argc, char **argv, char **f);
void GetInfo_oexcem(char *file,  char **info);


// read files
void Read_1col(char *file, Float_t *x, Int_t &n);
void Read_2col(char *file, Float_t *x, Float_t *x2, Int_t &n);
void Read_3col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Int_t &n);
void Read_4col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Int_t &n);
void Read_5col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Int_t &n);
void Read_6col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Float_t *x6, Int_t &n);


// fiting functions
Double_t Background_lin(Double_t *x, Double_t *par);
Double_t Background_exp(Double_t *x, Double_t *par);
Double_t Background_expb(Double_t *x, Double_t *par);                   //new
Double_t Background_exp2(Double_t *x, Double_t *par);
Double_t Signal(Double_t *x, Double_t *par);
Double_t gaus1(Double_t *x, Double_t *par);
Double_t gaus2(Double_t *x, Double_t *par);
Double_t gaus3(Double_t *x, Double_t *par);
Double_t fit_lgaus(Double_t *x, Double_t *par);
Double_t fit_gaus2e(Double_t *x, Double_t *par);
Double_t fit_egaus(Double_t *x, Double_t *par);
Double_t fit_egausb(Double_t *x, Double_t *par);                    //new
Double_t fit_egaus2(Double_t *x, Double_t *par);
Double_t fit_egaus2b(Double_t *x, Double_t *par);
Double_t fit_egaus3(Double_t *x, Double_t *par);
Double_t fit_lgaus3(Double_t *x, Double_t *par);

Double_t fit_lga1ga2(Double_t *x, Double_t *par);
Double_t fit2gaus(Double_t *x, Double_t *par);
Double_t fit3gaus(Double_t *x, Double_t *par);

//resolution calculations
void Resol_ga(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_egb(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg2(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg2b(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg3(TF1 *g1, Float_t &r, Float_t &dr);

// error messages or legends
void MsgError(void);
void PrintStats(TF1 *g1, Int_t &cont, Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean, Float_t &integral);
void PrintLegend(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLegend2(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLegend3(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLatex(Text_t *text, Int_t position, Int_t color, Int_t &number);
void PrintLatex2(Text_t *text, Float_t posx, Float_t posy, Int_t color);


// Histogram functions

//  creating a vector with log-scale for 2D histograms.
void LogAxis(Float_t &mx, Float_t &Mx, Float_t &my, Float_t &My, Int_t &nbins, Float_t *xbins, Float_t *ybins);



//***************************** FUNCTIONS DECLARATIONS **********************************


// Palette Definition for ZCol graphs
void set_plot_style(void)
{
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;
   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);
}

// Basic functions (Max, Min, etc)

// Get the maximum value of a vector
Float_t GetMax(Float_t *x, Int_t &n)
{
Float_t max=x[0]; 
for (Int_t k=0;k<n;k++)			
	if (max<x[k]) max=x[k];
return max;
}
// Get the minimum value of a vector
Float_t GetMin(Float_t *x, Int_t &n)
{
Float_t min=x[0]; 
for (Int_t k=0;k<n;k++)			
	if (min>x[k]) min=x[k];
return min;
}


// MCA functions
void Read_MCA(char *file, Float_t *datos,  Float_t &days, Int_t &n)
{
	
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define Nmax 8192 
char ci[100]="";
Int_t i,da[3],ti[3],sec=0,da0[3],ti0[3];

ifstream *in = new ifstream(file);
ifstream *in2 = new ifstream(".date.txt");
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	
		{
		*in >> ci;
		if ((strstr(ci,"START_TIME")!=NULL))
			{
				
			*in >> ci; 
			*in >> ci; //cout << "da " << ci <<endl;
			da[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
			da[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			da[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
			*in >> ci; //cout << "ti " << ci <<endl;
			ti[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
			ti[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			ti[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
					
				
			if(*in2) 
				{
				*in2 >> ci;
				da0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
				da0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				da0[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
				*in2 >> ci;
				ti0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
				ti0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				ti0[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
				sec=86400*(da[1]-da0[1])+86400*30*(da[0]-da0[0])+86400*30*366*(da[2]-da0[2])+ti[2]+ti[1]*60+ti[0]*3600-(ti0[2]+ti0[1]*60+ti0[0]*3600); //sec since file
				}
			else
				{
				sec=86400*(da[1]-14)+86400*30*(da[0]-8)+86400*30*366*(da[2]-2012)+ti[2]+ti[1]*60+ti[0]*3600-42093; //seconds since 08/01/2012  16:58:14
				}

			//days=sec/86400.0;
			days=sec/60.0; // divide by 60 if you want min , 3600 if you want hours or  86400 (days)
			cout << "****************************************************************************"<<endl;
			cout << "> "<<da[0]<<"/"<<da[1]<<"/"<<da[2]<<" -- "<<ti[0]<<":"<<ti[1]<<":"<< ti[2]<<"  t(s)= "<< sec << "= "<<days<<" days"<<endl;
			}

		//if ((strstr(ci,"LIVE_ti")!=NULL))  strcpy(liveti,ci);
		//if ((strstr(ci,"START_ti")!=NULL))  strcpy(startti,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	for (i=0;i<Nmax;i++)
		{			
		*in >> datos[i];                  
		if ((strstr(ci,"END")!=NULL)) i=Nmax;
		}
	n=i;
	}
delete in;
}


void Read_GV(char *file, Float_t *datos,  Float_t &days,  Int_t &n, Int_t &a, Int_t &b)
{
	
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define Nmax 8192 
char ci[100]="";
Int_t i,da[3],ti[3],sec=0,da0[3],ti0[3];

ifstream *in = new ifstream(file);
ifstream *in2 = new ifstream(".date.txt");
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	
		{
		*in >> ci;
		if ((strstr(ci,"DATE_MEA")!=NULL))
			{
			*in >> ci; //cout << "da " << ci <<endl;
			da[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
			da[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			da[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
			*in >> ci; //cout << "ti " << ci <<endl;
			ti[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
			ti[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			ti[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
			if(*in2) 
				{
				*in2 >> ci;
				da0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
				da0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				da0[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
				*in2 >> ci;
				ti0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
				ti0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				ti0[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
				sec=86400*(da[1]-da0[1])+86400*30*(da[0]-da0[0])+86400*30*366*(da[2]-da0[2]);
				sec=sec+ti[2]+ti[1]*60+ti[0]*3600-(ti0[2]+ti0[1]*60+ti0[0]*3600); //sec since file
				}
			else
				{
				sec=86400*(da[1]-14)+86400*30*(da[0]-8)+86400*30*366*(da[2]-2012)+ti[2]+ti[1]*60+ti[0]*3600-42093;
				 //seconds since 08/01/2012  16:58:14
				}
			days=sec/60.0; // divide by 60 if you want min, 3600 if you want hours or  86400 (days)
			cout << "****************************************************************************"<<endl;
			cout << "> "<<da[0]<<"/"<<da[1]<<"/"<<da[2]<<" -- "<<ti[0]<<":"<<ti[1]<<":"<< ti[2]<<endl;
			}
		//if ((strstr(ci,"LIVE_ti")!=NULL))  strcpy(liveti,ci);
		//if ((strstr(ci,"START_ti")!=NULL))  strcpy(startti,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			*in >> ci;*in >> ci;
			i=0;
			}
		}
	while (i!=0);
	for (i=0;i<Nmax;i++)
		{			
		*in >> datos[i]; //if (i%10==0) cout << datos[i] << endl;                 
		if ((strstr(ci,"ROI")!=NULL)) 
			{ 
			i=Nmax;
			*in >> ci; 
       			*in >> ci; a=atoi(ci); 
			*in >> ci; b=atoi(ci); 
			}
		
		}

	i=0;
	while (i!=0);
	 	{
		*in >> ci;
		if ((strstr(ci,"ROI")!=NULL)) 
			{ 
			i=Nmax;
			*in >> ci;  
       			*in >> ci; a=atoi(ci); cout << "limit a " << a <<endl; 
			*in >> ci; b=atoi(ci); cout << "limit b " << b <<endl; 
			}

		}
	n=i;
	}
delete in;
}

void Read_GV2(char *file, Float_t *datos,  Float_t &days,  Int_t &n)
{
	
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define Nmax 8192 
char ci[100]="";
Int_t i,da[3],ti[3],sec=0,da0[3],ti0[3];

ifstream *in = new ifstream(file);
ifstream *in2 = new ifstream(".date.txt");
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	
		{
		*in >> ci;
		if ((strstr(ci,"DATE_MEA")!=NULL))
			{
			*in >> ci; //cout << "da " << ci <<endl;
			da[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
			da[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			da[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
			*in >> ci; //cout << "ti " << ci <<endl;
			ti[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
			ti[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			ti[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
			if(*in2) 
				{
				*in2 >> ci;
				da0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
				da0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				da0[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
				*in2 >> ci;
				ti0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0');  
				ti0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				ti0[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
				sec=86400*(da[1]-da0[1])+86400*30*(da[0]-da0[0])+86400*30*366*(da[2]-da0[2]);
				sec=sec+ti[2]+ti[1]*60+ti[0]*3600-(ti0[2]+ti0[1]*60+ti0[0]*3600); //sec since file
				}
			else
				{
				sec=86400*(da[1]-14)+86400*30*(da[0]-8)+86400*30*366*(da[2]-2012)+ti[2]+ti[1]*60+ti[0]*3600-42093;
				 //seconds since 08/01/2012  16:58:14
				}
			days=sec/60.0; // divide by 60 if you want min, 3600 if you want hours or  86400 (days)
			cout << "****************************************************************************"<<endl;
			cout << "> "<<da[0]<<"/"<<da[1]<<"/"<<da[2]<<" -- "<<ti[0]<<":"<<ti[1]<<":"<< ti[2]<<endl;
			}

		//if ((strstr(ci,"LIVE_ti")!=NULL))  strcpy(liveti,ci);
		//if ((strstr(ci,"START_ti")!=NULL))  strcpy(startti,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			*in >> ci; *in >> ci; cout << "> "<< ci << endl; 
			i=0;
			}
		}
	while (i!=0);
	for (i=0;i<Nmax;i++)
		{			
		*in >> datos[i];   // cout << "> "<< datos[i] << endl;              
		if ((strstr(ci,"ROI")!=NULL)) 
			{ 
			i=Nmax;
			}
		
		}
	n=i;
	}
delete in;
}



void Read_tFluor(char *file, Float_t *data, Int_t &n, Float_t &conv, Float_t &acqtime)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
char ci[100]="",*ci2;
Int_t i;
ifstream *in = new ifstream(file);
if(!*in)	cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=1;
	do	
		{
		*in >> ci;		
		if ((strstr(ci,"Real")!=NULL))	 // Real time: 174.287
			{
			*in >> ci; *in >> ci;
			acqtime=atof(ci);
			cout << "Real time "<< acqtime << " s" << endl; 
			} 
		if ((strstr(ci,"calibration:")!=NULL))	//Time calibration: 1.75583ns/ch
			{
			*in >> ci; 
			ci2=strtok(ci,"ns/ch");
			conv=atof(ci2);
			cout << "conversion "<< conv << " ns/ch" << endl; 
			}		
		if ((strstr(ci,"Data")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	while (!in->eof())
		{
		*in >> ci >> data[i];               
		data[i]=data[i]/acqtime;		
		i++;		
		}
	n=i;
	}
delete in;
}




void Read_eFluor(char *file, Float_t *data, Int_t &n, Float_t &start, Float_t &stop)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
char ci[100]="";
Int_t i;
ifstream *in = new ifstream(file);
if(!*in)	cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=1;
	do	
		{
		*in >> ci;		
		if ((strstr(ci,"Start:")!=NULL))	 // Real time: 174.287
			{
			*in >> ci; 
			start=atof(ci);
			cout << "Start "<< start << " nm" << endl; 
			} 
		if ((strstr(ci,"Stop:")!=NULL))	//Time calibration: 1.75583ns/ch
			{
			*in >> ci; 
			stop=atof(ci);
			cout << "Stop: "<< stop << " nm" << endl; 
			}		
		if ((strstr(ci,"CorrectedData")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	while (!in->eof())
		{
		*in >> ci >> data[i] >> ci; 
             	//cout << "data: "<< data[i] << " " << endl; 
		i++;		
		}
	n=i; 
	}
delete in;
}




void Read_SPG4(char *file, Float_t *x,  Float_t *y,  Int_t &npoints)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Float_t xa,ya,ya2,ya3,ya4,ya_old;
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	Int_t l=0,i=0;	
	while ((!in->eof())&&(l<499000))
		{
		ya_old=ya3;		
		*in >>  xa >> ya >> ya2 >> ya3 >> ya4;   
		if ((ya_old-ya3)>0.001||(ya3-ya_old)>0.001)
			{
			xa=xa*1000;
			x[l]=xa;                 
			y[l]=ya3; 
			l++;  
			}
		i++;
		}
	npoints=l;
	}
delete in;
}


void Plot_SPG4(TH2F *H, Float_t *x,  Float_t *y,  Int_t &npoints, Int_t first, Int_t Color)
{
char title[100]=""; 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
for (Int_t k=0;k<npoints;k++)			
	H->Fill(x[k],y[k]);		// fill the histogram
H->SetMarkerColor(Color);
H->SetMarkerStyle(7);
H->SetMarkerSize(1);
H->GetXaxis()->SetRangeUser(0.01,1300);
H->GetYaxis()->SetRangeUser(1,200);
if (first==1)
	{
	H->SetTitle(title);
	H->GetXaxis()->SetTitle("Energy (keV)");
	H->GetYaxis()->SetTitle("dEdx (MeV.cm^{2}/g)");
	H->GetXaxis()->CenterTitle();
	H->GetYaxis()->CenterTitle();
	H->Draw();
	}
else 	
	H->Draw("same");

}




void Read_SPNI(char *Scint, Float_t *x,  Float_t *y,  Int_t &npoints)
{
Int_t Vm=1000; // maximum vector size
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Float_t aa[Vm],a2[Vm],a22[Vm],a23[Vm],a24[Vm];
ifstream *in2 = new ifstream(Form("/home/martin/geant4_work/examples/dE_dx-Scintillators/NIST/%s_wo.dat",Scint));
if(!*in2) cout << " ERROR OPENING FILE " << endl; 
else    {
	Int_t i=0;
	while ((!in2->eof())&&(i<Vm))
		{
		*in2 >>  aa[i] >> a2[i] >> a22[i] >> a23[i] >> a24[i]; 
		x[i]=aa[i]*1000;		// to convert them in keV
		y[i]=a23[i];			
		i++;
		}
	npoints=i;
	}
delete in2;
}
void Plot_SPNI(TH2F *H, Float_t *x,  Float_t *y,  Int_t &npoints, Int_t first, Int_t Color)
{
char title[100]=""; 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
for (Int_t k=0;k<npoints;k++)			
	H->Fill(x[k],y[k]);		// fill the histogram
H->SetMarkerColor(Color);
H->SetMarkerStyle(4);
H->SetMarkerSize(1);
H->SetTitle(title);
if (first==1) H->Draw();
else H->Draw("same");
}



// READ FILMETRICS TRANSMISSION-REFLECTION FILES in energy
void Read_FTRe(char *file, Float_t *x, Float_t *y, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i;
char ci[100];
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=0;
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;  // Removes the header
	while (!in->eof())
		{
		*in >> x[i] >> y[i];
		if (x[i]!=0)	x[i]=(float)(1240/x[i]);
		else 		x[i]=0;		//cout << x[i] <<endl;
		i++;
		}
	n=i;
	}
}
 

// READ FILMETRICS TRANSMISSION-REFLECTION FILES in wavelenght
void Read_FTRw(char *file, Float_t *x, Float_t *y, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i;
char ci[100];
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=0;
	*in >> ci;*in >> ci;*in >> ci;*in >> ci;  // Removes the header
	while (!in->eof())
		{
		*in >> x[i] >> y[i];
		i++;
		}
	n=i;
	}
}




void Calc_Abs(Float_t *wv, Float_t *T, Float_t *R, Float_t *A, Int_t &nr, Float_t &D)
{
Int_t i;
for (i=0;i<nr;i++)     
	{
	if (wv[i]<1) i=nr;
	else
		{
		if (T[i]<0) T[i]=0.000000000001;		
		A[i]= -1/D*(TMath::Log(T[i]/100/((1-R[i]/100)*(1-R[i]/100))));
		std::cout << wv[i] << "\t" << A[i] << std::endl;
		}
	}
}


void Plot_Abs(TGraph *gr, Int_t first, Int_t Color)
{
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr->SetMarkerColor(Color);						
gr->SetMarkerStyle(20);					
gr->SetTitle(title);					
gr->GetXaxis()->SetTitle("Energy (eV)");				
gr->GetYaxis()->SetTitle("Absorption coeff. (cm^{-1}) .10^{4}");				
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
gr->GetXaxis()->SetRangeUser(1.1272,6.2);	
if (first==1) gr->Draw("Ac");
else gr->Draw("samec");
}


void Plot_TR(TGraph *gr, Int_t first, Int_t Color)
{
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr->SetMarkerColor(Color);						
gr->SetMarkerStyle(20);					
gr->SetTitle(title);	
gr->GetXaxis()->SetTitle("Wavelength (nm)");
gr->GetYaxis()->SetTitle("Reflectance (%)");					
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
gr->GetXaxis()->SetRangeUser(200,1100);	
if (first==1) gr->Draw("Ac");
else gr->Draw("samec");
}



///////////////////  get the time of file
void GetDate(char *file, char *tim)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t yy=0,mm=0,dd=0;
struct tm* clock;				// create a time structure
struct stat attrib;			// create a file attribute structure
stat(file, &attrib);		// get the attributes of afile.txt
clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure
yy = clock->tm_year; yy=yy+1900;
mm = clock->tm_mon; mm=mm+1;
dd = clock->tm_mday; 
if ((mm<10) && (dd<10)) sprintf(tim,"%4i-0%i-0%i",yy,mm,dd);  
if ((mm<10) && (dd>10)) sprintf(tim,"%4i-0%i-%i",yy,mm,dd);  
if ((mm>10) && (dd<10)) sprintf(tim,"%4i-%i-0%i",yy,mm,dd);  
if ((mm>10) && (dd>10)) sprintf(tim,"%4i-%i-%i",yy,mm,dd); 
cout << "Measurement date: " << tim << endl;
}

void GetTime(char *file, char *tim)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t yy=0,mm=0,dd=0;
struct tm* clock;				// create a time structure
struct stat attrib;			// create a file attribute structure
stat(file, &attrib);		// get the attributes of afile.txt
clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure
yy = clock->tm_year; yy=yy+1900;
mm = clock->tm_mon; mm=mm+1;
dd = clock->tm_mday; 
if ((mm<10) && (dd<10)) sprintf(tim,"%4i-0%i-0%i",yy,mm,dd);  
if ((mm<10) && (dd>10)) sprintf(tim,"%4i-0%i-%i",yy,mm,dd);  
if ((mm>10) && (dd<10)) sprintf(tim,"%4i-%i-0%i",yy,mm,dd);  
if ((mm>10) && (dd>10)) sprintf(tim,"%4i-%i-%i",yy,mm,dd); 
cout << "Measurement date: " << tim << endl;
}


void OpenFiles(int argc, char **argv, char **f)
{
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f[0],"%s.txt",argv[1]);	 
		break;
	case 3: sprintf(f[0],"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f[1],"%s.txt",argv[2]);
		break;
	case 4: sprintf(f[0],"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f[1],"%s.txt",argv[2]);
		sprintf(f[2],"%s.txt",argv[3]);
		break;
	case 5: sprintf(f[0],"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f[1],"%s.txt",argv[2]);
		sprintf(f[2],"%s.txt",argv[3]);
		sprintf(f[3],"%s.txt",argv[4]);
		break;
	case 6: sprintf(f[0],"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		sprintf(f[1],"%s.txt",argv[2]);
		sprintf(f[2],"%s.txt",argv[3]);
		sprintf(f[3],"%s.txt",argv[4]);
		sprintf(f[4],"%s.txt",argv[5]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   
}



void GetInfo_oexcem(char *file,  char **info)
{
Char_t *sepa,*f;
sprintf(f,"%s",file);
sepa=strtok(f,"-");  
sprintf(info[0],"%s",sepa);
std::cout << "sample# = "<< info[0] << std::endl;
/*
sepa=strtok(NULL,"-"); 
sprintf(scint,"%s",sepa);
cout << "scint = "<< scint << endl;
sprintf(title,"Optical Excitation - %s - Sample %s ",scint,sample);
sepa=strtok(NULL,"-"); 
sprintf(dp,"%s",sepa);
cout << "dopant = "<< dp << endl;
sepa=strtok(NULL,"-"); 
sepa=strtok(NULL,"-"); 
sepa=strtok(NULL,"-Emission"); 
sprintf(emis,"%s",sepa);
cout << "emis = "<< emis << " nm" << endl;
cout << "***************************"<< endl;
*/



}





// READ FILES
void Read_1col(char *file, Float_t *x, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl; }
else    {
	while (!in->eof()) { *in >> x[i]; i++;}	
	n=i;
	}
}


void Read_2col(char *file, Float_t *x, Float_t *x2, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i];  i++; 	}	
	n=i;
	}
}
void Read_3col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i];   i++; 	}	
	n=i;
	}
}

void Read_4col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i];   i++; 	}	
	n=i;
	}
}




void Read_5col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i] >> x5[i];   i++; 	}	
	n=i;
	}
}

void Read_6col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Float_t *x6, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i] >> x5[i] >> x6[i] ; i++; 	}	
	n=i;
	}
}





// Linear background function
Double_t Background_lin(Double_t *x, Double_t *par)
{  Double_t val = par[0]+par[1]*x[0];
   return val;
}

// Exponential background function
Double_t Background_exp(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}

// Exponential background function
Double_t Background_expb(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*(x[0]-par[2]));
   return val;
}

// Exponential background function
Double_t Background_exp2(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}

// The signal function: a gaussian
Double_t Signal(Double_t *x, Double_t *par)
{  	Double_t arg = 0;
   	if (par[2]) arg = (x[0] - par[1])/par[2];
   		Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   	return sig;
}

// The signal function: doble gaussian gaussian g1
Double_t gaus1(Double_t *x, Double_t *par)
{  Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}

// The signal function: doble gaussian gaussian g2
Double_t gaus2(Double_t *x, Double_t *par)
{  Double_t arg2 = 0;
   if (par[2]) arg2 = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg2*arg2);
   return sig;
}
// The signal function: doble gaussian gaussian g3
Double_t gaus3(Double_t *x, Double_t *par)
{  Double_t arg2 = 0;
   if (par[2]) arg2 = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg2*arg2);
   return sig;
}

// Combined background (linear) + signal
Double_t fit_lgaus(Double_t *x, Double_t *par)
{  	Double_t tot = Background_lin(x,par) + Signal(x,&par[2]);
   	return tot;
}

// Combined background (exponential) + signal
Double_t fit_egaus(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Signal(x,&par[2]);            
   	return tot;
}

// Combined background (exponential) + signal                     //new
Double_t fit_egausb(Double_t *x, Double_t *par)
{  	Double_t tot = Background_expb(x,par) + Signal(x,&par[3]);
   	return tot;
}

// Combined background gaus + 2x expo
Double_t fit_gaus2e(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Background_exp2(x,&par[2])+gaus1(x,&par[4]);
   	return tot;
}

// Combined background expo + 2x gaus
Double_t fit_egaus2(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5]);
   	return tot;
}

Double_t fit_egaus2b(Double_t *x, Double_t *par)
{  	Double_t tot = Background_expb(x,par) + gaus1(x,&par[3])+gaus2(x,&par[6]);
   	return tot;
}
// Combined background expo + 3x gaus
Double_t fit_egaus3(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5])+gaus3(x,&par[8]);
   	return tot;
}

// Combined background lineal + 3x gaus
Double_t fit_lgaus3(Double_t *x, Double_t *par)
{  	Double_t tot = Background_lin(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5])+gaus3(x,&par[8]);
   	return tot;
}

// Combined background (exponential) + signal
Double_t fitFcn(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Signal(x,&par[2]);
   	return tot;
}
// Combined background + signal
Double_t fit_lga1ga2(Double_t *x, Double_t *par)
{  
    //Double_t tot = gaus1(x,par) + gaus2(x,par);//
	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2]) + gaus2(x,&par[5]);
	return tot;
}


// Combined two gaussian functions
Double_t fit2gaus(Double_t *x, Double_t *par)
{  
	Double_t tot = gaus1(x,par) + gaus2(x,&par[3]);
	return tot;
}

// Combined three gaussian functions
Double_t fit3gaus(Double_t *x, Double_t *par)
{  
	Double_t tot = gaus1(x,par) + gaus2(x,&par[3])+ gaus3(x,&par[6]);
	return tot;
}



//resolution calculations

// calculate the resolution for a gaussian Function
void Resol_ga(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(1);       			// obtain the mean value
	sigma = g1->GetParameter(2);
	dmean = g1->GetParError(1);		// uncertainty in mean
	dsigma = g1->GetParError(2);		// uncertainty in sigma	
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution

}


// calculate the resolution for a gaussian + exponential Function
void Resol_eg(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(3); 	// get the mean value
	sigma = g1->GetParameter(4);	// get the sigma
	if (sigma<0) sigma=-sigma;	
	dmean = g1->GetParError(3);		// uncertainty in mean
	dsigma = g1->GetParError(4);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}

// calculate the resolution for a gaussian + exponential Function with 3 parameters
void Resol_egb(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(4); 	// get the mean value
	sigma = g1->GetParameter(5);	// get the sigma
	if (sigma<0) sigma=-sigma;	
	dmean = g1->GetParError(4);		// uncertainty in mean
	dsigma = g1->GetParError(5);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;				
}





// calculate the resolution for a 2nd gaussian + exponential Function
void Resol_eg2(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(6); 	// get the mean value
	sigma = g1->GetParameter(7);	// get the sigma
	dmean = g1->GetParError(6);		// uncertainty in mean
	dsigma = g1->GetParError(7);		// uncertainty in sigma	
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}

void Resol_eg2b(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(7); 	// get the mean value
	sigma = g1->GetParameter(8);	// get the sigma
	dmean = g1->GetParError(7);		// uncertainty in mean
	dsigma = g1->GetParError(8);		// uncertainty in sigma	
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}


// calculate the resolution for a 3rd gaussian + exponential Function
void Resol_eg3(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(9); 	// get the mean value
	sigma = g1->GetParameter(10);	// get the sigma
	dmean = g1->GetParError(9);		// uncertainty in mean
	dsigma = g1->GetParError(10);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}

// ******************************************************** error messages **************************** 
// Print the error message
void MsgError(void)
{ 	using namespace std;	 
        cout << "									  " << "\n";
        cout << "************************************************************************ " << "\n";
	cout << "SYNTAX ERROR: You entered the incorrect number of arguments.             " << "\n";
	cout << "PROGRAM [FILENAME-WITHOUT EXTENSION] [PARAMETERS] 			  " << "\n";
	cout << "OPEN THE CC FILE FOR ADDITIONAL INFORMATION				  " << "\n";
	cout << "Author: Martin Gascon. Stanford University. 2O11                         " << "\n";
        cout << "*************************************************************************" << "\n";    
        cout << "									  " << "\n";
}

// Print statistics
void PrintStats(TF1 *g1, Int_t &cont, Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean, Float_t &integral)
{ 	using namespace std;	
	Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2 y rebinin
	chis = g1->GetChisquare();  
	ndf= g1->GetNDF();
	chiondf=chis/ndf;
	cout << "*******************************************************************" << endl;
	cout << " X2: " << chis << " -- ndf: " << ndf << " --  X2/ndf: " << chiondf  << " --  Reb: x"<< cont*2 << endl;
	cout << " E.R.: "<< r << "+" << dr << "   --  P.H.: "<< mean << "+" << dmean << endl;
	cout << "*******************************************************************" << endl;      
	cout << "								    " << "\n";
}

// Print Legend
void PrintLegend(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 	
using namespace std;	
//Int_t m; 
char ar[100];
TLegend *legend=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.92,0.52,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}


// Print 2nd. Legend 
void PrintLegend2(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 
char ar[100];
using namespace std;	
TLegend *legend=new TLegend(0.57,0.87,0.90,0.92); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.87,0.52,0.92);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}



// Print 3rd. Legend 
void PrintLegend3(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 	 
char ar[100];
using namespace std;	
TLegend *legend=new TLegend(0.57,0.82,0.90,0.87); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.82,0.52,0.87);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}




// Print Latex 
void PrintLatex(Text_t *text, Int_t position, Int_t color, Int_t number)
{ 
using namespace std;	
TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.05);
tx1->SetTextColor(color);
Float_t posx=0,posy=0;
if (position==1) {posx=0.2; posy=0.9-number*0.05;}      // left - superior
if (position==2) {posx=0.8; posy=0.9-number*0.05;} 	// right -superior
if (position==3) {posx=0.2; posy=0.2-number*0.05;}   	// left - inferior
if (position==4) {posx=0.8; posy=0.2-number*0.05;} 	// right - inferior
tx1->DrawLatex(posx,posy,text);
}

// Print Latex 2
void PrintLatex2(Text_t *text, Float_t posx, Float_t posy, Int_t color)
{ 
using namespace std;	
TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.05);
tx1->SetTextColor(color);
tx1->DrawLatex(posx,posy,text);
}




////////////////////////////////////////////  putting the log-scale in the 2D histogram.


void LogAxis(Float_t &mx, Float_t &Mx, Float_t &my, Float_t &My, Int_t &nbins, Double_t *xbins, Double_t *ybins)
{
Double_t logxmin = TMath::Log10(mx*0.9); //cout << "logxmin=" << logxmin << "  logxmax=" << logxmax <<  endl;
Double_t logxmax = TMath::Log10(Mx*1.5); //cout << "logymin=" << logymin << "  logymax=" << logymax <<  endl;
Double_t logymin = TMath::Log10(my*0.9);
Double_t logymax = TMath::Log10(My*1.5);
Double_t xbinwidth = (logxmax-logxmin)/nbins; //cout << "xbinwidth=" << xbinwidth <<  endl;
Double_t ybinwidth = (logymax-logymin)/nbins;//cout << "ybinwidth=" << ybinwidth <<  endl;
xbins[0] = mx;
ybins[0] = my;
for (Int_t i=1;i<nbins+1;i++) 
	{
 	xbins[i] = mx + TMath::Power(10,logxmin+i*xbinwidth);
 	ybins[i] = my + TMath::Power(10,logymin+i*ybinwidth);
   	}

}
