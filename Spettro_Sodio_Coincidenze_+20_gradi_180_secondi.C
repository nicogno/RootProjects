{
    
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    TCanvas *c1 = new TCanvas("c1","Spettro_Sodio_Coincidenze_+20_gradi_180_secondi", 1600, 1200);
    TH1D *h1 = new TH1D("Histogram and Fit parameters","Coincidenze Sodio (+20 gradi, 180 secondi);# CH;Counts",1024,0,1023);
    
    in.open("Spettro_Sodio_Coincidenze_+20_gradi_180_secondi.mca");
    
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
    
    h1->SetMinimum(0);
    Double_t par[7];
    TF1 *background    = new TF1("background","pol0",0,1000);
    TF1 *g0    = new TF1("g0","gaus",638,670);
    TF1 *g1    = new TF1("g1","gaus",678,710);
    TF1 *total = new TF1("total","pol0(0)+gaus(1)+gaus(4)",0,1000);
    total->SetLineColor(2);
    total->SetLineWidth(3);
    total->SetLineStyle(10);
    h1->Fit(g0,"R","goff");
    h1->Fit(g1,"R+","goff");
    h1->Fit(background,"R+","goff");
    background->GetParameters(&par[0]);
    g0->GetParameters(&par[1]);
    g1->GetParameters(&par[4]);
    total->SetParameters(par);
    total->SetParNames("Background","Constant(1)","Mean(1)", "Sigma(1)","Constant(2)","Mean(2)", "Sigma(2)");
    h1->Fit(total,"R");
    c1->SaveAs("Spettro_Sodio_Coincidenze_+20_gradi_180_secondi.pdf",".pdf");
    c1->SaveAs("Spettro_Sodio_Coincidenze_+20_gradi_180_secondi.root",".root");
}


