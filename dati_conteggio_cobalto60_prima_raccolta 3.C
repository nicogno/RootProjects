{
    ifstream in;
    
    gStyle->SetOptFit(1100);
    //gStyle->SetOptStat("rRmMen");
        
    in.open("dati_conteggio_cobalto60_prima_raccolta.dat");
    Int_t x = 0, y = 0, nlines = 0;

    TCanvas *c1 = new TCanvas("c1","Conteggi Cobalto60 da oscilloscopio", 1000, 800);
    TH1D *histo1 = new TH1D("Histogram and Fit parameters, 10 ms","",10,-0.5,9.5);
    TH1D *histo2 = new TH1D("Histogram and Fit parameters, 20 ms","",10,-0.5,9.5);

    while (1) {
        in >> x >> y;
        if (!in.good()) break;
        histo1->Fill(x);
        histo2->Fill(y);
        nlines++;
    }
    
    TF1 *poisson = new TF1("poisson","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)", -0.5, 9);
    poisson->SetParameters(1, 1, 1);
    //poisson->SetParNames("","","");
    
    histo1->GetXaxis()->SetTitle("# Signals");
    histo1->GetYaxis()->SetTitle("# Counts");
    histo2->GetXaxis()->SetTitle("# Signals");
    histo2->GetYaxis()->SetTitle("# Counts");

    c1->Divide(1,2);
    
    c1->cd(1);
    histo1->Fit("poisson", "R");
    c1->cd(2);
    histo2->Fit("poisson", "R");
    
    c1->SaveAs("dati_conteggio_cobalto60_prima_raccolta.pdf","pdf");
    

    in.close();
}

