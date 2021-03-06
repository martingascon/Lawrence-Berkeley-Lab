//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 
#include "HTCF.h"

#define GAUSSIANS 1 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

	      
Char_t f1[100],ci[2048]="";
Float_t OBJ = 0.05; // 40x   OBJ=0.20 //10x  OBJ=0.1333333 //15x

gROOT->SetStyle("Plain"); 
gStyle->SetOptTitle(0); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(1);     // display fit parameters 1 = on, 0 = off
set_plot_style();

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: sprintf(f1,"%s.dat",argv[1]);		// FILENAME 	
		break;						 

	case 3: sprintf(f1,"%s.dat",argv[1]);		// FILENAME 	
		OBJ=atof(argv[2]);			// Objective default 40x 
		OBJ=2/OBJ;   				// conversion to scale
		break;				 
default:
		MsgError();
		exit(1);
		break;

	};   

//GetInfo(f1,sample,scint,doped);

cout << "***************************"<< endl;
//sprintf(title,"Optical Excitation Mapping- %s - Sample %s ",scint,sample);
//GetCompound(scint,doped,scint);
Float_t x[1000],y[1000],xpos[1000],ypos[1000],xc[1000],yc[1000];
Char_t ci2[2000],*sepa,*sepa2;
Int_t l,k;

ifstream *in = new ifstream(f1);
if(!*in)
	{
	cout << " ERROR OPENING FILE " <<  f1 << endl; 
	}
else  
	{
	*in >> ci;  //cout << "ci: " << ci <<  endl;	// removes "wavelengths"
	Int_t p=0,aux=0,rows=0,cols=1,ref=0;		
	///////// reads the coordinates		// (x1,y1) (x2,y1) ... (xn,y1) (x2,y2) .. (xn,y2) etc.	
	do						
	 	{
	 	*in >> ci;  			 
		if (strstr(ci,"(")==NULL)  // todas las que tengan un parentesis
			aux=1;
		else
			{	
			sprintf(ci2,"%s",ci);	// lo copio a ci2
			sepa=strtok(ci2,"(,)");  // corto o parentesis o coma
			sepa2=strtok(NULL,"(,)"); // corto coma
			x[p] = atoi(sepa); 	// convierto a entero 
			y[p] = atoi(sepa2);
			if (p==0) ref=y[p];	// tomo el primer y1
			if ((p>0)&&(y[p]==ref))	// siempre que sea mayor que 0 & igual a la ref
				cols=cols+1;	// counting columns (only 1st row)					
			//cout << "x[p]= "<< x[p] << " // y[p]= " <<y[p] << endl;
			p++;
			}
	 	} 
	while (aux==0);  
	/////////////////////////// PRINTS THE SUMMARY
	Int_t points=p;
	rows=points/cols;	
	cout << "Objective: " << 2/OBJ << "x" << endl;
	cout << "Total points: " << points << " //  Rows: " << rows << " // Cols: " << cols << endl;

	/// x e y contienen las posiciones que leo del archivo (son el centro del cuadrado)	
	cout << "real X positions:";
	for (k=0;k<cols;k++) cout << " " << x[k]; cout << " " << endl;   
	cout << "real Y positions: "; l=0; 			
	for (k=0;k<points;k++) // tengo que leer una cada vez que cambiamos de fila -> k%cols==0
		if ((k==0)||(k%cols)==0) {cout << " " << y[k];l++;}	
	cout << " " << endl;

	////////////////////// calculo semi-steps
	
	Float_t minv=10e6, maxv=0;
	Float_t px = x[1]-x[0];
	Float_t py = y[0+cols]-y[0];
	cout << "semi-step in x: " << px/2 << " pts" <<  " // semi step in y: " << py/2 << " pts" << endl;
	cout << "semi-step in x: " << OBJ*px/2 << " um" <<  " // semi step in y: " << OBJ*py/2 << " um" << endl;
	////////////////////////// posiciones reales: xc, yc son transformadas del centro al borde.
	for (k=0;k<points;k++)  
		{
		xc[k]=OBJ*(x[k]-px/2); 
		yc[k]=OBJ*(y[points-1-k]-py/2); // le doy la vuelta a la Y ..... why?
		//yc[k]=OBJ*(y[k]-py/2);
		}
	cout << "X positions";
	for (k=0;k<cols;k++) cout << " " << x[k]-px/2; cout << " " << endl;
	cout << "Y positions: ";l=0;			
	for (k=0;k<points;k++)
		if ((k==0)||(k%cols)==0) {cout << " " << y[k]-py/2;l++;}	
	cout << " " << endl;


	cout << " ************************** " << endl;
	cout << "X positions corrected: ";


	for (k=0;k<cols;k++)	
		{		
		xpos[k]=OBJ*(x[k]-px/2);
		cout << " " << xpos[k];
		}
	xpos[cols]=xpos[cols-1]+OBJ*px;		// pos. final-1
	xpos[cols+1]=xpos[cols]+OBJ*px;
	//cout << " " << xpos[rows] << endl;
	cout << " " << endl;
	cout << "Y positions corrected: ";
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
	//cout << " " << ypos[l] << endl;   
	cout << " " << endl;   
	
  

	Float_t emis[1000],value[1500][points];     // cargamos todo en la puta tabla 
	aux=1;
	k=0;
	emis[0] = atof(ci);
	while (!in->eof()) 
		{
		for (p=0;p<points+1;p++)//			
			{
			
			if ((k==0)&&(p==0)) cout <<  ci << " ";
			else
			*in >> ci; 
			//cout <<  ci << " ";
			if (p==0) 
				{emis[k] = atof(ci); }		// primer elemento: WLenght
				//cout <<  emis[k] << ": - ";}// } 
			else 
				{
				value[k][p-1]=atof(ci); // 2, 3, 4... k is point, p-1 are intensities 	
				//if (p==0) cout <<  value[k][p-1] << " ";
				//cout << p << " " <<  p%(cols) << " " << cols-1-(int)p/(cols) << endl;
				if (value[k][p-1]<minv) minv=value[k][p-1]; // find min value of the matrix
				if (value[k][p-1]>maxv) maxv=value[k][p-1]; // find max value of the matrix
				}
			
			}
		k++;
		}

	///////////////////////////////////////////////////// pasos en emision e.g. 320 330 .. 600 nm.
	Int_t msteps=k-1;  	// el ultimo es mierda  
 	emis[msteps]= emis[msteps-1]+(emis[msteps-1]-emis[msteps-2]); // next emission step would be...
	cout << "Emission steps: "<< msteps << " from: " << emis[0] << " to " << emis[msteps-1] << " nm" << endl;
	cout << "min: "<< minv << " // max:" << maxv << endl;


	///////////////////////////////////////////////////// IF ALL IS CORRECT WE CONTINUE
	char res;
	cout << "Is all this correct? (y/n)?" << endl;  
	cin >> res;
 	if (res=='y')
		{
		TCanvas *c1 = new TCanvas("c1","OE",1700,100,555*cols/rows*1.15,555);				// all the pulses
		c1->SetFillColor(0);	
		c1->GetFrame()->SetFillColor(0); 
		c1->GetFrame()->SetBorderMode(-1);
		c1->GetFrame()->SetBorderSize(10);		
		c1->Divide(cols,rows);	
		//c1->Divide(10,10);

		//Int_t a[points];	
		Float_t p0[points],p1[points],p2[points],q0[points],q1[points],q2[points]; // componentes de 1/2 Gaussian 
		Float_t em[msteps],eme[msteps],emise[msteps];	 // vectores que contienen emision(lambda), emission(eV),  
		

		Float_t emeall[msteps];       		// contiene la suma de todos los emission
		for (k=0;k<msteps;k++) emeall[k]=0;  	// inicializo el vector
		TGraph *gr0[points]; 			// Declaro tantos graficos como puntos tengo
		TGraph *gr0all;				// Declaro grafico suma
		//points=100;
		for (p=0;p<points;p++)	
 			{
			for (k=0;k<msteps;k++)
				em[k]=value[k][p]-value[0][p];//;		//; // emision de 1 punto //cout << value[k][p] << endl;		
			W2E(emis,em,emise,eme,msteps);  		// Emis=X, em=Intensities, emise(X corregidas, eme=(Y corregidas), 
			for (Int_t j=0;j<msteps;j++) 
					emeall[j]=emeall[j]+eme[j]; 	// cargo en emeall el calculado
			for (k=0;k<msteps;k++)
				gr0[p] = new TGraph(msteps,emise,eme);
			gr0[p]->SetLineColor(4);					
			gr0[p]->SetLineWidth(2);			// Line color 0=white 	1=black, 2=red
			gr0[p]->SetMarkerColor(4);						
			gr0[p]->SetMarkerStyle(20);					
			gr0[p]->GetXaxis()->SetTitleSize(0.05);
			gr0[p]->GetYaxis()->SetTitleSize(0.05);
			gr0[p]->GetXaxis()->SetLabelSize(0.05);
			gr0[p]->GetYaxis()->SetLabelSize(0.05);
			gr0[p]->GetXaxis()->SetTitleOffset(0.90);
			gr0[p]->GetYaxis()->SetLabelSize(0.05);
			gr0[p]->GetXaxis()->SetTitle("Energy (eV)");
			gr0[p]->GetYaxis()->SetTitle("Intensity (a.u.)");
			gr0[p]->GetXaxis()->CenterTitle();					
			gr0[p]->GetYaxis()->CenterTitle();	
			} 


		///////////////////////////////////////////////////////////////////////////////////////////  Ahora ploteo el grafico con la suma
		//for (Int_t j=0;j<msteps;j++) emeall[j]=emeall[j]/points;
		TCanvas *c1all = new TCanvas("c1all","All",1700,750,555*cols/rows*1.15,555);	// 1 pulse
		c1all->SetFillColor(0);	
		c1all->GetFrame()->SetFillColor(0); 
		c1all->GetFrame()->SetBorderMode(-1);
		c1all->GetFrame()->SetBorderSize(10);

		gr0all = new TGraph(msteps,emise,emeall);
		gr0all->SetLineColor(4);					
		gr0all->SetLineWidth(2);			// Line color 0=white 	1=black, 2=red
		gr0all->SetMarkerColor(4);						
		gr0all->SetMarkerStyle(20);					
		gr0all->GetXaxis()->SetTitleSize(0.05);
		gr0all->GetYaxis()->SetTitleSize(0.05);
		gr0all->GetXaxis()->SetLabelSize(0.05);
		gr0all->GetYaxis()->SetLabelSize(0.05);
		gr0all->GetXaxis()->SetTitleOffset(0.90);
		gr0all->GetYaxis()->SetLabelSize(0.05);
		gr0all->GetXaxis()->SetTitle("Energy (eV)");
		gr0all->GetYaxis()->SetTitle("Intensity (a.u.)");
		gr0all->GetXaxis()->CenterTitle();					
		gr0all->GetYaxis()->CenterTitle();	
		gr0all->Draw("Ac");


		c1all->cd(1);	
		#if GAUSSIANS==1
			{
			TF1 *g1a   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",2.8,3.35);
			//TF1 *g1a   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",2.6,3.3);
			//TF1 *g1a   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",2.8,2.95); //*[4]/x
			//TF1 *g1a   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",emise[msteps-1],emise[0]);
			g1a->SetParameters(0.00807377,2.93638,0.121151); 	//for BaCl2(3%Eu)   //,3
			gr0all->Fit(g1a,"QR+");
			gr0all->Fit(g1a,"QR+");
			gr0all->Fit(g1a,"QR");
			p0[0] = g1a->GetParameter(0);
			p1[0] = g1a->GetParameter(1);
			p2[0] = g1a->GetParameter(2);
			PrintLatex2(Form("#lambda_{1} =%3.0f eV",1240/p1[0]),0.15,0.85,kRed);
			} 

		//TPaveStats *st = (TPaveStats*)gr0all->FindObject("stats");
      		//st->SetX1NDC(0.85);
		#endif 
		#if GAUSSIANS==2
			{
			TF1 *g2a   = new TF1("g2a","[0]*exp(-0.5*(((x-[1])/[2])^2))+[3]*exp(-0.5*(((x-[4])/[5])^2))",emise[msteps-1],emise[0]);
			//TF1 *g2a   = new TF1("g2a","[0]*exp(-0.5*(((x-[1])/[2])^2))+[3]*exp(-0.5*(((x-[4])/[5])^2))",2.7,3.4);


			//g2a->SetParameters(0.00807377,2.93638,0.121151,0.00997683,3.16415,0.15); //for BaCl2(3%Eu)*[6]/x
			g2a->SetParameters(0.9,2.8,0.015,3.05,3.1,0.07); //for BaCl2(3%Eu),0.33
			//g2a->SetParLimits(2,2.80,2.95);
			gr0all->Fit(g2a,"QR+");
			gr0all->Fit(g2a,"QR+");
			gr0all->Fit(g2a,"QR");
			p0[0] = g2a->GetParameter(0);
			p1[0] = g2a->GetParameter(1);
			p2[0] = g2a->GetParameter(2);
			q0[0] = g2a->GetParameter(3);
			q1[0] = g2a->GetParameter(4);
			q2[0] = g2a->GetParameter(5); 
			//if (p0[0]<0) p0[0]=-p0[0];if (p1[0]<0) p1[0]=-p1[0];if (p2[0]<0) p2[0]=-p2[0];   // les doy la vuelta si son negativos
			//if (q0[0]<0) q0[0]=-q0[0];if (q1[0]<0) q1[0]=-q1[0];if (q2[0]<0) q2[0]=-q2[0];   // los pongo en orden p1 primero
			TF1 *g2all   = new TF1("g2all","gaus",emise[msteps-1],emise[0]);		// dibujo los 
			g2all->SetParameters(p0[0],p1[0],p2[0]);
			TF1 *g2ball   = new TF1("g2ball","gaus",emise[msteps-1],emise[0]);
			g2ball->SetParameters(q0[0],q1[0],p2[0]);
			g2all->SetLineColor(kGreen+3);
			g2ball->SetLineColor(2);
			g2all->Draw("same");
			g2ball->Draw("same");
			PrintLatex2(Form("#lambda_{1} =%3.0f eV",1240/p1[0]),0.15,0.85,kRed);
			PrintLatex2(Form("#lambda_{2} =%3.0f eV",1240/q1[0]),0.15,0.75,kGreen+3);

			} 
		#endif 

		for (p=0;p<points;p++)	 // para cada punto hago lo siguiente
			{
			c1->cd(p+1);	
			gr0[p]->Draw("Al");
			#if GAUSSIANS==1
				{
				TF1 *g1   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",2.8,3.35); // for LaBaCl2(Eu)
				//TF1 *g1   = new TF1("g1","[0]*exp(-0.5*(((x-[1])/[2])^2))",2.6,3.3); // for LaBaCl2(Eu)
				//TF1 *g1   = new TF1("g1","gaus",emise[msteps-1],emise[0]);
				//TF1 *g1   = new TF1("g1","gaus",2.6,3.4); // for BaCl2(Eu)
				//TF1 *g1   = new TF1("g1","gaus",2.3,2.6); // for YAG(Ce)
				g1->SetLineColor(2);
				g1->FixParameter(1,p1[0]);
				g1->FixParameter(2,p2[0]);
				gr0[p]->Fit(g1,"QR+");
				gr0[p]->Fit(g1,"QR");
	

				p0[p] = g1->GetParameter(0);
				//p0[p] = p0[p]/(3.96517e-08*p*p-2.62828e-05*p+0.00720425)*0.0072;
				//p0[p] = p0[p]/(1.24292e-09*p*p*p*p-3.93855e-07*p*p*p+4.45894e-05*p*p-0.00218324*p+ 0.0554756)*0.05;
				p1[p] = g1->GetParameter(1);
				p2[p] = g1->GetParameter(2);
				//cout << p+1 << " "  << p0[p] <<  " "  << p1[p] <<endl;
				cout << p+1 << " "  << p0[p] <<  " "  << endl;			
				//cout << xc[p] << " "  << yc[p] <<  " "  << p0[p] <<endl;

				//if (p0[p]<0) {p0[p]=p0[p-1];p1[p]=p1[p-1];p2[p]=p2[p-1];}
				//a[p]=p0[p];
				//a[p]=p0[p]*p2[p]*2.506628273;  // 2.50066 = sqrt(2.pi)
				//a[p]=g1->Integral(emise[msteps-1],emise[0]);
				//a[p]=g1->Integral(2.6,3.7);
				//cout << p << " "  << p0[p] << " " << p1[p] << " " << p2[p] << endl;


				}
			#endif 
			#if GAUSSIANS==2
				{
				TF1 *g2   = new TF1("g2","[0]*exp(-0.5*(((x-[1])/[2])^2))+[3]*exp(-0.5*(((x-[4])/[5])^2))",emise[msteps-1],emise[0]);
				//TF1 *g2   = new TF1("g2","[0]*exp(-0.5*(((x-[1])/[2])^2))+[3]*exp(-0.5*(((x-[4])/[5])^2))",emise[msteps-1],emise[0]);
				g2->FixParameter(1,p1[0]);
				g2->FixParameter(2,p2[0]);
				g2->FixParameter(4,q1[0]);
				g2->FixParameter(5,q2[0]);

				gr0[p]->Fit(g2,"QR+");
				gr0[p]->Fit(g2,"QR+");
				gr0[p]->Fit(g2,"QR");
				p0[p] = g2->GetParameter(0);
				p1[p] = g2->GetParameter(1);
				p2[p] = g2->GetParameter(2);
				q0[p] = g2->GetParameter(3);
				q1[p] = g2->GetParameter(4);
				q2[p] = g2->GetParameter(5); // OR 2 or 5 depending on the previous def. 
				TF1 *g2a   = new TF1("g2a","gaus",emise[msteps-1],emise[0]);
				g2a->SetParameters(p0[p],p1[p],p2[p]);
				TF1 *g2b   = new TF1("g2b","gaus",emise[msteps-1],emise[0]);
				g2b->SetParameters(q0[p],q1[p],p2[p]);
				g2a->SetLineColor(kGreen+3);
				g2b->SetLineColor(2);
				g2a->Draw("same");
				g2b->Draw("same");

				
				cout <<p<<"p0,q0,p2,.. "<<p0[p]<<" "<<q0[p]<<" "<<p1[p]<<" "<<q1[p]<<" "<< p2[p]<<" "<<q2[p]<< endl;
				//a[p]=g2->Integral(emise[msteps-1],emise[0]);
				
				//g2a->Draw("same");
				//g2b->Draw("same");
				} 
			#endif 

			} 
	///////////////////////////////////////////////////////////////// first map ( Integral of the gaussian)
		
		
		TCanvas *c2 = new TCanvas("c2","OE Mapping TH2F (Integral)",0,600,555*cols/rows*1.15,555); 
		c2->SetFillColor(0);
		c2->GetFrame()->SetFillColor(0); 
		c2->GetFrame()->SetBorderMode(-1);
		c2->SetLogz();
		TVirtualPad *vp =  c2->cd(1);
		vp->SetFillColor(10);
		vp->SetBorderSize(2);
		vp->SetFrameFillColor(0);
		vp->SetLeftMargin(.15);
		vp->SetRightMargin(.15);		
		vp->SetBottomMargin(.1);
		vp->SetTopMargin(.05);

  		
		TH2F *H = new TH2F("H","H",cols,xpos,rows,ypos);    
	 	for (p=0;p<points;p++)                                             
			{
			H->SetBinContent(p%(cols)+1,rows-1-(int)p/(cols)+1,p0[p]);
	 		//cout << p << " " <<  p%(cols) << " " << rows-1-(int)p/(cols)<< " ";
			//cout << xpos[p%(cols)] << " " << ypos[rows-1-(int)p/(cols)] << endl;
			}
	        H->SetMarkerStyle(21);
		H->SetMarkerSize(0.1);
		H->GetXaxis()->SetTitle("Position X (#mum)");
		H->GetYaxis()->SetTitle("Position Y (#mum)");
	
		H->GetXaxis()->CenterTitle();
		H->GetYaxis()->CenterTitle();		
		H->GetXaxis()->SetTitleOffset(1.2);
		H->GetYaxis()->SetTitleOffset(1.6);
		//H->GetXaxis()->SetLimits(200,xpos[cols+1]);
   		//H->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
		H->SetContour(99); 
		//H->GetZaxis()->SetRangeUser(0.0092,0.0104);
		H->Draw("cont4z"); 
		ReverseYAxis(H);
		/**/

		////////////////////////////////////////////////  CON TGRAPH2D
		TGaxis::SetMaxDigits(4);

		TCanvas *c2b = new TCanvas("c2b","OE Mapping TGraph2D (Integral)",0,100,555*cols/rows*1.15,555); 
		c2b->SetFillColor(0);
		c2b->GetFrame()->SetFillColor(0); 
		c2b->GetFrame()->SetBorderMode(-1);
		TVirtualPad *vp2 =  c2b->cd(1);
		vp2->SetFillColor(10);
		vp2->SetBorderSize(2);
		vp2->SetFrameFillColor(0);
		vp2->SetLeftMargin(.15);
		vp2->SetRightMargin(.15);
		vp2->SetBottomMargin(.1);
		vp2->SetTopMargin(.05);

		TGraph2D *H2 = new TGraph2D(points,xc,yc,p0);   
        	//for (p=0;p<points;p++)
			//H2->SetPoint(p,xpos[p%(cols)],ypos[rows-1-(int)p/(cols)],p0[p]); // le doy la vuelta a la Y
		H2->SetNpy(499);  
		H2->SetNpx(499);
		H2->SetMarkerStyle(21);
		H2->SetMarkerSize(0.1);	   
		H2->GetXaxis()->SetLimits(xpos[0],xpos[cols+1]);
   		H2->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
		H2->GetZaxis()->SetRangeUser(0.0092, 0.0103);
		
		H2->GetZaxis()->SetRangeUser(0.0092,0.0104);

		H2->Draw("colz");     
 		ReverseYAxis(H2);	
		/*for (p=0;p<points;p++)
			{
			TBox *box1 = new TBox(x[p],y[p],x[p]+1,y[p]+1); 			box1->SetFillStyle(0);
   			box1->SetLineColor(1);
			box1->Draw();
			}*/
		H2->GetYaxis()->SetLabelSize(0);
		H2->GetXaxis()->SetTitle("Position X (#mum)");
		H2->GetYaxis()->SetTitle("Position Y (#mum)");
		H2->GetXaxis()->SetTitleOffset(1.2);
		H2->GetYaxis()->SetTitleOffset(1.6);
		H2->GetXaxis()->CenterTitle();
		H2->GetYaxis()->CenterTitle();	
		PrintLatex_small(Form("%s [%s]","OE-integral",argv[1]),0.3,0.98,kBlack);

	


	/////////////////////////////////////////////////////////////////////////////////////////////////////// second map ( AREA)

/*	TCanvas *c3 = new TCanvas("c3","OE-wavelenght",0,750,555*cols/rows*1.15,555);	 
	c3->SetFillColor(0);
	c3->GetFrame()->SetFillColor(0); 
	c3->GetFrame()->SetBorderMode(-1);
	c3->GetFrame()->SetBorderSize(10);	
	TVirtualPad *vp3 =  c3->cd(1);
	vp3->SetFillColor(10);
	vp3->SetBorderSize(2);
	vp3->SetFrameFillColor(0);
	vp3->SetLeftMargin(.15);
	vp3->SetRightMargin(.15);
	vp3->SetBottomMargin(.1);
	vp3->SetTopMargin(.05);
	
	Float_t lambda[points];
	for (p=0;p<points;p++)
		lambda[p]=1240/p1[p]; 
	

	TGraph2D *H3 = new TGraph2D(points,xc,yc,lambda);
	H3->SetMarkerStyle(21);
	H3->SetMarkerSize(0.1);
	H3->SetNpy(499);  
	H3->SetNpx(499);
	H3->Draw("ColZ"); 	
	ReverseYAxis(H3);
	H3->GetXaxis()->SetTitle("position X (#mum)");	
	H3->GetYaxis()->SetTitle("position Y (#mum)");
	H3->GetXaxis()->SetTitleOffset(1.2);
	H3->GetXaxis()->SetTitleOffset(1.2);
	H3->GetYaxis()->SetTitleOffset(1.6);
	H3->GetXaxis()->CenterTitle();
	H3->GetYaxis()->CenterTitle();	
	H3->GetYaxis()->SetLabelSize(0);		
	H3->SetMaximum(1240/GetMin(p1,points));
	H3->SetMinimum(1240/GetMax(p1,points));
	PrintLatex_small(Form("%s - %s","#lambda_{Max}",argv[1]),0.38,0.98,kBlack);
	

	TCanvas *c4 = new TCanvas("c4","OE Mapping (FWHM)",850,750,555*cols/rows*1.15,555);	// third map is centroid
 	c4->SetFillColor(0);
	c4->GetFrame()->SetFillColor(0); 
	c4->GetFrame()->SetBorderMode(-1);
	c4->GetFrame()->SetBorderSize(10);
	TVirtualPad *vp4 =  c4->cd(1);
	vp4->SetFillColor(10);
	vp4->SetBorderSize(2);
	vp4->SetFrameFillColor(0);
	vp4->SetLeftMargin(.15);
	vp4->SetRightMargin(.15);
	vp4->SetBottomMargin(.1);
	vp4->SetTopMargin(.05);
 	

	Float_t fwhm[points];
	for (p=0;p<points;p++)
		fwhm[p]=p2[p]*2.35; 

	TGraph2D *H4 = new TGraph2D(points,xc,yc,fwhm);
	H4->SetMarkerStyle(21);
	H4->SetMarkerSize(0.1);
 	H4->SetNpy(499);  
	H4->SetNpx(499);
	H4->Draw("ColZ");  
	ReverseYAxis(H4);
	H4->GetXaxis()->SetTitle("position X (#mum)");
	H4->GetYaxis()->SetTitle("position Y (#mum)");
	H4->GetXaxis()->SetTitleOffset(1.2);
	H4->GetYaxis()->SetTitleOffset(1.6);
	H4->GetXaxis()->CenterTitle();
	H4->GetYaxis()->CenterTitle();	
	H4->GetYaxis()->SetLabelSize(0);
	H4->SetMaximum(2.35*GetMax(p2,points));
	H4->SetMinimum(2.35*GetMin(p2,points));
	PrintLatex_small(Form("%s - %s","FWHM",argv[1]),0.34,0.98,kBlack);

*/
	//#if GAUSSIANS==1
	//{
	cout << argv[1] << endl;
	Char_t res2='s'; 
	cout << "Do you want to save your data into data.txt (y/n)?" << endl;  
	cin >> res2;
	if (res2=='s'||res2=='y')
		{
		c1-> SaveAs(Form("%s%s",argv[1],"_EMI.png"));
		c2b-> SaveAs(Form("%s%s",argv[1],"_INT1.png"));
		c1all -> SaveAs(Form("%s%s",argv[1],"_sEMI.png"));
		}

	//#endif
	//}
/**/
	#if GAUSSIANS==2
		{
		TCanvas *c2bb = new TCanvas("c2bb","OE Mapping TGraph2D (Integral)",850,100,555*cols/rows*1.15,555); 
		c2bb->SetFillColor(0);
		c2bb->GetFrame()->SetFillColor(0); 
		c2bb->GetFrame()->SetBorderMode(-1);
		TVirtualPad *vp2b =  c2bb->cd(1);
		vp2b->SetFillColor(10);
		vp2b->SetBorderSize(2);
		vp2b->SetFrameFillColor(0);
		vp2b->SetLeftMargin(.15);
		vp2b->SetRightMargin(.15);
		vp2b->SetBottomMargin(.1);
		vp2b->SetTopMargin(.05);

		TGraph2D *H2b = new TGraph2D(points,xc,yc,q0);   
		H2b->SetNpy(499);  
		H2b->SetNpx(499);
		H2b->SetMarkerStyle(21);
		H2b->SetMarkerSize(0.1);	   
		H2b->GetXaxis()->SetLimits(xpos[0],xpos[cols+1]);
		H2b->GetYaxis()->SetLimits(ypos[0],ypos[rows+1]);
		H2b->Draw("colz");     
		ReverseYAxis(H2b);	
		H2b->GetYaxis()->SetLabelSize(0);
		H2b->GetXaxis()->SetTitle("Position X (#mum)");
		H2b->GetYaxis()->SetTitle("Position Y (#mum)");
		H2b->GetXaxis()->SetTitleOffset(1.2);
		H2b->GetYaxis()->SetTitleOffset(1.6);
		H2b->GetXaxis()->CenterTitle();
		H2b->GetYaxis()->CenterTitle();	
		PrintLatex_small(Form("%s [%s]","OE-integral -2 ",argv[1]),0.38,0.98,kBlack);
/*
		TCanvas *c3b = new TCanvas("c3b","OE-wavelenght",100,850,555*cols/rows*1.15,555);	 
		c3b->SetFillColor(0);
		c3b->GetFrame()->SetFillColor(0); 
		c3b->GetFrame()->SetBorderMode(-1);
		c3b->GetFrame()->SetBorderSize(10);	
		TVirtualPad *vp3b =  c3b->cd(1);
		vp3b->SetFillColor(10);
		vp3b->SetBorderSize(2);
		vp3b->SetFrameFillColor(0);
		vp3b->SetLeftMargin(.15);
		vp3b->SetRightMargin(.15);
		vp3b->SetBottomMargin(.1);
		vp3b->SetTopMargin(.05);
	
		Float_t lambda2[points];
		for (p=0;p<points;p++)
			lambda2[p]=1240/q1[p]; 
		
		TGraph2D *H3b = new TGraph2D(points,xc,yc,lambda2);
		H3b->SetMarkerStyle(21);
		H3b->SetMarkerSize(0.1);
		H3b->SetNpy(499);  
		H3b->SetNpx(499);
		H3b->Draw("ColZ"); 	
		ReverseYAxis(H3b);
		H3b->GetXaxis()->SetTitle("position X (#mum)");	
		H3b->GetYaxis()->SetTitle("position Y (#mum)");
		H3b->GetXaxis()->SetTitleOffset(1.2);
		H3b->GetXaxis()->SetTitleOffset(1.2);	
		H3b->GetYaxis()->SetTitleOffset(1.6);
		H3b->GetXaxis()->CenterTitle();
		H3b->GetYaxis()->CenterTitle();	
		H3b->GetYaxis()->SetLabelSize(0);		
		H3b->SetMaximum(1240/GetMin(q1,points));	
		H3b->SetMinimum(1240/GetMax(q1,points));
		PrintLatex_small(Form("%s - %s","#lambda_{Max} -2 ",argv[1]),0.38,0.98,kBlack);
	

		TCanvas *c4b = new TCanvas("c4b","OE Mapping (FWHM)",950,850,555*cols/rows*1.15,555);	// third map is centroid
 		c4b->SetFillColor(0);
		c4b->GetFrame()->SetFillColor(0); 
		c4b->GetFrame()->SetBorderMode(-1);
		c4b->GetFrame()->SetBorderSize(10);
		TVirtualPad *vp4 =  c4->cd(1);
		vp4->SetFillColor(10);
		vp4->SetBorderSize(2);
		vp4->SetFrameFillColor(0);
		vp4->SetLeftMargin(.15);
		vp4->SetRightMargin(.15);
		vp4->SetBottomMargin(.1);
		vp4->SetTopMargin(.05);
 	

		Float_t fwhm2[points];
		for (p=0;p<points;p++)
			fwhm2[p]=q2[p]*2.35; 
		TGraph2D *H4b = new TGraph2D(points,xc,yc,fwhm2);
		H4b->SetMarkerStyle(21);
		H4b->SetMarkerSize(0.1);
 		H4b->SetNpy(499);  
		H4b->SetNpx(499);
		H4b->Draw("ColZ");  
		ReverseYAxis(H4b);
		H4b->GetXaxis()->SetTitle("position X (#mum)")	;
		H4b->GetYaxis()->SetTitle("position Y (#mum)");	
		H4b->GetXaxis()->SetTitleOffset(1.2);
		H4b->GetYaxis()->SetTitleOffset(1.6);
		H4b->GetXaxis()->CenterTitle();
		H4b->GetYaxis()->CenterTitle();	
		H4b->GetYaxis()->SetLabelSize(0);
		H4b->SetMaximum(2.35*GetMax(q2,points));
		H4b->SetMinimum(2.35*GetMin(q2,points));
		PrintLatex_small(Form("%s - %s","FWHM -2 ",argv[1]),0.34,0.98,kBlack);
*/	
		cout << argv[1] << endl;
		Char_t res3='s'; 
		cout << "Do you want to save your data into data.txt (y/n)?" << endl;  
		cin >> res3;
		if (res3=='s'||res3=='y')
			{
			c1-> SaveAs(Form("%s%s",argv[1],"_EMI.png"));
			c2b-> SaveAs(Form("%s%s",argv[1],"_INT1.png"));
			c2bb -> SaveAs(Form("%s%s",argv[1],"_INT2.png"));
			c1all -> SaveAs(Form("%s%s",argv[1],"_sEMI.png"));
			}
	
 
		}

	#endif


	
	
 




	}




	}

theApp->Run(kTRUE);
delete theApp;
return 0;
}
