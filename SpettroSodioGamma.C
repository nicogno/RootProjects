{
    //gROOT->SetBatch(1);
    ifstream in;
    
    const Int_t CHANNELS = 2048;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    TCanvas *c1 = new TCanvas("c1","SpettroSodioGamma", 900, 600);
    TH1D *h1 = new TH1D("Histogram parameters","Spettro Sodio Gamma;# CH;Counts",2048,0,2047);
    TH1D *h2 = new TH1D("Histogram and fit parameters","Spettro Sodio Gamma;# CH;Counts",400,0,399);
    
    in.open("SpettroSodioGamma.mca");
    
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
            h2->Fill(channel, numericData);
            h2->SetBinError(channel+1,TMath::Sqrt(numericData));
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
    
    h1->Draw();
    c1->SaveAs("SpettroSodioGamma.pdf",".pdf");
    c1->SaveAs("SpettroSodioGamma.root",".root");
    
    TCanvas *c2 = new TCanvas("c2","SpettroSodioGamma", 1600, 1200);
    
    h2->SetMinimum(0);
    Double_t par[3];
    //TF1 *g0    = new TF1("g0","gaus",114,140);
    // TF1 *g1    = new TF1("g1","pol0",140,2048);
    TF1 *total = new TF1("total","gaus",70,108);    //Chi quadrato critico è 49.80
    total->SetParameters(1,1,1);
    total->SetLineColor(2);
    total->SetLineWidth(5);
    // h2->Fit(g0,"R","goff");
    // h2->Fit(g1,"R+","goff");
    // g0->GetParameters(&par[0]);
    // g1->GetParameters(&par[3]);
    total->SetParNames("Constant","Mean", "Sigma");
    h2->Fit(total,"R");
    c2->SaveAs("SpettroSodioGammaconFit.pdf",".pdf");
    c2->SaveAs("SpettroSodioGammaconFit.root",".root");
    
    /*TF1 *totalTest = new TF1("totalTest","gaus",80,140);
    
    for(int a = 0; a < 120; a++) {
        for(int b = 120; b > a; b--) {
        h2->Fit("totalTest", "MQ", "", a, b);
            if(totalTest->GetChisquare()/totalTest->GetNDF() < 1.4 && totalTest->GetParameter(1)+totalTest->GetParameter(2) > 80 && b-a>30){
        cout << "a = \t" << a << "\t b = \t" << b << "\t Chi Quadrato \t " << totalTest->GetChisquare() << "\t Mean + Sigma = \t" << totalTest->GetParameter(1)+totalTest->GetParameter(2) << "\t b-a \t" << b-a << endl;
            }
        }
    }*/
    
    
}

