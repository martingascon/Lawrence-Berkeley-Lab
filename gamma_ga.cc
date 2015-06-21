 //************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 		// ****** Own functions


using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.


int main(int argc, char **argv)
{
//********************************** variable declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t k,a=1,b=1000,cont=0,reb=1,N=8192; //i  
Float_t par[3],dpar[3],r,dr,r2,dr2,data[N],x[N],y[N],sig_left=1.8,sig_right=1.8,days=0,integral=0; 		      
Char_t file[100],title[150]="",res;//,ci[100]="";
TH1I *H = new TH1I("H",file,8192,0,8191); 
gROOT->SetStyle("Bold");


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(file,"%s",argv[1]);		// FILENAME 	
		break;						 
	case 3: sprintf(file,"%s",argv[1]);		// FILENAME REB
		reb=atoi(argv[2]);			//REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;
	case 4: sprintf(file,"%s",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);		
		break;
	case 5: sprintf(file,"%s",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		reb=atoi(argv[4]);	
		break;		
	default:
		MsgError();
		exit(1);
		break;

	};   


Read_GV2(file, data,days,N);

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=data[k];
	H->Fill(x[k],y[k]);
	}
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();
H->Rebin(reb);


TF1 *g2 = new TF1("g2","gaus",a,b);          // this is used to find the best rebining - begin
TH1I *h2 = (TH1I*)H->Clone("h2");                 

H->Fit(g2,"QR"); 
ifstream *in2 = new ifstream(".param3.txt");
		if(!*in2) 
			cout << " No previous file with parameters was found "  << endl; 
		else    {
			*in2 >> par[0];
			*in2 >> par[1];
			*in2 >> par[2];
			g2->SetParameters(par[0],par[1],par[2]); 
			}


par[0] = g2->GetParameter(0); 
par[1] = g2->GetParameter(1); 
par[2] = g2->GetParameter(2);
/*
dpar[0] = g2->GetParError(0);
dpar[1] = g2->GetParError(1);
dpar[2] = g2->GetParError(2);

*/
					
a=Int_t(par[1]-sig_left*par[2]);                            // sig_left and sig_right are the values to integrate 
b=Int_t(par[1]+sig_right*par[2]);				// on the left and on the right of the peak (default: 1.8)

integral=h2->Integral(a,b);
cout << integral << endl;
Int_t final=0;				// this is used to find the best rebining -  begin

do 
{	H->Fit(g2,"QR");
	Resol_ga(g2,r,dr);
	h2->Rebin(2);
	h2->Fit(g2,"QR");
	Resol_ga(g2,r2,dr2);


	if (r>r2) 
		{
		H=h2;
		cont++;
		}
	else
		final=1;
}
while ((final==0)&&(cont<15));              // this is used to find the best rebining - end


cout << "value for a: " << a << ", value for b: " << b << endl;

H->Fit(g2,"QR"); 
g2->SetLineColor(4);

Resol_ga(g2,r,dr);

H->Draw();


par[0] = g2->GetParameter(0); 
par[1] = g2->GetParameter(1); 
par[2] = g2->GetParameter(2);
dpar[0] = g2->GetParError(0);
dpar[1] = g2->GetParError(1);
dpar[2] = g2->GetParError(2);
	

PrintStats(g2,cont,r,dr,par[1],dpar[1],integral);
PrintLegend(r2,dr2,par[1],dpar[1]);


gStyle->SetOptStat(0);   
gStyle->SetOptFit(0);     
theApp->Run(kTRUE);

cout << "Do you want to save your data into data.txt (y/n)?" << endl;  
cin >> res;
if (res=='s'||res=='y')
  	{
	ofstream *out = new ofstream("PHvsTime.txt",ios::app);
	ofstream *dat = new ofstream(".param3.txt",ios::trunc);
	*out <<  std::fixed << std::setprecision(4) << days << "\t"  << 0.0014 << "\t" << std::fixed << std::setprecision(1) <<par[1]<<"\t"<< dpar[1]*3<<"\t"<<r<<"\t"<<dr<<endl;	
	*dat << par[0] << "\t" << par[1] << "\t" << par[2] << endl;
	}
else
	exit(1);



delete theApp;
return 0;
}
