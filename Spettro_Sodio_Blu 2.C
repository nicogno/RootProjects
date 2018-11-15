{
    
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    TCanvas *c2 = new TCanvas("c2","Spettro_Sodio_Blu_No_Fit", 1600, 1200);
    TH1D *h1 = new TH1D("Histogram and Polynomial Fit parameters","Spettro Sodio (scintillatore B);# CH;Counts",1024,0,1023);
    TH1D *h2 = new TH1D("Histogram parameters","Spettro Sodio (scintillatore B);# CH;Counts",1024,0,1023);
    TH1D *h3 = new TH1D("Gauss Fit parameters","",1024,0,1023);
    
    in.open("Spettro_Sodio_Blu.mca");
    
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
            h3->Fill(channel, numericData);
            h3->SetBinError(channel+1,TMath::Sqrt(numericData));
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
    
    h2->Draw();
    c2->SaveAs("Spettro_Sodio_Blu_No_Fit.pdf",".pdf");
    
    TCanvas *c1 = new TCanvas("c1","Spettro_Sodio_Blu", 1600, 1200);
    
    h1->SetMinimum(0);
    Double_t par[6];
    
    TF1 *fit0 = new TF1("fit0","pol2",220,310);
    fit0->SetParNames("a","b","c");
    TF1 *g1 = new TF1("g1","gaus",310,370);
    fit0->SetLineColor(6);
    fit0->SetLineWidth(10);
    fit0->SetLineStyle(8);
    g1->SetLineColor(2);
    g1->SetLineWidth(5);
    g1->SetLineStyle(10);
    
    h1->Fit(fit0, "R");
    
    c1->Modified(); c1->Update();
    
    TPaveStats *stats = (TPaveStats*)c1->GetPrimitive("stats");
    stats->SetName("h1stats");
    stats->SetY1NDC(.55);    stats->SetX1NDC(.6);
    stats->SetY2NDC(.85);    stats->SetX2NDC(.85);
    stats->SetTextColor(6);
    
    h3->Fit(g1,"R","sames");
    c1->Update();
    TPaveStats *stats2 = (TPaveStats*)c1->GetPrimitive("stats");
    stats2->SetOptStat(0010);
    stats2->SetName("h1stats2");
    stats2->SetY1NDC(.3);   stats2->SetX1NDC(.6);
    stats2->SetY2NDC(.5);   stats2->SetX2NDC(.85);
    stats2->SetTextColor(2);
    
    
    cout << -(fit0->GetParameter(1))/(2*fit0->GetParameter(2)) << endl;
    Double_t vertex = -(fit0->GetParameter(1))/(2*fit0->GetParameter(2));
    Double_t A = pow((fit0->GetParError(1)/(2*fit0->GetParameter(2))),2);
    Double_t B = pow(((fit0->GetParError(2)*fit0->GetParameter(1))/(2*pow(fit0->GetParameter(2),2))),2);
    cout << sqrt(A+B) << endl;
    c1->SaveAs("Spettro_Sodio_Blu_Con_Fit.pdf",".pdf");
    c1->SaveAs("Spettro_Sodio_Blu.root",".root");
}


