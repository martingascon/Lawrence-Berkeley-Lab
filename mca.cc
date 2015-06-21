//************** Copyright: Martin Gascon. LBNL ***************************************
//included libraries
#include "LIBRARIES.h" 
#include "FUNCTIONS.h" 		// ****** Own functions
 
#define GRAPH 1

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t i,k,m,a=1000,b=2000,c=1,d=1,e=1,f=1,cont=0,reb=1,N=8192,con=0,aux=0, factor=1; // n,date[3],tim[3],sec=0;  
Float_t me[3],si[3],dm[3],ds[3],data[N],x[N],y[N],integral=0,r[3],dr[3],days=0,ndf=0,chis=0,chiondf=0; //[n] refers to a vector 		      
Char_t file[100],title[150]="",res,scint[100]="",sample[10]="00000",ene[10]; 	//ci[100]="";               			//title is a string with 150 characters
Double_t rana,ranb,signo=0;

#if GRAPH
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);						
#endif 




gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);                     			// display stats
gStyle->SetOptFit(0);    					// display fit parameters 1 = on, 0 = off

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME 	
		break;						 
	case 3: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME REB
		reb=atoi(argv[2]);				//REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;
	case 4: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);		
		break;
	case 5: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		reb=atoi(argv[4]);	
		break;
	case 6: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);
		break;
	case 7: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]); 		
		reb=atoi(argv[6]);	
		break;
	case 8: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);		
		e=atoi(argv[6]);			
		f=atoi(argv[7]);		
		break;
	case 9: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);		
		e=atoi(argv[6]);			
		f=atoi(argv[7]);		
		reb=atoi(argv[8]);	
		break;
	default:
		MsgError();
		exit(1);
		break;

	};   

Read_MCA(file, data, days,N);

GetInfo_ALS_MCA(file, sample, scint,ene);



/*ifstream *in3 = new ifstream(".date.txt"); //new
		if(!*in3)
			{
			cout << " No previous date was defined "  << endl; 
			}
		else    {		
			for (i=0;i<6;i++)   

				*in2 >> par1[i];                  
			}
*/
TH1I *H = new TH1I("H",file,N,0,N-1);  // declaration of the histogram	 
for (k=0;k<N;k++)			
	{
	x[k]=k;                 
	y[k]=data[k];	
	H->Fill(x[k],y[k]);		// fill the histogram
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
//H->GetXaxis()->SetRange(1,8192);
//H->GetXaxis()->SetBit(TAxis::kAxisRange);


if (argc==2) argc=4;   // takes A and B as default values
if (argc==3) argc=4;  // takes A and B as default values
if (argc==5) argc=4;   // takes A and B as default values
if (argc==7) argc=6;  // takes A and B as default values
if (argc==9) argc=8;  // takes A and B as default values


Double_t par1[6],parg1[3],pare1[3]; 					//   new
//Double_t par1[5],parg1[3]; 				
Double_t par2[8],parg2[3],pare2[2];
Double_t par3[11],parg3[3],pare3[2];

//TF1 *eg1   = new TF1("eg1",fit_egaus,a,b,5);
TF1 *eg1   = new TF1("eg1",fit_egausb,a,b,6);

TF1 *g1    = new TF1("g1","gaus",a*0.8,b*1.2);
//TF1 *e1    = new TF1("e1",Background_exp,a*0.9,b*1.1,2);
TF1 *e1    = new TF1("e1",Background_expb,a*0.3,b*1.5,3);             //new


TF1 *eg2   = new TF1("eg2",fit_egaus2,a,d,8);
TF1 *g2    = new TF1("g2","gaus",c*0.8,d*1.2);
TF1 *e2    = new TF1("e2",Background_exp,a*0.9,d*1.1,2);


TF1 *eg3   = new TF1("eg3",fit_egaus3,a,f,11);
TF1 *g3    = new TF1("g3","gaus",e,f);
TF1 *e3    = new TF1("e3",Background_exp,a*0.9,f*1.1,2);



//TF1 *total1 = new TF1("total1",fit_egaus,a,b,5); // change added 6 instead of 5 and b in egaus
TF1 *total1 = new TF1("total1",fit_egausb,a,b,6);  //new
TF1 *total2 = new TF1("total2",fit_egaus2,a,d,8);
TF1 *total3 = new TF1("total3",fit_egaus3,a,f,11);

total1->SetLineColor(4);
total2->SetLineColor(4);
total3->SetLineColor(4);

switch (argc)   
	{
	case 4:	{
		//ifstream *in2 = new ifstream(".param5.txt");
		ifstream *in2 = new ifstream(".param6.txt"); //new
		if(!*in2)
			{
			cout << " No previous file with parameters was found "  << endl; 
			H->Fit(g1,"NQR+");	
			g1->GetParameters(&parg1[0]);
			H->Fit(e1,"NQR+");	
			e1->GetParameters(&pare1[0]);
			eg1->SetParameters(pare1[0],pare1[1],pare1[2],parg1[0],parg1[1],parg1[2]); 	
			//eg1->SetParameters(1.6e+08,-7.9e-03,4.3e+01,(b+a)/2,2.7e+02); 	// for Na22 Cryo eg1->SetParameters(1,-0.01,1,(b+a)/2,100);
			//eg1->SetParameters(88,-0.003,55,(b+a)/2,122);  			// for Cs 137 PV
			//eg1->SetParameters(1.33e+04,-1.87e-02,7.1e+03,(b+a)/2,4.4e+01); 	// for Am241 PV 
			//eg1->SetParameters(1.92e+03,-7.6e-04,1.08e+02,(b+a)/2,2.7e+02); 	// for Na22 Cryoeg1->SetParameters(1,-0.01,1,(b+a)/2,100);
			//eg1->SetParameters(1.6e+04,-1.43e-02,7.3e+03,b+a/2,6.2e+01); 		// for Na22 Cryoeg1->SetParameters(1,-0.01,1,(b+a)/2,100);	
			}
		else    {		
//			for (i=0;i<5;i++)   
			for (i=0;i<6;i++)   
				*in2 >> par1[i];                  
			eg1->SetParameters(par1[0],par1[1],par1[2],par1[3],par1[4],par1[5]); 
			}	


		H->Fit(eg1,"NQR+");		
		eg1->GetParameters(&par1[0]);
		total1->SetParameters(par1);




//		total1->SetParameters(1.28e+05,-3.2e-03,1.1e+02,(b+a)/2,1.8e+02);  	// for Na22 PV
		//total1->SetParameters(par1);
		//total1->SetParameters(1.28e+05,-3.2e-03,1.1e+02,(b+a)/2,1.8e+02);  	// for Na22 PV
		//total1->SetParameters(1.6e+05,-4.37e-02,1.96e+02,2.25e+02,4.37e+01); // for Cd109 PV 
		do
			{
			chis = 0; ndf= 0; chiondf= 0;
			H->Fit(total1,"NQR+");
			total1->GetParameters(&par1[0]);
//			g1->SetParameters(par1[2],par1[3],par1[4]);     
			g1->SetParameters(par1[3],par1[4],par1[5]);       // new
			e1->SetParameters(par1[0],par1[1],par1[2]);       // new
			//if (par1[2]>-0.0002) 	par1[2]<par1[1]/10;	
			
			me[0] = total1->GetParameter(4); 
			si[0] = total1->GetParameter(5);
			dm[0] = total1->GetParError(4);
			ds[0] = total1->GetParError(5);	


			Resol_egb(total1,r[0],dr[0]);
			srand ( (unsigned)time(NULL) );
			factor=(int)((b+a)/1000);
			if (factor<1) factor=1;
			rana = (rand()) % factor + 1;
			ranb = (rand()) % factor + 1;	
			signo = rand() % 10 + 1; 		
			if (signo>5) signo=-1; 	else signo=1;   
			a=a+signo*1*int(rana); b = b+1*signo*int(ranb);	
			if (a<0.0) {a=-a;} if (b<0.0) {b =-b;}
			if (a>b) {aux=a; a=b; b=aux;}	
			total1->SetRange(a,b);
			chis = total1->GetChisquare();  
			ndf= total1->GetNDF();		
			chiondf=chis/ndf;
			con++;
 			cout << "a=" << a << " b=" << b << " X="<< chiondf << " n=" << con <<endl;		
			} 
			while (chiondf>1.2&&con<50); 
		Float_t rang=0;
		rang=(b+a)/2;
/* 		if (rang<200) 			total1->SetParameters(2.0e+04,-3.7e-03,2.2e+02,rang,1.8e+02);
		if (rang<200) 			total1->SetParameters(1.6e+04,-1.43e-02,7.3e+03,rang,6.2e+01);
		if ((rang>200)&&(rang<1400)) 	total1->SetParameters(2.9e+04,-1.2e-02,8.2e+03,rang,8.3e+01); //cout << rang << " rango " <<endl;
		if ((rang>1400)&&(rang<2000)) total1->SetParameters(6.7e+01,-4.2e-03,2.1e+02,rang,1.0e+02); 
		//if ((rang>2000)&&(rang<4500)) total1->SetParameters(2.e+04,-1.5e-03,6.77e+01,rang,-5.4e+02);
		if ((rang>2000)&&(rang<4500)) total1->SetParameters(1.9e+05,-2.5e-03,8.9e+02,rang,1.47e+02);
		if ((rang>4500)&&(rang<5500)) total1->SetParameters(1.1e+07,-2.5e-03,2.0e+02,rang,2.1e+02);
		if ((rang>5500)&&(rang<8000)) total1->SetParameters(1.1e+07,-2.5e-03,2.0e+02,rang,2.1e+02);
  
*/

		//total1->SetParameters(1.10e+07,-2.5e-03,2.0e+02,(b+a)/2,2.12e+02);  	//around ch 5k   - 5.4k		// for Na22 Cryo
		//total1->SetParameters(1.92e+03,-7.6e-04,1.08e+02,(b+a)/2,2.7e+02);  	//around ch 5k   - 5.4k		// for Na22 Cryo
		//total1->SetParameters(par1[2],par1[3],par1[4],par1[0],par1[1]);
		//total1->SetParameters(6.e+04,-4.77e-03,3.04e+02,(b+a)/2,1.38e+02);  	//around ch 1.4k - 1.5k		// for SrI2 and Cs-137 PV
		//total1->SetParameters(2.e+04,-1.5e-03,6.77e+01,(b+a)/2,-5.38e+02);  	//around ch 3k   - 4.5k		// for NaITl and Cs-137 PV

		H->Fit(total1,"R+");
		total1->GetParameters(&par1[0]);
		total1->SetLineColor(4);
		g1->SetParameters(par1[3],par1[4],par1[5]);
//		g1->SetParameters(par1[2],par1[3],par1[4]);
//		e1->SetParameters(par1[0],par1[1]);
		e1->SetParameters(par1[0],par1[1],par1[2]);	//new


/*		me[0] = total1->GetParameter(3); 
		si[0] = total1->GetParameter(4);
		dm[0] = total1->GetParError(3);
		ds[0] = total1->GetParError(4);	*/

		me[0] = total1->GetParameter(4); 
		si[0] = total1->GetParameter(5);
		dm[0] = total1->GetParError(4);
		ds[0] = total1->GetParError(5);
	
		Resol_egb(total1,r[0],dr[0]);
		g1->Draw("same");
		e1->SetRange(a*0.9,b*1.1);
		e1->Draw("same");
		e1->SetLineColor(kGreen+3);
  		PrintStats(total1,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		H->GetXaxis()->SetRangeUser(100,8000);
		if (rang<400) H->GetXaxis()->SetRangeUser(10,1000);
		if (rang>400&&rang<2000) H->GetXaxis()->SetRangeUser(10,5000);
		if (rang>2000&&rang<4000) H->GetXaxis()->SetRangeUser(100,6000);
		if (rang>4000&&rang<7000) H->GetXaxis()->SetRangeUser(2000,8000);
		}
		break;
	case 6:	{
		H->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		H->Fit(g2,"NQR+");
		g2->GetParameters(&parg2[0]);	
		H->Fit(e2,"NQR+");
		e2->GetParameters(&pare2[0]);	
		eg2->SetParameters(pare2[0],pare2[1],parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2]);	
		H->Fit(eg2,"NR");
		eg2->GetParameters(&par2[0]); 
		//par2 = {9.093e+03,-4.80e-03,7.22e+03,8.92e+01,2.976e+01,9.024e+02,2.376e+02,3.58e+01};   	//for Ba-133 PV
		//par2 = {9.093e+03,-4.80e-03,7.22e+03,8.92e+01,2.976e+01,9.024e+02,2.376e+02,3.58e+01};   	//for Ba-133 PV
		//par2 = {2.35e+03,-6.69e-03,4.27e+03,1.61e+02,3.436e+01,1.35e+02,3.76e+02,3.08e+01};   	//for Ba-133
		par2[0] = 1.544e+04; par2[1] = -2.11e-03;
		par2[2] = 3.259e+04; par2[3] = 1.269e+02;
		par2[4] = 4.58e+01;  par2[5] = 9.57e+03;
		par2[6] = 3.72e+02;  par2[7] = 8.16e+01;   //for Eu-152 PV
		total2->SetParameters(par2);	
		do  


			{
			H->Fit(total2,"R");
			total2->GetParameters(&par2[0]);	
			g1->SetParameters(par2[2],par2[3],par2[4]);
			g2->SetParameters(par2[5],par2[6],par2[7]);
			e2->SetParameters(par2[0],par2[1]);
			me[0] = total2->GetParameter(3); me[1] = total2->GetParameter(6); 
			si[0] = total2->GetParameter(4); si[1] = total2->GetParameter(7);
			dm[0] = total2->GetParError(3);  dm[1] = total2->GetParError(6);
			ds[0] = total2->GetParError(4);	 ds[1] = total2->GetParError(7);			
			Resol_eg(total2,r[0],dr[0]);
			Resol_eg2(total2,r[1],dr[1]);
			srand ( (unsigned)time(NULL) );
			factor=(int)((b+a)/1000);	
			if (factor<1) factor=1;
			rana = rand() % factor + 1;;
			ranb = rand() % factor + 1;	
			signo = rand() % 10 + 1; 		
			if (signo>5) signo=-1; 	else signo=1;   
			a=a+signo*1*int(rana); b = b+1*signo*int(ranb);	
			if (a<0.0) {a=-a;} if (b<0.0) {b =-b;}
			if (a>b) {aux=a; a=b; b=aux;}	
			
			a=a+signo*int(rana); b=b+signo*int(ranb);
			chis = total2->GetChisquare();  
			ndf= total2->GetNDF();		
			chiondf=chis/ndf;
			con++;
 			cout << " limits =>  a=" << a << " b=" << b << " chiondf="<< chiondf << " con=" << con <<endl;		
			} 
		while (chiondf>1.05&&con<50);
		H->Fit(total2,"R");
		total2->GetParameters(&par2[0]);	
		g1->SetParameters(par2[2],par2[3],par2[4]);
		g2->SetParameters(par2[5],par2[6],par2[7]);
		e2->SetParameters(par2[0],par2[1]);
		g1->Draw("same");
		g2->Draw("same");
		e2->Draw("same");
		e2->SetLineColor(kGreen+3);
		me[0] = total2->GetParameter(3); me[1] = total2->GetParameter(6); 
		si[0] = total2->GetParameter(4); si[1] = total2->GetParameter(7);
		dm[0] = total2->GetParError(3);  dm[1] = total2->GetParError(6);
		ds[0] = total2->GetParError(4);	 ds[1] = total2->GetParError(7);	
		Resol_eg(total2,r[0],dr[0]);
		Resol_eg2(total2,r[1],dr[1]);
		PrintStats(total2,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintStats(total2,cont,r[1],dr[1],me[1],dm[1],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		PrintLegend2(r[1],dr[1],me[1],dm[1]);
		}
		break;
	case 8: {
		H->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		H->Fit(g2,"NQR+");
		g2->GetParameters(&parg2[0]);	
		H->Fit(g3,"NQR+");
		g3->GetParameters(&parg3[0]);	
		H->Fit(e3,"NQR+");
		e3->GetParameters(&pare3[0]);	
		eg3->SetParameters(pare3[0],pare3[1],parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2],parg3[0],parg3[1],parg3[2]);	
		H->Fit(eg3,"NR");
		eg3->GetParameters(&par3[0]);
		total3->SetParameters(par3);
		H->Fit(total3,"R+");
		H->Fit(total3,"R+");
		H->Fit(total3,"R+");
		total3->GetParameters(&par3[0]);	
		g1->SetParameters(par3[2],par3[3],par3[4]);
		g2->SetParameters(par3[5],par3[6],par3[7]);
		g3->SetParameters(par3[8],par3[9],par3[10]);
		e3->SetParameters(par3[0],par3[1]);
		g1->Draw("same");
		g2->Draw("same");
		g3->Draw("same");
		e2->Draw("same");
		e2->SetLineColor(kGreen+3);
		me[0] = total3->GetParameter(3); me[1] = total3->GetParameter(6);  me[2] = total3->GetParameter(9); 
		si[0] = total3->GetParameter(4); si[1] = total3->GetParameter(7);  si[2] = total3->GetParameter(10);
		dm[0] = total3->GetParError(3);  dm[1] = total3->GetParError(6);   dm[2] = total3->GetParError(9);
		ds[0] = total3->GetParError(4);	 ds[1] = total3->GetParError(7);   ds[2] = total3->GetParError(10);		
		Resol_eg(total3,r[0],dr[0]);
		Resol_eg2(total3,r[1],dr[1]);
		Resol_eg3(total3,r[2],dr[2]);
		PrintStats(total3,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintStats(total3,cont,r[1],dr[1],me[1],dm[1],integral);
		PrintStats(total3,cont,r[2],dr[2],me[2],dm[2],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		PrintLegend2(r[1],dr[1],me[1],dm[1]);
		PrintLegend3(r[2],dr[2],me[2],dm[2]);
		}
		break;
	}

#if GRAPH
	theApp->Run(kTRUE);						
#endif 



#if GRAPH
cout << "Do you want to save your data into data.txt (y/n)?" << endl;  
cin >> res;
#else
res='s';
#endif 
if (res=='s'||res=='y')
  	{
	
	Char_t output[100]="";
	sprintf(output,"NP_%s_%s.txt",sample,scint);
	ofstream *out = new ofstream(output,ios::app);
	ofstream *dat = new ofstream(".param5.txt",ios::trunc);
 	switch (argc)   
   	 	{
    		case 4:
		*out <<  std::fixed << std::setprecision(1) << ene << "\t"  << 0.1 << "\t" << std::fixed << std::setprecision(1) << me[0] << "\t" << dm[0]*3 <<"\t" <<  r[0] << "\t" << dr[0] << endl;	
		*dat << par1[0] << "\t" << par1[1] << "\t" << par1[2] << "\t" << par1[3] <<  "\t" << par1[4] << "\t" << par1[5] << endl;
		break;
    		case 6:	
			ofstream *out2 = new ofstream("data2.txt",ios::app);
	   		*out <<  std::fixed << std::setprecision(1) << ene << "\t"  << 0.1 << "\t" << std::fixed << std::setprecision(1) << me[0] << "\t" <<  dm[0]*3 <<"\t" << r[0] << "\t" << dr[0] << endl;		
    	   		*out2 <<  std::fixed << std::setprecision(1) << ene << "\t"  << 0.1 << "\t" << std::fixed << std::setprecision(1) << me[1] << "\t" <<  dm[1]*3  <<"\t" <<  r[1] << "\t" << dr[1] << endl;	

			ofstream *dat2 = new ofstream(".param8.txt",ios::trunc);
	   		*dat2 << par2[0] << "\t" << par2[1] << "\t" << par2[2] <<"\t" << par2[3] <<"\t" << par2[4] <<"\t" << par2[5] <<"\t" << par2[6] <<"\t" << par2[7] << endl;
    		break;
		};

	}
else
	exit(1);



delete theApp;
return 0;

}
