//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

//#define COLUMNS 6
#define GRAPH 1

//#define OBJ 0.05 //40x           
//#define OBJ 0.20 //10x
#define OBJ 0.1333333//15x

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  
set_plot_style();

// DECLARATION OF VARIABLES
Int_t i,k,p, points=0, N=1000,aux=0,cols=1,rows=1;
Float_t x[N],y[N],z[N],xc[N],yc[N],xpos[N],ypos[N]; 	
char ci[100]="",file[100],ci2[100],ci3[100]="",ci4[100]="",ci5[100]="",ci6[100]="",*sepa;

// OUTPUT FILES
ofstream *out = new ofstream("Positions.txt",ios::app);


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(file,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
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
	i=0;

	do						
	 	{
	 	*in >> ci;  
		if (strstr(ci,"decays:")!=NULL) 
			{ *in >> ci; points=atoi(ci)+1;	}		 
		if (strstr(ci,"Intensity")!=NULL)   
			aux=1;
	 	} 
	while (aux==0);  
	i=0;
	while (!in->eof())
		{
		//if (COLUMNS==4) {*in >> ci >> ci2 >> ci3 >> ci4;}
		//if (COLUMNS==5) {*in >> ci >> ci2 >> ci3 >> ci4 >> ci5;}
		//if (COLUMNS==6)	{
		*in >> ci >> ci2 >> ci3 >> ci4; //}
		sepa=strtok(ci2,".");  // corto .
		x[i] = atoi(sepa);
		sepa=strtok(ci3,".");  // corto .
		y[i] = atoi(sepa);
		sepa=strtok(ci4,".");  // corto .
		z[i] = atoi(sepa);
		cout << "z= "<< z[i] << endl;
		i++;
		}
	
	for (k=0;k<points;k++)  // para ver el numero de columnas
		{
		if ((y[k]-y[0])!=0)
			{
			cols=k;
			k=points;
			}	
		}

	rows=points/cols;

	cout << "Objective: " << 2/OBJ << "x" << endl;
	cout << "Total points: " << points << " //  Rows: " << rows << " // Cols: " << cols << endl;
	cout << " ************************** " << endl;
	Float_t px = x[1]-x[0];
	Float_t py = y[0+cols]-y[0];
	cout << "semi-step in x: " << px/2 << " pts" <<  " // semi step in y: " << py/2 << " pts" << endl;
	cout << "semi-step in x: " << OBJ*px/2 << " um" <<  " // semi step in y: " << OBJ*py/2 << " um" << endl;
	cout << " ************************** " << endl;
	cout << "real X positions: " << endl;
	for (k=0;k<cols;k++) 
		cout << " " << x[k]; cout << " " << endl;
	cout << "real Y positions: "<< endl;
	Int_t l=0;			
	for (k=0;k<points;k++)
		{
		if ((k==0)||(k%cols)==0)
			{
			cout << " " << y[k];
			l++;
			}	
		}
	cout << " " << endl;
	*out << rows << "\t"  << cols << endl; // first the number of rows and cols
	for (k=0;k<points;k++)
		{
		xc[k]=OBJ*(x[k]-px/2); 
		yc[k]=OBJ*(y[points-1-k]-py/2); // le doy la vuelta a la Y
		*out <<  std::fixed << std::setprecision(1) << xc[k] << "\t"  << yc[k] << endl;	
		}
	delete out;
	xc[points]=OBJ*(x[k]+px/2);
	yc[points]=OBJ*(yc[k]);

	
	cout << " ************************** " << endl;
	cout << "Displaced X positions" << endl;
	for (k=0;k<cols;k++)	
		cout << " " << x[k]-px/2;
	cout << " " << endl;
	cout << "Displaced Y positions: " << endl;
	l=0;			
	for (k=0;k<points;k++)
		{
		if ((k==0)||(k%cols)==0)
			{
			cout << " " << y[k]-py/2;
			l++;
			}	
		}
	cout << " " << endl;
	cout << " ************************** " << endl;
	cout << "X positions corrected: "<< endl;
	for (k=0;k<cols;k++)	
		{		
		xpos[k]=OBJ*(x[k]-px/2);
		cout << " " << xpos[k];
		}
	xpos[cols]=xpos[cols-1]+OBJ*px;		// pos. final-1
	xpos[cols+1]=xpos[cols]+OBJ*px;
	cout << " " << endl;
	cout << "Y positions corrected: "<< endl;
	l=0;			
	for (k=0;k<points;k++)
		{
		if ((k==0)||(k%cols)==0)
			{
			//cout << " k= "<< k<<endl;
			ypos[l]=OBJ*(y[k]-py/2);
			cout << " " << ypos[l];
			l++;
			}	
		}	
	ypos[l]=ypos[l-1]+OBJ*py;
	ypos[l+1]=ypos[l]+OBJ*py;
	cout << " " << endl;   
	cout << " ************************** " << endl;


	TCanvas *c2 = new TCanvas("c2","OE Decay Mapping",100,100,500*cols/rows*py/px,500); 
	c2->SetFillColor(0);
	c2->GetFrame()->SetFillColor(0); 
	c2->GetFrame()->SetBorderMode(-1);
	TVirtualPad *vp =  c2->cd(1);
	vp->SetFillColor(10);
	vp->SetBorderSize(2);
	vp->SetFrameFillColor(0);
	vp->SetLeftMargin(.15);
	vp->SetRightMargin(.15);		
	vp->SetBottomMargin(.1);
	vp->SetTopMargin(.05);


	TGraph2D *H2 = new TGraph2D(points,xc,yc,z);   
	H2->SetNpy(499);  
	H2->SetNpx(499);
	H2->SetMarkerStyle(21);
	H2->SetMarkerSize(0.1);	   
	
	H2->Draw("colz"); 
       /* for (p=0;p<points;p++)
			{
			TBox *box1 = new TBox(xc[p],yc[p],xc[p]+0.5,yc[p]+0.5); 			box1->SetFillStyle(0);
   			box1->SetLineColor(1);
			box1->Draw();
			}*/	   
	ReverseYAxis(H2);
	H2->GetYaxis()->SetLabelSize(0);
	H2->GetXaxis()->SetTitle("Position X (#mum)");
	H2->GetYaxis()->SetTitle("Position Y (#mum)");
	H2->GetXaxis()->SetTitleOffset(1.2);
	H2->GetYaxis()->SetTitleOffset(1.6);
	H2->GetXaxis()->CenterTitle();
	H2->GetYaxis()->CenterTitle();	
	PrintLatex_small(Form("%s [%s]","OE-integral",argv[1]),0.18,0.98,kBlack);



}



#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
