#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>
#include <vector>
#include "TRandom.h"
#include "TRandom3.h"
#include "TMath.h"
#include <TStyle.h>
#endif

using std::vector;
using namespace std;

void decade(Int_t n0, Double_t alfa, Double_t time_bin, Double_t T) {
    Int_t size=1+(T/time_bin);
    cout << "size = " << size << endl;
    Int_t ndec;
    TCanvas *c = new TCanvas("c", "Canvas", 500, 500);
    TH1D *h = new TH1D("h","Istogramma",size,-time_bin,T+time_bin);
    
    for (Double_t t=0; t<T+time_bin; t+=time_bin) {
        ndec=0;
        cout << "Tempo trascorso " << t << endl;
        for(Int_t n=0; n<n0; n++) {
            if((gRandom->Rndm())<(alfa*time_bin)) {
                ndec++;
            }
        }
        cout << "Numero di particelle decadute al tempo " << t << " = " << ndec << endl;
        n0=n0-ndec;
        cout << "Al tempo " << t << " restano " << n0 << " particelle " << endl;
        h->Fill(t,n0);
        cout << "bin = " << t+time_bin/2 << endl;
    }
    
    h->Draw("hist");
}
