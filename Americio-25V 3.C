{
    
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    // TCanvas *c2 = new TCanvas("c1","Spettro_Cobalto_Acciaio_No_Fit", 1600, 1200);
    TH1D *h1 = new TH1D("Histogram and Fit parameters","Americio-25V",1024,0,1023);
    // TH1D *h2 = new TH1D("Histogram parameters","Spettro Cobalto (scintillatore A);# CH;Counts",1024,0,1023);
    
    in.open("Americio-25V.mca");
    
    while (1) {
        in >> stringData;
        
       if(dataStop == false) {          //Controllo se questa è l'ultima riga e quindi va fermata l'acquisizione
            if(stringData == "<<END>>") {
                dataStop = true;
            }
        }
        
        if(dataStart && !dataStop) {
            numericData = stoi(stringData);
            if (!in.good()) break;
            h1->Fill(channel, numericData);
	    h1->SetBinError(channel+1,TMath::Sqrt(numericData));
	    // h2->Fill(channel, numericData);
	    // h2->SetBinError(channel+1,TMath::Sqrt(numericData));
            channel++;
        }
        
        if(dataStart == false) {        //Controllo se dalla prossima riga si pò iniziare l'acquisizione dei dati
            if(stringData == "<<DATA>>") {
               dataStart = true;
            }
        }
        
        in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if (!in.good()) break;
        nlines++;
    }
    in.close();
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    gStyle->SetStatH(0.07); gStyle->SetStatW(0.12);
    
    // h2->Draw();
    // c2->SaveAs("Spettro_Cobalto_Acciaio_No_Fit.pdf",".pdf");
    
    TCanvas *c1 = new TCanvas("c1","Americio-25V", 1600, 1200);
    
    h1->SetMinimum(0);
    Double_t par[4];
    TF1 *g0    = new TF1("g0","gaus",600,735);
    TF1 *g1    = new TF1("g1","pol0",0,1024);
    TF1 *total = new TF1("total","gaus(0)+pol0(3)",0,1024);
    total->SetLineColor(2);
    total->SetLineWidth(5);
    total->SetLineStyle(10);
    h1->Fit(g0,"R","goff");
    h1->Fit(g1,"R+","goff");
    g0->GetParameters(&par[0]);
    g1->GetParameters(&par[3]);
    total->SetParameters(par);
    total->SetParNames("Constant","Mean", "Sigma","Background");
    h1->Fit(total,"R");
    c1->SaveAs("Americio-25VconFit.pdf",".pdf");
    c1->SaveAs("Americio-25VconFit.root",".root");
}
