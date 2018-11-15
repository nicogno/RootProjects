#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <Riostream.h>
#endif

// Dichiarazione delle funzioni
void Decay(Int_t n0 = 50000,Double_t alpha = 0.03, Double_t Delt = 1.,
           Double_t ttot = 300., UInt_t seed=95689);

Double_t exponential(Double_t *x, Double_t *par);

//_____________________________________________________________
void Decay(Int_t n0,Double_t alpha, Double_t Delt,Double_t ttot, UInt_t seed){
  gRandom->SetSeed(seed);
  Int_t Nbins = static_cast<Int_t>(ttot/Delt); // numero di intervalli di tempo
  cout << "Numero di celle: "<<Nbins<<endl;
  Double_t timetot = Delt*Nbins;  // tempo totale = ttot a meno di arrotondamenti
  // histogram booking
  TH1D *h1 = new TH1D("h1","Remaining nuclei",Nbins+1,-Delt/2.,timetot+Delt/2.);
  cout<<"Celle istogramma "<<Nbins+1<<" low "<<-Delt/2.<<" high "<<timetot+Delt/2.<<endl;
  h1->SetFillColor(kOrange+2);
  //funzione teorica
  TF1 *fteo = new TF1("fteo",exponential,0.,timetot,2);
  fteo->SetLineColor(kBlue);
  Double_t N0 = n0;
  Double_t ALPHA = alpha;
  fteo->SetParameters(N0,ALPHA);
  fteo->SetParNames("normalizzazione","coefficiente");
  Double_t prob = alpha*Delt; //probabilita
  
// simulazione
  h1->Fill(0.,static_cast<Double_t>(n0));
  for(Double_t time=Delt; time<timetot+Delt/2.; time+=Delt){
    Int_t ndec = 0;
    for(Int_t nuclei=0; nuclei<n0;nuclei++)if(gRandom->Rndm()<prob)ndec++;
    n0-=ndec;
    h1->Fill(time,static_cast<Double_t>(n0));
  }
    
  TFile *file = new TFile("decay.root","recreate");
  h1->Write();
  fteo->Write();
  h1->Draw("hist");
  fteo->Draw("same");

  file->ls();
}

//_____________________________________________________________
Double_t exponential(Double_t *x, Double_t *par){
  Double_t xx = x[0];
  return par[0]*exp(-par[1]*xx);
}
