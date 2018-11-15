#include <Riostream.h>
#include "Ambiente.h"
#include "TString.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include "TFile.h"
#include "TMath.h"
#include "Rete.h"
#include "Persona.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLine.h"


void linee(int n){
  int mat[n][2];

  for(int i=0;i<n;i++){
    for(int j=0;j<2;j++) mat[i][j]=n*gRandom->Rndm();
  }

    TCanvas *c1= new TCanvas("c1","grafico",0,0,500,500);

    TH1D* t = new TH1D("t","grafo",110,0,n);
    t->SetMaximum(n);
    t->Draw("e1");

    for(int i=0;i<n;i+=2){
      TLine *l=new TLine(mat[i][0],mat[i][1],mat[i+1][0],mat[i+1][1]);
      l->SetLineColor(kBlue);
      l->Draw();
    }
    
}
