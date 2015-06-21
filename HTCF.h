//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
//***************************** FUNCTIONS DECLARATIONS **********************************

// READ HTCF FILES
void Read_OE1D(char *file, Float_t *x, Float_t *y, Int_t &n);
void Plot_OE1D(TGraph *gr,Int_t first, Int_t Color);

void Read_PXR(char *file, Float_t *x, Float_t *y, Int_t &n);
void Plot_PXR(TGraph *gr, Int_t first, Int_t Color);
void Plot_PXRh(TH1F *gr, Float_t *x, Float_t *y, Int_t first, Int_t Color, Int_t &n);

void Read_XRL(char *file, Float_t *x, Float_t *y, Int_t &n);
void Plot_XRL(TH1F *gr, Int_t first, Int_t Color);

void Read_XRD(char *file, Float_t *x, Float_t *y, Int_t &n);
void Plot_XRD(TGraph *gr, Float_t *x, Float_t *y, Int_t n, Int_t first, Int_t Color);

// Get File - attributes
void GetInfo(char *file,  char *sample, char *scint, char *dopant);
void GetInfo(char *file,  char *sample, char *scint);
void GetInfo(char *file,  char *sample);
void GetCompound(char *scint, char *dopant, char *compound);




//***************************** FUNCTIONS DECLARATIONS **********************************

// READ FILMETRICS TRANSMISSION-REFLECTION FILES in energy
void Read_OE1D(char *file, Float_t *x, Float_t *y, Int_t &n)
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
	n=i-1;
	}

}

void Plot_OE1D(TGraph *gr,Int_t first, Int_t Color)
{
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr->SetMarkerColor(Color);	
gr->SetMarkerSize(1);					
gr->SetMarkerStyle(20);					
gr->SetTitle(title);	
gr->GetXaxis()->SetTitle("Wavelength (nm)");
gr->GetYaxis()->SetTitle("Transmittance (%)");		
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
gr->GetXaxis()->SetRangeUser(200,1100);	
if (first==1) gr->Draw("Apl");
else gr->Draw("samepl");
}



void Read_PXR(char *file, Float_t *x, Float_t *y, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
Float_t bl=0;
char ci[100];
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	*in >> ci; *in >> ci;*in >> ci; *in >> ci;*in >> ci; *in >> ci;*in >> ci; // removes the header
	while (!in->eof())
		{
		*in >> x[i] >> y[i]; 
		//if (i==0) cout << x[i] << endl; 
		i++;
		}
	n=i-1;
	}

for (int i=0; i<10; i++)
	bl=bl+y[i];
bl=bl/10;
for (int i=0; i<n; i++)
	y[i]=y[i]-bl;	// removes the baseline

}



void Plot_PXR(TGraph *gr, Int_t first, Int_t Color)
{
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr->SetMarkerColor(Color);						
gr->SetMarkerStyle(20);					
gr->SetTitle(title);	
gr->GetXaxis()->SetTitle("Time (ns)");
gr->GetYaxis()->SetTitle("Intensity (a.u.)");					
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
if (first==1) gr->Draw("Al");
else gr->Draw("samel");
}



 
void Plot_PXRh(TH1F *H, Float_t *x, Float_t *y, Int_t first, Int_t Color, Int_t &n)
{
char title[100]="";
H->SetLineColor(Color);

H->SetMarkerColor(Color);
H->SetLineColor(Color);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Time (ns)");
H->GetYaxis()->SetTitle("Intensity (a.u.)");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();
H->Rebin(1);

for (Int_t k=0;k<n;k++)
	{
	H->Fill(k,y[k]);
	}

if (first==1) H->Draw();
else H->Draw("samel");
}



/*

*/


void Read_XRL(char *file, Float_t *x, Float_t *y, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i;
char ci[100];
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=0;
	*in >> ci; *in >> ci;*in >> ci;  // Removes the header
	while (!in->eof())
		{
		*in >> x[i] >> y[i]; 
		//cout << y[i] <<endl;
		i++;
		}
	n=i;
	}
}




void Plot_XRL(TGraph *gr, Int_t first, Int_t Color)
{
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr->SetMarkerColor(Color);						
gr->SetFillColor(19);
gr->SetMarkerStyle(8);					
gr->SetTitle(title);	
gr->GetXaxis()->SetTitle("Wavelength (nm)");
gr->GetYaxis()->SetTitle("Intensity (a.u.)");					
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
gr->GetXaxis()->SetRangeUser(230,950);	
if (first==1) gr->Draw("AC");
else gr->Draw("same");
}








void Read_XRD(char *file, Float_t *x, Float_t *y, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i;
char ci[100];
ifstream *in = new ifstream(file);
if(!*in)cout << " ERROR OPENING FILE " <<  file << endl; 
else    {
	i=0;
	*in >> ci; cout << ci << endl;
	*in >> ci; cout << ci << endl;
	*in >> ci; cout << ci << endl;
	*in >> ci;  cout << ci << endl;
	*in >> ci; cout << ci << endl;  // Removes the header
	*in >> ci; cout << ci << endl; 
	*in >> ci; cout << ci << endl; 
	*in >> ci;  cout << ci << endl;
	*in >> ci; cout << ci << endl;  // Removes the header
	while (!in->eof())
		{
		*in >> x[i] >> y[i]; 
		i++;
		}
	n=i;
	}
}




void Plot_XRD(TH1F *gr, Float_t *x, Float_t *y, Int_t n, Int_t first, Int_t Color)
{
for (Int_t k=0;k<n-1;k++)			
	gr->Fill(x[k],y[k]);		
char title[100]="";
gr->SetLineColor(Color);					
gr->SetLineWidth(2);	
gr->SetFillColor(0);		
gr->SetMarkerColor(Color);						
gr->SetMarkerStyle(8);					
gr->SetTitle(title);	
gr->GetXaxis()->SetTitle("2\\Theta (deg)");
gr->GetYaxis()->SetTitle("Intensity (a.u.)");					
gr->GetXaxis()->SetTitleSize(0.05);
gr->GetYaxis()->SetTitleSize(0.05);
gr->GetXaxis()->SetLabelSize(0.05);
gr->GetYaxis()->SetLabelSize(0.05);
gr->GetXaxis()->SetTitleOffset(0.90);
gr->GetYaxis()->SetTitleOffset(0.90);
gr->GetXaxis()->CenterTitle();					
gr->GetYaxis()->CenterTitle();	
gr->GetXaxis()->SetRangeUser(20,48);	

TH1 *backY;
backY=gr->ShowBackground(20);
backY->SetLineColor(0);
gr->Add(backY,-1);
if (first==1) gr->Draw();
else gr->Draw("same");
}



























////////////////////////////// info file functions

void GetInfo(char *file,  char *sample, char *scint, char *dopant)
{
char *sepa,f[100]="";
sprintf(f,"%s",file);
sepa=strtok(f,"-");
sprintf(sample,"%s",sepa);
std::cout << "sample# = "<< sample << std::endl;
sepa=strtok(NULL,"-"); /// go back to -
sprintf(scint,"%s",sepa);
std::cout << "scint = "<< scint << std::endl;
sepa=strtok(NULL,"-"); /// go back to -
sprintf(dopant,"%s",sepa);
if (strstr(dopant,"PXray")!= NULL) sprintf(dopant," "); //std::cout << "dopant = YES "<< std::endl;
if (strstr(dopant,"OptEx")!= NULL) sprintf(dopant," "); //std::cout << "dopant = YES "<< std::endl;
std::cout << "dopant = "<< dopant << std::endl;
}


void GetInfo(char *file,  char *sample, char *scint)
{
char *sepa,f[100]="";
sprintf(f,"%s",file);
sepa=strtok(f,"-"); /// go back to - 
sprintf(sample,"%s",sepa);
std::cout << "sample# = "<< sample << std::endl;
sepa=strtok(NULL,"-");  /// go back to - 
sprintf(scint,"%s",sepa);
std::cout << "scint = "<< scint << std::endl;
std::cout << "**************************************"<< std::endl;
}

void GetInfo(char *file,  char *sample)
{
char f[100]="";
sprintf(f,"%s",file);
sprintf(sample,"%s",f);
std::cout << "sample# = "<< sample << std::endl;
std::cout << "**************************************"<< std::endl;
}





void GetCompound(char *scint, char *dopant, char *compound)
{
Int_t dig=0,dop=1,lenscint=(unsigned)strlen(scint);
Int_t lendopant=(unsigned)strlen(dopant); 
std::string str;


for (int i=0; i<lenscint; i++)
	{
	if (isdigit(scint[i]))
		{
		dig=atoi(&scint[i]);
		if (dig==0)
			{			
			str.append("_{");
			str.append(scint,i,1);
			str.append(".");
			str.append(scint,i+2,1);
			str.append(scint,i+3,1);
			str.append(scint,i+4,1);
			str.append("}");
			i=i+4;	
			}
		else
			if ((dig!=1))
				{			
				str.append("_{");
				str.append(scint,i,1);
				str.append("}");
				}




		}
	else
		{
		str.append(scint,i,1);  
 		}
    
  	}

if (strstr(dopant, "OptEx") != NULL)
	{
	std::cout << " no dopant "<< std::endl;
	dop=0;
	}

if (strstr(dopant, "XRL") != NULL)
	{
	std::cout << " no dopant "<< std::endl;
	dop=0;
	}	

if (strstr(dopant, " ") != NULL)
	{
	dop=0;
	}	

else
	{
	for (int i=0; i<lendopant; i++)
		{
		if (isdigit(dopant[i]) && (!isdigit(dopant[i+1]))&&(i<lendopant))
			{
			if (i==0)			
				{str.append("(");
				str.append(dopant,i,1);
				str.append("% ");
				}
			else
				{
				//str.append("^{");
				//str.append(dopant,i,1);
				//str.append("+}");
				}
			}
		else
			str.append(dopant,i,1); 

		}
		
	if (dop!=0) str.append(")");

	}

 

int len2=str.length();
for (int a=0;a<len2;a++)
            compound[a]=str[a];
std::cout << "compound = "<< compound << std::endl;



std::cout << "**************************************"<< std::endl;
}




