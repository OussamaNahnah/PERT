#include <iostream>
#include<graphics.h>
#include <iomanip>
#include <fstream>
#define length 26
using namespace std;
int n=0;
int mat[length][length],ma_copie[length][length],ma_etat[length][length],niv[length][length],temp[length],temp_etat[length],tab_max[length],tab_min[length],nbr_n=-1, cas_debut=0,cas_fin=0,som_dur=0
,dptar[length][length],dptau[length][length],h=0,w=0;
int etat[length][length];
char tab_c[26];
	char plus_tau[256], plus_tar[256], durre[256],number[256],nivv[256];
		bool related=false;
void init(){

	 for (int i = 0;  i<length ; i++) {
	 	temp[i]=-1;	temp_etat[i]=-1;
	 	tab_max [i]=-99;
	 	tab_min [i]=99;
        for ( int j = 0; j <length ; j++) {
			mat[i][j]=0;
			etat[i][j]=0;
			ma_etat[i][j]=0;
			ma_copie[i][j]=0;
			niv[i][j]=0;
			dptau[i][j]=-1;
			 dptar[i][j]=99;
           
    }
}
	char c = 'A';
    for (int i = 0; i<26; i++){
    	tab_c[i]=c;
    	c++;
	}
}
int find(char c){
	for (int i =0;i<26;i++)
	{
		if (tab_c[i]==c){
			return i;
		}   
	}
}

void PrintMat(int m[][length],int t,int l ){
    int i,j;
    cout<<"\n\n"<<setw(4)<<"";
    for ( i = 0; i < t; ++i) {
        cout<<setw(3)<<"("<<i+1<<")";
    }
    cout<<"\n\n";
    for (i = 0;  i<l ; i++) {
        cout<<setw(3)<<"("<<i+1<<")";
        for ( j = 0; j <t ; j++) {
            cout<<setw(3)<<m[i][j] ;
        }
        cout<<"\n\n";
    }

}

void Printduree(int t [length],int l){
    int i;
    for ( i = 0; i < l; ++i) {
        cout<<"duree de tache "<<i+1<<" est = "<<t[i]<<"\n";
    }
    cout<<"\n\n";


}
bool matvide(){
    bool vide=true;
    int i,j;
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if ((mat[i][j]==1)||(mat[i][j]==0))
                vide=false;
        }
    }
    return vide;}


void calculniveau(){
    bool ni,rowsupp;//premier niveau
    bool mat_v=matvide();

    if(mat_v==false) {
        nbr_n++;

        for ( int i = 0; i < n; ++i) {
            ni=true;rowsupp=true;
            for(int row=0;row<n;row++){
                if (mat[row][i]!=-1){
                    rowsupp=false;
                }
            }
            for (  int j = 0; j < n; ++j) {
                if(mat[i][j]==1){
                    ni=false;
                }
            }
            if(ni&&(rowsupp==false)){
                niv[nbr_n][i]=1;
            }
        }

        for ( int i = 0; i < n; ++i){
            if (niv[nbr_n][i]==1){

                for ( int j = 0;  j<n ; j++) {
                 
                    mat[j][i]=-1;
                }
            }}


        cout<<endl;

        calculniveau();
    }}

void init_dpaut(){
    for (int i = 0;  i<=w ; i++) {
        for ( int j = 0; j <=w ; j++) {
            if(etat[i][j]==1){
                dptau[i][j]=temp_etat[j];
            } 
        }
    }
}
void init_dptar(){
    for (int i = 0;  i<=w ; i++) {
        for ( int j = 0; j <=w ; j++) {
            if(etat[i][j]==1){
                dptar[i][j]=som_dur;
            }
        }
    }

}
void printNiveau(){

    for (int i = 0;  i<=nbr_n ; i++) {
        cout<<"level "<< i+1<<" ; ";
        for ( int j = 0; j <n ; j++) {
            if (niv[i][j]==1)
                cout<<j+1<<"\t";

        }
        cout<<endl;
    }

}
void printtab(){
    cout<<" tache --> dureé --> tache précedant "<<endl;
    for (int i = 0;  i<n ; i++) {
        cout<<setw(2)<< i+1<<setw(2)<<"-------->"<<setw(2)<<temp[i]<<setw(2)<<"-------->"<<setw(2);
        for ( int j = 0; j <n ; j++) {
            if (ma_copie[i][j]==1)
                cout<<j+1<<setw(1);

        }
        cout<<endl;
    }}
int mx(){
	int m=-99;
	 for (int i = 0;  i<w ; i++) {
	 if (m>tab_max[i])m=tab_max[i];
	 }
	 return m;
}

void clc_dptau(){
int mx=0;
    for (int i = 1;  i<=w ; i++) {
        for ( int j = 0; j <=w ; j++) {
            if( dptau[i][j]!=-1){
            	 for (int l = i-1;  l>=0 ; l--) {
                for (int k = 0;  k<=w ; k++) {
               
                    if( dptau[l][k]!=-1){
                        if(ma_etat[j][k]!=0){
                        	 if(mx<dptau[l][k]) mx=dptau[l][k];
                        
                        }  }
                }
         
		    }  dptau[i][j]=dptau[i][j]+mx;
		   mx=0;
		   som_dur=dptau[i][j];}
        }
    }
}

void clc_dptar(){
	int mn=99;
cout<<"w"<<w<<"h"<<h;
    for (int i = h-1;  i>=0 ; i--) {
        for ( int j = 0; j <=w ; j++) {
            if( dptar[i][j]!=99){ 
			    for (int l = i+1;  l<=h ; l++) {
                for (int k = 0;  k<=w ; k++) {
            
         /*    if(( dptar[l][k]!=99)&&(ma_etat[k][j]!=0 )&&temp_etat[j]==0){
        	dptar[i][j]= dptar[l][k];
        					 }else 
			   // */if(( dptar[l][k]!=99)&&(ma_etat[k][j]!=0 )){
			    	cout<<"i= "<<i<<" j= " <<j<< " l="<<l<<" k= "<<k<<endl;
			    	int pop=dptar[l][k]-temp_etat[k];
			    	cout <<"dptar[i][j]-temp_etat[j]="<<pop<<endl;
                if(mn>pop) mn=pop;
                cout <<"mn= "<<mn<<endl;
            	    dptar[i][j]=mn;
                    
                         }
               }
                
		   }
		   
		   mn=99;
            }


        }
    }
}
void custom(){
	     w=n-1;
	     h =nbr_n;
        for ( int i = 0; i <=length ; i++) {
            if( niv[0][i]!=0){
            cas_debut++;
           
				}
				  if( niv[nbr_n][i]!=0){
            cas_fin++;
				}
				}
				if(cas_debut>1){
					 cout<<"debut "<<cas_debut<<endl;
					h++;w++;
					etat[0][0]=1; temp_etat[0]=0;
					for (int i = 0;  i<length ; i++) {	
					temp_etat[i+1]=temp[i] ;
						for ( int j = 0; j <length ; j++) {
						
						etat[i+1][j+1]=niv[i][j];
						ma_etat[i+1][j+1]=ma_copie[i][j];
						
						}}	
					for ( int j = 0; j <length ; j++) {
						if(etat[1][j]==1){
						ma_etat[j][0]=1;
						}
					
													}		
	}else{ cout<<"vide1 "<<endl;
	for (int i = 0;  i<length ; i++) {	
			temp_etat[i]=temp[i] ;
		for ( int j = 0; j <length ; j++) {
						etat[i][j]=niv[i][j];
						ma_etat[i][j]=ma_copie[i][j];
						}}	
		
	}
	cout<<"fin "<<cas_fin<<endl;
		if(cas_fin>1){
			 
			w++;h++;
	etat[ h][w]=1; temp_etat[w]=0;
	for ( int j = 0; j <length ; j++) {
		if(etat[h-1][j]==1){
		ma_etat[w][j]=1;
		}
					
	}}

cout<<"h "<<h<<endl;
 cout<<"w "<<w<<endl;/*
for (int i =1;  i<h ; i++) {	
for ( int j = 0; j <=w ; j++) {
bool relier=false;
for ( int k = 0; j <=w ; j++) {
	if ((ma_etat[k][j]!=0)&&(etat[i+1][k]!=0)){
		relier=true;
	}	}
	if(!relier){
		ma_etat[w][j]=1;
		}
	}					
}
}
*/	
//*************custom realations**********************


		for (int i =1;  i<h ; i++) {	
		for ( int j = 0; j <=w ; j++) {
			if(etat[i][j]!=0){
					cout<<"ii="<<i<<"jj="<<j<<endl;
				 for (int l = i+1;  l<=h ; l++) {
                for (int k = 0;  k<=w ; k++) {
                	if(( etat[l][k]!=0)&&(ma_etat[k][j]!=0 )){
                	cout<<"---related with l="<<l<<"k="<<k<<endl;	
                		related=true;
                		
			}}}
	/*	if (related	){
	cout<<"related"<<endl;	}else{
			cout<<"not related"<<endl;
	}*/
			if (!related){
				cout<<"not related i="<<i<<"jj="<<j<<endl;
				 for (int k = 0;  k<=w ; k++) {
				 	if(etat[h][k]!=0){
					 cout<<"relier avec="<<h<<"jj="<<k<<endl;
				ma_etat[k][j]=1;
					//ma_etat[j][k]=1;		
			}}}
			
		} related=false;}
} 
}

void drawgraph(){
	int COLOR_B=2;
		int size=33;
DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
initwindow(screenWidth,screenHeight,"PERT" );
floodfill(1,1,WHITE);
setcolor(BLACK);
setbkcolor(COLOR_B);
int maxx;int maxy;
	floodfill(1,1,WHITE);

	
 	setfillstyle(SOLID_FILL,COLOR_B);
	rectangle(50,50,200,100);
	floodfill(51,51,BLACK);
	outtextxy(75, 75, "draw graph");
		setfillstyle(SOLID_FILL,COLOR_B);
		rectangle(50,125,200,175);
		floodfill(51,126,BLACK);
		outtextxy(75, 150, "N=");
		
		rectangle(50,200,200,250);
		floodfill(51,202,BLACK);
		outtextxy(75, 225, "duree");
		
		rectangle(50,275,200,325);
		floodfill(51,276,BLACK);
		outtextxy(75, 300, "plus tau ");
		
		rectangle(50,350,200,400);
		floodfill(51,351,BLACK);
		outtextxy(75, 375, "plus tar");
		rectangle(50,425,200,475);
		floodfill(51,426,BLACK);
		outtextxy(70, 450, "chemin creitique");
		

		int mX,mY;
	while(1){
	getmouseclick(WM_LBUTTONDOWN,mX,mY);		
		setbkcolor(WHITE);
	if((mX>50)&&(mX<200)&&(mY>50)&&(mY<100)){

	  for (int i = 0;  i<=h ; i++) {
        for ( int j = 0; j <=w ; j++) {
            if( etat[i][j]!=0){
			int u=i*100+250;
			int p=j*60+100;
			setcolor(BLACK);
			setlinestyle(0,0,1);
			circle(u,p,size);
			maxx=u;
			maxy=p;
			      
			}}}

			   for (int i = 0;  i<=h ; i++) {	
        for ( int j = 0; j <=w ; j++) {
        
            if( etat[i][j]!=0){
            
			
            	for( int k = 0; k <=w ; k++) {
			 		for(int l=i+1;l<=h;l++){
            	if (( etat[l][k]!=0)&&(ma_etat[k][j]!=0 )){

			int u=i*100+250;
			int p=j*60+100;
			int c=l*100+250;
			int o=k*60+100;
			if(((temp_etat[i]==0)&&(dptau[i][j]+temp_etat[k]==dptau[l][k]))||((dptar[i][j]==dptar[l][k]))){
			setcolor(4);
			setlinestyle(3,0,1);
			line(u+33,p,c-33,o);		
			}else{
			setcolor(BLACK);
			setlinestyle(0,0,1);
			line(u+33,p,c-33,o);	
			}

				
				}
            }	
			      
		}
			}}}
	
		
		
		
	}else if((mX>50)&&(mX<200)&&(mY>125)&&(mY<175)){
		int num=0;
		  for (int i = 0;  i<=h ; i++) {
		
        for ( int j = 0; j <=w ; j++) {
            if( etat[i][j]!=0){
				num++;
			
			sprintf(number, "%d",num);
		
			int u=i*100+250;
			int p=j*60+100;
		
			setcolor(BLACK);
			setlinestyle(0,0,1);
			line(u,p-size,u,p+size);
			line(u-size,p,u+size,p);
			settextstyle(8,0,1);
			outtextxy(u-23, p-21, number);
			

			      
			}}}
	}else if((mX>50)&&(mX<200)&&(mY>200)&&(mY<250)){
		//duree
		 for (int i = 0;  i<=h ; i++) {
		
        for ( int j = 0; j <=w ; j++) {
            if( etat[i][j]!=0){
            	sprintf(durre, "%d",temp_etat[j]);
			
		
		
				int u=i*100+250;
			int p=j*60+100;
		
			setcolor(BLACK);
			setlinestyle(0,0,1);
			line(u,p-size,u,p+size);
			line(u-size,p,u+size,p);
			settextstyle(8,0,1);
			outtextxy(u+2, p-21, durre);
		
	
			      
			}}}
	
	}else if((mX>50)&&(mX<200)&&(mY>275)&&(mY<325)){
		//plus tau
		 for (int i = 0;  i<=h ; i++) {
		
        for ( int j = 0; j <=w ; j++) {
            if( etat[i][j]!=0){
	
		sprintf(plus_tau, "%d",dptau[i][j]);
		
		
		
				int u=i*100+250;
			int p=j*60+100;
		
			setcolor(BLACK);
			setlinestyle(0,0,1);
			line(u,p-size,u,p+size);
			line(u-size,p,u+size,p);
			settextstyle(8,0,1);
			outtextxy(u-23, p+2,plus_tau );
   
			}}}
	
	}else if((mX>50)&&(mX<200)&&(mY>350)&&(mY<400)){
		
	//plus tar
	 for (int i = 0;  i<=h ; i++) {
		
        for ( int j = 0; j <=w ; j++) {
            if( etat[i][j]!=0){
		sprintf(plus_tar, "%d",dptar[i][j]);
			
			
			int u=i*100+250;
			int p=j*60+100;
		
			setcolor(BLACK);
			setlinestyle(0,0,1);
			line(u,p-size,u,p+size);
			line(u-size,p,u+size,p);
			settextstyle(8,0,1);
			outtextxy(u+2, p+1,plus_tar);
    
			}}}
	}else if((mX>50)&&(mX<200)&&(mY>425)&&(mY<475)){
		   for (int i = 0;  i<=h ; i++) {	
        for ( int j = 0; j <=w ; j++) {
        
            if((  etat[i][j]!=0)&&(0==dptau[i][j]-dptar[i][j])){
            	for( int k = 0; k <=w ; k++) { 
            		for(int l=i+1;l<=h;l++){
            	if (( etat[l][k]!=0)&&(ma_etat[k][j]!=0 )&&(0==dptau[l][k]-dptar[l][k])){

		
				int u=i*100+250;
			int p=j*60+100;
			int c=l*100+250;
			int o=k*60+100;
				setcolor(4);
				setlinestyle(3,0,3);
				line(u+31,p+6,c-35,o+6);
				//line(u+40,p+30,c-30,o-40);	
	
				}
            	
			      
		}}	}}}
			}
		setlinestyle(0,0,1);
			setcolor(BLACK);
		settextstyle(8,0,1);
		outtextxy((maxx+100)/2, maxy+100," dans cette sence");
		line(300,maxy+100,maxx-10,maxy+100);
		line(maxx-10,maxy+100,maxx-20,maxy+90);
		line(maxx-10,maxy+100,maxx-20,maxy+110);
	
	delay(1);
	}
	
	getch();
	
}

int main() {
	
init();	

string s;
ifstream inn("pert.txt");
if (!inn) {
	cout << "Cannot open file.\n";
}else{
while(!inn.eof()) {
	getline(inn, s);
	n++;	
}

ifstream in("pert.txt");
if (!in) {
	cout << "Cannot open file.\n";
}else{

	char x;
	while (in >> x) {
	int i,j;
 	if(x=='*'){
		in >> x;
		 i =find(x);
	}
	if(x=='-'){
		in >>temp[i];
		in>>x;
		if(x=='-'){
			in>>x;
		if(x!=';'){
	while(x!=';'){
		
		 j =find(x);
			cout<< "i= "<<i<<" j="<<j<<endl;
			mat[i][j]=1;
			ma_copie[i][j]=1;
			in >> x;
	}	
	}	}}
	
}

in.close();


/*
    int i ,j ,v;
    init();
    cout << "entrer le nombre de sommets : " ;
    cin>>n;

    cout << "\n";
    for ( i = 0; i <n ; ++i) {
        do{
            cout << "enter la dureÃ© de tache  " << i+1 << " : "  ;
            cin>>temp[i];
        }while (temp[i]<0);
        for ( j = 0; j <n ; ++j) {
            if(i!=j){

                do{cout << " Est ce que le precedeur de  la tache " << i+1 << "  est  " << j+1 << " ???  (1)||(0):"  ;
                    cin>>v;
                    mat[i][j]=v;
                    ma_copie[i][j]=v;
                }while (mat[i][j]!=0 && mat[i][j]!=1);


            } else mat[i][j]=0;

        }

    }
*/
cout<<n;
    PrintMat(mat,n,n);
   Printduree(temp,n);
    calculniveau();
     PrintMat(ma_copie,n,n);
    printtab();
    printNiveau();
    custom();
    PrintMat(etat ,n+2,n+2);
    PrintMat(ma_etat,n+2,n+2);
    Printduree(temp_etat,n+2);
    init_dpaut();
    //PrintMat(dptau,n+2,n+2);
    clc_dptau();
    cout<<"dptau"<<endl;
    PrintMat(dptau,n+2,n+2);
  	init_dptar();
	//PrintMat(dptar,n+2,n+2);
    clc_dptar();
    cout<<"dptau"<<endl;
     PrintMat(dptar,n+2,n+2);
    drawgraph();}

    }

    system("pause");
    return 0;
}

