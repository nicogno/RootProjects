#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <vector>
#include "TRandom.h"
#include "TRandom3.h"
#endif

using std::vector;
using namespace std;

const UInt_t n=200000;

void tlc() { //Serve per verificare il Teorema del Limite Centrale
    
    vector <Double_t> box1;
    
    Double_t a = 0.;
    UInt_t i = 0;
    
    TH1D *hist1 = new TH1D("hist1","Istogramma",100,0,1);
    
    while(i<n) {
        a=gRandom->Uniform(0.0,1.0); //Genera double casuale fra 0 ed 1
        if((a<=0.2) || (a>=0.8)) {
            i++;
            box1.push_back(a);
            hist1->Fill(a);
        }
    }
    
    TCanvas * c1 = new TCanvas("c1", "c1", 500, 500);
    hist1->Draw();
    
    //if(gRandom) delete gRandom;
    //gRandom = new TRandom3(0);
    
    const Int_t t1 = 300;
    Int_t v1[t1];
    UInt_t j = 0;
    Double_t sum1 = 0., sum2 = 0., sum3 = 0., sum4 = 0., sum5 = 0., sum6 = 0., xmin2, xmin3, xmin4, xmin5, xmin6, xmin7, xmax2, xmax3, xmax4, xmax5, xmax6, xmax7;
    
    xmin2=xmin3=xmin4=xmin5=xmin6=xmin7 = t1;
    xmax2=xmax3=xmax4=xmax5=xmax6=xmax7 = 0.;
    
    TH1D *hist2 = new TH1D("hist2","Istogramma",100,xmin2,xmax2);
    TH1D *hist3 = new TH1D("hist3","Istogramma",100,xmin3,xmax3);
    TH1D *hist4 = new TH1D("hist4","Istogramma",100,xmin4,xmax4);
    TH1D *hist5 = new TH1D("hist5","Istogramma",100,xmin5,xmax5);
    TH1D *hist6 = new TH1D("hist6","Istogramma",100,xmin6,xmax6);
    TH1D *hist7 = new TH1D("hist7","Istogramma",100,xmin7,xmax7);
    
    while (j<n) {
        sum1=sum2=sum3=sum4=sum5=sum6=0;
        for(int i=0;i<t1;i++) {
            v1[i]=gRandom->Integer(n); //Genera un intero casuale fra 0 e n-1
            if (i<2) sum2=sum2+box1[v1[i]];
            if (i<5) sum3=sum3+box1[v1[i]];
            if (i<10) sum4=sum4+box1[v1[i]];
            if (i<100) sum5=sum5+box1[v1[i]];
            if (i<200) sum6=sum6+box1[v1[i]];
            sum1=sum1+box1[v1[i]];
            
        }
        if(sum1>xmax2) xmax2=sum1;
        if(sum1<xmin2) xmin2=sum1;
        hist2->Fill(sum1);
        if(sum2>xmax3) xmax3=sum2;
        if(sum2<xmin3) xmin3=sum2;
        hist3->Fill(sum2);
        if(sum3>xmax4) xmax4=sum3;
        if(sum3<xmin4) xmin4=sum3;
        hist4->Fill(sum3);
        if(sum4>xmax5) xmax5=sum4;
        if(sum4<xmin5) xmin5=sum4;
        hist5->Fill(sum4);
        if(sum5>xmax6) xmax6=sum5;
        if(sum5<xmin6) xmin6=sum5;
        hist6->Fill(sum5);
        if(sum6>xmax7) xmax7=sum6;
        if(sum6<xmin7) xmin7=sum6;
        hist7->Fill(sum6);
        j++;
    }
    TCanvas * c2 = new TCanvas("c2", "c2", 500, 500);
    hist2->GetXaxis()->SetLimits(xmin2-1, xmax2+1);
    hist2->Draw();
    TCanvas * c3 = new TCanvas("c3", "c3", 500, 500);
    hist3->GetXaxis()->SetLimits(xmin3-1, xmax3+1);
    hist3->Draw();
    TCanvas * c4 = new TCanvas("c4", "c4", 500, 500);
    hist4->GetXaxis()->SetLimits(xmin4-1, xmax4+1);
    hist4->Draw();
    TCanvas * c5 = new TCanvas("c5", "c5", 500, 500);
    hist5->GetXaxis()->SetLimits(xmin5-1, xmax5+1);
    hist5->Draw();
    TCanvas * c6 = new TCanvas("c6", "c6", 500, 500);
    hist6->GetXaxis()->SetLimits(xmin6-1, xmax6+1);
    hist6->Draw();
    TCanvas * c7 = new TCanvas("c7", "c7", 500, 500);
    hist7->GetXaxis()->SetLimits(xmin7-1, xmax7+1);
    hist7->Draw();
}

